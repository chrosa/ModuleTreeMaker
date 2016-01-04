#define ModuleSelector_cxx
// The class definition in ModuleSelector.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("ModuleSelector.C")
// Root > T->Process("ModuleSelector.C","some options")
// Root > T->Process("ModuleSelector.C+")
//

#include "ModuleSelector.h"
#include <TH2.h>
#include <TStyle.h>


void ModuleSelector::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   h_NumberOfDefects_b = new TH1F("NumberOfDefects_b","NumberOfDefects_b",201,0.5,200.5);
   h_Eta_b = new TH1F("Eta_b","Eta_b",13,-6.5,6.5);
   h_Phi_b = new TH1F("Phi_b","Phi_b",71,-0.5,70.5);
   h_BarrelEndcap_b = new TH1F("BarrelEndcap_b","BarrelEndcap_b",5,-2.5,2.5);
   h_Layer_b = new TH1F("Layer_b","Layer_b",11,-0.5,10.5);
   h_Runs_NoisyStrips_b = new TH1F("Runs_NoisyStrips_b","Runs_NoisyStrips_b",300,255000,285000);
   h_Eta_NoisyStrips_b = new TH1F("Eta_NoisyStrips_b","Eta_NoisyStrips_b",13,-6.5,6.5);
   h_Phi_NoisyStrips_b = new TH1F("Phi_NoisyStrips_b","Phi_NoisyStrips_b",71,-0.5,70.5);
   h_BarrelEndcap_NoisyStrips_b = new TH1F("BarrelEndcap_NoisyStrips_b","BarrelEndcap_NoisyStrips_b",5,-2.5,2.5);
   h_Layer_NoisyStrips_b = new TH1F("Layer_NoisyStrips_b","Layer_NoisyStrips_b",11,-0.5,10.5);

   h_NumberOfDefects_e = new TH1F("NumberOfDefects_e","NumberOfDefects_e",201,0.5,200.5);
   h_Eta_e = new TH1F("Eta_e","Eta_e",13,-6.5,6.5);
   h_Phi_e = new TH1F("Phi_e","Phi_e",71,-0.5,70.5);
   h_BarrelEndcap_e = new TH1F("BarrelEndcap_e","BarrelEndcap_e",5,-2.5,2.5);
   h_Layer_e = new TH1F("Layer_e","Layer_e",11,-0.5,10.5);
   h_Runs_NoisyStrips_e = new TH1F("Runs_NoisyStrips_e","Runs_NoisyStrips_e",300,255000,285000);
   h_Eta_NoisyStrips_e = new TH1F("Eta_NoisyStrips_e","Eta_NoisyStrips_e",13,-6.5,6.5);
   h_Phi_NoisyStrips_e = new TH1F("Phi_NoisyStrips_e","Phi_NoisyStrips_e",71,-0.5,70.5);
   h_BarrelEndcap_NoisyStrips_e = new TH1F("BarrelEndcap_NoisyStrips_e","BarrelEndcap_NoisyStrips_e",5,-2.5,2.5);
   h_Layer_NoisyStrips_e = new TH1F("Layer_NoisyStrips_e","Layer_NoisyStrips_e",11,-0.5,10.5);

}

void ModuleSelector::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t ModuleSelector::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either ModuleSelector::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

   GetEntry(entry);

   //std::cout << until << endl;

   if (BarrelEndcap == 0) {
     h_NumberOfDefects_b->Fill(NumberOfDefects);
     h_Eta_b->Fill(Eta);
     h_Phi_b->Fill(Phi);
     h_BarrelEndcap_b->Fill(BarrelEndcap);
     h_Layer_b->Fill(Layer);
     if (NumberOfDefects>10){
       for (int i = since; i < until; i += 100){
	 h_Runs_NoisyStrips_b->Fill(i);
       }
       h_Eta_NoisyStrips_b->Fill(Eta);
       h_Phi_NoisyStrips_b->Fill(Phi);
       h_Layer_NoisyStrips_b->Fill(Layer);
       h_BarrelEndcap_NoisyStrips_b->Fill(BarrelEndcap);
     }
   } else {
     h_NumberOfDefects_e->Fill(NumberOfDefects);
     h_Eta_e->Fill(Eta);
     h_Phi_e->Fill(Phi);
     h_BarrelEndcap_e->Fill(BarrelEndcap);
     h_Layer_e->Fill(Layer);
     if (NumberOfDefects>10){
       for (int i = since; i < until; i += 100){
	 h_Runs_NoisyStrips_e->Fill(i);
       }
       h_Eta_NoisyStrips_e->Fill(Eta);
       h_Phi_NoisyStrips_e->Fill(Phi);
       h_Layer_NoisyStrips_e->Fill(Layer);
       h_BarrelEndcap_NoisyStrips_e->Fill(BarrelEndcap);
     }

   }

   return kTRUE;
}

void ModuleSelector::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void ModuleSelector::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
  
   gROOT->SetStyle("Plain");
   gStyle->SetPalette(51, 0);
   
   // For the canvas:
   gStyle->SetCanvasColor(0);
   gStyle->SetCanvasBorderMode(0);
   
   // For the Pad:
   gStyle->SetPadColor(0);
   gStyle->SetPadTickX(1);
   gStyle->SetPadTickY(1);
   gStyle->SetPadBorderSize(2);
   gStyle->SetPadBorderMode(0);
   
   // For the frame:
   gStyle->SetFrameBorderMode(0);
   
   // For the histo:
   gStyle->SetMarkerSize(0.7);
   gStyle->SetMarkerStyle(20);
   gStyle->SetMarkerColor(1);
   
   // For the statistics box:
   gStyle->SetOptStat(0);
   gStyle->SetOptFit(1011);
   
   // Margins:
   gStyle->SetPadBottomMargin(0.15);
   gStyle->SetPadTopMargin(0.05);
   gStyle->SetPadLeftMargin(0.15);
   gStyle->SetPadRightMargin(0.10);
   
   // For the Global title:
   gStyle->SetOptTitle(0);
   gStyle->SetTitleColor(1);
   gStyle->SetTitleFillColor(10);
   gStyle->SetTitleTextColor(1);
   gStyle->SetTitleFont(42);
   gStyle->SetTitleFontSize(0.05);
   gStyle->SetTitleBorderSize(0);
   
   // For the axis
   gStyle->SetNdivisions(510, "X");
   gStyle->SetNdivisions(510, "Y");
   gStyle->SetTickLength(0.03);
   
   // For the axis titles:
   gStyle->SetTitleOffset(1.0, "X");
   gStyle->SetTitleOffset(1.4, "Y");
   gStyle->SetTitleOffset(1.0, "Z");
   gStyle->SetTitleSize(0.05, "XYZ");
   gStyle->SetTitleFont(42, "XYZ");
   
   // For the axis labels:
   gStyle->SetLabelSize(0.04, "XYZ");
   gStyle->SetLabelOffset(0.01, "XYZ");
   gStyle->SetLabelFont(42, "XYZ");
   
   // For the legend
   gStyle->SetLegendBorderSize(0);
   
   gROOT->ForceStyle();

   TCanvas *c1 = new TCanvas("c1", "c1", 800, 800);
   c1->cd()->SetLogy(true);
   h_NumberOfDefects_b->GetYaxis()->SetTitle("number of modules");
   h_NumberOfDefects_b->GetXaxis()->SetTitle("number of defects");
   h_NumberOfDefects_b->Draw();
   c1->SaveAs("NumberOfDefects_b.pdf");
   
   TCanvas *c2 = new TCanvas("c2", "c2", 800, 800);
   c2->cd()->SetLogy(false);
   h_Eta_b->GetYaxis()->SetTitle("number of modules");
   h_Eta_b->GetXaxis()->SetTitle("eta");
   h_Eta_b->Draw();
   c2->SaveAs("Eta_b.pdf");

   TCanvas *c3 = new TCanvas("c3", "c3", 800, 800);
   c3->cd()->SetLogy(false);
   h_Phi_b->GetYaxis()->SetTitle("number of modules");
   h_Phi_b->GetXaxis()->SetTitle("phi");
   h_Phi_b->Draw();
   c3->SaveAs("Phi_b.pdf");

   TCanvas *c4 = new TCanvas("c4", "c4", 800, 800);
   c4->cd()->SetLogy(false);
   h_BarrelEndcap_b->GetYaxis()->SetTitle("number of modules");
   h_BarrelEndcap_b->GetXaxis()->SetTitle("barrel endcap");
   h_BarrelEndcap_b->Draw();
   c4->SaveAs("BarrelEndcap_b.pdf");

   TCanvas *c5 = new TCanvas("c5", "c5", 800, 800);
   c5->cd()->SetLogy(false);
   h_Layer_b->GetYaxis()->SetTitle("number of modules");
   h_Layer_b->GetXaxis()->SetTitle("layer");
   h_Layer_b->Draw();
   c5->SaveAs("Layer_b.pdf");

   TCanvas *c6 = new TCanvas("c6", "c6", 800, 800);
   c6->cd()->SetLogy(false);
   h_Runs_NoisyStrips_b->GetYaxis()->SetTitle("number of noisy modules");
   h_Runs_NoisyStrips_b->GetXaxis()->SetTitle("runs");
   h_Runs_NoisyStrips_b->Draw();
   c6->SaveAs("Runs_NoisyStrips_b.pdf");

   TCanvas *c7 = new TCanvas("c7", "c7", 800, 800);
   c7->cd()->SetLogy(false);
   h_Eta_NoisyStrips_b->GetYaxis()->SetTitle("number of noisy modules");
   h_Eta_NoisyStrips_b->GetXaxis()->SetTitle("eta");
   h_Eta_NoisyStrips_b->Draw();
   c7->SaveAs("Eta_NoisyStrips_b.pdf");

   TCanvas *c8 = new TCanvas("c8", "c8", 800, 800);
   c8->cd()->SetLogy(false);
   h_Phi_NoisyStrips_b->GetYaxis()->SetTitle("number of noisy modules");
   h_Phi_NoisyStrips_b->GetXaxis()->SetTitle("phi");
   h_Phi_NoisyStrips_b->Draw();
   c8->SaveAs("Phi_NoisyStrips_b.pdf");

   TCanvas *c9 = new TCanvas("c9", "c9", 800, 800);
   c9->cd()->SetLogy(false);
   h_Layer_NoisyStrips_b->GetYaxis()->SetTitle("number of noisy modules");
   h_Layer_NoisyStrips_b->GetXaxis()->SetTitle("layer");
   h_Layer_NoisyStrips_b->Draw();
   c9->SaveAs("Layer_NoisyStrips_b.pdf");

   TCanvas *c10 = new TCanvas("c10", "c10", 800, 800);
   c10->cd()->SetLogy(false);
   h_BarrelEndcap_NoisyStrips_b->GetYaxis()->SetTitle("number of noisy modules");
   h_BarrelEndcap_NoisyStrips_b->GetXaxis()->SetTitle("barrel endcap");
   h_BarrelEndcap_NoisyStrips_b->Draw();
   c10->SaveAs("BarrelEndcap_NoisyStrips_b.pdf");

   TCanvas *c11 = new TCanvas("c11", "c11", 800, 800);
   c11->cd()->SetLogy(true);
   h_NumberOfDefects_e->GetYaxis()->SetTitle("number of modules");
   h_NumberOfDefects_e->GetXaxis()->SetTitle("number of defects");
   h_NumberOfDefects_e->Draw();
   c11->SaveAs("NumberOfDefects_e.pdf");

   TCanvas *c12 = new TCanvas("c12", "c12", 800, 800);
   c12->cd()->SetLogy(false);
   h_Eta_e->GetYaxis()->SetTitle("number of modules");
   h_Eta_e->GetXaxis()->SetTitle("eta");
   h_Eta_e->Draw();
   c12->SaveAs("Eta_e.pdf");

   TCanvas *c13 = new TCanvas("c13", "c13", 800, 800);
   c13->cd()->SetLogy(false);
   h_Phi_e->GetYaxis()->SetTitle("number of modules");
   h_Phi_e->GetXaxis()->SetTitle("phi");
   h_Phi_e->Draw();
   c13->SaveAs("Phi_e.pdf");

   TCanvas *c14 = new TCanvas("c14", "c14", 800, 800);
   c14->cd()->SetLogy(false);
   h_BarrelEndcap_e->GetYaxis()->SetTitle("number of modules");
   h_BarrelEndcap_e->GetXaxis()->SetTitle("barrel endcap");
   h_BarrelEndcap_e->Draw();
   c14->SaveAs("BarrelEndcap_e.pdf");

   TCanvas *c15 = new TCanvas("c15", "c15", 800, 800);
   c15->cd()->SetLogy(false);
   h_Layer_e->GetYaxis()->SetTitle("number of modules");
   h_Layer_e->GetXaxis()->SetTitle("layer");
   h_Layer_e->Draw();
   c15->SaveAs("Layer_e.pdf");

   TCanvas *c16 = new TCanvas("c16", "c16", 800, 800);
   c16->cd()->SetLogy(false);
   h_Runs_NoisyStrips_e->GetYaxis()->SetTitle("number of noisy modules");
   h_Runs_NoisyStrips_e->GetXaxis()->SetTitle("runs");
   h_Runs_NoisyStrips_e->Draw();
   c16->SaveAs("Runs_NoisyStrips_e.pdf");

   TCanvas *c17 = new TCanvas("c17", "c17", 800, 800);
   c17->cd()->SetLogy(false);
   h_Eta_NoisyStrips_e->GetYaxis()->SetTitle("number of noisy modules");
   h_Eta_NoisyStrips_e->GetXaxis()->SetTitle("eta");
   h_Eta_NoisyStrips_e->Draw();
   c17->SaveAs("Eta_NoisyStrips_e.pdf");

   TCanvas *c18 = new TCanvas("c18", "c18", 800, 800);
   c18->cd()->SetLogy(false);
   h_Phi_NoisyStrips_b->GetYaxis()->SetTitle("number of noisy modules");
   h_Phi_NoisyStrips_b->GetXaxis()->SetTitle("phi");
   h_Phi_NoisyStrips_b->Draw();
   c18->SaveAs("Phi_NoisyStrips_b.pdf");

   TCanvas *c19 = new TCanvas("c19", "c19", 800, 800);
   c19->cd()->SetLogy(false);
   h_Layer_NoisyStrips_e->GetYaxis()->SetTitle("number of noisy modules");
   h_Layer_NoisyStrips_e->GetXaxis()->SetTitle("layer");
   h_Layer_NoisyStrips_e->Draw();
   c19->SaveAs("Layer_NoisyStrips_e.pdf");

   TCanvas *c20 = new TCanvas("c20", "c20", 800, 800);
   c20->cd()->SetLogy(false);
   h_BarrelEndcap_NoisyStrips_e->GetYaxis()->SetTitle("number of noisy modules");
   h_BarrelEndcap_NoisyStrips_e->GetXaxis()->SetTitle("barrel endcap");
   h_BarrelEndcap_NoisyStrips_e->Draw();
   c20->SaveAs("BarrelEndcap_NoisyStrips_e.pdf");
 
}
