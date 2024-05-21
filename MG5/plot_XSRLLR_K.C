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



         TPad* pad4 = new TPad("pad4","This is pad4",0.1,0.1,0.9,0.9,21);
pad4->SetFillColor(0);
pad4->SetBorderMode(0);
pad4->SetFrameFillColor(10);
pad4->SetLogy(0);
   pad4->SetTopMargin(0.1);
   pad4->SetBottomMargin(0.16);
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
  c1->cd();
  pad1->cd();
  TString xtitle0 = "M_{#tilde{#mu}} [GeV]";
  TString ytitle0 = "#sigma(pp->#tilde{#mu}#bar{#tilde{#mu}}) [fb]";
  const unsigned int nMC = 7;


  // double  XSLOCOR[nMC] = {9.554037,4.2,2.085,1.1,0.642,0.37,0.23685237};//Robin's values 14 TeV

  double  Msmu[nMC] = {200,250,300,350,400,450,500};
  Double_t ex[nMC] = {0};

//--------Mising LR+RL-------------------//
  // MIXING RL+LR 90500 LO  13TeV

double ERROR_RLLR13TEV[nMC] = {7.86e-03,3.316e-03,1.903e-03,9.257e-04,5.334e-04,3.697e-04,1.711e-04};
double K_RLLR13TEV[nMC] = {0.004482*2*1.4*1000,0.001888*2*1.4*1000,0.0009079*2*1.4*1000,0.0004742*2*1.48*1000,0.0002646*2*1.4*1000,0.0001551*2*1.4*1000,9.443e-05*2*1.4*1000};

   auto gr = new TGraphErrors(nMC,Msmu,K_RLLR13TEV,ex,ERROR_RLLR13TEV);
//    gr->SetTitle("TGraphErrors Example");
gr->Draw("ALP");
   gr->SetMarkerColor(1);
   gr->SetMarkerStyle(22);
    gr->SetLineColor(1);
    gr->SetTitle("Smuon production cross section");
    gr->GetXaxis()->SetTitle(xtitle0);
    gr->GetYaxis()->SetTitle(ytitle0);
    gr->SetFillStyle(0);
    gr->SetFillColor(0);   

// MIXING RL+LR 90500 LO1J 13TeV

double ERROR_RLLR13TEV1J[nMC] = {1.535e-02,1.05e-02,3.632e-03,2.406e-03,1.022e-03,6.861e-04,4.128e-04};
double K_RLLR13TEV1J[nMC] = {0.007178*2*1000,0.003125*2*1000,0.001533*2*1000,0.000821*2*1000,0.0004676*2*1000,0.0002767*2*1000,0.0001709*2*1000};
    auto gr2 = new TGraphErrors(nMC,Msmu,K_RLLR13TEV1J,ex,ERROR_RLLR13TEV1J);
    gr2->SetTitle("TGraphErrors Example");
    gr2->SetMarkerColor(2);
    gr2->SetLineColor(2);
    gr2->SetMarkerStyle(22);
        gr2->SetFillStyle(0);
   gr2->SetFillColor(0);    

// MIXING RL+LR 90500 LO  14TeV

double ERROR_RLLR14TEV[nMC] = {9.788e-03,3.495e-03,2.144e-03,1.135e-03,6.609e-04,4.463e-04,2.162e-04};
double K_RLLR14TEV[nMC] = {0.005086*2*1.4*1000,0.002167*2*1.4*1000,0.001053*2*1.4*1000,0.0005574*2*1.4*1000,0.0003142*2*1.4*1000,0.0001865*2*1.4*1000,0.0001149*2*1.4*1000};
   auto gr3 = new TGraphErrors(nMC,Msmu,K_RLLR14TEV,ex,ERROR_RLLR14TEV);
    gr3->SetTitle("TGraphErrors Example");
    gr3->SetMarkerColor(3);
    gr3->SetLineColor(3);
    gr3->SetMarkerStyle(22);
        gr3->SetFillStyle(0);
   gr3->SetFillColor(0);

// MIXING RL+LR 90500 LO1J 14TeV

double ERROR_RLLR14TEV1J[nMC] = {1.671e-02,8.147e-03,5.016e-03,2.734e-03,1.277e-03,9.81e-04,5.457e-04};
double K_RLLR14TEV1J[nMC] = {0.008224*2*1000,0.003638*2*1000,0.001799*2*1000,0.0009728*2*1000,0.0005624*2*1000,0.000336*2*1000,0.0002104*2*1000};
    auto gr4 = new TGraphErrors(nMC,Msmu,K_RLLR14TEV1J,ex,ERROR_RLLR14TEV1J);
    gr4->SetTitle("TGraphErrors Example");
    gr4->SetMarkerColor(4);
    gr4->SetLineColor(4);
    gr4->SetMarkerStyle(22);
    gr4->SetFillStyle(0);
   gr4->SetFillColor(0);
    

//-------Plotting --/


gr2->Draw("LPSAME");
gr3->Draw("LPSAME");
gr4->Draw("LPSAME");

  TLegend* leg0 = new TLegend(0.6,0.55,0.8,0.85);
  leg0->SetHeader("pp -> #tilde{#mu}#bar{#tilde{#mu}}");//  #tilde{#chi}^{1}_{0}
  leg0->SetBorderSize(0);
  leg0->SetFillStyle(0);
  leg0->SetFillColor(kWhite);
  leg0->SetTextFont(42);
  leg0->SetTextSize(0.04);
  
  
    TLegend* leg1 = new TLegend(0.6,0.81,0.8,0.9);
  leg1->SetHeader("PDF4LHC15_nlo_mc (90500) ");//  #tilde{#chi}^{1}_{0}
  leg1->SetBorderSize(0);
  leg1->SetFillStyle(0);
  leg1->SetFillColor(kWhite);
  leg1->SetTextFont(42);
  leg1->SetTextSize(0.04);
  
    gr->SetMaximum(50);
    
    leg0->AddEntry(gr4,"RL+LR LO1J 14TeV ");
      leg0->AddEntry(gr2,"RL+LR LO1J 13TeV ");
    leg0->AddEntry(gr3,"RL+LR LO*K 14TeV ");
    leg0->AddEntry(gr,"RL+LR LO*K 13TeV ");
    leg0->Draw();
    leg1->Draw();

 c1->Update();

 c1->SaveAs("CrossSectionRLLR_K.pdf");
 c1->SaveAs("CrossSectionRLLR_K.png");




// c4->cd();

// // *****************************************************************************

//   pad4->cd();
 
//   double ratioXS[nMC]={0};
//   double ratio2XS[nMC]={0};
//   for ( unsigned int k = 0 ; k < nMC ; k++  )
//     {
//         ratioXS[k]=  XSLO14[k]/XSLOCOR[k];

//     }

//    auto gr3 = new TGraphErrors(nMC,Msmu,ratioXS,ex,ey);
//    gr3->SetTitle("Cross sections ratio at 14Tev between Paul  and Robin");
//    gr3->SetMarkerColor(1);
//    gr3->SetMarkerStyle(20);
//    gr3->Draw("ALP");

//    gr3->GetYaxis()->SetTitle("14TevPaul/14TevRobin");
//    gr3->GetXaxis()->SetTitle(xtitle0);
//    c1->Update();
//    auto gr6 = new TGraphErrors(nMC,Msmu,ratio2XS,ex,ey);
//    gr6->SetMarkerColor(3);
//    gr6->SetMarkerStyle(20);
//    gr6->Draw("LSAME");

//   TLegend* leg2 = new TLegend(0.8,0.6,0.9,0.85);

//   leg2->SetBorderSize(0);
//   leg2->SetFillStyle(0);
//   leg2->SetFillColor(kWhite);
//   leg2->SetTextFont(42);
//   leg2->SetTextSize(0.04);
//   leg2->AddEntry(gr3,"Paul LO");
//   leg2->AddEntry(gr6,"Paul LO");
//   leg2->Draw();

//  c1->SaveAs("CrossSection.pdf");
//  c1->SaveAs("CrossSection.png");
//  c3->Update();
// // *****************************************************************************

// c4->cd();
// pad4->cd();

 

}
