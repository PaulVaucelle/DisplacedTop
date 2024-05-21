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
// #include "Func.h"

void plot()
{
// *****************************************************************************
int stati=0;
bool fit= 0;
bool logy=1;
// TCanvas *c1 = new TCanvas("c1", "plots",200,0,900,500);

TCanvas *c1 = new TCanvas("c1", "C1",200,0,1500,1000);
c1->SetFillColor(10);
c1->SetFillStyle(4000);
c1->SetBorderSize(2);


TPad* pad1 = new TPad("pad1","This is pad1",0.1,0.1,0.9,0.9,21);
pad1->SetFillColor(0);
pad1->SetBorderMode(0);
pad1->SetFrameFillColor(10);
pad1->SetLogy(logy);
   pad1->SetTopMargin(0.1);
   pad1->SetBottomMargin(0.16);
   pad1->SetRightMargin(0.05);
   pad1->SetLeftMargin(0.10);
   pad1->Draw();

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
  c1->cd();
  pad1->cd();
  TString xtitle0 = "M_{#tilde{#mu}} [GeV]";
  TString ytitle0 = "#sigma(pp->#tilde{#mu}#bar{#tilde{#mu}}) [fb]";
  const unsigned int nMC = 7;


  // double  XSLOCOR[nMC] = {9.554037,4.2,2.085,1.1,0.642,0.37,0.23685237};//Robin's values 14 TeV

  double  Msmu[nMC] = {200,250,300,350,400,450,500};
  Double_t ex[nMC] = {0};

//-------------Left+Left--------------------//
// LL 90500 L0 13 TeV

double LL13TEV[nMC] = {0.01793*1000,0.007552*1000,0.003632*1000,0.001897*1000,0.001058*1000,0.0006204*1000,0.0003777*1000};
double ERROR_LL13TEV[nMC] = {2.961e-02,1.327e-02,7.612e-03,3.703e-03,2.134e-03,1.479e-03,6.844e-04};

   auto gr5 = new TGraphErrors(nMC,Msmu,LL13TEV,ex,ERROR_LL13TEV);
//    gr->SetTitle("TGraphErrors Example");
   gr5->SetMarkerColor(1);
   gr5->SetLineColor(1);
   gr5->SetMarkerStyle(21);
   gr5->SetFillStyle(0);
   gr5->SetFillColor(0);
   gr5->Draw("ALP");
    gr5->SetTitle("Smuon production cross section");
    gr5->GetXaxis()->SetTitle(xtitle0);
    gr5->GetYaxis()->SetTitle(ytitle0);


// LL 90500 L01J 13 TeV

double LL13TEV1J[nMC] = {0.02871*1000,0.0125*1000,0.006133*1000,0.003283*1000,0.001871*1000,0.001107*1000,0.0006838*1000};
double ERROR_LL13TEV1J[nMC] = {6.141e-02,4.201e-02,1.454e-02,9.188e-03,4.088e-03,2.745e-03,1.651e-03};

   auto gr6 = new TGraphErrors(nMC,Msmu,LL13TEV1J,ex,ERROR_LL13TEV1J);
//    gr->SetTitle("TGraphErrors Example");
   gr6->SetMarkerColor(2);
   gr6->SetLineColor(2);
   gr6->SetMarkerStyle(21);
   gr6->SetFillStyle(0);
   gr6->SetFillColor(0);
   gr6->Draw("LPsame");


// LL 90500 L0 14 TeV

double LL14TEV[nMC] = {0.02034*1000,0.008666*1000,0.004213*1000,0.002229*1000,0.001257*1000,0.0007462*1000,0.0004596*1000};
double ERROR_LL14TEV[nMC] = {3.915e-02,1.398e-02,8.576e-03,4.538e-03,2.644e-03,1.785e-06,8.648e-04};
   auto gr7 = new TGraphErrors(nMC,Msmu,LL14TEV,ex,ERROR_LL14TEV);
//    gr->SetTitle("TGraphErrors Example");
   gr7->SetMarkerColor(3);
   gr7->SetLineColor(3);
   gr7->SetMarkerStyle(21);
   gr7->SetFillStyle(0);
   gr7->SetFillColor(0);
   gr7->Draw("LPsame");


// LL 90500 L01J 14 TeV

double LL14TEV1J[nMC] = {0.03289*1000,0.01455*1000,0.007198*1000,0.003891*1000,0.00225*1000,0.001344*1000,0.0008416*1000};
double ERROR_LL14TEV1J[nMC] = {6.685e-02,3.259e-02,2.006e-02,1.094e-02,5.104e-03,3.924e-03,2.183e-03};

   auto gr8 = new TGraphErrors(nMC,Msmu,LL14TEV1J,ex,ERROR_LL14TEV1J);
//    gr->SetTitle("TGraphErrors Example");
   gr8->SetMarkerColor(4);
   gr8->SetLineColor(4);
   gr8->SetMarkerStyle(21);
   gr8->SetFillStyle(0);
   gr8->SetFillColor(0);
   gr8->Draw("LPsame");

gr5->SetMaximum(50);


//-------Plotting --/

  TLegend* leg0 = new TLegend(0.6,0.55,0.8,0.85);
  leg0->SetHeader("pp -> #tilde{#mu}#bar{#tilde{#mu}}");//  #tilde{#chi}^{1}_{0}
  leg0->SetBorderSize(0);
  leg0->SetFillStyle(0);
  leg0->SetFillColor(kWhite);
  leg0->SetTextFont(42);
  leg0->SetTextSize(0.04);
  
    TLegend* leg1 = new TLegend(0.6,0.81,0.75,0.9);
  leg1->SetHeader("PDF4LHC15_nlo_mc (90500) ");//  #tilde{#chi}^{1}_{0}
  leg1->SetBorderSize(0);
  leg1->SetFillStyle(0);
  leg1->SetFillColor(kWhite);
  leg1->SetTextFont(42);
  leg1->SetTextSize(0.04);
  

   leg0->AddEntry(gr8,"LL LO1J 14 TeV");
   leg0->AddEntry(gr6,"LL LO1J 13 TeV");
    leg0->AddEntry(gr7,"LL LO 14 TeV");
    leg0->AddEntry(gr5,"LL LO 13 TeV");
    
   
   
    leg0->Draw();
    leg1->Draw();

 c1->Update();

 c1->SaveAs("CrossSectionLL.pdf");
 c1->SaveAs("CrossSectionLL.png");
 

}
