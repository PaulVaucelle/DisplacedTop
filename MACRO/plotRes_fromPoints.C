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

   TPad* pad2 = new TPad("pad2","This is pad2",0.04,0.02,0.49,0.5,21);
pad2->SetFillColor(0);
pad2->SetBorderMode(0);
pad2->SetFrameFillColor(10);
pad2->Draw();
pad2->SetLogy(0);
   pad2->SetTopMargin(0.1);
   pad2->SetBottomMargin(0.16);
   pad2->SetRightMargin(0.05);
   pad2->SetLeftMargin(0.10);

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
  const unsigned int nMC = 10;
  double  RES[nMC] = {0.1,0.3,1,3,10,20,30,40,50,100};

  double   RES68[nMC] = {0.0045,0.0045,0.005,0.01,0.015,0.04,0.12,0.6,1.8,3.5};
  double   RES90[nMC] = {0.04,0.06,0.06,0.2,0.25,0.5,1.8,4.5,7.0,12.0};
  double   RES68_sup[nMC] = {0.018,0.011,0.010,0.015,0.025,0.05,0.08,0.16,0.3,0.8};
  double   RES90_sup[nMC] = {0.10,0.10,0.15,0.2,0.5,1.0,0.8,1.5,4.0,6.0};   
// *****************************************************************************
  pad1->cd();
  TString xtitle0 = "Decay length [cm]";
  TString ytitle0 = "Spatial resolution [cm]";

  double  Msmu[nMC] = {200,250,300,350,400,450,500};
  TString  Name[nMC] = {"smu200","smu250","smu300","smu350","smu400","smu450","smu500"};

  Double_t ex[nMC] = {0};
  Double_t ey[nMC] = {0};
  Double_t ey1J[nMC] = {0};
   
   auto gr = new TGraphErrors(nMC,RES,RES68,ex,ey);
//    gr->SetTitle("TGraphErrors Example");
   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->Draw("ALP");

  TLegend* leg0 = new TLegend(0.6,0.2,0.8,0.4);
  leg0->SetHeader("Fraction of Matched Vertices");//  #tilde{#chi}^{1}_{0}
  leg0->SetBorderSize(0);
  leg0->SetFillStyle(0);
  leg0->SetFillColor(kWhite);
  leg0->SetTextFont(42);
  leg0->SetTextSize(0.04);
  
  
//     TLegend* leg1 = new TLegend(0.65,0.81,0.8,0.9);
//   leg1->SetHeader("PDF4LHC15_nlo_mc (90500) ");//  #tilde{#chi}^{1}_{0}
//   leg1->SetBorderSize(0);
//   leg1->SetFillStyle(0);
//   leg1->SetFillColor(kWhite);
//   leg1->SetTextFont(42);
//   leg1->SetTextSize(0.04);
  

    gr->SetTitle("Spatial resolution for |#eta|<1.5");
    gr->GetXaxis()->SetTitle(xtitle0);
    gr->GetYaxis()->SetTitle(ytitle0);

    auto gr2 = new TGraphErrors(nMC,RES,RES90,ex,ey);
    gr2->SetTitle("TGraphErrors Example");
    gr2->SetMarkerColor(1);
    gr2->SetMarkerStyle(22);
    gr2->Draw("LPSAME");
    gr->SetMaximum(50);
    leg0->AddEntry(gr2,"90");
    leg0->AddEntry(gr,"68");
    leg0->Draw();
    // leg1->Draw();
//  c1->Update();
pad1->SaveAs("ResTrans.pdf");
// *****************************************************************************

  pad2->cd();
    pad2->SetLogy(logy);
   auto gr3 = new TGraphErrors(nMC,RES,RES68_sup,ex,ey);
   gr3->SetTitle("Spatial resolution for |#eta|>1.5");
   gr3->SetMarkerColor(4);
   gr3->SetMarkerStyle(21);
   gr3->Draw("ALP");
   gr3->GetYaxis()->SetTitle(ytitle0);
   gr3->GetXaxis()->SetTitle(xtitle0);
   gr3->SetMaximum(10);
    c1->Update();
   auto gr4 = new TGraphErrors(nMC,RES,RES90_sup,ex,ey);
   gr4->SetTitle("|#eta|>1.5");
   gr4->SetMarkerColor(1);
   gr4->SetMarkerStyle(22);
   gr4->Draw("LPSAME");
    

     TLegend* leg2 = new TLegend(0.6,0.2,0.8,0.4);
  leg2->SetHeader("Fraction of Matched Vertices");//  #tilde{#chi}^{1}_{0}
  leg2->SetBorderSize(0);
  leg2->SetFillStyle(0);
  leg2->SetFillColor(kWhite);
  leg2->SetTextFont(42);
  leg2->SetTextSize(0.04);
  leg2->AddEntry(gr4,"90");
  leg2->AddEntry(gr3,"68");
  leg2->Draw();
    pad2->SaveAs("ResLong.pdf");
 c1->SaveAs("Res.pdf");
 c1->SaveAs("Res.png");
 c1->Update();
// *****************************************************************************

 

}
