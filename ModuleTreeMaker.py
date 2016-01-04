#!/afs/cern.ch/sw/lcg/releases/LCG_72a/Python/2.7.6/x86_64-slc6-gcc48-opt/bin/python
# #!/usr/bin/python

import ROOT, array
import numpy as np

# open the output file
f = ROOT.TFile("tree.root", "recreate")
t = ROOT.TTree("modules", "modules")

# create 1 dimensional float arrays (python's float datatype corresponds to c++ doubles)
# as fill variables
detid = np.zeros(1, dtype=int)
insertion_time = np.zeros(5, dtype=int)
since = np.zeros(1, dtype=int)
until = np.zeros(1, dtype=int)
SampleSize = np.zeros(1, dtype=int)
BarrelEndcap = np.zeros(1, dtype=int)
Layer = np.zeros(1, dtype=int)
Eta = np.zeros(1, dtype=int)
Phi = np.zeros(1, dtype=int)
# DefectType = np.zeros(1, dtype=str)
Threshold = np.zeros(1, dtype=float)
# DefectList = np.zeros(1, dtype=str)
NumberOfDefects = np.zeros(1, dtype=int)
 
# create the branches and assign the fill-variables to them
t.Branch('detid', detid, 'detid/I')
t.Branch('insertion_time', insertion_time, 'insertion_time[5]/I')
t.Branch('since', since, 'since/I')
t.Branch('until', until, 'until/I')
t.Branch('SampleSize', SampleSize, 'SampleSize/I')
t.Branch('BarrelEndcap', BarrelEndcap, 'BarrelEndcap/I')
t.Branch('Layer', Layer, 'Layer/I')
t.Branch('Eta', Eta, 'Eta/I')
t.Branch('Phi', Phi, 'Phi/I')
# t.Branch('DefectType', DefectType, 'DefectType/S')
t.Branch('Threshold', Threshold, 'Threshold/D')
# t.Branch('DefectList', DefectList, 'DefectList/S')
t.Branch('NumberOfDefects', NumberOfDefects, 'NumberOfDefects/I')

fobj = open("COOL.out")
line = fobj.readline()

# loop over events
while line:

    if line.find("channel id") > -1:
       print line
       fields = line.split('"')
       detid = fields[1]
       fields2 = fields[3].split(" ")
       insertion_time[0] = fields2[3]
       if fields2[2] == "Jan":
           insertion_time[1] = 1
       elif fields2[2] == "Feb":
           insertion_time[1] = 2
       elif fields2[2] == "Mar":
           insertion_time[1] = 3
       elif fields2[2] == "Apr":
           insertion_time[1] = 4
       elif fields2[2] == "May":
           insertion_time[1] = 5
       elif fields2[2] == "Jun":
           insertion_time[1] = 6
       elif fields2[2] == "Jul":
           insertion_time[1] = 7
       elif fields2[2] == "Aug":
           insertion_time[1] = 8
       elif fields2[2] == "Sep":
           insertion_time[1] = 9
       elif fields2[2] == "Oct":
           insertion_time[1] = 10
       elif fields2[2] == "Nov":
           insertion_time[1] = 11
       elif fields2[2] == "Dec":
           insertion_time[1] = 12
       else:
           insertion_time[1] = 0

       insertion_time[2] = fields2[1]
       fields3 = fields2[4].split(":")
       insertion_time[3] = fields3[0]
       insertion_time[4] = fields3[1]

       #Between the start of the IOV (IOVuntil) and the runNumber:
       #IOVsince = runNumber << 32
       #runNumber = IOVsince >> 32
       #Between the end of the IOV (IOVuntil) and the runNumber:
       #IOVuntil = ((runNumber+1) << 32) - 1
       #runNumber = ((IOVUntil+1) >> 32) + 1 ???
       since[0] = int( long(fields[5]) >> 32 )
       until[0] = int( ( ( long(fields[7]) + 1 ) >> 32) )
       if until[0] > 999999:
           until[0] = 999999

    line = fobj.readline()
    if line.find("SampleSize") > -1:
        SampleSize[0] = line.split(">")[1].split("<")[0]
    line = fobj.readline()
    if line.find("BarrelEndcap") > -1:
        BarrelEndcap[0] = line.split(">")[1].split("<")[0]
    line = fobj.readline()
    if line.find("Layer") > -1:
        Layer[0] = line.split(">")[1].split("<")[0]
    line = fobj.readline()
    if line.find("Eta") > -1:
        Eta[0] = line.split(">")[1].split("<")[0]
    line = fobj.readline()
    if line.find("Phi") > -1:
        Phi[0] = line.split(">")[1].split("<")[0]
    line = fobj.readline()
    if line.find("Threshold") > -1:
        Threshold[0] = line.split(">")[1].split("<")[0]
    line = fobj.readline()
   #DefectType[0] = "NOISY"
    line = fobj.readline()
    if line.find("DefectList") > -1:
        DefectList = line.split(">")[1].split("<")[0]
        NOD = 0
        fields_nod = DefectList.strip().split(" ")
        for s in fields_nod:
            if s.find("-") > -1:
                fields_nod2 = s.split("-")
                NOD = NOD + int(fields_nod2[1]) - int(fields_nod2[0])
            elif len(s) > 0:
                NOD = NOD + 1
        NumberOfDefects[0] = NOD

    t.Fill()

    line = fobj.readline()

# end of loop over events

# write the tuple to the output file and close it
f.cd()
t.Write()
