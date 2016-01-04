//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Nov  4 20:49:28 2015 by ROOT version 5.34/34
// from TTree modules/modules
// found on file: tree.root
//////////////////////////////////////////////////////////

#ifndef ModuleSelector_h
#define ModuleSelector_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <iostream>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class ModuleSelector : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   Int_t           detid;
   Int_t           insertion_time[5];
   Int_t           since;
   Int_t           until;
   Int_t           SampleSize;
   Int_t           BarrelEndcap;
   Int_t           Layer;
   Int_t           Eta;
   Int_t           Phi;
   Double_t        Threshold;
   Int_t           NumberOfDefects;

   // List of branches
   TBranch        *b_detid;   //!
   TBranch        *b_insertion_time;   //!
   TBranch        *b_since;   //!
   TBranch        *b_until;   //!
   TBranch        *b_SampleSize;   //!
   TBranch        *b_BarrelEndcap;   //!
   TBranch        *b_Layer;   //!
   TBranch        *b_Eta;   //!
   TBranch        *b_Phi;   //!
   TBranch        *b_Threshold;   //!
   TBranch        *b_NumberOfDefects;   //!

   ModuleSelector(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~ModuleSelector() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   TH1F *h_NumberOfDefects_b, *h_Eta_b, *h_Phi_b, *h_BarrelEndcap_b, *h_Layer_b;
   TH1F *h_Runs_NoisyStrips_b, *h_Eta_NoisyStrips_b, *h_Phi_NoisyStrips_b, *h_BarrelEndcap_NoisyStrips_b, *h_Layer_NoisyStrips_b;

   TH1F *h_NumberOfDefects_e, *h_Eta_e, *h_Phi_e, *h_BarrelEndcap_e, *h_Layer_e;
   TH1F *h_Runs_NoisyStrips_e, *h_Eta_NoisyStrips_e, *h_Phi_NoisyStrips_e, *h_BarrelEndcap_NoisyStrips_e, *h_Layer_NoisyStrips_e;

   ClassDef(ModuleSelector,0);
};

#endif

#ifdef ModuleSelector_cxx
void ModuleSelector::Init(TTree *tree)
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

   fChain->SetBranchAddress("detid", &detid, &b_detid);
   fChain->SetBranchAddress("insertion_time", insertion_time, &b_insertion_time);
   fChain->SetBranchAddress("since", &since, &b_since);
   fChain->SetBranchAddress("until", &until, &b_until);
   fChain->SetBranchAddress("SampleSize", &SampleSize, &b_SampleSize);
   fChain->SetBranchAddress("BarrelEndcap", &BarrelEndcap, &b_BarrelEndcap);
   fChain->SetBranchAddress("Layer", &Layer, &b_Layer);
   fChain->SetBranchAddress("Eta", &Eta, &b_Eta);
   fChain->SetBranchAddress("Phi", &Phi, &b_Phi);
   fChain->SetBranchAddress("Threshold", &Threshold, &b_Threshold);
   fChain->SetBranchAddress("NumberOfDefects", &NumberOfDefects, &b_NumberOfDefects);
}

Bool_t ModuleSelector::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef ModuleSelector_cxx
