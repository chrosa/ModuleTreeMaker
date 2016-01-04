//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Nov 13 13:09:30 2015 by ROOT version 5.34/34
// from TTree modules/modules
// found on file: tree2.root
//////////////////////////////////////////////////////////

#ifndef ModuleSelector2_h
#define ModuleSelector2_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TSelector.h>
#include <TGraph.h>
#include <TProfile.h>
#include <vector>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class ModuleSelector2 : public TSelector {
    public :
        TTree          *fChain;   //!pointer to the analyzed TTree or TChain

        // Declaration of leaf types
        UInt_t          Run;
        UInt_t          Start;
        UInt_t          End;
        UInt_t          Duration;
        Bool_t          Good;
        UInt_t          NumberOfDefects[3][9][12][56];
        UInt_t          NumberOfNewDefects[3][9][12][56];
        UInt_t          NumberOfRefDefects[3][9][12][56];
        UInt_t          NumberOfNPtGainDefects[3][9][12][56];
        UInt_t          NumberOfNoiseOccupancyDefects[3][9][12][56];
        UInt_t          NumberOfNoisyStripsMon[3][9][12][56];
        UInt_t          NumberOfNoisyStripsMonOnly[3][9][12][56];
        Float_t         NoiseOccupancy[3][9][12][56];
        Float_t         Efficiency[3][9][3];
        UInt_t          ByteStreamErrors[3][9][3];
        Bool_t          NoisyStripsMeasured;
        Bool_t          NoiseOccupancyMeasured;
        Bool_t          EfficiencyMeasured;
        Bool_t          ByteStreamErrorsMeasured;
        Char_t          Data[21];

        // List of branches
        TBranch        *b_Run;   //!
        TBranch        *b_Start;   //!
        TBranch        *b_End;   //!
        TBranch        *b_Duration;   //!
        TBranch        *b_Good;   //!
        TBranch        *b_NumberOfDefects;   //!
        TBranch        *b_NumberOfNewDefects;   //!
        TBranch        *b_NumberOfRefDefects;   //!
        TBranch        *b_NumberOfNPtGainDefects;   //!
        TBranch        *b_NumberOfNoiseOccupancyDefects;   //!
        TBranch        *b_numberOfNoisyStripsMon;   //!
        TBranch        *b_numberOfNoisyStripsMonOnly;   //!
        TBranch        *b_NoiseOccupancy;   //!
        TBranch        *b_Efficiency;   //!
        TBranch        *b_ByteStreamErrors;   //!
        TBranch        *b_NoisyStripsMeasured;   //!
        TBranch        *b_NoiseOccupancyMeasured;   //!
        TBranch        *b_EfficiencyMeasured;   //!
        TBranch        *b_ByteStreamErrorsMeasured;   //!
        TBranch        *b_Data;   //!

        ModuleSelector2(TTree * /*tree*/ =0) : fChain(0) { }
        virtual ~ModuleSelector2() { }
        virtual Int_t   Version() const {
            return 2;
        }
        virtual void    Begin(TTree *tree);
        virtual void    SlaveBegin(TTree *tree);
        virtual void    Init(TTree *tree);
        virtual Bool_t  Notify();
        virtual Bool_t  Process(Long64_t entry);
        virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) {
            return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0;
        }
        virtual void    SetOption(const char *option) {
            fOption = option;
        }
        virtual void    SetObject(TObject *obj) {
            fObject = obj;
        }
        virtual void    SetInputList(TList *input) {
            fInput = input;
        }
        virtual TList  *GetOutputList() const {
            return fOutput;
        }
        virtual void    SlaveTerminate();
        virtual void    Terminate();

        TH1F *h_NumberOfDefects_tot;
        TH1F *h_NumberOfDefects_b, *h_Eta_b, *h_Phi_b, *h_BarrelEndcap_b, *h_Layer_b;
        TH1F *h_NumberOfDefects_e, *h_Eta_e, *h_Phi_e, *h_BarrelEndcap_e, *h_Layer_e;
        std::vector<double> v_NumberOfDefects_b;
        std::vector<double> v_NumberOfDefects_e;
        std::vector<double> v_NumberOfDefects_tot;
        std::vector<double> v_NumberOfDefectsMon_tot;
        std::vector<double> v_NumberOfDefectsMonOnly_tot;
        std::vector<double> v_time;

        TH2F *h_NumberOfDefects_vs_Duration;

        ClassDef(ModuleSelector2,0);
};

#endif

#ifdef ModuleSelector2_cxx
void ModuleSelector2::Init(TTree *tree)
{
    // The Init() function is called when the selector needs to initialize
    // a new tree or chain. Typically here the branch addresses and branch
    // pointers of the tree will be set.
    // It is normally not necessary to make changes to the generated
    // code, but the routine can be extended by the user if needed.
    // Init() will be called many times when running on PROOF
    // (once per file to be processed).

    // Set branch addresses and branch pointers
    if (!tree) return;
    fChain = tree;
    fChain->SetMakeClass(1);

    fChain->SetBranchAddress("Run", &Run, &b_Run);
    fChain->SetBranchAddress("Start", &Start, &b_Start);
    fChain->SetBranchAddress("End", &End, &b_End);
    fChain->SetBranchAddress("Duration", &Duration, &b_Duration);
    fChain->SetBranchAddress("Good", &Good, &b_Good);
    fChain->SetBranchAddress("NumberOfDefects", NumberOfDefects, &b_NumberOfDefects);
    fChain->SetBranchAddress("NumberOfNewDefects", NumberOfNewDefects, &b_NumberOfNewDefects);
    fChain->SetBranchAddress("NumberOfRefDefects", NumberOfRefDefects, &b_NumberOfRefDefects);
    fChain->SetBranchAddress("NumberOfNPtGainDefects", NumberOfNPtGainDefects, &b_NumberOfNPtGainDefects);
    fChain->SetBranchAddress("NumberOfNoiseOccupancyDefects", NumberOfNoiseOccupancyDefects, &b_NumberOfNoiseOccupancyDefects);
    fChain->SetBranchAddress("NumberOfNoisyStripsMon", NumberOfNoisyStripsMon, &b_numberOfNoisyStripsMon);
    fChain->SetBranchAddress("NumberOfNoisyStripsMonOnly", NumberOfNoisyStripsMonOnly, &b_numberOfNoisyStripsMonOnly);
    fChain->SetBranchAddress("NoiseOccupancy", NoiseOccupancy, &b_NoiseOccupancy);
    fChain->SetBranchAddress("Efficiency", Efficiency, &b_Efficiency);
    fChain->SetBranchAddress("ByteStreamErrors", ByteStreamErrors, &b_ByteStreamErrors);
    fChain->SetBranchAddress("NoisyStripsMeasured", &NoisyStripsMeasured, &b_NoisyStripsMeasured);
    fChain->SetBranchAddress("NoiseOccupancyMeasured", &NoiseOccupancyMeasured, &b_NoiseOccupancyMeasured);
    fChain->SetBranchAddress("EfficiencyMeasured", &EfficiencyMeasured, &b_EfficiencyMeasured);
    fChain->SetBranchAddress("ByteStreamErrorsMeasured", &ByteStreamErrorsMeasured, &b_ByteStreamErrorsMeasured);
    fChain->SetBranchAddress("Data", Data, &b_Data);
}

Bool_t ModuleSelector2::Notify()
{
    // The Notify() function is called when a new file is opened. This
    // can be either for a new TTree in a TChain or when when a new TTree
    // is started when using PROOF. It is normally not necessary to make changes
    // to the generated code, but the routine can be extended by the
    // user if needed. The return value is currently not used.

    return kTRUE;
}

#endif // #ifdef ModuleSelector2_cxx
