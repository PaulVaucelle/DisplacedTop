#include <iostream>
#include <TROOT.h>
#include "TH1.h"

void plot()
{
int stati=0;
bool fit= 1;
bool logy=1;

// number of vertices:
  int nvtx = 2;
  float hmax = 1E5;	         // for eta<2.4 pt>80 or CRlowpt
  if ( nvtx == 1 ) hmax = 1E6;   // for eta<2.4 pt>80  
  if ( nvtx == 2 ) hmax = 1E3;   // for eta<2.4 pt>80  

 TFile* f1_DY  = new TFile("../output_240311/h_DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8.root");
 TFile* f2_DY  = new TFile("../output_240311/h_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8.root");
 TFile* f1_TT  = new TFile("../output_240311/h_TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8.root");
//$$ TFile* f2_TT  = new TFile("../output_240311/h_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8.root");
 TFile* f1_ST  = new TFile("../output_240311/h_ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8.root");
 TFile* f2_ST  = new TFile("../output_240311/h_ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8.root");
 TFile* f1_TTV = new TFile("../output_240311/h_ttWJetsToLNu_5f_EWK_TuneCP5_13TeV_amcatnlo-pythia8.root");
 TFile* f2_TTV = new TFile("../output_240311/h_TTZToLL_5f_TuneCP5_13TeV-madgraphMLM-pythia8.root");
 TFile* f3_TTV = new TFile("../output_240311/h_TTWW_TuneCP5_13TeV-madgraph-pythia8.root");
 TFile* f1_VV  = new TFile("../output_240311/h_WWTo2L2Nu_TuneCP5_13TeV-powheg-pythia8.root");
 TFile* f2_VV  = new TFile("../output_240311/h_WZTo2Q2L_mllmin4p0_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
 TFile* f3_VV  = new TFile("../output_240311/h_ZZTo2Q2L_mllmin4p0_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
 TFile* f1_LLP = new TFile("../output_240311/h_RPV_2018_smu250_neu200_ctau100.root");
 TFile* f2_LLP = new TFile("../output_240311/h_RPV_2018_smu300_neu250_ctau100.root");
 TFile* f3_LLP = new TFile("../output_240311/h_RPV_2018_smu400_neu300_ctau100.root");
 TFile* f4_LLP = new TFile("../output_240311/h_RPV_2018_smu500_neu350_ctau100.root");
 
 TString htitleA = "hData_CRlowpt_Hemi_2Vtx_Mass"; 
 TString htitleB = "hData_Hemi_2Vtx_CutEvt_Mass"; 
 TString htitleC = "hData_CRlooselowpt_Hemi_2Vtx_CutEvt_Mass"; 
 TString htitleD = "hData_CRloose_Hemi_2Vtx_CutEvt_Mass"; 
 TString xtitle = "max. vertex mass [GeV]"; 
 TString ytitle = "Events / 4 GeV"; 
 int nbin = 25; 
 float xmin =   0.;
 float xmax = 100.;

 float xsec_DY[2], xsec_TT[3], xsec_ST[2], xsec_TTV[3], xsec_VV[3]; 
 xsec_DY[0] = 5379.0; xsec_DY[1] = 15910.0;
 xsec_TT[0] = 88.3; xsec_TT[1] = 365.3; xsec_TT[2] = 378.0;
 xsec_ST[0] = 32.51; xsec_ST[1] = 32.45;
 xsec_TTV[0] = 0.29; xsec_TTV[1] = 0.052; xsec_TTV[2] =  0.0070;
 xsec_VV[0] = 11.09; xsec_VV[1] = 6.57; xsec_VV[2] = 3.68;
 
// signal cross section (fb), choose 1 or 10
 int SigXsec = 10;
 if ( nvtx == 2 ) SigXsec = 1;
 float SigXsec1 = 7.55;
 float SigXsec2 = 3.63;
 float SigXsec3 = 1.06;
 float SigXsec4 = 0.38;

 float events = 0.;
 float lumi = 60000.;
 float norm = lumi / 100000.;

  TLegend* leg;
    
// *****************************************************************************

TCanvas *c1 = new TCanvas("c1", "plots",200,0,700,700);
c1->SetFillColor(10);
c1->SetFillStyle(4000);
c1->SetBorderSize(2);

// TPad* pad1 = new TPad("pad1","This is pad1",0.04,0.49,0.48,0.91,21);
// TPad* pad2 = new TPad("pad2","This is pad2",0.52,0.49,0.96,0.91,21);
// TPad* pad3 = new TPad("pad3","This is pad3",0.04,0.04,0.48,0.46,21);
// TPad* pad4 = new TPad("pad4","This is pad4",0.52,0.04,0.96,0.46,21);
// 
TPad* pad1 = new TPad("pad1","This is pad1",0.03,0.48,0.49,0.92,21);
TPad* pad2 = new TPad("pad2","This is pad2",0.51,0.48,0.97,0.92,21);
TPad* pad3 = new TPad("pad3","This is pad3",0.03,0.03,0.49,0.47,21);
TPad* pad4 = new TPad("pad4","This is pad4",0.51,0.03,0.97,0.47,21);

pad1->SetFillColor(0);
pad1->SetBorderMode(0);
pad1->SetFrameFillColor(10);
pad1->Draw();
pad1->SetLogy(logy);
   pad1->SetTopMargin(0.07);
   pad1->SetBottomMargin(0.13);
   pad1->SetRightMargin(0.04);
   pad1->SetLeftMargin(0.16);

pad2->SetFillColor(0);
pad2->SetBorderMode(0);
pad2->SetFrameFillColor(10);
pad2->Draw();
pad2->SetLogy(logy);
   pad2->SetTopMargin(0.07);
   pad2->SetBottomMargin(0.13);
   pad2->SetRightMargin(0.04);
   pad2->SetLeftMargin(0.16);

pad3->SetFillColor(0);
pad3->SetBorderMode(0);
pad3->SetFrameFillColor(10);
pad3->Draw();
pad3->SetLogy(logy);
   pad3->SetTopMargin(0.07);
   pad3->SetBottomMargin(0.13);
   pad3->SetRightMargin(0.04);
   pad3->SetLeftMargin(0.16);

pad4->SetFillColor(0);
pad4->SetBorderMode(0);
pad4->SetFrameFillColor(10);
pad4->Draw();
pad4->SetLogy(logy);
   pad4->SetTopMargin(0.07);
   pad4->SetBottomMargin(0.13);
   pad4->SetRightMargin(0.04);
   pad4->SetLeftMargin(0.16);

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
// gStyle->SetPadGridX(false); gStyle->SetPadGridY(false);

 TH1F* htot  = new TH1F("htot","",nbin,xmin,xmax);
 TH1F* e1_DY = (TH1F*)gROOT->FindObject("hData_Filter");
 TH1F* g1_DY = (TH1F*)gROOT->FindObject(htitleB);
 TH1F* e2_DY = (TH1F*)gROOT->FindObject("hData_Filter");
 TH1F* g2_DY = (TH1F*)gROOT->FindObject(htitleB);
 TH1F*  h_DY = new TH1F("h_DY","",nbin,xmin,xmax);

 TH1F* e1_VV = (TH1F*)gROOT->FindObject("hData_Filter");
 TH1F* g1_VV = (TH1F*)gROOT->FindObject(htitleB);
 TH1F* e2_VV = (TH1F*)gROOT->FindObject("hData_Filter");
 TH1F* g2_VV = (TH1F*)gROOT->FindObject(htitleB);
 TH1F* e3_VV = (TH1F*)gROOT->FindObject("hData_Filter");
 TH1F* g3_VV = (TH1F*)gROOT->FindObject(htitleB);
 TH1F*  h_VV = new TH1F("h_VV","",nbin,xmin,xmax);

 TH1F* e1_TVV = (TH1F*)gROOT->FindObject("hData_Filter");
 TH1F* g1_TVV = (TH1F*)gROOT->FindObject(htitleB);
 TH1F* e2_TVV = (TH1F*)gROOT->FindObject("hData_Filter");
 TH1F* g2_TVV = (TH1F*)gROOT->FindObject(htitleB);
 TH1F* e3_TVV = (TH1F*)gROOT->FindObject("hData_Filter");
 TH1F* g3_TVV = (TH1F*)gROOT->FindObject(htitleB);
 TH1F*  h_TVV = new TH1F("h_TVV","",nbin,xmin,xmax);

 TH1F* e1_ST = (TH1F*)gROOT->FindObject("hData_Filter");
 TH1F* g1_ST = (TH1F*)gROOT->FindObject(htitleB);
 TH1F* e2_ST = (TH1F*)gROOT->FindObject("hData_Filter");
 TH1F* g2_ST = (TH1F*)gROOT->FindObject(htitleB);
 TH1F*  h_ST = new TH1F("h_ST","",nbin,xmin,xmax);

 TH1F* e1_TT = (TH1F*)gROOT->FindObject("hData_Filter");
 TH1F* g1_TT = (TH1F*)gROOT->FindObject(htitleB);
 TH1F*  h_TT = new TH1F("h_TT","",nbin,xmin,xmax);

 TH1F* e1_LLP = (TH1F*)gROOT->FindObject("hData_Filter");
 TH1F* g1_LLP = (TH1F*)gROOT->FindObject(htitleB);
 TH1F* h1_LLP = new TH1F("h1_LLP","",nbin,xmin,xmax);
 TH1F* e2_LLP = (TH1F*)gROOT->FindObject("hData_Filter");
 TH1F* g2_LLP = (TH1F*)gROOT->FindObject(htitleB);
 TH1F* h2_LLP = new TH1F("h2_LLP","",nbin,xmin,xmax);
 TH1F* e3_LLP = (TH1F*)gROOT->FindObject("hData_Filter");
 TH1F* g3_LLP = (TH1F*)gROOT->FindObject(htitleB);
 TH1F* h3_LLP = new TH1F("h3_LLP","",nbin,xmin,xmax);

// *****************************************************************************

 pad1->cd();

 htot = new TH1F("htot","",nbin,xmin,xmax);

 f1_DY->cd();
 e1_DY = (TH1F*)gROOT->FindObject("hData_Filter");
 e1_DY->Sumw2();
 norm = 0.;
 if  ( e1_DY->Integral(0,3) > 0 ) norm = 60000. / e1_DY->Integral(0,3);
 g1_DY = (TH1F*)gROOT->FindObject(htitleA);
 g1_DY->Sumw2();
 h_DY = new TH1F("h_DY","",nbin,xmin,xmax);
 h_DY->Add(g1_DY, h_DY, xsec_DY[0]*norm,0);

 f2_DY->cd();
 e2_DY = (TH1F*)gROOT->FindObject("hData_Filter");
 e2_DY->Sumw2();
 norm = 0.;
 if  ( e2_DY->Integral(0,3) > 0 ) norm = 60000. / e2_DY->Integral(0,3);
 g2_DY = (TH1F*)gROOT->FindObject(htitleA);
 g2_DY->Sumw2();
 h_DY->Add(g2_DY, h_DY, xsec_DY[1]*norm, 1);

 f1_VV->cd();
 e1_VV = (TH1F*)gROOT->FindObject("hData_Filter");
 e1_VV->Sumw2();
 norm = 0.;
 if  ( e1_VV->Integral(0,3) > 0 ) norm = 60000. / e1_VV->Integral(0,3);
 g1_VV = (TH1F*)gROOT->FindObject(htitleA);
 g1_VV->Sumw2();
 h_VV = new TH1F("h_VV","",nbin,xmin,xmax);
 h_VV->Add(g1_VV, h_VV, xsec_VV[0]*norm,0);

 f2_VV->cd();
 e2_VV = (TH1F*)gROOT->FindObject("hData_Filter");
 e2_VV->Sumw2();
 norm = 0.;
 if  ( e2_VV->Integral(0,3) > 0 ) norm = 60000. / e2_VV->Integral(0,3);
 g2_VV = (TH1F*)gROOT->FindObject(htitleA);
 g2_VV->Sumw2();
 h_VV->Add(g2_VV, h_VV, xsec_VV[1]*norm, 1);

 f3_VV->cd();
 e3_VV = (TH1F*)gROOT->FindObject("hData_Filter");
 e3_VV->Sumw2();
 norm = 0.;
 if  ( e3_VV->Integral(0,3) > 0 ) norm = 60000. / e3_VV->Integral(0,3);
 g3_VV = (TH1F*)gROOT->FindObject(htitleA);
 g3_VV->Sumw2();
 h_VV->Add(g3_VV, h_VV, xsec_VV[2]*norm, 1);

 f1_TTV->cd();
 e1_TVV = (TH1F*)gROOT->FindObject("hData_Filter");
 e1_TVV->Sumw2();
 norm = 0.;
 if  ( e1_TVV->Integral(0,3) > 0 ) norm = 60000. / e1_TVV->Integral(0,3);
 g1_TTV = (TH1F*)gROOT->FindObject(htitleA);
 g1_TVV->Sumw2();
 h_TTV = new TH1F("h_TTV","",nbin,xmin,xmax);
 h_TTV->Add(g1_TTV, h_TTV, xsec_TTV[0]*norm,0);

 f2_TTV->cd();
 e2_TVV = (TH1F*)gROOT->FindObject("hData_Filter");
 e2_TVV->Sumw2();
 norm = 0.;
 if  ( e2_TVV->Integral(0,3) > 0 ) norm = 60000. / e2_TVV->Integral(0,3);
 g2_TTV = (TH1F*)gROOT->FindObject(htitleA);
 g2_TVV->Sumw2();
 h_TTV->Add(g2_TTV, h_TTV, xsec_TTV[1]*norm, 1);

 f3_TTV->cd();
 e3_TVV = (TH1F*)gROOT->FindObject("hData_Filter");
 e3_TVV->Sumw2();
 norm = 0.;
 if  ( e3_TVV->Integral(0,3) > 0 ) norm = 60000. / e3_TVV->Integral(0,3);
 g3_TTV = (TH1F*)gROOT->FindObject(htitleA);
 g3_TVV->Sumw2();
 h_TTV->Add(g3_TTV, h_TTV, xsec_TTV[2]*norm, 1);

 f1_ST->cd();
 e1_ST = (TH1F*)gROOT->FindObject("hData_Filter");
 e1_ST->Sumw2();
 norm = 0.;
 if  ( e1_ST->Integral(0,3) > 0 ) norm = 60000. / e1_ST->Integral(0,3);
 g1_ST = (TH1F*)gROOT->FindObject(htitleA);
 g1_ST->Sumw2();
 h_ST = new TH1F("h_ST","",nbin,xmin,xmax);
 h_ST->Add(g1_ST, h_ST, xsec_ST[0]*norm,0);

 f2_ST->cd();
 e2_ST = (TH1F*)gROOT->FindObject("hData_Filter");
 e2_ST->Sumw2();
 norm = 0.;
 if  ( e2_ST->Integral(0,3) > 0 ) norm = 60000. / e2_ST->Integral(0,3);
 g2_ST = (TH1F*)gROOT->FindObject(htitleA);
 g2_ST->Sumw2();
 h_ST->Add(g2_ST, h_ST, xsec_ST[1]*norm, 1);

 f1_TT->cd();
 e1_TT = (TH1F*)gROOT->FindObject("hData_Filter");
 e1_TT->Sumw2();
 norm = 0.;
 if  ( e1_TT->Integral(0,3) > 0 ) norm = 60000. / e1_TT->Integral(0,3);
 g1_TT = (TH1F*)gROOT->FindObject(htitleA);
 g1_TT->Sumw2();
 h_TT = new TH1F("h_TT","",nbin,xmin,xmax);
 h_TT->Add(g1_TT, h_TT, xsec_TT[0]*norm,0);

 htot->Add(htot, h_DY, 1, 1);
 htot->Add(htot, h_VV, 1, 1);
 htot->Add(htot, h_TTV, 1, 1);
 htot->Add(htot, h_ST, 1, 1);
 htot->Add(htot, h_TT, 1, 1);

 h_VV->Add(h_VV, h_TTV, 1, 1);
 h_VV->Add(h_VV, h_ST, 1, 1);
 h_VV->Add(h_VV, h_TT, 1, 1);

 h_TTV->Add(h_TTV, h_ST, 1, 1);
 h_TTV->Add(h_TTV, h_TT, 1, 1);

 h_ST->Add(h_ST, h_TT, 1, 1);

 htot->Draw("HE"); 
 htot->SetFillColor(kGreen-6);
 htot->SetLineColor(kGreen-6);
 htot->SetLineStyle(1);
 htot->SetLineWidth(3);
 htot->SetTickLength(0.03, "YZ");
 htot->SetTickLength(0.03,"X");
 htot->SetLabelOffset(0.015,"X");
 htot->SetLabelOffset(0.007,"Y");
 htot->SetLabelSize(0.045, "XYZ");
 htot->SetLabelFont(42, "XYZ"); 
 htot->SetTitleSize(0.045, "XYZ"); 
 htot->SetTitleFont(42, "XYZ");
 htot->SetTitleOffset(1.2,"X"); 
 htot->SetTitleOffset(1.3,"Y");
 htot->GetXaxis()->SetTitle(xtitle);
 htot->GetXaxis()->SetTitleColor(1);
 htot->GetYaxis()->SetTitle(ytitle);
 htot->GetYaxis()->SetTitleColor(1);
 htot->SetNdivisions(509,"XYZ");
 htot->SetMinimum(1.); 
 htot->SetMaximum(hmax); 

 h_VV->Draw("HEsame"); 
 h_VV->SetFillColor(kOrange-2);
 h_VV->SetLineColor(kOrange-2);
 h_VV->SetLineStyle(1);
 h_VV->SetLineWidth(3);

 h_TTV->Draw("HEsame"); 
 h_TTV->SetFillColor(kAzure+4);
 h_TTV->SetLineColor(kAzure+4);
 h_TTV->SetLineStyle(1);
 h_TTV->SetLineWidth(3);

 h_ST->Draw("HEsame"); 
 h_ST->SetFillColor(kAzure+2);
 h_ST->SetLineColor(kAzure+2);
 h_ST->SetLineStyle(1);
 h_ST->SetLineWidth(3);

 h_TT->Draw("HEsame"); 
 h_TT->SetFillColor(kAzure+1);
 h_TT->SetLineColor(kAzure+1);
 h_TT->SetLineStyle(1);
 h_TT->SetLineWidth(3);
 h_TT->SetTickLength(0.03, "YZ");
 h_TT->SetTickLength(0.03,"X");

 f1_LLP->cd();
 e1_LLP = (TH1F*)gROOT->FindObject("hData_Filter");
 e1_LLP->Sumw2();
 norm = 0.;
 if ( e1_LLP->Integral(0,3) > 0. ) norm = SigXsec1*60000. / e1_LLP->Integral(0,3);
 g1_LLP = (TH1F*)gROOT->FindObject(htitleA);
 g1_LLP->Sumw2();
 h1_LLP = new TH1F("h1_LLP","",nbin,xmin,xmax);
 h1_LLP->Add(g1_LLP, h1_LLP, 0.001*norm,0);

 f2_LLP->cd();
 e2_LLP = (TH1F*)gROOT->FindObject("hData_Filter");
 e2_LLP->Sumw2();
 norm = 0.;
 if ( e2_LLP->Integral(0,3) > 0. ) norm = SigXsec2*60000. / e2_LLP->Integral(0,3);
 g2_LLP = (TH1F*)gROOT->FindObject(htitleA);
 g2_LLP->Sumw2();
 h2_LLP = new TH1F("h2_LLP","",nbin,xmin,xmax);
 h2_LLP->Add(g2_LLP, h2_LLP, 0.001*norm,0);

 f3_LLP->cd();
 e3_LLP = (TH1F*)gROOT->FindObject("hData_Filter");
 e3_LLP->Sumw2();
 norm = 0.;
 if ( e3_LLP->Integral(0,3) > 0. ) norm = SigXsec3*60000. / e3_LLP->Integral(0,3);
 g3_LLP = (TH1F*)gROOT->FindObject(htitleA);
 g3_LLP->Sumw2();
 h3_LLP = new TH1F("h3_LLP","",nbin,xmin,xmax);
 h3_LLP->Add(g3_LLP, h3_LLP, 0.001*norm,0);

//            f4_LLP->cd();
//      TH1F* e4_LLP = (TH1F*)gROOT->FindObject("hData_Filter");
//            e4_LLP->Sumw2();
// 	   norm = 0.;
// 	   if ( e4_LLP->Integral(0,3) > 0. ) norm = SigXsec4*60000. / e4_LLP->Integral(0,3);
//      TH1F* g4_LLP = (TH1F*)gROOT->FindObject(htitleA);
//            g4_LLP->Sumw2();
//      TH1F* h4_LLP = new TH1F("h4_LLP","",nbin,xmin,xmax);
//            h4_LLP->Add(g4_LLP, h4_LLP, 0.001*norm,0);

 h1_LLP->Draw("HEsame"); 
 h1_LLP->SetLineColor(kRed-1);
 h1_LLP->SetLineStyle(1);
 h1_LLP->SetLineWidth(2);

 h2_LLP->Draw("HEsame"); 
 h2_LLP->SetLineColor(kRed-2);
 h2_LLP->SetLineStyle(2);
 h2_LLP->SetLineWidth(2);

 h3_LLP->Draw("HEsame");
 h3_LLP->SetLineColor(kRed-3);
 h3_LLP->SetLineStyle(3);
 h3_LLP->SetLineWidth(2);

//  h4_LLP->Draw("HEsame"); 
//  h4_LLP->SetLineColor(kRed-4);
//  h4_LLP->SetLineStyle(2);
//  h4_LLP->SetLineWidth(4);

//  e1_LLP->Draw("HEsame"); 
//  e1_LLP->SetLineColor(kWhite);
//  e1_LLP->SetLineStyle(1);
//  e1_LLP->SetLineWidth(3);

  leg = new TLegend(0.17,0.93,0.50,0.98);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->SetTextFont(42);
  leg->SetTextSize(0.05);
  leg->SetHeader("simulation 2018, 60 fb^{-1} (13 TeV)");
  leg->Draw();

  leg = new TLegend(0.53,0.50,0.85,0.89);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->SetTextFont(42);
  leg->SetTextSize(0.035);
  leg->AddEntry(htot, " DY","F");
  leg->AddEntry(h_VV, " WW, WZ, ZZ","F");
  leg->AddEntry(h_TTV," t#bar{t}W, t#bar{t}Z, t#bar{t}WW","F");
  leg->AddEntry(h_ST, " tW","F");
  leg->AddEntry(h_TT, " t#bar{t}","F");
  leg->AddEntry(h1_LLP," m_{#tilde{#mu} (#tilde{#chi}^{0})} = 250 (200) GeV","L");
  leg->AddEntry(h2_LLP," m_{#tilde{#mu} (#tilde{#chi}^{0})} = 300 (250) GeV","L");
  leg->AddEntry(h3_LLP," m_{#tilde{#mu} (#tilde{#chi}^{0})} = 400 (300) GeV","L");
//   leg->AddEntry(h4_LLP,"Signal, m_{#tilde{#mu}}= 500 GeV, m_{#tilde{#chi}^{0}}= 350 GeV","L");
  leg->Draw();

  leg = new TLegend(0.18,0.85,0.45,0.89);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->SetTextFont(42);
  leg->SetTextSize(0.04);
  leg->SetHeader(" 2 loose vertices");
  leg->Draw();
  leg = new TLegend(0.18,0.80,0.45,0.84);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->SetTextFont(42);
  leg->SetTextSize(0.04);
  leg->SetHeader(" hem. p_{T} > 80 GeV");
  leg->Draw();

// *****************************************************************************

 pad2->cd();

 htot = new TH1F("htot","",nbin,xmin,xmax);

 f1_DY->cd();
 e1_DY = (TH1F*)gROOT->FindObject("hData_Filter");
 e1_DY->Sumw2();
 norm = 0.;
 if  ( e1_DY->Integral(0,3) > 0 ) norm = 60000. / e1_DY->Integral(0,3);
 g1_DY = (TH1F*)gROOT->FindObject(htitleB);
 g1_DY->Sumw2();
 h_DY = new TH1F("h_DY","",nbin,xmin,xmax);
 h_DY->Add(g1_DY, h_DY, xsec_DY[0]*norm,0);

 f2_DY->cd();
 e2_DY = (TH1F*)gROOT->FindObject("hData_Filter");
 e2_DY->Sumw2();
 norm = 0.;
 if  ( e2_DY->Integral(0,3) > 0 ) norm = 60000. / e2_DY->Integral(0,3);
 g2_DY = (TH1F*)gROOT->FindObject(htitleB);
 g2_DY->Sumw2();
 h_DY->Add(g2_DY, h_DY, xsec_DY[1]*norm, 1);

 f1_VV->cd();
 e1_VV = (TH1F*)gROOT->FindObject("hData_Filter");
 e1_VV->Sumw2();
 norm = 0.;
 if  ( e1_VV->Integral(0,3) > 0 ) norm = 60000. / e1_VV->Integral(0,3);
 g1_VV = (TH1F*)gROOT->FindObject(htitleB);
 g1_VV->Sumw2();
 h_VV = new TH1F("h_VV","",nbin,xmin,xmax);
 h_VV->Add(g1_VV, h_VV, xsec_VV[0]*norm,0);

 f2_VV->cd();
 e2_VV = (TH1F*)gROOT->FindObject("hData_Filter");
 e2_VV->Sumw2();
 norm = 0.;
 if  ( e2_VV->Integral(0,3) > 0 ) norm = 60000. / e2_VV->Integral(0,3);
 g2_VV = (TH1F*)gROOT->FindObject(htitleB);
 g2_VV->Sumw2();
 h_VV->Add(g2_VV, h_VV, xsec_VV[1]*norm, 1);

 f3_VV->cd();
 e3_VV = (TH1F*)gROOT->FindObject("hData_Filter");
 e3_VV->Sumw2();
 norm = 0.;
 if  ( e3_VV->Integral(0,3) > 0 ) norm = 60000. / e3_VV->Integral(0,3);
 g3_VV = (TH1F*)gROOT->FindObject(htitleB);
 g3_VV->Sumw2();
 h_VV->Add(g3_VV, h_VV, xsec_VV[2]*norm, 1);

 f1_TTV->cd();
 e1_TVV = (TH1F*)gROOT->FindObject("hData_Filter");
 e1_TVV->Sumw2();
 norm = 0.;
 if  ( e1_TVV->Integral(0,3) > 0 ) norm = 60000. / e1_TVV->Integral(0,3);
 g1_TTV = (TH1F*)gROOT->FindObject(htitleB);
 g1_TVV->Sumw2();
 h_TTV = new TH1F("h_TTV","",nbin,xmin,xmax);
 h_TTV->Add(g1_TTV, h_TTV, xsec_TTV[0]*norm,0);

 f2_TTV->cd();
 e2_TVV = (TH1F*)gROOT->FindObject("hData_Filter");
 e2_TVV->Sumw2();
 norm = 0.;
 if  ( e2_TVV->Integral(0,3) > 0 ) norm = 60000. / e2_TVV->Integral(0,3);
 g2_TTV = (TH1F*)gROOT->FindObject(htitleB);
 g2_TVV->Sumw2();
 h_TTV->Add(g2_TTV, h_TTV, xsec_TTV[1]*norm, 1);

 f3_TTV->cd();
 e3_TVV = (TH1F*)gROOT->FindObject("hData_Filter");
 e3_TVV->Sumw2();
 norm = 0.;
 if  ( e3_TVV->Integral(0,3) > 0 ) norm = 60000. / e3_TVV->Integral(0,3);
 g3_TTV = (TH1F*)gROOT->FindObject(htitleB);
 g3_TVV->Sumw2();
 h_TTV->Add(g3_TTV, h_TTV, xsec_TTV[2]*norm, 1);

 f1_ST->cd();
 e1_ST = (TH1F*)gROOT->FindObject("hData_Filter");
 e1_ST->Sumw2();
 norm = 0.;
 if  ( e1_ST->Integral(0,3) > 0 ) norm = 60000. / e1_ST->Integral(0,3);
 g1_ST = (TH1F*)gROOT->FindObject(htitleB);
 g1_ST->Sumw2();
 h_ST = new TH1F("h_ST","",nbin,xmin,xmax);
 h_ST->Add(g1_ST, h_ST, xsec_ST[0]*norm,0);

 f2_ST->cd();
 e2_ST = (TH1F*)gROOT->FindObject("hData_Filter");
 e2_ST->Sumw2();
 norm = 0.;
 if  ( e2_ST->Integral(0,3) > 0 ) norm = 60000. / e2_ST->Integral(0,3);
 g2_ST = (TH1F*)gROOT->FindObject(htitleB);
 g2_ST->Sumw2();
 h_ST->Add(g2_ST, h_ST, xsec_ST[1]*norm, 1);

 f1_TT->cd();
 e1_TT = (TH1F*)gROOT->FindObject("hData_Filter");
 e1_TT->Sumw2();
 norm = 0.;
 if  ( e1_TT->Integral(0,3) > 0 ) norm = 60000. / e1_TT->Integral(0,3);
 g1_TT = (TH1F*)gROOT->FindObject(htitleB);
 g1_TT->Sumw2();
 h_TT = new TH1F("h_TT","",nbin,xmin,xmax);
 h_TT->Add(g1_TT, h_TT, xsec_TT[0]*norm,0);

 htot->Add(htot, h_DY, 1, 1);
 htot->Add(htot, h_VV, 1, 1);
 htot->Add(htot, h_TTV, 1, 1);
 htot->Add(htot, h_ST, 1, 1);
 htot->Add(htot, h_TT, 1, 1);

 h_VV->Add(h_VV, h_TTV, 1, 1);
 h_VV->Add(h_VV, h_ST, 1, 1);
 h_VV->Add(h_VV, h_TT, 1, 1);

 h_TTV->Add(h_TTV, h_ST, 1, 1);
 h_TTV->Add(h_TTV, h_TT, 1, 1);

 h_ST->Add(h_ST, h_TT, 1, 1);

 htot->Draw("HE"); 
 htot->SetFillColor(kGreen-6);
 htot->SetLineColor(kGreen-6);
 htot->SetLineStyle(1);
 htot->SetLineWidth(3);
 htot->SetTickLength(0.03, "YZ");
 htot->SetTickLength(0.03,"X");
 htot->SetLabelOffset(0.015,"X");
 htot->SetLabelOffset(0.007,"Y");
 htot->SetLabelSize(0.045, "XYZ");
 htot->SetLabelFont(42, "XYZ"); 
 htot->SetTitleSize(0.045, "XYZ"); 
 htot->SetTitleFont(42, "XYZ");
 htot->SetTitleOffset(1.2,"X"); 
 htot->SetTitleOffset(1.3,"Y");
 htot->GetXaxis()->SetTitle(xtitle);
 htot->GetXaxis()->SetTitleColor(1);
 htot->GetYaxis()->SetTitle(ytitle);
 htot->GetYaxis()->SetTitleColor(1);
 htot->SetNdivisions(509,"XYZ");
 htot->SetMinimum(1.); 
 htot->SetMaximum(hmax); 

 h_VV->Draw("HEsame"); 
 h_VV->SetFillColor(kOrange-2);
 h_VV->SetLineColor(kOrange-2);
 h_VV->SetLineStyle(1);
 h_VV->SetLineWidth(3);

 h_TTV->Draw("HEsame"); 
 h_TTV->SetFillColor(kAzure+4);
 h_TTV->SetLineColor(kAzure+4);
 h_TTV->SetLineStyle(1);
 h_TTV->SetLineWidth(3);

 h_ST->Draw("HEsame"); 
 h_ST->SetFillColor(kAzure+2);
 h_ST->SetLineColor(kAzure+2);
 h_ST->SetLineStyle(1);
 h_ST->SetLineWidth(3);

 h_TT->Draw("HEsame"); 
 h_TT->SetFillColor(kAzure+1);
 h_TT->SetLineColor(kAzure+1);
 h_TT->SetLineStyle(1);
 h_TT->SetLineWidth(3);
 h_TT->SetTickLength(0.03, "YZ");
 h_TT->SetTickLength(0.03,"X");

 f1_LLP->cd();
 e1_LLP = (TH1F*)gROOT->FindObject("hData_Filter");
 e1_LLP->Sumw2();
 norm = 0.;
 if ( e1_LLP->Integral(0,3) > 0. ) norm = SigXsec1*60000. / e1_LLP->Integral(0,3);
 g1_LLP = (TH1F*)gROOT->FindObject(htitleB);
 g1_LLP->Sumw2();
 h1_LLP = new TH1F("h1_LLP","",nbin,xmin,xmax);
 h1_LLP->Add(g1_LLP, h1_LLP, 0.001*norm,0);

 f2_LLP->cd();
 e2_LLP = (TH1F*)gROOT->FindObject("hData_Filter");
 e2_LLP->Sumw2();
 norm = 0.;
 if ( e2_LLP->Integral(0,3) > 0. ) norm = SigXsec2*60000. / e2_LLP->Integral(0,3);
 g2_LLP = (TH1F*)gROOT->FindObject(htitleB);
 g2_LLP->Sumw2();
 h2_LLP = new TH1F("h2_LLP","",nbin,xmin,xmax);
 h2_LLP->Add(g2_LLP, h2_LLP, 0.001*norm,0);

 f3_LLP->cd();
 e3_LLP = (TH1F*)gROOT->FindObject("hData_Filter");
 e3_LLP->Sumw2();
 norm = 0.;
 if ( e3_LLP->Integral(0,3) > 0. ) norm = SigXsec3*60000. / e3_LLP->Integral(0,3);
 g3_LLP = (TH1F*)gROOT->FindObject(htitleB);
 g3_LLP->Sumw2();
 h3_LLP = new TH1F("h3_LLP","",nbin,xmin,xmax);
 h3_LLP->Add(g3_LLP, h3_LLP, 0.001*norm,0);

//            f4_LLP->cd();
//      TH1F* e4_LLP = (TH1F*)gROOT->FindObject("hData_Filter");
//            e4_LLP->Sumw2();
// 	   norm = 0.;
// 	   if ( e4_LLP->Integral(0,3) > 0. ) norm = SigXsec4*60000. / e4_LLP->Integral(0,3);
//      TH1F* g4_LLP = (TH1F*)gROOT->FindObject(htitleB);
//            g4_LLP->Sumw2();
//      TH1F* h4_LLP = new TH1F("h4_LLP","",nbin,xmin,xmax);
//            h4_LLP->Add(g4_LLP, h4_LLP, 0.001*norm,0);

 h1_LLP->Draw("HEsame"); 
 h1_LLP->SetLineColor(kRed-1);
 h1_LLP->SetLineStyle(1);
 h1_LLP->SetLineWidth(2);

 h2_LLP->Draw("HEsame"); 
 h2_LLP->SetLineColor(kRed-2);
 h2_LLP->SetLineStyle(2);
 h2_LLP->SetLineWidth(2);

 h3_LLP->Draw("HEsame");
 h3_LLP->SetLineColor(kRed-3);
 h3_LLP->SetLineStyle(3);
 h3_LLP->SetLineWidth(2);

//  h4_LLP->Draw("HEsame"); 
//  h4_LLP->SetLineColor(kRed-4);
//  h4_LLP->SetLineStyle(2);
//  h4_LLP->SetLineWidth(4);

//  e1_LLP->Draw("HEsame"); 
//  e1_LLP->SetLineColor(kWhite);
//  e1_LLP->SetLineStyle(1);
//  e1_LLP->SetLineWidth(3);

  leg = new TLegend(0.17,0.93,0.50,0.98);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->SetTextFont(42);
  leg->SetTextSize(0.05);
  leg->SetHeader("simulation 2018, 60 fb^{-1} (13 TeV)");
  leg->Draw();

  leg = new TLegend(0.53,0.50,0.85,0.89);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->SetTextFont(42);
  leg->SetTextSize(0.035);
  leg->AddEntry(htot, " DY","F");
  leg->AddEntry(h_VV, " WW, WZ, ZZ","F");
  leg->AddEntry(h_TTV," t#bar{t}W, t#bar{t}Z, t#bar{t}WW","F");
  leg->AddEntry(h_ST, " tW","F");
  leg->AddEntry(h_TT, " t#bar{t}","F");
  leg->AddEntry(h1_LLP," m_{#tilde{#mu} (#tilde{#chi}^{0})} = 250 (200) GeV","L");
  leg->AddEntry(h2_LLP," m_{#tilde{#mu} (#tilde{#chi}^{0})} = 300 (250) GeV","L");
  leg->AddEntry(h3_LLP," m_{#tilde{#mu} (#tilde{#chi}^{0})} = 400 (300) GeV","L");
//   leg->AddEntry(h4_LLP,"Signal, m_{#tilde{#mu}}= 500 GeV, m_{#tilde{#chi}^{0}}= 350 GeV","L");
  leg->Draw();

  leg = new TLegend(0.18,0.85,0.45,0.89);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->SetTextFont(42);
  leg->SetTextSize(0.04);
  leg->SetHeader(" 2 tight vertices");
  leg->Draw();
  leg = new TLegend(0.18,0.80,0.45,0.84);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->SetTextFont(42);
  leg->SetTextSize(0.04);
  leg->SetHeader(" hem. p_{T} > 80 GeV");
  leg->Draw();

// *****************************************************************************

 pad3->cd();

 htot = new TH1F("htot","",nbin,xmin,xmax);
 hmax = 1E5; 

 f1_DY->cd();
 e1_DY = (TH1F*)gROOT->FindObject("hData_Filter");
 e1_DY->Sumw2();
 norm = 0.;
 if  ( e1_DY->Integral(0,3) > 0 ) norm = 60000. / e1_DY->Integral(0,3);
 g1_DY = (TH1F*)gROOT->FindObject(htitleC);
 g1_DY->Sumw2();
 h_DY = new TH1F("h_DY","",nbin,xmin,xmax);
 h_DY->Add(g1_DY, h_DY, xsec_DY[0]*norm,0);

 f2_DY->cd();
 e2_DY = (TH1F*)gROOT->FindObject("hData_Filter");
 e2_DY->Sumw2();
 norm = 0.;
 if  ( e2_DY->Integral(0,3) > 0 ) norm = 60000. / e2_DY->Integral(0,3);
 g2_DY = (TH1F*)gROOT->FindObject(htitleC);
 g2_DY->Sumw2();
 h_DY->Add(g2_DY, h_DY, xsec_DY[1]*norm, 1);

 f1_VV->cd();
 e1_VV = (TH1F*)gROOT->FindObject("hData_Filter");
 e1_VV->Sumw2();
 norm = 0.;
 if  ( e1_VV->Integral(0,3) > 0 ) norm = 60000. / e1_VV->Integral(0,3);
 g1_VV = (TH1F*)gROOT->FindObject(htitleC);
 g1_VV->Sumw2();
 h_VV = new TH1F("h_VV","",nbin,xmin,xmax);
 h_VV->Add(g1_VV, h_VV, xsec_VV[0]*norm,0);

 f2_VV->cd();
 e2_VV = (TH1F*)gROOT->FindObject("hData_Filter");
 e2_VV->Sumw2();
 norm = 0.;
 if  ( e2_VV->Integral(0,3) > 0 ) norm = 60000. / e2_VV->Integral(0,3);
 g2_VV = (TH1F*)gROOT->FindObject(htitleC);
 g2_VV->Sumw2();
 h_VV->Add(g2_VV, h_VV, xsec_VV[1]*norm, 1);

 f3_VV->cd();
 e3_VV = (TH1F*)gROOT->FindObject("hData_Filter");
 e3_VV->Sumw2();
 norm = 0.;
 if  ( e3_VV->Integral(0,3) > 0 ) norm = 60000. / e3_VV->Integral(0,3);
 g3_VV = (TH1F*)gROOT->FindObject(htitleC);
 g3_VV->Sumw2();
 h_VV->Add(g3_VV, h_VV, xsec_VV[2]*norm, 1);

 f1_TTV->cd();
 e1_TVV = (TH1F*)gROOT->FindObject("hData_Filter");
 e1_TVV->Sumw2();
 norm = 0.;
 if  ( e1_TVV->Integral(0,3) > 0 ) norm = 60000. / e1_TVV->Integral(0,3);
 g1_TTV = (TH1F*)gROOT->FindObject(htitleC);
 g1_TVV->Sumw2();
 h_TTV = new TH1F("h_TTV","",nbin,xmin,xmax);
 h_TTV->Add(g1_TTV, h_TTV, xsec_TTV[0]*norm,0);

 f2_TTV->cd();
 e2_TVV = (TH1F*)gROOT->FindObject("hData_Filter");
 e2_TVV->Sumw2();
 norm = 0.;
 if  ( e2_TVV->Integral(0,3) > 0 ) norm = 60000. / e2_TVV->Integral(0,3);
 g2_TTV = (TH1F*)gROOT->FindObject(htitleC);
 g2_TVV->Sumw2();
 h_TTV->Add(g2_TTV, h_TTV, xsec_TTV[1]*norm, 1);

 f3_TTV->cd();
 e3_TVV = (TH1F*)gROOT->FindObject("hData_Filter");
 e3_TVV->Sumw2();
 norm = 0.;
 if  ( e3_TVV->Integral(0,3) > 0 ) norm = 60000. / e3_TVV->Integral(0,3);
 g3_TTV = (TH1F*)gROOT->FindObject(htitleC);
 g3_TVV->Sumw2();
 h_TTV->Add(g3_TTV, h_TTV, xsec_TTV[2]*norm, 1);

 f1_ST->cd();
 e1_ST = (TH1F*)gROOT->FindObject("hData_Filter");
 e1_ST->Sumw2();
 norm = 0.;
 if  ( e1_ST->Integral(0,3) > 0 ) norm = 60000. / e1_ST->Integral(0,3);
 g1_ST = (TH1F*)gROOT->FindObject(htitleC);
 g1_ST->Sumw2();
 h_ST = new TH1F("h_ST","",nbin,xmin,xmax);
 h_ST->Add(g1_ST, h_ST, xsec_ST[0]*norm,0);

 f2_ST->cd();
 e2_ST = (TH1F*)gROOT->FindObject("hData_Filter");
 e2_ST->Sumw2();
 norm = 0.;
 if  ( e2_ST->Integral(0,3) > 0 ) norm = 60000. / e2_ST->Integral(0,3);
 g2_ST = (TH1F*)gROOT->FindObject(htitleC);
 g2_ST->Sumw2();
 h_ST->Add(g2_ST, h_ST, xsec_ST[1]*norm, 1);

 f1_TT->cd();
 e1_TT = (TH1F*)gROOT->FindObject("hData_Filter");
 e1_TT->Sumw2();
 norm = 0.;
 if  ( e1_TT->Integral(0,3) > 0 ) norm = 60000. / e1_TT->Integral(0,3);
 g1_TT = (TH1F*)gROOT->FindObject(htitleC);
 g1_TT->Sumw2();
 h_TT = new TH1F("h_TT","",nbin,xmin,xmax);
 h_TT->Add(g1_TT, h_TT, xsec_TT[0]*norm,0);

 htot->Add(htot, h_DY, 1, 1);
 htot->Add(htot, h_VV, 1, 1);
 htot->Add(htot, h_TTV, 1, 1);
 htot->Add(htot, h_ST, 1, 1);
 htot->Add(htot, h_TT, 1, 1);

 h_VV->Add(h_VV, h_TTV, 1, 1);
 h_VV->Add(h_VV, h_ST, 1, 1);
 h_VV->Add(h_VV, h_TT, 1, 1);

 h_TTV->Add(h_TTV, h_ST, 1, 1);
 h_TTV->Add(h_TTV, h_TT, 1, 1);

 h_ST->Add(h_ST, h_TT, 1, 1);

 htot->Draw("HE"); 
 htot->SetFillColor(kGreen-6);
 htot->SetLineColor(kGreen-6);
 htot->SetLineStyle(1);
 htot->SetLineWidth(3);
 htot->SetTickLength(0.03, "YZ");
 htot->SetTickLength(0.03,"X");
 htot->SetLabelOffset(0.015,"X");
 htot->SetLabelOffset(0.007,"Y");
 htot->SetLabelSize(0.045, "XYZ");
 htot->SetLabelFont(42, "XYZ"); 
 htot->SetTitleSize(0.045, "XYZ"); 
 htot->SetTitleFont(42, "XYZ");
 htot->SetTitleOffset(1.2,"X"); 
 htot->SetTitleOffset(1.3,"Y");
 htot->GetXaxis()->SetTitle(xtitle);
 htot->GetXaxis()->SetTitleColor(1);
 htot->GetYaxis()->SetTitle(ytitle);
 htot->GetYaxis()->SetTitleColor(1);
 htot->SetNdivisions(509,"XYZ");
 htot->SetMinimum(1.); 
 htot->SetMaximum(hmax); 

 h_VV->Draw("HEsame"); 
 h_VV->SetFillColor(kOrange-2);
 h_VV->SetLineColor(kOrange-2);
 h_VV->SetLineStyle(1);
 h_VV->SetLineWidth(3);

 h_TTV->Draw("HEsame"); 
 h_TTV->SetFillColor(kAzure+4);
 h_TTV->SetLineColor(kAzure+4);
 h_TTV->SetLineStyle(1);
 h_TTV->SetLineWidth(3);

 h_ST->Draw("HEsame"); 
 h_ST->SetFillColor(kAzure+2);
 h_ST->SetLineColor(kAzure+2);
 h_ST->SetLineStyle(1);
 h_ST->SetLineWidth(3);

 h_TT->Draw("HEsame"); 
 h_TT->SetFillColor(kAzure+1);
 h_TT->SetLineColor(kAzure+1);
 h_TT->SetLineStyle(1);
 h_TT->SetLineWidth(3);
 h_TT->SetTickLength(0.03, "YZ");
 h_TT->SetTickLength(0.03,"X");

 f1_LLP->cd();
 e1_LLP = (TH1F*)gROOT->FindObject("hData_Filter");
 e1_LLP->Sumw2();
 norm = 0.;
 if ( e1_LLP->Integral(0,3) > 0. ) norm = SigXsec1*60000. / e1_LLP->Integral(0,3);
 g1_LLP = (TH1F*)gROOT->FindObject(htitleC);
 g1_LLP->Sumw2();
 h1_LLP = new TH1F("h1_LLP","",nbin,xmin,xmax);
 h1_LLP->Add(g1_LLP, h1_LLP, 0.001*norm,0);

 f2_LLP->cd();
 e2_LLP = (TH1F*)gROOT->FindObject("hData_Filter");
 e2_LLP->Sumw2();
 norm = 0.;
 if ( e2_LLP->Integral(0,3) > 0. ) norm = SigXsec2*60000. / e2_LLP->Integral(0,3);
 g2_LLP = (TH1F*)gROOT->FindObject(htitleC);
 g2_LLP->Sumw2();
 h2_LLP = new TH1F("h2_LLP","",nbin,xmin,xmax);
 h2_LLP->Add(g2_LLP, h2_LLP, 0.001*norm,0);

 f3_LLP->cd();
 e3_LLP = (TH1F*)gROOT->FindObject("hData_Filter");
 e3_LLP->Sumw2();
 norm = 0.;
 if ( e3_LLP->Integral(0,3) > 0. ) norm = SigXsec3*60000. / e3_LLP->Integral(0,3);
 g3_LLP = (TH1F*)gROOT->FindObject(htitleC);
 g3_LLP->Sumw2();
 h3_LLP = new TH1F("h3_LLP","",nbin,xmin,xmax);
 h3_LLP->Add(g3_LLP, h3_LLP, 0.001*norm,0);

//            f4_LLP->cd();
//      TH1F* e4_LLP = (TH1F*)gROOT->FindObject("hData_Filter");
//            e4_LLP->Sumw2();
// 	   norm = 0.;
// 	   if ( e4_LLP->Integral(0,3) > 0. ) norm = SigXsec4*60000. / e4_LLP->Integral(0,3);
//      TH1F* g4_LLP = (TH1F*)gROOT->FindObject(htitleC);
//            g4_LLP->Sumw2();
//      TH1F* h4_LLP = new TH1F("h4_LLP","",nbin,xmin,xmax);
//            h4_LLP->Add(g4_LLP, h4_LLP, 0.001*norm,0);

 h1_LLP->Draw("HEsame"); 
 h1_LLP->SetLineColor(kRed-1);
 h1_LLP->SetLineStyle(1);
 h1_LLP->SetLineWidth(2);

 h2_LLP->Draw("HEsame"); 
 h2_LLP->SetLineColor(kRed-2);
 h2_LLP->SetLineStyle(2);
 h2_LLP->SetLineWidth(2);

 h3_LLP->Draw("HEsame");
 h3_LLP->SetLineColor(kRed-3);
 h3_LLP->SetLineStyle(3);
 h3_LLP->SetLineWidth(2);

//  h4_LLP->Draw("HEsame"); 
//  h4_LLP->SetLineColor(kRed-4);
//  h4_LLP->SetLineStyle(2);
//  h4_LLP->SetLineWidth(4);

//  e1_LLP->Draw("HEsame"); 
//  e1_LLP->SetLineColor(kWhite);
//  e1_LLP->SetLineStyle(1);
//  e1_LLP->SetLineWidth(3);

  leg = new TLegend(0.17,0.93,0.50,0.98);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->SetTextFont(42);
  leg->SetTextSize(0.05);
  leg->SetHeader("simulation 2018, 60 fb^{-1} (13 TeV)");
  leg->Draw();

  leg = new TLegend(0.53,0.50,0.85,0.89);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->SetTextFont(42);
  leg->SetTextSize(0.035);
  leg->AddEntry(htot, " DY","F");
  leg->AddEntry(h_VV, " WW, WZ, ZZ","F");
  leg->AddEntry(h_TTV," t#bar{t}W, t#bar{t}Z, t#bar{t}WW","F");
  leg->AddEntry(h_ST, " tW","F");
  leg->AddEntry(h_TT, " t#bar{t}","F");
  leg->AddEntry(h1_LLP," m_{#tilde{#mu} (#tilde{#chi}^{0})} = 250 (200) GeV","L");
  leg->AddEntry(h2_LLP," m_{#tilde{#mu} (#tilde{#chi}^{0})} = 300 (250) GeV","L");
  leg->AddEntry(h3_LLP," m_{#tilde{#mu} (#tilde{#chi}^{0})} = 400 (300) GeV","L");
//   leg->AddEntry(h4_LLP,"Signal, m_{#tilde{#mu}}= 500 GeV, m_{#tilde{#chi}^{0}}= 350 GeV","L");
  leg->Draw();

  leg = new TLegend(0.18,0.85,0.45,0.89);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->SetTextFont(42);
  leg->SetTextSize(0.04);
  leg->SetHeader(" 2 loose vertices");
  leg->Draw();
  leg = new TLegend(0.18,0.80,0.45,0.84);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->SetTextFont(42);
  leg->SetTextSize(0.04);
  leg->SetHeader(" #geq1 hem. p_{T} 40-80 GeV");
  leg->Draw();

// *****************************************************************************

 pad4->cd();

 htot = new TH1F("htot","",nbin,xmin,xmax);
 hmax = 1E5; 

 f1_DY->cd();
 e1_DY = (TH1F*)gROOT->FindObject("hData_Filter");
 e1_DY->Sumw2();
 norm = 0.;
 if  ( e1_DY->Integral(0,3) > 0 ) norm = 60000. / e1_DY->Integral(0,3);
 g1_DY = (TH1F*)gROOT->FindObject(htitleD);
 g1_DY->Sumw2();
 h_DY = new TH1F("h_DY","",nbin,xmin,xmax);
 h_DY->Add(g1_DY, h_DY, xsec_DY[0]*norm,0);

 f2_DY->cd();
 e2_DY = (TH1F*)gROOT->FindObject("hData_Filter");
 e2_DY->Sumw2();
 norm = 0.;
 if  ( e2_DY->Integral(0,3) > 0 ) norm = 60000. / e2_DY->Integral(0,3);
 g2_DY = (TH1F*)gROOT->FindObject(htitleD);
 g2_DY->Sumw2();
 h_DY->Add(g2_DY, h_DY, xsec_DY[1]*norm, 1);

 f1_VV->cd();
 e1_VV = (TH1F*)gROOT->FindObject("hData_Filter");
 e1_VV->Sumw2();
 norm = 0.;
 if  ( e1_VV->Integral(0,3) > 0 ) norm = 60000. / e1_VV->Integral(0,3);
 g1_VV = (TH1F*)gROOT->FindObject(htitleD);
 g1_VV->Sumw2();
 h_VV = new TH1F("h_VV","",nbin,xmin,xmax);
 h_VV->Add(g1_VV, h_VV, xsec_VV[0]*norm,0);

 f2_VV->cd();
 e2_VV = (TH1F*)gROOT->FindObject("hData_Filter");
 e2_VV->Sumw2();
 norm = 0.;
 if  ( e2_VV->Integral(0,3) > 0 ) norm = 60000. / e2_VV->Integral(0,3);
 g2_VV = (TH1F*)gROOT->FindObject(htitleD);
 g2_VV->Sumw2();
 h_VV->Add(g2_VV, h_VV, xsec_VV[1]*norm, 1);

 f3_VV->cd();
 e3_VV = (TH1F*)gROOT->FindObject("hData_Filter");
 e3_VV->Sumw2();
 norm = 0.;
 if  ( e3_VV->Integral(0,3) > 0 ) norm = 60000. / e3_VV->Integral(0,3);
 g3_VV = (TH1F*)gROOT->FindObject(htitleD);
 g3_VV->Sumw2();
 h_VV->Add(g3_VV, h_VV, xsec_VV[2]*norm, 1);

 f1_TTV->cd();
 e1_TVV = (TH1F*)gROOT->FindObject("hData_Filter");
 e1_TVV->Sumw2();
 norm = 0.;
 if  ( e1_TVV->Integral(0,3) > 0 ) norm = 60000. / e1_TVV->Integral(0,3);
 g1_TTV = (TH1F*)gROOT->FindObject(htitleD);
 g1_TVV->Sumw2();
 h_TTV = new TH1F("h_TTV","",nbin,xmin,xmax);
 h_TTV->Add(g1_TTV, h_TTV, xsec_TTV[0]*norm,0);

 f2_TTV->cd();
 e2_TVV = (TH1F*)gROOT->FindObject("hData_Filter");
 e2_TVV->Sumw2();
 norm = 0.;
 if  ( e2_TVV->Integral(0,3) > 0 ) norm = 60000. / e2_TVV->Integral(0,3);
 g2_TTV = (TH1F*)gROOT->FindObject(htitleD);
 g2_TVV->Sumw2();
 h_TTV->Add(g2_TTV, h_TTV, xsec_TTV[1]*norm, 1);

 f3_TTV->cd();
 e3_TVV = (TH1F*)gROOT->FindObject("hData_Filter");
 e3_TVV->Sumw2();
 norm = 0.;
 if  ( e3_TVV->Integral(0,3) > 0 ) norm = 60000. / e3_TVV->Integral(0,3);
 g3_TTV = (TH1F*)gROOT->FindObject(htitleD);
 g3_TVV->Sumw2();
 h_TTV->Add(g3_TTV, h_TTV, xsec_TTV[2]*norm, 1);

 f1_ST->cd();
 e1_ST = (TH1F*)gROOT->FindObject("hData_Filter");
 e1_ST->Sumw2();
 norm = 0.;
 if  ( e1_ST->Integral(0,3) > 0 ) norm = 60000. / e1_ST->Integral(0,3);
 g1_ST = (TH1F*)gROOT->FindObject(htitleD);
 g1_ST->Sumw2();
 h_ST = new TH1F("h_ST","",nbin,xmin,xmax);
 h_ST->Add(g1_ST, h_ST, xsec_ST[0]*norm,0);

 f2_ST->cd();
 e2_ST = (TH1F*)gROOT->FindObject("hData_Filter");
 e2_ST->Sumw2();
 norm = 0.;
 if  ( e2_ST->Integral(0,3) > 0 ) norm = 60000. / e2_ST->Integral(0,3);
 g2_ST = (TH1F*)gROOT->FindObject(htitleD);
 g2_ST->Sumw2();
 h_ST->Add(g2_ST, h_ST, xsec_ST[1]*norm, 1);

 f1_TT->cd();
 e1_TT = (TH1F*)gROOT->FindObject("hData_Filter");
 e1_TT->Sumw2();
 norm = 0.;
 if  ( e1_TT->Integral(0,3) > 0 ) norm = 60000. / e1_TT->Integral(0,3);
 g1_TT = (TH1F*)gROOT->FindObject(htitleD);
 g1_TT->Sumw2();
 h_TT = new TH1F("h_TT","",nbin,xmin,xmax);
 h_TT->Add(g1_TT, h_TT, xsec_TT[0]*norm,0);

 htot->Add(htot, h_DY, 1, 1);
 htot->Add(htot, h_VV, 1, 1);
 htot->Add(htot, h_TTV, 1, 1);
 htot->Add(htot, h_ST, 1, 1);
 htot->Add(htot, h_TT, 1, 1);

 h_VV->Add(h_VV, h_TTV, 1, 1);
 h_VV->Add(h_VV, h_ST, 1, 1);
 h_VV->Add(h_VV, h_TT, 1, 1);

 h_TTV->Add(h_TTV, h_ST, 1, 1);
 h_TTV->Add(h_TTV, h_TT, 1, 1);

 h_ST->Add(h_ST, h_TT, 1, 1);

 htot->Draw("HE"); 
 htot->SetFillColor(kGreen-6);
 htot->SetLineColor(kGreen-6);
 htot->SetLineStyle(1);
 htot->SetLineWidth(3);
 htot->SetTickLength(0.03, "YZ");
 htot->SetTickLength(0.03,"X");
 htot->SetLabelOffset(0.015,"X");
 htot->SetLabelOffset(0.007,"Y");
 htot->SetLabelSize(0.045, "XYZ");
 htot->SetLabelFont(42, "XYZ"); 
 htot->SetTitleSize(0.045, "XYZ"); 
 htot->SetTitleFont(42, "XYZ");
 htot->SetTitleOffset(1.2,"X"); 
 htot->SetTitleOffset(1.3,"Y");
 htot->GetXaxis()->SetTitle(xtitle);
 htot->GetXaxis()->SetTitleColor(1);
 htot->GetYaxis()->SetTitle(ytitle);
 htot->GetYaxis()->SetTitleColor(1);
 htot->SetNdivisions(509,"XYZ");
 htot->SetMinimum(1.); 
 htot->SetMaximum(hmax); 

 h_VV->Draw("HEsame"); 
 h_VV->SetFillColor(kOrange-2);
 h_VV->SetLineColor(kOrange-2);
 h_VV->SetLineStyle(1);
 h_VV->SetLineWidth(3);

 h_TTV->Draw("HEsame"); 
 h_TTV->SetFillColor(kAzure+4);
 h_TTV->SetLineColor(kAzure+4);
 h_TTV->SetLineStyle(1);
 h_TTV->SetLineWidth(3);

 h_ST->Draw("HEsame"); 
 h_ST->SetFillColor(kAzure+2);
 h_ST->SetLineColor(kAzure+2);
 h_ST->SetLineStyle(1);
 h_ST->SetLineWidth(3);

 h_TT->Draw("HEsame"); 
 h_TT->SetFillColor(kAzure+1);
 h_TT->SetLineColor(kAzure+1);
 h_TT->SetLineStyle(1);
 h_TT->SetLineWidth(3);
 h_TT->SetTickLength(0.03, "YZ");
 h_TT->SetTickLength(0.03,"X");

 f1_LLP->cd();
 e1_LLP = (TH1F*)gROOT->FindObject("hData_Filter");
 e1_LLP->Sumw2();
 norm = 0.;
 if ( e1_LLP->Integral(0,3) > 0. ) norm = SigXsec1*60000. / e1_LLP->Integral(0,3);
 g1_LLP = (TH1F*)gROOT->FindObject(htitleD);
 g1_LLP->Sumw2();
 h1_LLP = new TH1F("h1_LLP","",nbin,xmin,xmax);
 h1_LLP->Add(g1_LLP, h1_LLP, 0.001*norm,0);

 f2_LLP->cd();
 e2_LLP = (TH1F*)gROOT->FindObject("hData_Filter");
 e2_LLP->Sumw2();
 norm = 0.;
 if ( e2_LLP->Integral(0,3) > 0. ) norm = SigXsec2*60000. / e2_LLP->Integral(0,3);
 g2_LLP = (TH1F*)gROOT->FindObject(htitleD);
 g2_LLP->Sumw2();
 h2_LLP = new TH1F("h2_LLP","",nbin,xmin,xmax);
 h2_LLP->Add(g2_LLP, h2_LLP, 0.001*norm,0);

 f3_LLP->cd();
 e3_LLP = (TH1F*)gROOT->FindObject("hData_Filter");
 e3_LLP->Sumw2();
 norm = 0.;
 if ( e3_LLP->Integral(0,3) > 0. ) norm = SigXsec3*60000. / e3_LLP->Integral(0,3);
 g3_LLP = (TH1F*)gROOT->FindObject(htitleD);
 g3_LLP->Sumw2();
 h3_LLP = new TH1F("h3_LLP","",nbin,xmin,xmax);
 h3_LLP->Add(g3_LLP, h3_LLP, 0.001*norm,0);

//            f4_LLP->cd();
//      TH1F* e4_LLP = (TH1F*)gROOT->FindObject("hData_Filter");
//            e4_LLP->Sumw2();
// 	   norm = 0.;
// 	   if ( e4_LLP->Integral(0,3) > 0. ) norm = SigXsec4*60000. / e4_LLP->Integral(0,3);
//      TH1F* g4_LLP = (TH1F*)gROOT->FindObject(htitleD);
//            g4_LLP->Sumw2();
//      TH1F* h4_LLP = new TH1F("h4_LLP","",nbin,xmin,xmax);
//            h4_LLP->Add(g4_LLP, h4_LLP, 0.001*norm,0);

 h1_LLP->Draw("HEsame"); 
 h1_LLP->SetLineColor(kRed-1);
 h1_LLP->SetLineStyle(1);
 h1_LLP->SetLineWidth(2);

 h2_LLP->Draw("HEsame"); 
 h2_LLP->SetLineColor(kRed-2);
 h2_LLP->SetLineStyle(2);
 h2_LLP->SetLineWidth(2);

 h3_LLP->Draw("HEsame");
 h3_LLP->SetLineColor(kRed-3);
 h3_LLP->SetLineStyle(3);
 h3_LLP->SetLineWidth(2);

//  h4_LLP->Draw("HEsame"); 
//  h4_LLP->SetLineColor(kRed-4);
//  h4_LLP->SetLineStyle(2);
//  h4_LLP->SetLineWidth(4);

//  e1_LLP->Draw("HEsame"); 
//  e1_LLP->SetLineColor(kWhite);
//  e1_LLP->SetLineStyle(1);
//  e1_LLP->SetLineWidth(3);

  leg = new TLegend(0.17,0.93,0.50,0.98);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->SetTextFont(42);
  leg->SetTextSize(0.05);
  leg->SetHeader("simulation 2018, 60 fb^{-1} (13 TeV)");
  leg->Draw();

  leg = new TLegend(0.53,0.50,0.85,0.89);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->SetTextFont(42);
  leg->SetTextSize(0.035);
  leg->AddEntry(htot, " DY","F");
  leg->AddEntry(h_VV, " WW, WZ, ZZ","F");
  leg->AddEntry(h_TTV," t#bar{t}W, t#bar{t}Z, t#bar{t}WW","F");
  leg->AddEntry(h_ST, " tW","F");
  leg->AddEntry(h_TT, " t#bar{t}","F");
  leg->AddEntry(h1_LLP," m_{#tilde{#mu} (#tilde{#chi}^{0})} = 250 (200) GeV","L");
  leg->AddEntry(h2_LLP," m_{#tilde{#mu} (#tilde{#chi}^{0})} = 300 (250) GeV","L");
  leg->AddEntry(h3_LLP," m_{#tilde{#mu} (#tilde{#chi}^{0})} = 400 (300) GeV","L");
//   leg->AddEntry(h4_LLP,"Signal, m_{#tilde{#mu}}= 500 GeV, m_{#tilde{#chi}^{0}}= 350 GeV","L");
  leg->Draw();

  leg = new TLegend(0.18,0.85,0.45,0.89);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->SetTextFont(42);
  leg->SetTextSize(0.04);
  leg->SetHeader(" 2 tight vertices");
  leg->Draw();
  leg = new TLegend(0.18,0.80,0.45,0.84);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->SetTextFont(42);
  leg->SetTextSize(0.04);
  leg->SetHeader(" #geq1 hem. p_{T} 40-80 GeV");
  leg->Draw();

// *****************************************************************************

  c1->Update();
}