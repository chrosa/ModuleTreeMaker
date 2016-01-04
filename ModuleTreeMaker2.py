#!/afs/cern.ch/sw/lcg/releases/LCG_72a/Python/2.7.6/x86_64-slc6-gcc48-opt/bin/python
# #!/usr/bin/python

from ROOT import TDatime, TTree, TFile
import numpy as np
from os import walk, path, listdir, system
import re
import xml.etree.cElementTree as et
#from array import array

# open the output file
f = TFile("tree2.root", "recreate")
t = TTree("t", "t")

# create 1 dimensional float arrays (python's float datatype corresponds to c++ doubles)
# as fill variables
run = np.zeros([1], dtype=np.uint32)
good =  np.zeros([1], dtype=np.bool)
numberOfDefects = np.zeros([3,9,12,56], dtype=np.uint32)
numberOfNewDefects = np.zeros([3,9,12,56], dtype=np.uint32)
numberOfRefDefects = np.zeros([3,9,12,56], dtype=np.uint32)
numberOfNPtGainDefects = np.zeros([3,9,12,56], dtype=np.uint32)
numberOfNoiseOccupancyDefects = np.zeros([3,9,12,56], dtype=np.uint32)
numberOfNoisyStripsMon = np.zeros([3,9,12,56], dtype=np.uint32)
numberOfNoisyStripsMonOnly = np.zeros([3,9,12,56], dtype=np.uint32)
channelID = np.zeros([3,9,12,56], dtype=np.uint32)
noise_occup = np.zeros([3,9,12,56], dtype=np.float32)
eff = np.zeros([3,9,3], dtype=np.float32)
n_err_link = np.zeros([3,9,3], dtype=np.uint32)
noisy_strips_measured =  np.zeros([1], dtype=np.bool)
noise_occup_measured =  np.zeros([1], dtype=np.bool)
eff_measured =  np.zeros([1], dtype=np.bool)
n_err_link_measured =  np.zeros([1], dtype=np.bool)

start_time = TDatime()
end_time = TDatime()
start = np.zeros([1], dtype=np.uint32)
end = np.zeros([1], dtype=np.uint32)
duration = np.zeros([1], dtype=np.uint32)

data = bytearray(21) # all bytes of char_array are zeroed by default here (all b'\x00')

# create the branches and assign the fill-variables to them
t.Branch('Run', run, 'Run[1]/i')
t.Branch('Start', start, 'Start[1]/i')
t.Branch('End', end, 'End[1]/i')
t.Branch('Duration', duration, 'Duration[1]/i')
t.Branch('Good', good, 'Good[1]/O')
t.Branch('NumberOfDefects', numberOfDefects, 'NumberOfDefects[3][9][12][56]/i')
t.Branch('NumberOfNewDefects', numberOfNewDefects, 'NumberOfNewDefects[3][9][12][56]/i')
t.Branch('NumberOfRefDefects', numberOfRefDefects, 'NumberOfRefDefects[3][9][12][56]/i')
t.Branch('NumberOfNPtGainDefects', numberOfNPtGainDefects, 'NumberOfNPtGainDefects[3][9][12][56]/i')
t.Branch('NumberOfNoiseOccupancyDefects', numberOfNoiseOccupancyDefects, 'NumberOfNoiseOccupancyDefects[3][9][12][56]/i')
t.Branch('NumberOfNoisyStripsMon', numberOfNoisyStripsMon, 'numberOfNoisyStripsMon[3][9][12][56]/i')
t.Branch('NumberOfNoisyStripsMonOnly', numberOfNoisyStripsMonOnly, 'numberOfNoisyStripsMonOnly[3][9][12][56]/i')
t.Branch("NoiseOccupancy", noise_occup, "NoiseOccupancy[3][9][12][56]/F");
t.Branch("Efficiency", eff, "Efficiency[3][9][3]/F");
t.Branch("ByteStreamErrors", n_err_link, "ByteStreamErrors[3][9][3]/i");
t.Branch("NoisyStripsMeasured", noisy_strips_measured, "NoisyStripsMeasured/O");
t.Branch("NoiseOccupancyMeasured", noise_occup_measured, "NoiseOccupancyMeasured/O");
t.Branch("EfficiencyMeasured", eff_measured, "EfficiencyMeasured/O");
t.Branch("ByteStreamErrorsMeasured", n_err_link_measured, "ByteStreamErrorsMeasured/O");
t.Branch('Data', data, 'Data[21]/C')

def find_between(s, first, last):
    start = s.index( first ) + len( first )
    end = s.index( last, start )
    return s[start:end]

# Values of the position variables get converted to array indices
def get_indices(variables):
    if len(variables) == 4:
        BarrelEndcap, Layer, Phi, Eta = [int(i) for i in variables]
        bec_index = (BarrelEndcap + 2)/2
        eta_index = Eta + (int(Eta < 0) + 5) * int(bec_index == 1)
        return (bec_index, Layer, Phi, eta_index)
    elif len(variables) == 3:
        BarrelEndcap, Layer, Eta = [int(i) for i in variables]
        bec_index = (BarrelEndcap + 2)/2
        return (bec_index, Layer, Eta)
    return 0

# find the first filename in a given directory structure where s is in the name
def find_first_file(directory, s):
    if not path.isdir(directory):
        return ""
    for root, dirs, filenames in walk(directory):
        for filename in filenames:
            if s in filename:
                return path.join(root, filename)
    return ""

# extract information from the calibration summary file
def read_file(filename):
    fobj_run = open(filename)
    line = fobj_run.readline()
    while line:
        if line.find("StartTime") > -1:
            to_TDatime(start_time, find_between(line, '">', '</'))
        if line.find("EndTime") > -1:
            to_TDatime(end_time, find_between(line, '">', '</'))
        if line.find("Duration") > -1:
            duration[0] = find_between(line, '">', '</')
        if line.find("<module>") > -1:
            line = fobj_run.readline()
            line = fobj_run.readline()
            if line.find("BecLayerPhiEta") > -1:
                fields = line.split(">")[1].split("<")[0].split('.')
                idx = get_indices(fields)
            line = fobj_run.readline()
            line = fobj_run.readline()
            line = fobj_run.readline()
            NOD = 0
            if line.find("OfflineAll") > -1:
                DefectList = line.split(">")[1].split("<")[0]
                fields_nod = DefectList.strip().split(" ")
                for s in fields_nod:
                    if s.find("-") > -1:
                        fields_nod2 = s.split("-")
                        NOD = NOD + int(fields_nod2[1]) - int(fields_nod2[0])
                    elif len(s) > 0:
                        NOD = NOD + 1
            numberOfDefects[idx[0]][idx[1]][idx[3]][idx[2]] = NOD
            line = fobj_run.readline()
            NOD = 0
            if line.find("OfflineNew") > -1:
                DefectList = line.split(">")[1].split("<")[0]
                fields_nod = DefectList.strip().split(" ")
                for s in fields_nod:
                    if s.find("-") > -1:
                        fields_nod2 = s.split("-")
                        NOD = NOD + int(fields_nod2[1]) - int(fields_nod2[0])
                    elif len(s) > 0:
                        NOD = NOD + 1
            numberOfNewDefects[idx[0]][idx[1]][idx[3]][idx[2]] = NOD
            line = fobj_run.readline()
            NOD = 0
            if line.find("OfflineRef") > -1:
                DefectList = line.split(">")[1].split("<")[0]
                fields_nod = DefectList.strip().split(" ")
                for s in fields_nod:
                    if s.find("-") > -1:
                        fields_nod2 = s.split("-")
                        NOD = NOD + int(fields_nod2[1]) - int(fields_nod2[0])
                    elif len(s) > 0:
                        NOD = NOD + 1
            numberOfRefDefects[idx[0]][idx[1]][idx[3]][idx[2]] = NOD
        line = fobj_run.readline()

# extract information from the express summary file
def read_express_file(filename, target_array):
    target_array.fill(0)
    xml_root = et.parse(filename).getroot()
    for c in xml_root:
        if c.tag == "data":
            for gc in c:
                vals = [ggc.text for ggc in gc]
                if vals[0] == "EndCapC":
                    vals[0] = -2
                elif vals[0] == "EndCapA":
                    vals[0] = 2
                else:
                    vals[0] = 0
                    vals[2] = 0
                idx = get_indices(vals[:-1])
                target_array[idx[0]][idx[1]][idx[2]] = float(vals[-1])

def get_LOD(filename):
    fields = []
    fobj_cool = open(filename)
    line = fobj_cool.readline()
    while line:
        if line.find("defectBeginChannel") > -1:
            DefectList = line.split(">")[1].split("<")[0]
            fields = DefectList.strip().split(" ")
            return fields
        line = fobj_cool.readline()
    return fields

def get_NOD(fields):
    NOD = 0
    for s in fields:
        if s.find("-") > -1:
            fields2 = s.split("-")
            NOD = NOD + int(fields2[1]) - int(fields2[0])
        elif len(s) > 0:
            NOD = NOD + 1
    return NOD

def get_NOD_expanded(fields):
    return len(fields)

def expand_LOD(fields_orig):
    fields_expand = []
    for s in fields_orig:
        if s.find("-") > -1:
            fields_tmp = s.split("-")
            for i in range(int(fields_tmp[0]),int(fields_tmp[1])):
                fields_expand.append(i)
        elif len(s) > 0:
            fields_expand.append(int(s))
    return fields_expand

def get_LOD_cleaned(fields_orig, fields_veto):
    fields_cleaned = []
    for i in fields_orig:
        if i not in fields_veto:
            fields_cleaned.append(i)
    #print fields_cleaned
    return fields_cleaned

# Set tdatime with time from given time string
def to_TDatime(tdatime,string):
    x = np.array(re.findall('\d+', string)[:-1], dtype=np.uint32)
    tdatime.Set(int(x[2]), int(x[1]), int(x[0]), int(x[3]), int(x[4]), int(x[5]))

runs_good = []
fobj_good = open("ListOfGoodRuns.txt")
line = fobj_good.readline()
while line:
    runs_good.append(int(line))
    line = fobj_good.readline()

print "Good runs: ", runs_good

dirs = []
fobj_dirs = open("dirs.txt")
line = fobj_dirs.readline()
while line:
    dirs.append(line.splitlines()[0])
    line = fobj_dirs.readline()

print "dirs: ", dirs

subdir = "calibration_SCTNoise"
subdir_express = "express_express"

print "subdir: ", subdir
print "subdir_express: ", subdir_express

# Loop over data runs
for i in dirs:

    data[:21] = i.ljust(11,'\x00')
    print "processing directory ", i

    if i.find("data10") > -1: resultdir = "/home/sctcalib/Results_2010/"
    else: resultdir = "/home/sctcalib/Results/"

    # Loop over runs
    for x in listdir(resultdir+i+"/"+subdir):

        print "processing run ", x

        if x.isdigit():
        #if x.isdigit() and int(x) < 153565:

            IOVsince = int(x) << 32
            IOVuntil = ((int(x)+1) << 32) - 1
            system("rm -f temp.cool temp2.cool temp3.cool")
            if int(x) < 220000:
                system("xmllint --format 'http://coolcherrypy.cern.ch:8080/cooldb/ATLAS_COOLPROD/ATLAS_COOLOFL_SCT/COMP200/SCT/Derived/Monitoring/timespan/"+str(IOVsince)+"-"+str(IOVuntil)+"/tag/SctDerivedMonitoring-UPD4-003/channels/*' > temp.cool")
                system("xmllint --format 'http://coolcherrypy.cern.ch:8080/cooldb/ATLAS_COOLPROD/ATLAS_COOLONL_SCT/COMP200/SCT/DAQ/Calibration/NoiseOccupancyDefects/timespan/"+str(IOVsince)+"-"+str(IOVuntil)+"/channels/*' > temp2.cool")
                system("xmllint --format 'http://coolcherrypy.cern.ch:8080/cooldb/ATLAS_COOLPROD/ATLAS_COOLONL_SCT/COMP200/SCT/DAQ/Calibration/NPtGainDefects/timespan/"+str(IOVsince)+"-"+str(IOVuntil)+"/channels/*' > temp3.cool")
            else:
                system("xmllint --format 'http://coolcherrypy.cern.ch:8080/cooldb/ATLAS_COOLPROD/ATLAS_COOLOFL_SCT/CONDBR2/SCT/Derived/Monitoring/timespan/"+str(IOVsince)+"-"+str(IOVuntil)+"/tag/SctDerivedMonitoring-RUN2-UPD4-004/channels/*' > temp.cool")
                system("xmllint --format 'http://coolcherrypy.cern.ch:8080/cooldb/ATLAS_COOLPROD/ATLAS_COOLONL_SCT/CONDBR2/SCT/DAQ/Calibration/NoiseOccupancyDefects/timespan/"+str(IOVsince)+"-"+str(IOVuntil)+"/channels/*' > temp2.cool")
                system("xmllint --format 'http://coolcherrypy.cern.ch:8080/cooldb/ATLAS_COOLPROD/ATLAS_COOLONL_SCT/CONDBR2/SCT/DAQ/Calibration/NPtGainDefects/timespan/"+str(IOVsince)+"-"+str(IOVuntil)+"/channels/*' > temp3.cool")

            fobj = open("temp.cool")
            line = fobj.readline()
            index = np.zeros([4], dtype=np.int32)

            # loop over events
            while line:

                if line.find("channel id") > -1:

                    cid = line.split('"')[1]
                    #print cid
                    active = True
                    while active:
            
                        if line.find("BarrelEndcap") > -1:
                            index[0] = line.split(">")[1].split("<")[0]
                        if line.find("Layer") > -1:
                            index[1] = line.split(">")[1].split("<")[0]
                        if line.find("Eta") > -1:
                            index[3] = line.split(">")[1].split("<")[0]
                        if line.find("Phi") > -1:
                            index[2] = line.split(">")[1].split("<")[0]
                        if line.find("DefectList") > -1:
                            DefectList = line.split(">")[1].split("<")[0]
                            fields_nod = DefectList.strip().split(" ")
                            NOD = get_NOD(fields_nod)
                            #print index
                            idx = get_indices(index)
                            #print idx
                            numberOfNoisyStripsMon[idx[0]][idx[1]][idx[3]][idx[2]] = NOD
                            channelID[idx[0]][idx[1]][idx[3]][idx[2]] = cid
                            # get masked channels from COOL database
                            #if int(x) < 220000:
                            #    system("xmllint --format 'http://coolcherrypy.cern.ch:8080/cooldb/ATLAS_COOLPROD/ATLAS_COOLONL_SCT/COMP200/SCT/DAQ/Calibration/NoiseOccupancyDefects/timespan/"+str(IOVsince)+"-"+str(IOVuntil)+"/channels/"+cid+" > temp2.cool")
                            #    system("xmllint --format 'http://coolcherrypy.cern.ch:8080/cooldb/ATLAS_COOLPROD/ATLAS_COOLONL_SCT/COMP200/SCT/DAQ/Calibration/NPtGainDefects/timespan/"+str(IOVsince)+"-"+str(IOVuntil)+"/channels/"+cid+" > temp3.cool")
                            #else:
                            #    system("xmllint --format 'http://coolcherrypy.cern.ch:8080/cooldb/ATLAS_COOLPROD/ATLAS_COOLONL_SCT/CONDBR2/SCT/DAQ/Calibration/NoiseOccupancyDefects/timespan/"+str(IOVsince)+"-"+str(IOVuntil)+"/channels/"+cid+" > temp2.cool")
                            #    system("xmllint --format 'http://coolcherrypy.cern.ch:8080/cooldb/ATLAS_COOLPROD/ATLAS_COOLONL_SCT/CONDBR2/SCT/DAQ/Calibration/NPtGainDefects/timespan/"+str(IOVsince)+"-"+str(IOVuntil)+"/channels/"+cid+" > temp3.cool")
                            
                            system("fgrep -ir --after-context=8 "+cid+" temp2.cool > temp2_cut.cool") 
                            system("fgrep -ir --after-context=8 "+cid+" temp3.cool > temp3_cut.cool") 
                            
                            numberOfNoiseOccupancyDefects[idx[0]][idx[1]][idx[3]][idx[2]] = get_NOD(get_LOD("temp3_cut.cool"))
                            numberOfNPtGainDefects[idx[0]][idx[1]][idx[3]][idx[2]] = get_NOD(get_LOD("temp2_cut.cool"))
                            numberOfNoisyStripsMonOnly[idx[0]][idx[1]][idx[3]][idx[2]] = get_NOD_expanded(get_LOD_cleaned(get_LOD_cleaned(expand_LOD(fields_nod),expand_LOD(get_LOD("temp3_cut.cool"))),expand_LOD(get_LOD("temp2_cut.cool"))))
                            
                            active = False

                        line = fobj.readline()

                line = fobj.readline()

            # Open BadStripsSummaryFile
            for y in listdir(resultdir+i+"/"+subdir+"/"+x):
                print y
                if y.find("_c0") == len(y)-3 or y.find(".c0") == len(y)-3 or y.find(".c1") == len(y)-3:
                    calibdir = resultdir+i+"/"+subdir+"/"+x+"/"+y
                    #print "calibdir: ",  calibdir
                    summary_filename = find_first_file(calibdir, "BadStripsSummaryFile")
                    if path.isfile(summary_filename):
                        read_file(summary_filename)
                        noisy_strips_measured[0] = True
                    else:
                        numberOfDefects.fill(0)
                        numberOfNewDefects.fill(0)
                        numberOfRefDefects.fill(0)
                        noisy_strips_measured[0] = False
                                
                    run[0] = int(x)
                    start[0] = start_time.Convert()
                    end[0] = end_time.Convert()
                    if int(x) in runs_good:
                        good[0] = 1
                    else:
                        good[0] = 0
               
            if path.isdir(resultdir+i+"/"+subdir_express+"/"+x):
                for y in listdir(resultdir+i+"/"+subdir_express+"/"+x):

                    # Open BSErrorSummaryFile
                    if y.find("BSErrorDB") >-1 and y.find("_c0") == len(y)-3:
                        calibdir_express = resultdir+i+"/"+subdir_express+"/"+x+"/"+y
                        #print "calibdir_express: ",  calibdir_express
                        summary_express_filename = find_first_file(calibdir_express, "BSErrorSummaryFile")
                        if path.isfile(summary_express_filename):
                            read_express_file(summary_express_filename, n_err_link)
                            #n_err_link_measured[0] = sum(sum(sum(n_err_link))) != 0
                            n_err_link_measured[0] = True
                        else:
                            n_err_link.fill(0)
                            n_err_link_measured[0] = False

                    # Open NoiseOccupancySummaryFile
                    if y.find("NoiseOccupancy") >-1 and y.find("_c0") == len(y)-3:
                        calibdir_express = resultdir+i+"/"+subdir_express+"/"+x+"/"+y
                        #print "calibdir_express: ",  calibdir_express
                        summary_express_filename = find_first_file(calibdir_express, "NoiseOccupancySummaryFile")
                        if path.isfile(summary_express_filename):
                            read_express_file(summary_express_filename, noise_occup)
                            #noise_occup_measured[0] = sum(sum(sum(noise_occup))) != 0
                            noise_occup_measured[0] = True
                        else:
                            noise_occup.fill(0)
                            noise_occup_measured[0] = False

                    # Open EfficiencySummaryFile
                    if y.find("Efficiency") >-1 and y.find("_c0") == len(y)-3:
                        calibdir_express = resultdir+i+"/"+subdir_express+"/"+x+"/"+y
                        #print "calibdir_express: ",  calibdir_express
                        summary_express_filename = find_first_file(calibdir_express, "EfficiencySummaryFile")
                        if path.isfile(summary_express_filename):
                            read_express_file(summary_express_filename, eff)
                            #eff_measured[0] = sum(sum(sum(eff))) != 0
                            eff_measured[0] = True
                        else:
                            eff.fill(0)
                            eff_measured[0] = False

            else:
                n_err_link.fill(0)
                n_err_link_measured[0] = False
                noise_occup.fill(0)
                noise_occup_measured[0] = False
                eff.fill(0)
                eff_measured[0] = False
               
            t.Fill()

f.cd()
t.Write()
