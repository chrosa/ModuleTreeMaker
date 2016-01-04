#define ModuleSelector2_cxx
// The class definition in ModuleSelector2.h has been generated automatically
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
// Root > T->Process("ModuleSelector2.C")
// Root > T->Process("ModuleSelector2.C","some options")
// Root > T->Process("ModuleSelector2.C+")
//

#include "ModuleSelector2.h"
#include <iostream>
#include <TStyle.h>
#include <TCanvas.h>


void ModuleSelector2::Begin(TTree * /*tree*/)
{
    // The Begin() function is called at the start of the query.
    // When running with PROOF Begin() is only called on the client.
    // The tree argument is deprecated (on PROOF 0 is passed).

    TString option = GetOption();

    h_NumberOfDefects_b = new TH1F("NumberOfDefects_b","NumberOfDefects_b",200,0,400);
    h_NumberOfDefects_e = new TH1F("NumberOfDefects_e","NumberOfDefects_e",200,0,400);
    h_NumberOfDefects_tot = new TH1F("NumberOfDefects_tot","NumberOfDefects_tot",200,0,400);

    h_Eta_b = new TH1F("Eta_b","Eta_b",13,-6.5,6.5);
    h_Phi_b = new TH1F("Phi_b","Phi_b",71,-0.5,70.5);
    h_BarrelEndcap_b = new TH1F("BarrelEndcap_b","BarrelEndcap_b",5,-2.5,2.5);
    h_Layer_b = new TH1F("Layer_b","Layer_b",11,-0.5,10.5);

    h_Eta_e = new TH1F("Eta_e","Eta_e",13,-6.5,6.5);
    h_Phi_e = new TH1F("Phi_e","Phi_e",71,-0.5,70.5);
    h_BarrelEndcap_e = new TH1F("BarrelEndcap_e","BarrelEndcap_e",5,-2.5,2.5);
    h_Layer_e = new TH1F("Layer_e","Layer_e",11,-0.5,10.5);

    h_NumberOfDefects_vs_Duration = new TH2F("h_NumberOfDefects_vs_Duration","NumberOfDefects_vs_Duration",40,0,80000,20,0,10000);
}

void ModuleSelector2::SlaveBegin(TTree * /*tree*/)
{
    // The SlaveBegin() function is called after the Begin() function.
    // When running with PROOF SlaveBegin() is called on each slave server.
    // The tree argument is deprecated (on PROOF 0 is passed).

    TString option = GetOption();

}

Bool_t ModuleSelector2::Process(Long64_t entry)
{
    // The Process() function is called for each entry in the tree (or possibly
    // keyed object in the case of PROOF) to be processed. The entry argument
    // specifies which entry in the currently loaded tree is to be processed.
    // It can be passed to either ModuleSelector2::GetEntry() or TBranch::GetEntry()
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

    int NOD_tot = 0;
    int NOD_Mon_tot = 0;
    int NOD_MonOnly_tot = 0;
    int NOD_e = 0;
    int NOD_b = 0;
    for (int i_bec = 0; i_bec < 3; ++i_bec) {
        for (int i_layer = 0; i_layer < 9; ++i_layer) {
            for (int i_eta = 0; i_eta < 12; ++i_eta) {
                for (int i_phi = 0; i_phi < 56; ++i_phi) {
                    NOD_tot += NumberOfDefects[i_bec][i_layer][i_eta][i_phi];
                    NOD_Mon_tot += NumberOfNoisyStripsMon[i_bec][i_layer][i_eta][i_phi];
                    NOD_MonOnly_tot += NumberOfNoisyStripsMonOnly[i_bec][i_layer][i_eta][i_phi];
                    h_NumberOfDefects_tot->Fill(NumberOfDefects[i_bec][i_layer][i_eta][i_phi]);
                    if (i_bec == 1) {
                        NOD_b += NumberOfDefects[i_bec][i_layer][i_eta][i_phi];
                        h_NumberOfDefects_b->Fill(NumberOfDefects[i_bec][i_layer][i_eta][i_phi]);
                        h_Eta_b->Fill(i_eta);
                        h_Phi_b->Fill(i_phi);
                        h_BarrelEndcap_b->Fill(i_bec);
                        h_Layer_b->Fill(i_layer);
                    } else {
                        NOD_e += NumberOfDefects[i_bec][i_layer][i_eta][i_phi];
                        h_NumberOfDefects_e->Fill(NumberOfDefects[i_bec][i_layer][i_eta][i_phi]);
                        h_Eta_e->Fill(i_eta);
                        h_Phi_e->Fill(i_phi);
                        h_BarrelEndcap_e->Fill(i_bec);
                        h_Layer_e->Fill(i_layer);
                    }
                }
            }
        }
    }
    //std::cout << Start << std::endl;
    if (Start > 0 && Duration > 3600) {
        v_time.push_back(Start);
        v_NumberOfDefects_tot.push_back(NOD_tot);
        v_NumberOfDefectsMon_tot.push_back(NOD_Mon_tot);
        v_NumberOfDefectsMonOnly_tot.push_back(NOD_MonOnly_tot);
        v_NumberOfDefects_e.push_back(NOD_e);
        v_NumberOfDefects_b.push_back(NOD_b);
    }
    h_NumberOfDefects_vs_Duration->Fill(Duration,NOD_Mon_tot);

    return kTRUE;
}

void ModuleSelector2::SlaveTerminate()
{
    // The SlaveTerminate() function is called after all entries or objects
    // have been processed. When running with PROOF SlaveTerminate() is called
    // on each slave server.

}

void ModuleSelector2::Terminate()
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
    gStyle->SetTimeOffset(0);

    gROOT->ForceStyle();

    TCanvas *c1_tot = new TCanvas("c1_tot", "c1_tot", 800, 800);
    c1_tot->cd()->SetLogy(true);
    h_NumberOfDefects_tot->GetYaxis()->SetTitle("a.u.");
    h_NumberOfDefects_tot->GetXaxis()->SetTitle("number of defects");
    h_NumberOfDefects_tot->Draw();
    c1_tot->SaveAs("NumberOfDefects_tot.pdf");

    TCanvas *c1_e = new TCanvas("c1_e", "c1_e", 800, 800);
    c1_e->cd()->SetLogy(true);
    h_NumberOfDefects_e->GetYaxis()->SetTitle("a.u.");
    h_NumberOfDefects_e->GetXaxis()->SetTitle("number of defects");
    h_NumberOfDefects_e->Draw();
    c1_e->SaveAs("NumberOfDefects_e.pdf");

    TCanvas *c1_b = new TCanvas("c1_b", "c1_b", 800, 800);
    c1_b->cd()->SetLogy(true);
    h_NumberOfDefects_b->GetYaxis()->SetTitle("a.u.");
    h_NumberOfDefects_b->GetXaxis()->SetTitle("number of defects");
    h_NumberOfDefects_b->Draw();
    c1_b->SaveAs("NumberOfDefects_b.pdf");

    TCanvas *c3 = new TCanvas("c3", "c3", 1200, 800);
    c3->cd();
    h_NumberOfDefects_vs_Duration->GetYaxis()->SetTitle("number of defects");
    h_NumberOfDefects_vs_Duration->GetXaxis()->SetTitle("duration (sec)");
    h_NumberOfDefects_vs_Duration->Draw("COLZ");
    TProfile* p_NumberOfDefects_vs_Duration = h_NumberOfDefects_vs_Duration->ProfileX("_pfx",1,-1);
    p_NumberOfDefects_vs_Duration->SetLineColor(kRed);
    p_NumberOfDefects_vs_Duration->SetLineWidth(2);
    p_NumberOfDefects_vs_Duration->SetMarkerColor(kRed);
    p_NumberOfDefects_vs_Duration->Draw("same");
    c3->SaveAs("NumberOfDefects_bvs_Duration.pdf");

    TGraph *g_NumberOfDefects_vs_time_tot = new TGraph(v_time.size(), &(v_time.at(0)), &(v_NumberOfDefects_tot.at(0)));
    TCanvas *c2_tot = new TCanvas("c2_tot","c2_tot",1600, 800);
    c2_tot->cd()->SetLogy(true);
    g_NumberOfDefects_vs_time_tot->GetXaxis()->SetTimeDisplay(1);
    g_NumberOfDefects_vs_time_tot->GetXaxis()->SetTimeFormat("%m/%Y");
    g_NumberOfDefects_vs_time_tot->GetXaxis()->SetTitle("Date");
    g_NumberOfDefects_vs_time_tot->GetYaxis()->SetTitle("Number of noisy strips");
    g_NumberOfDefects_vs_time_tot->Draw("AP");
    g_NumberOfDefects_vs_time_tot->GetHistogram()->SetMinimum(50);
    g_NumberOfDefects_vs_time_tot->GetHistogram()->SetMaximum(50000);
    c2_tot->SaveAs("NumberOfDefects_vs_time_tot.pdf");

    TGraph *g_NumberOfDefectsMon_vs_time_tot = new TGraph(v_time.size(), &(v_time.at(0)), &(v_NumberOfDefectsMon_tot.at(0)));
    TCanvas *c2_Mon_tot = new TCanvas("c2_Mon_tot","c2_Mon_tot",1600, 800);
    c2_Mon_tot->cd()->SetLogy(true);
    g_NumberOfDefectsMon_vs_time_tot->GetXaxis()->SetTimeDisplay(1);
    g_NumberOfDefectsMon_vs_time_tot->GetXaxis()->SetTimeFormat("%m/%Y");
    g_NumberOfDefectsMon_vs_time_tot->GetXaxis()->SetTitle("Date");
    g_NumberOfDefectsMon_vs_time_tot->GetYaxis()->SetTitle("Number of noisy strips");
    g_NumberOfDefectsMon_vs_time_tot->Draw("AP");
    g_NumberOfDefectsMon_vs_time_tot->GetHistogram()->SetMinimum(50);
    g_NumberOfDefectsMon_vs_time_tot->GetHistogram()->SetMaximum(50000);
    c2_Mon_tot->SaveAs("NumberOfDefectsMon_vs_time_tot.pdf");

    TGraph *g_NumberOfDefectsMonOnly_vs_time_tot = new TGraph(v_time.size(), &(v_time.at(0)), &(v_NumberOfDefectsMonOnly_tot.at(0)));
    TCanvas *c2_MonOnly_tot = new TCanvas("c2_MonOnly_tot","c2_MonOnly_tot",1600, 800);
    c2_MonOnly_tot->cd()->SetLogy(true);
    g_NumberOfDefectsMonOnly_vs_time_tot->GetXaxis()->SetTimeDisplay(1);
    g_NumberOfDefectsMonOnly_vs_time_tot->GetXaxis()->SetTimeFormat("%m/%Y");
    g_NumberOfDefectsMonOnly_vs_time_tot->GetXaxis()->SetTitle("Date");
    g_NumberOfDefectsMonOnly_vs_time_tot->GetYaxis()->SetTitle("Number of noisy strips");
    g_NumberOfDefectsMonOnly_vs_time_tot->Draw("AP");
    g_NumberOfDefectsMonOnly_vs_time_tot->GetHistogram()->SetMinimum(50);
    g_NumberOfDefectsMonOnly_vs_time_tot->GetHistogram()->SetMaximum(50000);
    c2_MonOnly_tot->SaveAs("NumberOfDefectsMonOnly_vs_time_tot.pdf");

    //g_NumberOfDefects_vs_time_e = new TGraph();
    //g_NumberOfDefects_vs_time_b = new TGraph();

}
