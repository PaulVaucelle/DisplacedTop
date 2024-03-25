#include <iostream>
#include <TROOT.h>
#include "TVectorD.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TEfficiency.h" 
#include "TMath.h" 

void plot()
{
 TFile *f1;
 
//  f1 = new TFile("../output/h_UDD_bgctau10_smu250_snu200.root");
//  f2 = new TFile("../output/h_UDD_bgctau30_smu300_snu250.root");
//  f1 = new TFile("../output/h_UDD_bgctau50_smu275_snu225_Neu.root");
//  f4 = new TFile("../output/h_UDD_bgctau70_smu250_snu200.root");

TString  Datasets[14] = {"ST_tW_antitop_5f_NoFullyHadronicDecays","ST_tW_top_5f_NoFullyHadronicDecays","DYJetsToLL_M10to50","DYJetsToLL_M50","WWTo2L2Nu_MLL_200To600","WWTo2L2Nu_MLL_600To1200","WWTo2L2Nu","TTJets_DiLept","TTTo2L2Nu","TTWW","ttWJetsToLNu_5f_EWK","TTZToLL_5f","WZTo2Q2L_mllmin4p0","ZZTo2Q2L_mllmin4p0"};
TString Sample = "TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8";
f1 = new TFile("./histofile_"+Sample+".root");


int stati=0;
bool fit= 0;
bool logy=0;

 TLegend* leg;
 TString htitle0, htitle1, htitle2, htitle3;
 TString dof = "50";

//  TString htitle = "hSim_Hemi_LLP_dist_ping"; 
 TString xtitle = "x [cm]"; 
 TString ytitle = "y [cm]";  

// *****************************************************************************

// TCanvas *c1 = new TCanvas("c1", "plots",200,0,900,500);
TCanvas *c1 = new TCanvas("c1", "plots",200,0,1000,1100);
c1->SetFillColor(10);
c1->SetFillStyle(4000);
c1->SetBorderSize(2);

TPad* pad1 = new TPad("pad1","This is pad1",0.01,0.01,0.99,1,21);
pad1->SetFillColor(0);
pad1->SetBorderMode(0);
pad1->SetFrameFillColor(10);
pad1->Draw();
pad1->SetLogy(logy);
   pad1->SetTopMargin(0.1);
   pad1->SetBottomMargin(0.1);
   pad1->SetRightMargin(0.1);
   pad1->SetLeftMargin(0.1);
   


gStyle->SetOptDate(0);
gStyle->SetStatColor(0);
gStyle->SetTitleFont(62);
gStyle->SetTitleColor(1);
gStyle->SetTitleTextColor(1);
gStyle->SetTitleFillColor(10);
gStyle->SetTitleFontSize(0.05);
gStyle->SetTitleW(0.4);
gStyle->SetTitleH(0.09);
gStyle->SetOptStat(stati);
gStyle->SetPadTickX(1); gStyle->SetPadTickY(1);
if (fit) {
gStyle->SetStatW(0.3);
gStyle->SetStatH(0.1);
gStyle->SetOptFit(111);
} else {
gStyle->SetStatW(0.3);
gStyle->SetStatH(0.2);
gStyle->SetOptFit(0);
}

// *****************************************************************************

  pad1->cd();

/////////
 f1->cd();
  // htitle0 = "hData_reco_SecInt_xy_TrackerMatched__"+Sample;
  // htitle0 = "hData_reco_SecInt_xy_Selec__"+Sample;
  // htitle0 = "hData_reco_SecInt_r_TrackerMatched__"+Sample;
  htitle0 = "hData_reco_SecInt_rz_Selec__"+Sample;



//  htitle0 = "hData_Hemi_Vtx_xvsy";
  //  htitle0 = "hData_WoVeto";
 TH2F* h0 = (TH2F*)gROOT->FindObject(htitle0);
 h0->Sumw2(); 

       h0->Draw("L"); 
       h0->SetLineColor(kBlack);
       h0->SetLineStyle(1);
       h0->SetLineWidth(3);
       h0->SetTickLength(0.03, "XYZ");
       h0->SetLabelOffset(0.007,"X");
       h0->SetLabelOffset(0.007,"Y");
       h0->SetLabelSize(0.022, "XYZ");
       h0->SetLabelFont(42, "XYZ"); 
       h0->SetTitleFont(42, "XYZ");
       h0->SetTitleSize(0.03, "XYZ"); 
       h0->SetTitleOffset(1.,"Y");
       h0->GetYaxis()->SetTitle(ytitle);
       h0->GetYaxis()->SetTitleColor(1);
       h0->SetNdivisions(1001,"XYZ");
       h0->SetMinimum(0.); 
       h0->GetYaxis()->SetRangeUser(0,60);
       h0->GetXaxis()->SetTitle(xtitle);
       h0->SetTitle("Secondary Interactions");
  // leg = new TLegend(0.70,0.75,0.9,0.85);
  // leg->SetBorderSize(0);
  // leg->SetFillColor(kWhite);
  // leg->SetTextFont(42);
  // leg->SetTextSize(0.025);
  // leg->SetHeader("MC Samples");
  // leg->AddEntry(h0,"Secondary Vertices","LE");

  // leg->Draw();
  
// *****************************************************************************
 
 c1->Update();
 c1->SaveAs(htitle0+".pdf");
}
