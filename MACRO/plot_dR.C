#include <iostream>
#include <TROOT.h>
#include "TVectorD.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TH1F.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TEfficiency.h" 
#include "TMath.h" 
#include "Func.h"

void plot()
{
// *****************************************************************************
int stati=0;
bool fit= 0;
bool logy=0;
// TCanvas *c1 = new TCanvas("c1", "plots",200,0,900,500);
TCanvas *c1 = new TCanvas("c1", "plots",200,0,1500,1000);
c1->SetFillColor(10);
c1->SetFillStyle(4000);
c1->SetBorderSize(2);

TPad* pad1 = new TPad("pad1","This is pad1",0.04,0.51,0.49,1,21);
pad1->SetFillColor(0);
pad1->SetBorderMode(0);
pad1->SetFrameFillColor(10);
pad1->Draw();
pad1->SetLogy(logy);
   pad1->SetTopMargin(0.1);
   pad1->SetBottomMargin(0.16);
   pad1->SetRightMargin(0.05);
   pad1->SetLeftMargin(0.10);

TPad* pad2 = new TPad("pad2","This is pad2",0.04,0.01,0.49,0.49,21);
pad2->SetFillColor(0);
pad2->SetBorderMode(0);
pad2->SetFrameFillColor(10);
pad2->Draw();
pad2->SetLogy(0);
   pad2->SetTopMargin(0.1);
   pad2->SetBottomMargin(0.20);
   pad2->SetRightMargin(0.05);
   pad2->SetLeftMargin(0.10);


TPad* pad3 = new TPad("pad3","This is pad3",0.53,0.51,0.95,1,21);
pad3->SetFillColor(0);
pad3->SetBorderMode(0);
pad3->SetFrameFillColor(10);
pad3->Draw();
pad3->SetLogy(0);
   pad3->SetTopMargin(0.1);
   pad3->SetBottomMargin(0.20);
   pad3->SetRightMargin(0.05);
   pad3->SetLeftMargin(0.10);

   TPad* pad4 = new TPad("pad4","This is pad4",0.53,0.01,0.95,0.49,21);
pad4->SetFillColor(0);
pad4->SetBorderMode(0);
pad4->SetFrameFillColor(10);
pad4->Draw();
pad4->SetLogy(0);
   pad4->SetTopMargin(0.1);
   pad4->SetBottomMargin(0.20);
   pad4->SetRightMargin(0.05);
   pad4->SetLeftMargin(0.10);


gStyle->SetOptDate(0);
gStyle->SetStatColor(0);
gStyle->SetTitleFont(62);
gStyle->SetTitleColor(1);
gStyle->SetTitleTextColor(1);
gStyle->SetTitleFillColor(10);
gStyle->SetTitleFontSize(0.06);
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

//  htitle0 = "hSim_Hemi_LLP_dist"; 
//  htitle1 = "hSim_Hemi_LLP_dist_chiOK"; 
//  htitle2 = "hSim_Hemi_LLP_dist_ping"; 

// htitle0 = "hData_dR_GenGen";  
// htitle1 = "hData_dR_RecoReco"; 
// htitle2 = "hData_dR_GenReco"; 

const int nMC = 3;
  TString  Datasets[nMC] = {"RPV_2018_smu200_neu180_ctau001","RPV_2018_smu200_neu180_ctau1000","RPV_2018_smu500_neu480_ctau1000"};
  TString  Name[nMC] = {"smu200_neu180_ctau001","smu200_neu180_ctau1000","smu500_neu480_ctau1000"};
    TFile *fX[nMC];
    for (int i = 0; i < nMC; i++) 
      {
        fX[i] = new TFile("./histofile_"+Datasets[i]+".root");
      }

  TString htitle0 = "hSim_dR_GenGen_noSel_";
  TString xtitle0 = "#Delta R_{#chi-#chi}"; 
  TString ytitle0 = "a.u"; 
  TH1F* histograms0[nMC];
  // int Colors[nMC] = {4,1,2,3,33,5,6,7,8,9,30,38,41,43,46,49};
  int Colors0[nMC];

for (int i = 0; i < nMC; i++) {
    Colors0[i]= i+1;
    fX[i]->cd();
    TString histogramTitle = htitle0+"_"+Datasets[i]; // Assuming htitle is an array of strings
    histograms0[i] = (TH1F*)gROOT->FindObject(histogramTitle);
    histograms0[i]->GetXaxis()->SetRangeUser(1,5);
}

/////////
  TLegend* leg0 = new TLegend(0.65,0.6,0.9,0.85);
  leg0->SetHeader("#beta#gamma c#tau #tilde{#chi}^{1}_{0}");
  leg0->SetBorderSize(0);
  leg0->SetFillStyle(0);
  leg0->SetFillColor(kWhite);
  leg0->SetTextFont(42);
  leg0->SetTextSize(0.03);
    for (unsigned int k = 0; k < nMC; k++)
    {
      StyleAndDraw(histograms0[k], Colors0[k], 2, 1, Datasets[k]);
      leg0->AddEntry(histograms0[k],Name[k],"L");
    }

  histograms0[0]->SetMaximum(0.1);
  histograms0[0]->SetTitle("#Delta R between Generated Neutralinos");
  histograms0[0]->GetXaxis()->SetTitle(xtitle0);
  histograms0[0]->GetYaxis()->SetTitle(ytitle0);
 leg0->Draw();
 c1->Update();
// *****************************************************************************

  pad2->cd();

  /////////
  TString htitle1 = "hData_dR_RecoReco_noSel_";
  TString xtitle1 = "#Delta R_{H-H}"; 
  TString ytitle1 = "a.u"; 
  TH1F* histograms1[nMC];
  // int Colors[nMC] = {4,1,2,3,33,5,6,7,8,9,30,38,41,43,46,49};
  int Colors1[nMC];

for (int i = 0; i < nMC; i++) {
    Colors1[i]= i+1;
    fX[i]->cd();
    TString histogramTitle = htitle1+"_"+Datasets[i]; // Assuming htitle is an array of strings
    histograms1[i] = (TH1F*)gROOT->FindObject(histogramTitle);
    histograms1[i]->GetXaxis()->SetRangeUser(1,5);
}

/////////
  TLegend* leg1 = new TLegend(0.65,0.6,0.9,0.85);
  leg1->SetHeader("#beta#gamma c#tau #tilde{#chi}^{1}_{0}");
  leg1->SetBorderSize(0);
  leg1->SetFillStyle(0);
  leg1->SetFillColor(kWhite);
  leg1->SetTextFont(42);
  leg1->SetTextSize(0.03);
    for (unsigned int k = 0; k < nMC; k++)
    {
      StyleAndDraw(histograms1[k], Colors1[k], 2, 1, Datasets[k]);
      leg1->AddEntry(histograms1[k],Name[k],"L");
    }

  histograms1[0]->SetMaximum(0.1);
  histograms1[0]->SetTitle("#Delta R between Reconstructed Hemispheres");
  histograms1[0]->GetXaxis()->SetTitle(xtitle1);
  histograms1[0]->GetYaxis()->SetTitle(ytitle1);
 leg1->Draw();
 c1->Update();
// *****************************************************************************

  pad3->cd();

   /////////
  TString htitle2 = "hSim_dPhi_GenGen_noSel_";
  TString xtitle2 = "#Delta #phi_{#chi-#chi}"; 
  TString ytitle2 = "a.u"; 
  TH1F* histograms2[nMC];
  // int Colors[nMC] = {4,1,2,3,33,5,6,7,8,9,30,38,41,43,46,49};
  int Colors2[nMC];

for (int i = 0; i < nMC; i++) {
    Colors2[i]= i+1;
    fX[i]->cd();
    TString histogramTitle = htitle2+"_"+Datasets[i]; // Assuming htitle is an array of strings
    histograms2[i] = (TH1F*)gROOT->FindObject(histogramTitle);
    histograms2[i]->GetXaxis()->SetRangeUser(0,5);
}

/////////
  TLegend* leg2 = new TLegend(0.65,0.6,0.9,0.85);
  leg2->SetHeader("Signal Samples");
  leg2->SetBorderSize(0);
  leg2->SetFillStyle(0);
  leg2->SetFillColor(kWhite);
  leg2->SetTextFont(42);
  leg2->SetTextSize(0.03);
    for (unsigned int k = 0; k < nMC; k++)
    {
      StyleAndDraw(histograms2[k], Colors2[k], 2, 1, Datasets[k]);
      leg2->AddEntry(histograms2[k],Name[k],"L");
    }

  histograms2[0]->SetMaximum(0.2);
  histograms2[0]->SetTitle("#Delta #phi between Generated Neutralinos");
  histograms2[0]->GetXaxis()->SetTitle(xtitle2);
  histograms2[0]->GetYaxis()->SetTitle(ytitle2);
  histograms2[0]->GetXaxis()->SetTitleSize(0.06);
 leg2->Draw();
 
 c1->Update();
pad3->SaveAs("dPhi_GenGen.pdf");
 // *****************************************************************************

  pad4->cd();

   /////////
  TString htitle3 = "hSim_dR_GenReco_noSel_";
  TString xtitle3 = "#Delta R_{#chi-H}"; 
  TString ytitle3 = "a.u"; 
  TH1F* histograms3[nMC];
  // int Colors[nMC] = {4,1,2,3,33,5,6,7,8,9,30,38,41,43,46,49};
  int Colors3[nMC];

for (int i = 0; i < nMC; i++) {
    Colors3[i]= i+1;
    fX[i]->cd();
    TString histogramTitle = htitle3+"_"+Datasets[i]; // Assuming htitle is an array of strings
    histograms3[i] = (TH1F*)gROOT->FindObject(histogramTitle);
    histograms3[i]->GetXaxis()->SetRangeUser(0,5);
}

/////////
  TLegend* leg3 = new TLegend(0.6,0.6,0.9,0.85);
  leg3->SetHeader("#beta#gamma c#tau #tilde{#chi}^{1}_{0}");
  leg3->SetBorderSize(0);
  leg3->SetFillStyle(0);
  leg3->SetFillColor(kWhite);
  leg3->SetTextFont(42);
  leg3->SetTextSize(0.03);
    for (unsigned int k = 0; k < nMC; k++)
    {
      StyleAndDraw(histograms3[k], Colors3[k], 2, 1, Datasets[k]);
      leg3->AddEntry(histograms3[k],Name[k],"L");
    }

  histograms3[0]->SetMaximum(0.1);
  histograms3[0]->SetTitle("#Delta R between Generated Neutralinos and Reconstructed Axes ");
  histograms3[0]->GetXaxis()->SetTitle(xtitle3);
  histograms3[0]->GetYaxis()->SetTitle(ytitle3);
 leg3->Draw();
 
 c1->Update();
}
