#include <iostream>
#include <TROOT.h>
#include "TH1.h"

void plot()
{
int stati=0;
bool fit= 1;
bool logy=1;

//$$
// number of vertices: -1 all filtered event, 1 vertex, 2 vertices
  int nvtx = 1;
//   float hmax = 2E8;  
  float hmax = 1E8;              // for eta<2.4 pt>60  
//   float hmax = 2E7;              // for eta<2.0 pt>80   
  if ( nvtx == 1 ) hmax = 1E6;  
  if ( nvtx == 2 ) hmax = 1E5;  
//   if ( nvtx == 1 ) hmax = 1E7;  // for CRloose
//   if ( nvtx == 2 ) hmax = 1E5;  // for CRloose  
//   float hmax = 1E5;             // for SameSign 
//   if ( nvtx == 1 ) hmax = 1E2;  // for SameSign 
//$$

// signal cross section (fb), choose 1 or 10
//   int SigXsec = 10;

  // signal cross section (fb), choose 1 or 10
  float SigXsec1 =  4.5;
  float SigXsec2 =  2;
  float SigXsec3 =  0.6;
  float SigXsec4 =  0.25;
  TString ctau= "10cm";
  TString Prod= "BDT090_Mini";
//   if ( nvtx == 2 ) SigXsec = 1;

//   ./BKGEstimation_RPV_2018_smu500_neu180_ctau030.root
// if (thesample.Contains("DYJetsToLL_M10to50"))                     { XS = 15910.0;   }
// if (thesample.Contains("ST_tW_antitop_5f_NoFullyHadronicDecays")) { XS = 10.8707;   }
// if (thesample.Contains("ST_tW_top_5f_NoFullyHadronicDecays"))     { XS = 10.8908;   }
// if (thesample.Contains("TTJets_DiLept"))                          { XS = 53.07;     }
// if (thesample.Contains("WWTo2L2Nu_MLL_200To600"))                 { XS = 11.09;     }
// if (thesample.Contains("WWTo2L2Nu_MLL_600To1200"))                { XS = 11.09;     }
// if (thesample.Contains("WWTo2L2Nu"))                              { XS = 11.09;     }
// if (thesample.Contains("WZTo2Q2L_mllmin4p0"))                     { XS = 6.535;     }
// if (thesample.Contains("ZZTo2Q2L_mllmin4p0"))                     { XS = 3.676;     }
// if (thesample.Contains("TTTo2L2Nu"))                              { XS = 88.3;      }
// if (thesample.Contains("DYJetsToLL_M50"))                         { XS = 5379;      }
// if (thesample.Contains("ttWJetsToLNu_5f_EWK"))                    { XS = 0.290;     } // not found on XSDB, no file on tier2...approximation
//       //Took 0.868 pb (CMS-TOP-21-011)
//      // as a starting point and then divided by 3 (lepton universality)
// if (thesample.Contains("TTZToLL_5f"))                             { XS = 0.05188;   }//Not found on XSDB => used ana.py macro : 5.188e-02 +- 2.437e-04 pb
// if (thesample.Contains("TTToHadronic"))                           { XS = 378.9;     }
// if (thesample.Contains("TTWW"))                                   { XS = 0.006992;  }//found on XSDB
// if (thesample == "TTToSemiLeptonic")                              { XS = 365.34;    }

// //Signal
// if (thesample.Contains("smu200")) { XS = 0.01;   }
// if (thesample.Contains("smu250")) { XS = 0.0045; }
// if (thesample.Contains("smu300")) { XS = 0.002;  }
// if (thesample.Contains("smu350")) { XS = 0.001;  }
// if (thesample.Contains("smu400")) { XS = 0.0006; }
// if (thesample.Contains("smu450")) { XS = 0.0004; }
// if (thesample.Contains("smu500")) { XS = 0.00025;}
// outputroot

 TFile* f1_DY  = new TFile("../"+Prod+"/ABCD_DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8.root");
 TFile* f2_DY  = new TFile("../"+Prod+"/ABCD_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8.root");
 TFile* f1_TT  = new TFile("../"+Prod+"/ABCD_TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8.root");
//  TFile* f2_TT  = new TFile("../"+Prod+"/BKGEstimation_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8.root");
//  TFile* f1_ST  = new TFile("../"+Prod+"/BKGEstimation_ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8.root");
//  TFile* f2_ST  = new TFile("../"+Prod+"/BKGEstimation_ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8.root");
//  TFile* f1_TTV = new TFile("../"+Prod+"/BKGEstimation_ttWJetsToLNu_5f_EWK_TuneCP5_13TeV_amcatnlo-pythia8.root");
//  TFile* f2_TTV = new TFile("../"+Prod+"/BKGEstimation_TTZToLL_5f_TuneCP5_13TeV-madgraphMLM-pythia8.root");
//  TFile* f3_TTV = new TFile("../"+Prod+"/BKGEstimation_TTWW_TuneCP5_13TeV-madgraph-pythia8.root");
//  TFile* f1_VV  = new TFile("../"+Prod+"/BKGEstimation_WWTo2L2Nu_TuneCP5_13TeV-powheg-pythia8.root");
//  TFile* f2_VV  = new TFile("../"+Prod+"/BKGEstimation_WZTo2Q2L_mllmin4p0_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
//  TFile* f3_VV  = new TFile("../"+Prod+"/BKGEstimation_ZZTo2Q2L_mllmin4p0_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
 TFile* f1_LLP = new TFile("../"+Prod+"/ABCD_RPV_2018_smu250_neu200_ctau100.root");
 TFile* f2_LLP = new TFile("../"+Prod+"/ABCD_RPV_2018_smu300_neu180_ctau100.root");
 TFile* f3_LLP = new TFile("../"+Prod+"/ABCD_RPV_2018_smu400_neu300_ctau100.root");
 TFile* f4_LLP = new TFile("../"+Prod+"/ABCD_RPV_2018_smu500_neu350_ctau100.root");

 // hData_BDTHemi1
// hData_BDTHemi1
//  htitle0 = "hData_BDTevtABCD";
//  htitle1 = "hData_BDTevtDY";
 
//  TString htitle = "hData_Hemi_2Vtx_CutEvt_Mmumu"; 
// //  TString htitle = "hData_Hemi_2Vtx_CutEvt_Mmumu"; 
// // //  TString htitle = "hData_CRloose_Hemi_2Vtx_Mmumu"; 
//  TString xtitle = "m_{#mu^{+}#mu^{-}} [GeV]"; 
// //  TString htitle = "hData_SameSign_Mmumu"; 
// //  TString htitle = "hData_SameSign_Hemi_1Vtx_Mmumu"; 
// //  TString xtitle = "m_{#mu^{#pm}#mu^{#pm}} [GeV]"; 
//  TString ytitle = "Events / 20 GeV"; 
//  int nbin = 25; 
//  float xmin =	0.;
//  float xmax = 500.;

//  TString htitle = "hData_CRloose_Hemi_1Vtx_ptmin"; 
//  TString xtitle = "hemisphere min. p_{T} [GeV]"; 
//  TString ytitle = "Events / 40 GeV"; 
//  int nbin = 25; 
//  float xmin =    0.;
//  float xmax = 1000.;

//  TString htitle = "hData_Hemi_2Vtx_lead_ptmin"; 
//  TString xtitle = "jet1 min. p_{T} [GeV]"; 
//  TString ytitle = "Events / 20 GeV"; 
//  int nbin = 25; 
//  float xmin =	0.;
//  float xmax = 500.;

//  TString htitle = "hData_Hemi_eta"; 
//  TString xtitle = "hemisphere |#eta|"; 
//  TString ytitle = "Events / 20 GeV"; 
//  int nbin = 25; 
//  float xmin = 0.;
//  float xmax = 5.;

//  TString htitle = "hData_Hemi_2Vtx_nTrks"; 
//  TString xtitle = "min. nb. of tracks"; 
//  TString ytitle = "Events / bin"; 
//  int nbin = 25; 
//  float xmin =  0.;
//  float xmax = 50.;

//  TString htitle = "hData_njetNOmuAll"; 
//  TString xtitle = "nb. of jets (without #mu)"; 
//  TString ytitle = "Events / bin"; 
//  int nbin = 21; 
//  float xmin = -0.5;
//  float xmax = 20.5;

//  TString htitle = "hData_Hemi_CutEvt_njetNOmu"; 
//  TString xtitle = "min. nb. of jets (without #mu)"; 
//  TString ytitle = "Events / bin"; 
//  int nbin = 12; 
//  float xmin = -0.5;
//  float xmax = 11.5;

//  TString htitle = "hData_Hemi_2Vtx_BDTevt"; 
// //  TString htitle = "hData_Hemi_2Vtx_BDTevt"; 
//  TString xtitle = "event BDT"; 
// //  TString xtitle = "vertex BDT"; 
//  TString ytitle = "Events / bin"; 
//  int nbin = 40; 
//  float xmin = -1.;
//  float xmax =  1.;

// //  TString htitle = "hData_Hemi_1Vtx_BDTvtx"; 
// //  TString xtitle = "vertex BDT"; 
//  TString htitle = "hData_Hemi_2Vtx_BDTvtx"; 
//  TString xtitle = "max. vertex BDT"; 
//  TString ytitle = "Events / bin"; 
//  int nbin = 40; 
//  float xmin = -1.;
//  float xmax =  1.;

//  TString htitle = "hData_Hemi_mass"; 
//  TString xtitle = "min. hemisphere mass [GeV]"; 
//  TString ytitle = "Events / bin"; 
//  int nbin = 25; 
//  float xmin =   0.;
//  float xmax = 500.;

////////////////////--------------------Most useful---------------/////

 TString htitle = "hData_Hemi_1Vtx_CutEvt_Mass"; 
 TString xtitle = "max. vertex mass [GeV]"; 
 //TString htitle = "hData_Hemi_2VtxAll_Mass"; 
// //SR
// // hData_Hemi_2Vtx_CutVtx_CutEvt_Mass
// // hData_Hemi_2Vtx_CutEvt_Mass

// //CRfwd
// // hData_CRfwd_Hemi_2Vtx_CutEvt_Mass
// //CRLoose
// // hData_CRloose_Hemi_2Vtx_CutEvt_Mass
// //lowpt crontrol region
// // hData_CRlowpt_Hemi_2Vtx_Mass
// loose lowpt conrtol reion
// hData_CRlooselowpt_Hemi_2Vtx_CutEvt_Mass
// //SameSign control region
// // hData_SameSign_Hemi_2Vtx_CutEvt_Mass
//  TString xtitle = "vertex mass [GeV]"; 

// lowptloose
 TString ytitle = "Events / 4 GeV"; 
 int nbin = 25; 
 float xmin =	0.;
 float xmax = 100.;

// Using the BDTs ---------//
//  TString htitle = "hData_CRloose_Hemi_1SecVtx_CutEvt_Mass"; 
//  TString xtitle = "max. vertex mass [GeV]"; 
 // TString ytitle = "Events / 4 GeV"; 
 // int nbin = 25; 
 // float xmin =	0.;
 // float xmax = 100.;


//  hData_SR_1Vtx_MVtx
// hData_CRNoEvt_1Vtx_MVtx
// hData_CRNoEvtNoVtx_1Vtx_MVtx
// hData_CRNoVtx_1Vtx_MVtx

// hData_SR_2Vtx_MVtx
// hData_CRNoEvt_2Vtx_MVtx
// hData_CRNoEvtNoVtx_2Vtx_MVtx
// hData_CRNoVtx_2Vtx_MVtx

// hData2_SR_1Vtx_MVtx
// hData2_CRNoEvt_1Vtx_MVtx
// hData2_CRNoEvtNoVtx_1Vtx_MVtx
// hData2_CRNoVtx_1Vtx_MVtx

// hData2_SR_2Vtx_MVtx
// hData2_CRNoEvt_2Vtx_MVtx
// hData2_CRNoEvtNoVtx_2Vtx_MVtx
// hData2_CRNoVtx_2Vtx_MVtx

//- Using the merging category -/
//  TString htitle = "hData_CRlooselowpt_Hemi_2SecVtx_CutEvt_Mass"; 
//  TString xtitle = "max. vertex mass [GeV]"; 
//  TString ytitle = "Events / 4 GeV"; 
//  int nbin = 25; 
//  float xmin =	0.;
//  float xmax = 100.;

// hData_Hemi_2SecVtx_CutEvt_Mass
// hData_CRfwd_Hemi_2SecVtx_CutEvt_Mass
// hData_CRlowpt_Hemi_2SecVtx_CutEvt_Mass
// hData_CRloose_Hemi_2SecVtx_CutEvt_Mass
// hData_CRlooselowpt_Hemi_2SecVtx_CutEvt_Mass
// hData_SameSign_Hemi_2SecVtx_CutEvt_Mass

// hData_Hemi_1SecVtx_CutEvt_Mass
// hData_CRfwd_Hemi_1SecVtx_CutEvt_Mass
// hData_CRlowpt_Hemi_1SecVtx_CutEvt_Mass
//  hData_CRloose_Hemi_1SecVtx_CutEvt_Mass
// hData_CRlooselowpt_Hemi_1SecVtx_CutEvt_Mass
// hData_SameSign_Hemi_1SecVtx_CutEvt_Mass

////////////////////--------------------Most useful---------------/////

//   TString htitle = "hData_Hemi_2Vtx_CutEvt_massMu"; 
//  TString xtitle = "max. Mu+Hemi mass [GeV]"; 
// //  TString htitle = "hData_Hemi_2VtxAll_Mass"; 
// //  TString xtitle = "vertex mass [GeV]"; 
//  TString ytitle = "Events / 30 GeV"; 
//  int nbin = 25; 
//  float xmin =	0.;
//  float xmax = 750.;


//  TString htitle = "hData_Hemi_1Vtx_massMu"; 
//  TString xtitle = "min. mass(hemi-#mu) [GeV]"; 
// //  TString htitle = "hData_Hemi_2Vtx_massMu"; 
// //  TString xtitle = "max. mass(hemi-muon) [GeV]"; 
// //  TString htitle = "hData_Hemi_2VtxAll_massMu"; 
// //  TString xtitle = "mass(hemi-muon) [GeV]"; 
//  TString ytitle = "Events / bin"; 
//  int nbin = 25; 
//  float xmin =   0.;
//  float xmax = 800.;

//  TString htitle = "hData_Hemi_2Vtx_ptMu"; 
//  TString xtitle = "min. p_{T}(hemi-#mu) [GeV]"; 
//  TString ytitle = "Events / bin"; 
//  int nbin = 25; 
//  float xmin =    0.;
//  float xmax = 1000.;

//  TString htitle = "hData_Hemi_1Vtx_dRMu"; 
//  TString xtitle = "max. #DeltaR(hemi-#mu)"; 
//  TString ytitle = "Events / bin"; 
//  int nbin = 25; 
//  float xmin = 0.;
//  float xmax = 5.;

//  TString htitle = "hData_Hemi_1Vtx_PFMet"; 
//  TString xtitle = "MET [GeV]"; 
//  TString ytitle = "Events / bin"; 
//  int nbin = 25; 
//  float xmin = 0.;
//  float xmax = 500.;

 float xsec_DY[2], xsec_TT[3], xsec_ST[2], xsec_TTV[3], xsec_VV[3]; 
 xsec_DY[0] = 5379.0; xsec_DY[1] = 15910.0;
 xsec_TT[0] = 88.3; xsec_TT[1] = 365.3; xsec_TT[2] = 378.0;
 xsec_ST[0] = 10.8707; xsec_ST[1] = 10.8908;
 xsec_TTV[0] = 0.29; xsec_TTV[1] = 0.052; xsec_TTV[2] =  0.0070;
 xsec_VV[0] = 11.09; xsec_VV[1] = 6.57; xsec_VV[2] = 3.68;
 
 float events = 0.;
 float norm = 60000. / 100000.;

// *****************************************************************************

TCanvas *c1 = new TCanvas("c1", "plots",200,0,700,700);
c1->SetFillColor(10);
c1->SetFillStyle(4000);
c1->SetBorderSize(2);

TPad* pad1 = new TPad("pad1","This is pad1",0.04,0.02,0.99,0.99,21);

pad1->SetFillColor(0);
pad1->SetBorderMode(0);
pad1->SetFrameFillColor(10);
pad1->Draw();
pad1->SetLogy(logy);
// pad1->SetGrid(false);
pad1->SetLeftMargin(0.12);

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
// gStyle->SetPadTickX(1); gStyle->SetPadTickY(1);
// gStyle->SetPadGridX(false); gStyle->SetPadGridY(false);

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

 TH1F* htot = new TH1F("htot","",nbin,xmin,xmax);

           f1_DY->cd();
     TH1F* e1_DY = (TH1F*)gROOT->FindObject("hData_Filter");
           e1_DY->Sumw2();
	   norm = 0.;
	   if  ( e1_DY->Integral(0,3) > 0 ) norm = 60000. / e1_DY->Integral(0,3);
     TH1F* g1_DY = (TH1F*)gROOT->FindObject(htitle);
           g1_DY->Sumw2();
      TH1F* h_DY = new TH1F("h_DY","",nbin,xmin,xmax);
            h_DY->Add(g1_DY, h_DY, xsec_DY[0]*norm,0);

           f2_DY->cd();
     TH1F* e2_DY = (TH1F*)gROOT->FindObject("hData_Filter");
           e2_DY->Sumw2();
	   norm = 0.;
	   if  ( e2_DY->Integral(0,3) > 0 ) norm = 60000. / e2_DY->Integral(0,3);
     TH1F* g2_DY = (TH1F*)gROOT->FindObject(htitle);
           g2_DY->Sumw2();
 h_DY->Add(g2_DY, h_DY, xsec_DY[1]*norm, 1);

//            f1_VV->cd();
//      TH1F* e1_VV = (TH1F*)gROOT->FindObject("hData_Filter");
//            e1_VV->Sumw2();
// 	   norm = 0.;
// 	   if  ( e1_VV->Integral(0,3) > 0 ) norm = 60000. / e1_VV->Integral(0,3);
//      TH1F* g1_VV = (TH1F*)gROOT->FindObject(htitle);
//            g1_VV->Sumw2();
//       TH1F* h_VV = new TH1F("h_VV","",nbin,xmin,xmax);
//             h_VV->Add(g1_VV, h_VV, xsec_VV[0]*norm,0);

//            f2_VV->cd();
//      TH1F* e2_VV = (TH1F*)gROOT->FindObject("hData_Filter");
//            e2_VV->Sumw2();
// 	   norm = 0.;
// 	   if  ( e2_VV->Integral(0,3) > 0 ) norm = 60000. / e2_VV->Integral(0,3);
//      TH1F* g2_VV = (TH1F*)gROOT->FindObject(htitle);
//            g2_VV->Sumw2();
//  h_VV->Add(g2_VV, h_VV, xsec_VV[1]*norm, 1);

//            f3_VV->cd();
//      TH1F* e3_VV = (TH1F*)gROOT->FindObject("hData_Filter");
//            e3_VV->Sumw2();
// 	   norm = 0.;
// 	   if  ( e3_VV->Integral(0,3) > 0 ) norm = 60000. / e3_VV->Integral(0,3);
//      TH1F* g3_VV = (TH1F*)gROOT->FindObject(htitle);
//            g3_VV->Sumw2();
//  h_VV->Add(g3_VV, h_VV, xsec_VV[2]*norm, 1);

//            f1_TTV->cd();
//      TH1F* e1_TVV = (TH1F*)gROOT->FindObject("hData_Filter");
//            e1_TVV->Sumw2();
// 	   norm = 0.;
// 	   if  ( e1_TVV->Integral(0,3) > 0 ) norm = 60000. / e1_TVV->Integral(0,3);
//      TH1F* g1_TTV = (TH1F*)gROOT->FindObject(htitle);
//            g1_TTV->Sumw2();
//       TH1F* h_TTV = new TH1F("h_TTV","",nbin,xmin,xmax);
//             h_TTV->Add(g1_TTV, h_TTV, xsec_TTV[0]*norm,0);

//            f2_TTV->cd();
//      TH1F* e2_TVV = (TH1F*)gROOT->FindObject("hData_Filter");
//            e2_TVV->Sumw2();
// 	   norm = 0.;
// 	   if  ( e2_TVV->Integral(0,3) > 0 ) norm = 60000. / e2_TVV->Integral(0,3);
//      TH1F* g2_TTV = (TH1F*)gROOT->FindObject(htitle);
//            g2_TTV->Sumw2();
//  h_TTV->Add(g2_TTV, h_TTV, xsec_TTV[1]*norm, 1);

//            f3_TTV->cd();
//      TH1F* e3_TVV = (TH1F*)gROOT->FindObject("hData_Filter");
//            e3_TVV->Sumw2();
// 	   norm = 0.;
// 	   if  ( e3_TVV->Integral(0,3) > 0 ) norm = 60000. / e3_TVV->Integral(0,3);
//      TH1F* g3_TTV = (TH1F*)gROOT->FindObject(htitle);
//            g3_TTV->Sumw2();
//  h_TTV->Add(g3_TTV, h_TTV, xsec_TTV[2]*norm, 1);

//            f1_ST->cd();
//      TH1F* e1_ST = (TH1F*)gROOT->FindObject("hData_Filter");
//            e1_ST->Sumw2();
// 	   norm = 0.;
// 	   if  ( e1_ST->Integral(0,3) > 0 ) norm = 60000. / e1_ST->Integral(0,3);
//      TH1F* g1_ST = (TH1F*)gROOT->FindObject(htitle);
//            g1_ST->Sumw2();
//       TH1F* h_ST = new TH1F("h_ST","",nbin,xmin,xmax);
//             h_ST->Add(g1_ST, h_ST, xsec_ST[0]*norm,0);

//            f2_ST->cd();
//      TH1F* e2_ST = (TH1F*)gROOT->FindObject("hData_Filter");
//            e2_ST->Sumw2();
// 	   norm = 0.;
// 	   if  ( e2_ST->Integral(0,3) > 0 ) norm = 60000. / e2_ST->Integral(0,3);
//      TH1F* g2_ST = (TH1F*)gROOT->FindObject(htitle);
//            g2_ST->Sumw2();
//  h_ST->Add(g2_ST, h_ST, xsec_ST[1]*norm, 1);

           f1_TT->cd();
     TH1F* e1_TT = (TH1F*)gROOT->FindObject("hData_Filter");
           e1_TT->Sumw2();
	   norm = 0.;
	   if  ( e1_TT->Integral(0,3) > 0 ) norm = 60000. / e1_TT->Integral(0,3);
     TH1F* g1_TT = (TH1F*)gROOT->FindObject(htitle);
           g1_TT->Sumw2();
      TH1F* h_TT = new TH1F("h_TT","",nbin,xmin,xmax);
            h_TT->Add(g1_TT, h_TT, xsec_TT[0]*norm,0);

//            f2_TT->cd();
//      TH1F* e2_TT = (TH1F*)gROOT->FindObject("hData_Filter");
//            e2_TT->Sumw2();
// 	   norm = 0.;
// 	   if  ( e2_TT->Integral(0,3) > 0 ) norm = 60000. / e2_TT->Integral(0,3);
//      TH1F* g2_TT = (TH1F*)gROOT->FindObject(htitle);
//            g2_TT->Sumw2();
//  h_TT->Add(g2_TT, h_TT, xsec_TT[1]*norm, 1);




//--------------//
//            f3_TT->cd();
//      TH1F* e3_TT = (TH1F*)gROOT->FindObject("hData_Filter");
//            e3_TT->Sumw2();
// 	   if  ( e3_TT->Integral(0,3) > 0 ) norm = 60000. / e3_TT->Integral(0,3);
//      TH1F* g3_TT = (TH1F*)gROOT->FindObject(htitle);
//            g3_TT->Sumw2();
//  h_TT->Add(g3_TT, h_TT, xsec_TT[2]*norm, 1);

 htot->Add(htot, h_DY, 1, 1);
//  htot->Add(htot, h_VV, 1, 1);
//  htot->Add(htot, h_TTV, 1, 1);
//  htot->Add(htot, h_ST, 1, 1);
 htot->Add(htot, h_TT, 1, 1);

//  h_VV->Add(h_VV, h_TTV, 1, 1);
//  h_VV->Add(h_VV, h_ST, 1, 1);
//  h_VV->Add(h_VV, h_TT, 1, 1);

//  h_TTV->Add(h_TTV, h_ST, 1, 1);
//  h_TTV->Add(h_TTV, h_TT, 1, 1);

//  h_ST->Add(h_ST, h_TT, 1, 1);

 htot->Draw("H"); 
 htot->SetFillColor(kGreen-6);
 htot->SetLineColor(kGreen-6);
 htot->SetLineStyle(1);
 htot->SetLineWidth(3);
 htot->SetTickLength(0.03, "YZ");
 htot->SetTickLength(0.03,"X");
 htot->SetLabelOffset(0.007,"X");
 htot->SetLabelOffset(0.007,"Y");
 htot->SetLabelSize(0.035, "XYZ");
 htot->SetLabelFont(42, "XYZ"); 
 htot->SetTitleFont(42, "XYZ");
 htot->SetTitleSize(0.04, "XYZ"); 
 htot->SetTitleOffset(1.1,"X"); 
 htot->SetTitleOffset(1.5,"Y");
 htot->GetXaxis()->SetTitle(xtitle);
 htot->GetXaxis()->SetTitleColor(1);
 htot->GetYaxis()->SetTitle(ytitle);
 htot->GetYaxis()->SetTitleColor(1);
 htot->SetNdivisions(509,"XYZ");
 htot->SetMinimum(1.); 
//$$ 
 htot->SetMaximum(hmax); 
//$$ 

//  h_VV->Draw("Hsame"); 
//  h_VV->SetFillColor(kOrange-2);
//  h_VV->SetLineColor(kOrange-2);
//  h_VV->SetLineStyle(1);
//  h_VV->SetLineWidth(3);

//  h_TTV->Draw("Hsame"); 
//  h_TTV->SetFillColor(kAzure+4);
//  h_TTV->SetLineColor(kAzure+4);
//  h_TTV->SetLineStyle(1);
//  h_TTV->SetLineWidth(3);

//  h_ST->Draw("Hsame"); 
//  h_ST->SetFillColor(kAzure+2);
//  h_ST->SetLineColor(kAzure+2);
//  h_ST->SetLineStyle(1);
//  h_ST->SetLineWidth(3);

 h_TT->Draw("Hsame"); 
 h_TT->SetFillColor(kAzure+1);
 h_TT->SetLineColor(kAzure+1);
 h_TT->SetLineStyle(1);
 h_TT->SetLineWidth(3);
 h_TT->SetTickLength(0.03, "YZ");
 h_TT->SetTickLength(0.03,"X");

           f1_LLP->cd();
     TH1F* e1_LLP = (TH1F*)gROOT->FindObject("hData_Filter");
           e1_LLP->Sumw2();
	   norm = 0.;
	   if ( e1_LLP->Integral(0,3) > 0. ) norm = SigXsec1*60000. / e1_LLP->Integral(0,3);
     TH1F* g1_LLP = (TH1F*)gROOT->FindObject(htitle);
           g1_LLP->Sumw2();
     TH1F* h1_LLP = new TH1F("h1_LLP","",nbin,xmin,xmax);
           h1_LLP->Add(g1_LLP, h1_LLP, 0.001*norm,0);

           f2_LLP->cd();
     TH1F* e2_LLP = (TH1F*)gROOT->FindObject("hData_Filter");
           e2_LLP->Sumw2();
	   norm = 0.;
	   if ( e2_LLP->Integral(0,3) > 0. ) norm = SigXsec2*60000. / e2_LLP->Integral(0,3);
     TH1F* g2_LLP = (TH1F*)gROOT->FindObject(htitle);
           g2_LLP->Sumw2();
     TH1F* h2_LLP = new TH1F("h2_LLP","",nbin,xmin,xmax);
           h2_LLP->Add(g2_LLP, h2_LLP, 0.001*norm,0);

           f3_LLP->cd();
     TH1F* e3_LLP = (TH1F*)gROOT->FindObject("hData_Filter");
           e3_LLP->Sumw2();
	   norm = 0.;
	   if ( e3_LLP->Integral(0,3) > 0. ) norm = SigXsec3*60000. / e3_LLP->Integral(0,3);
     TH1F* g3_LLP = (TH1F*)gROOT->FindObject(htitle);
           g3_LLP->Sumw2();
     TH1F* h3_LLP = new TH1F("h3_LLP","",nbin,xmin,xmax);
           h3_LLP->Add(g3_LLP, h3_LLP, 0.001*norm,0);

           f4_LLP->cd();
     TH1F* e4_LLP = (TH1F*)gROOT->FindObject("hData_Filter");
           e4_LLP->Sumw2();
	   norm = 0.;
	   if ( e4_LLP->Integral(0,3) > 0. ) norm = SigXsec4*60000. / e4_LLP->Integral(0,3);
     TH1F* g4_LLP = (TH1F*)gROOT->FindObject(htitle);
           g4_LLP->Sumw2();
     TH1F* h4_LLP = new TH1F("h4_LLP","",nbin,xmin,xmax);
           h4_LLP->Add(g4_LLP, h4_LLP, 0.001*norm,0);

 h1_LLP->Draw("Hsame"); 
 h1_LLP->SetLineColor(kRed-1);
 h1_LLP->SetLineStyle(1);
 h1_LLP->SetLineWidth(3);

 h2_LLP->Draw("Hsame"); 
 h2_LLP->SetLineColor(kRed-2);
 h2_LLP->SetLineStyle(2);
 h2_LLP->SetLineWidth(3);

 h3_LLP->Draw("Hsame"); 
 h3_LLP->SetLineColor(kRed-3);
 h3_LLP->SetLineStyle(1);
 h3_LLP->SetLineWidth(3);

 h4_LLP->Draw("Hsame"); 
 h4_LLP->SetLineColor(kRed-4);
 h4_LLP->SetLineStyle(2);
 h4_LLP->SetLineWidth(3);

//  e1_LLP->Draw("Hsame"); 
 e1_LLP->SetLineColor(kWhite);
//  e1_LLP->SetLineStyle(1);
//  e1_LLP->SetLineWidth(3);

  TLegend* leg;
    
  leg = new TLegend(0.12,0.91,0.40,0.95);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->SetTextFont(42);
  leg->SetTextSize(0.035);
  leg->SetHeader("simulation 2018, 60 fb^{-1} (13 TeV)");
  leg->Draw();

  leg = new TLegend(0.43,0.55,0.75,0.87);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->SetTextFont(42);
  leg->SetTextSize(0.025);
  leg->AddEntry(htot,"DY","F");
//   leg->AddEntry(h_VV,"WW, WZ, ZZ","F");
//   leg->AddEntry(h_TTV,"t#bar{t}W, t#bar{t}Z, t#bar{t}WW","F");
//   leg->AddEntry(h_ST,"tW","F");
  leg->AddEntry(h_TT,"t#bar{t}","F");
  leg->AddEntry(h1_LLP,"Signal18, m_{#tilde{#mu}}= 250 GeV, m_{#tilde{#chi}^{0}}= 200 GeV","L");
  leg->AddEntry(h2_LLP,"Signal18, m_{#tilde{#mu}}= 300 GeV, m_{#tilde{#chi}^{0}}= 180 GeV","L");
  leg->AddEntry(h3_LLP,"Signal18, m_{#tilde{#mu}}= 400 GeV, m_{#tilde{#chi}^{0}}= 300 GeV","L");
  leg->AddEntry(h4_LLP,"Signal18, m_{#tilde{#mu}}= 500 GeV, m_{#tilde{#chi}^{0}}= 350 GeV","L");


//   if ( SigXsec ==  1 ) leg->AddEntry(e1_LLP,"c#tau(#tilde{#chi}^{0}) = 10 cm, #sigma(#tilde{#mu}^{+}#tilde{#mu}^{-}) = 1 fb","L");
//   if ( SigXsec == 10 ) leg->AddEntry(e1_LLP,"c#tau(#tilde{#chi}^{0}) = 10 cm, #sigma(#tilde{#mu}^{+}#tilde{#mu}^{-}) = 10 fb","L");
 leg->AddEntry(e1_LLP,"c#tau(#tilde{#chi}^{0}) = "+ctau,"L");

  leg->Draw();

  leg = new TLegend(0.14,0.85,0.40,0.89);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->SetTextFont(42);
  leg->SetTextSize(0.025);
//   leg->SetHeader(" per hemisphere:");
//   leg->SetHeader(" #geq 1 hemisphere with:");
  leg->Draw();
  leg = new TLegend(0.14,0.82,0.40,0.85);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->SetTextFont(42);
  leg->SetTextSize(0.025);
//  leg->SetHeader(" |#eta| < 2.4");
  leg->SetHeader(" |#eta| < 2.4, p_{T} > 80 GeV");
//   leg->SetHeader(" 2.4 < |#eta| < 3.0"); // CRfwd
//   leg->SetHeader(" 40 < p_{T} < 80 GeV"); // CRlowpt
// leg->SetHeader(" BDTEVT cut at 0 BDTVTX 0.5");
  leg->Draw();

  leg = new TLegend(0.66,0.83,0.88,0.87);
  leg->SetBorderSize(1);
  leg->SetFillColor(kWhite);
  leg->SetTextFont(42);
  leg->SetTextSize(0.025);
  if ( nvtx ==-1 ) leg->SetHeader(" no vertex selection");
//   if ( nvtx == 1 ) leg->SetHeader("    1 vtx, no cut");
//   if ( nvtx == 2 ) leg->SetHeader("    2 vtx, no cut");
//   if ( nvtx == 1 ) leg->SetHeader("    1 vtx, loose");
//   if ( nvtx == 2 ) leg->SetHeader("    2 vtx, loose");
//   if ( nvtx ==-1 ) leg->SetHeader(" no vtx selection, BDTevt>0");
  if ( nvtx == 1 ) leg->SetHeader("    1 vtx, "+Prod);
  if ( nvtx == 2 ) leg->SetHeader("    2 vtx, "+Prod);
//   leg->SetHeader(" 2 vtx, m_{vtx}^{max} > 8 GeV");
//   leg->SetHeader("    1 vtx, no cut");
//   leg->SetHeader(" 1 vtx, m_{vtx} > 8 GeV");
//   leg->SetHeader("     1 vtx, n_{jet} #geq 3");
//   leg->SetHeader(" 1 vtx, m_{vtx} > 8 GeV, n_{jet} #geq 3");
  leg->Draw();

  c1->Update();
}
