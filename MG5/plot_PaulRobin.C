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



TPad* pad1 = new TPad("pad1","This is pad1",0.1,0.5,0.9,0.95,21);
pad1->SetFillColor(0);
pad1->SetBorderMode(0);
pad1->SetFrameFillColor(10);
pad1->SetLogy(logy);
   pad1->SetTopMargin(0.1);
   pad1->SetBottomMargin(0.16);
   pad1->SetRightMargin(0.05);
   pad1->SetLeftMargin(0.10);
   pad1->Draw();



         TPad* pad4 = new TPad("pad4","This is pad4",0.1,0.1,0.9,0.5,21);
pad4->SetFillColor(0);
pad4->SetBorderMode(0);
pad4->SetFrameFillColor(10);
pad4->SetLogy(0);
   pad4->SetTopMargin(0.1);
   pad4->SetBottomMargin(0.16);
   pad4->SetRightMargin(0.05);
   pad4->SetLeftMargin(0.10);
   pad4->Draw();

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

// MIXING RL+LR 90500 LO  14TeV

double RLLR14TEV[nMC] = {0.005086*2*1000,0.002167*2*1000,0.001053*2*1000,0.0005574*2*1000,0.0003142*2*1000,0.0001865*2*1000,0.0001149*2*1000};
double ERROR_RLLR14TEV[nMC] = {9.788e-03,3.495e-03,2.144e-03,1.135e-03,6.609e-04,4.463e-04,2.162e-04};

   auto gr3 = new TGraphErrors(nMC,Msmu,RLLR14TEV,ex,ERROR_RLLR14TEV);
    gr3->SetTitle("XS at LO at 14 TeV");
    gr3->SetMarkerColor(3);
    gr3->SetLineColor(3);
    gr3->SetMarkerStyle(22);
        gr3->SetFillStyle(0);
   gr3->SetFillColor(0);

//Robin 14TeV

double Robin14Tev[nMC] = {9.554037,4.2,2.085,1.1,0.642,0.37,0.23685237};
double ERROR_Robin14Tev[nMC] = {0};

    auto gr4 = new TGraphErrors(nMC,Msmu,Robin14Tev,ex,ERROR_Robin14Tev);
    gr4->SetTitle("TGraphErrors Example");
    gr4->SetMarkerColor(4);
    gr4->SetLineColor(4);
    gr4->SetMarkerStyle(22);
    gr4->SetFillStyle(0);
   gr4->SetFillColor(0);
    

//-------Plotting --/

gr3->Draw("ALP");
gr4->Draw("LPSAME");

  TLegend* leg0 = new TLegend(0.6,0.55,0.8,0.85);
  leg0->SetHeader("pp -> #tilde{#mu}#bar{#tilde{#mu}}");//  #tilde{#chi}^{1}_{0}
  leg0->SetBorderSize(0);
  leg0->SetFillStyle(0);
  leg0->SetFillColor(kWhite);
  leg0->SetTextFont(42);
  leg0->SetTextSize(0.04);
  
  
    TLegend* leg1 = new TLegend(0.4,0.81,0.8,0.9);
  leg1->SetHeader("Robin : NNPDF30_lo_as_0118 (263000) / Paul : PDF4LHC15_nlo_mc (90500) ");//  #tilde{#chi}^{1}_{0}
  leg1->SetBorderSize(0);
  leg1->SetFillStyle(0);
  leg1->SetFillColor(kWhite);
  leg1->SetTextFont(42);
  leg1->SetTextSize(0.04);

//       TLegend* leg2 = new TLegend(0.45,0.7,0.75,0.8);
//   leg1->SetHeader("Robin : NNPDF30_lo_as_0118 (263000) / Paul : PDF4LHC15_nlo_mc (90500) ");//  #tilde{#chi}^{1}_{0}
//   leg1->SetBorderSize(0);
//   leg1->SetFillStyle(0);
//   leg1->SetFillColor(kWhite);
//   leg1->SetTextFont(42);
//   leg1->SetTextSize(0.04);
  
    gr3->SetMaximum(50);
    
    leg0->AddEntry(gr4,"Robin LO 14TeV ");
    leg0->AddEntry(gr3,"Paul LO 14TeV ");
    leg0->Draw();
    leg1->Draw();


  c1->Update();

pad4->cd();
double ratioXS[nMC]={0};

  for ( unsigned int k = 0 ; k < nMC ; k++  )
    {
        ratioXS[k]=  RLLR14TEV[k]/Robin14Tev[k];

    }
 auto gr10 = new TGraph(nMC,Msmu,ratioXS);
   gr10->SetTitle("Ratio of XS (Paul/Robin) at 14TeV ");
   gr10->SetMarkerColor(1);
   gr10->SetLineColor(1);
   gr10->SetMarkerStyle(22);
   gr10->SetFillStyle(0);
   gr10->SetFillColor(0);
   gr10->Draw("ALP");
  TLegend* leg3 = new TLegend(0.8,0.6,0.9,0.85);

  leg3->SetBorderSize(0);
  leg3->SetFillStyle(0);
  leg3->SetFillColor(kWhite);
  leg3->SetTextFont(42);
  leg3->SetTextSize(0.04);
  leg3->AddEntry(gr10,"Paul/Robin LO 14 TeV");
  leg3->Draw();

// // *****************************************************************************

  c1->Update();

 c1->SaveAs("CrossSectionPaul_Robin.pdf");
 c1->SaveAs("CrossSectionPaul_Robin.png");


}
