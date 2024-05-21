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


double RR13TEV[nMC] = {0.007659*1000,3.252600e-03*1000,0.001573*1000,0.0008262*1000,4.617900e-04*1000,0.0002718*1000,0.0001658*1000};
double ERROR_RR13TEV[nMC] = {9.335e-04,8.509e-03,3.282e-03,1.739e-03,6.406e-04,3.155e-04,1.5e-04};
   auto gr9 = new TGraphErrors(nMC,Msmu,RR13TEV,ex,ERROR_RR13TEV);
//    gr->SetTitle("TGraphErrors Example");
   gr9->SetMarkerColor(1);
   gr9->SetLineColor(1);
   gr9->SetMarkerStyle(21);
      gr9->SetFillStyle(0);
   gr9->SetFillColor(0);
   gr9->Draw("ALP");
    gr9->SetTitle("Smuon production cross section");
    gr9->GetXaxis()->SetTitle(xtitle0);
    gr9->GetYaxis()->SetTitle(ytitle0);

// RR 90500 L01J 13 TeV

double RR13TEV1J[nMC] = {0.0123*1000,0.005405*1000,0.002664*1000,0.00143*1000,0.0008179*1000,0.0004866*1000,0.000301*1000};
double ERROR_RR13TEV1J[nMC] = {2.846e-02,1.646e-02,5.83e-03,4.171e-03,1.539e-03,1.209e-03,7.336e-04};
   auto gr10 = new TGraphErrors(nMC,Msmu,RR13TEV1J,ex,ERROR_RR13TEV1J);
//    gr->SetTitle("TGraphErrors Example");
   gr10->SetMarkerColor(2);
   gr10->SetLineColor(2);
   gr10->SetMarkerStyle(21);
         gr10->SetFillStyle(0);
   gr10->SetFillColor(0);
   gr10->Draw("LPsame");



// RR 90500 L0 14 TeV

double RR14TEV[nMC] = {0.008697*1000,0.003732*1000,0.001823*1000,0.0009685*1000,0.0005483*1000,0.0003263*1000,0.0002015*1000};
double ERROR_RR14TEV[nMC] = {1.406e-02,6.474e-03,3.943e-03,1.915e-03,1.114e-03,7.571e-04,3.567e-04};
   auto gr11 = new TGraphErrors(nMC,Msmu,RR14TEV,ex,ERROR_RR14TEV);
//    gr->SetTitle("TGraphErrors Example");
   gr11->SetMarkerColor(3);
   gr11->SetLineColor(3);
   gr11->SetMarkerStyle(21);
         gr11->SetFillStyle(0);
   gr11->SetFillColor(0);
   gr11->Draw("LPsame");



// RR 90500 L01J 14 TeV

double RR14TEV1J[nMC] = {0.01407*1000,0.006282*1000,0.003127*1000,0.001698*1000,0.0009815*1000,0.0005902*1000,0.0003702*1000};
double ERROR_RR14TEV1J[nMC] = {3.161e-02,1.613e-02,8.352e-03,4.239e-03,2.204e-03,1.598e-03,8.542e-04};
   auto gr12 = new TGraphErrors(nMC,Msmu,RR14TEV1J,ex,ERROR_RR14TEV1J);
//    gr->SetTitle("TGraphErrors Example");
   gr12->SetMarkerColor(4);
    gr12->SetLineColor(4);
   gr12->SetMarkerStyle(21);
         gr12->SetFillStyle(0);
   gr12->SetFillColor(0);
   gr12->Draw("LPsame");


gr9->SetMaximum(50);


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
  

   leg0->AddEntry(gr12,"RR LO1J 14 TeV");
   leg0->AddEntry(gr10,"RR LO1J 13 TeV");
    leg0->AddEntry(gr11,"RR LO 14 TeV");
    leg0->AddEntry(gr9,"RR LO 13 TeV");
    
   
   
    leg0->Draw();
    leg1->Draw();

 c1->Update();

 c1->SaveAs("CrossSectionRR.pdf");
 c1->SaveAs("CrossSectionRR.png");
 

}
