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

void plot()
{
 TFile *f1, *f2, *f3, *f4, *f5;
 TGraphAsymmErrors *gr0, *gr1, *gr2, *gr3, *gr4;
 


// Parameters
// TString step = "";
// ""
// "_TightWP"
// "_LooseWP"

int Step = 1;
bool UseEta = false;
bool UseR = false;
bool UseDist = true;
TString dof = "";
//Plotting
int stati=0;
bool fit= 0;
bool logy=0;

TString ytitle = "entries"; 
TString xtitle="";
int nbin = 50; 
float binmin =   0;//0
float binmax = 100;//100

//--------------//
// 65,-6.5,6.5

 TLegend* leg;
 TString htitle0, htitle1, htitle2, htitle3, htitle4; 
if (UseR)
    {
        htitle0 = "hSim_Hemi_Vtx_r_noSel";
        htitle1 = "hData_Hemi_Vtx_r_Goodrecovtx"; 
        htitle2 = "hData_Hemi_Vtx_r_Ping";
        htitle3 = "hData_Hemi_Vtx_r_Tightping";
        htitle4 = "hData_Hemi_Vtx_r_Looseping";
        xtitle = "Transverse decay length [cm]";
        nbin = 50;
        binmin = 0;
        binmax = 100;
    }
if (UseEta)
    {
        htitle0 = "hSim_Hemi_Vtx_eta_noSel";
        htitle1 = "hData_Hemi_Vtx_eta_Goodrecovtx"; 
        htitle2 = "hData_Hemi_Vtx_eta_Ping";
        htitle3 = "hData_Hemi_Vtx_eta_Tightping";
        htitle4 = "hData_Hemi_Vtx_eta_Looseping";
        xtitle = "|#eta|";
        nbin = 26;
        binmin = -6.5;
        binmax = 6.5;
    }
if (UseDist)
    {
        htitle0 = "hSim_Hemi_Vtx_dist_noSel"; 
        htitle1 = "hData_Hemi_Vtx_dist_Goodrecovtx"; 
        htitle2 = "hData_Hemi_Vtx_dist_Ping";
        htitle3 = "hData_Hemi_Vtx_dist_Tightping";
        htitle4 = "hData_Hemi_Vtx_dist_Looseping";
        xtitle  = "decay length [cm]";
        nbin = 100;
        binmin = 0;
        binmax = 200; 
    }


//  htitle0 = "hSim_Hemi_LLP_dist"; 
//  htitle1 = "hSim_Hemi_LLP_dist_chiOK"; 
//  htitle2 = "hSim_Hemi_LLP_dist_ping"; 
// *****************************************************************************

TCanvas *c1 = new TCanvas("c1", "plots",200,0,1500,1000);
c1->SetFillColor(10);
c1->SetFillStyle(4000);
c1->SetBorderSize(2);

TPad* pad1 = new TPad("pad1","This is pad1",0.04,0.45,0.98,0.98,21);
pad1->SetFillColor(0);
pad1->SetBorderMode(0);
pad1->SetFrameFillColor(10);
pad1->Draw();
pad1->SetLogy(logy);
   pad1->SetTopMargin(0.10);
   pad1->SetBottomMargin(0.16);
   pad1->SetRightMargin(0.05);
   pad1->SetLeftMargin(0.10);

TPad* rap1 = new TPad("rap1","This is rap1",0.04,0.07,0.98,0.37,21);
rap1->SetFillColor(0);
rap1->SetBorderMode(0);
rap1->SetFrameFillColor(10);
rap1->Draw();
rap1->SetLogy(0);
   rap1->SetTopMargin(0.06);
   rap1->SetBottomMargin(0.20);
   rap1->SetRightMargin(0.05);
   rap1->SetLeftMargin(0.10);

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
  TH1F*    h_purity = new TH1F("h_purity","h_purity",nbin,binmin,binmax);
  TH1F*    h_efficacity = new TH1F("h_efficacity","h_efficacity",nbin,binmin,binmax);

  TH1F*    h_dist = new TH1F("h_dist","h_dist",nbin,binmin,binmax);
  TH1F*    h_chi2 = new TH1F("h_chi2","h_chi2",nbin,binmin,binmax);
  TH1F*    h_ping = new TH1F("h_ping","h_ping",nbin,binmin,binmax);


// if(UseDist){nbin=20;binmin=0;binmax=100;}
// if(UseEta){nbin=260;binmin=-6.5;binmax=6.5;}
// if(UseGen){nbin=10;binmin=0;binmax=100;}
// if(UseR){nbin=20;binmin=0;binmax=100;}


  const int nSMC = 22;
  TString Datasets[nSMC] = { 
                         "RPV_2018_smu200_neu180_ctau300",
                         "RPV_2018_smu250_neu180_ctau300",
                         "RPV_2018_smu250_neu200_ctau300",
                         "RPV_2018_smu250_neu230_ctau300",
                         "RPV_2018_smu300_neu180_ctau300",
                         "RPV_2018_smu300_neu200_ctau300",
                         "RPV_2018_smu300_neu250_ctau300",
                         "RPV_2018_smu300_neu280_ctau300",
                        //  "RPV_2018_smu350_neu180_ctau300",
                        //  "RPV_2018_smu350_neu200_ctau300",
                        //  "RPV_2018_smu350_neu250_ctau300",
                        //  "RPV_2018_smu350_neu300_ctau300",
                        //  "RPV_2018_smu350_neu330_ctau300",
                         "RPV_2018_smu400_neu180_ctau300",
                         "RPV_2018_smu400_neu200_ctau300",
                         "RPV_2018_smu400_neu250_ctau300",
                         "RPV_2018_smu400_neu300_ctau300",
                         "RPV_2018_smu400_neu350_ctau300",
                         "RPV_2018_smu400_neu380_ctau300",
                        //  "RPV_2018_smu450_neu180_ctau300",
                        //  "RPV_2018_smu450_neu200_ctau300",
                        //  "RPV_2018_smu450_neu250_ctau300",
                        //  "RPV_2018_smu450_neu300_ctau300",
                        //  "RPV_2018_smu450_neu350_ctau300",
                        //  "RPV_2018_smu450_neu400_ctau300",
                        //  "RPV_2018_smu450_neu430_ctau300",
                         "RPV_2018_smu500_neu180_ctau300",
                         "RPV_2018_smu500_neu200_ctau300",
                         "RPV_2018_smu500_neu250_ctau300",
                         "RPV_2018_smu500_neu300_ctau300",
                         "RPV_2018_smu500_neu350_ctau300",
                         "RPV_2018_smu500_neu400_ctau300",
                         "RPV_2018_smu500_neu450_ctau300",
                         "RPV_2018_smu500_neu480_ctau300"};

  TString HTITLE[5]={htitle0,htitle1,htitle2,htitle3,htitle4};       
  TFile *fX[nSMC];

      for (int i = 0; i < nSMC; i++) 
        {
          fX[i] = new TFile("../h_"+Datasets[i]+"_MiniIso_Merging.root");
        }
    
  TH1F* histograms[5*nSMC];
  for (int i = 0; i < nSMC; i++)
    {
      for (int j = 0 ; j < 5 ; j++){
        fX[i]->cd();
        TString histogramTitle = HTITLE[j]; //+"_"+Datasets[i]
        // std::cout<<"histo title : "<<histogramTitle<<std::endl;
        histograms[i*5+j] = (TH1F*)gROOT->FindObject(histogramTitle);
        histograms[i*5+j]->Sumw2();
      }
    }
  pad1->cd();


 for (unsigned int k = 1 ; k < nbin+1; k++)
  {
    float bindist = 1 ; //histograms[0]->GetBinContent(k)+histograms[5]->GetBinContent(k)+histograms[10]->GetBinContent(k)+histograms[15]->GetBinContent(k);
    float binchi2 = 1 ; //histograms[1]->GetBinContent(k)+histograms[6]->GetBinContent(k)+histograms[11]->GetBinContent(k)+histograms[16]->GetBinContent(k);
    float binping = 1 ; //histograms[2]->GetBinContent(k)+histograms[7]->GetBinContent(k)+histograms[12]->GetBinContent(k)+histograms[17]->GetBinContent(k);
    for (int m = 0 ; m < nSMC ; m++)
      {
        bindist += histograms[5*m]->GetBinContent(k);
        binchi2 += histograms[5*m+1]->GetBinContent(k);
        binping += histograms[5*m+3]->GetBinContent(k); 
      }
    // float bindist = histograms[0]->GetBinContent(k)+histograms[5]->GetBinContent(k)+histograms[10]->GetBinContent(k)+histograms[15]->GetBinContent(k);
    // float binchi2 = histograms[1]->GetBinContent(k)+histograms[6]->GetBinContent(k)+histograms[11]->GetBinContent(k)+histograms[16]->GetBinContent(k);
    // float binping = histograms[2]->GetBinContent(k)+histograms[7]->GetBinContent(k)+histograms[12]->GetBinContent(k)+histograms[17]->GetBinContent(k);
    // std::cout<<"dist + chi2 + ping : "<<bindist<<" "<<binchi2<<" "<<binping<<std::endl;
    float effiacity = binping/bindist;
    float purity = binping/binchi2;
    // std::cout<<"purity anf effiicacité"<<purity<<" "<<effiacity<<std::endl;

  }

  h_dist->Add(h_dist,histograms[0],0,1);
  h_chi2->Add(h_chi2,histograms[1],0,1);
  h_ping->Add(h_ping,histograms[3],0,1);
  for (int m = 1 ; m < nSMC ; m++)
    {
      h_dist->Add(h_dist,histograms[5*m],1,1);
      h_chi2->Add(h_chi2,histograms[5*m+1],1,1);
      h_ping->Add(h_ping,histograms[5*m+3],1,1);
    }


h_efficacity->Divide(h_ping,h_dist,1,1,"B");
h_purity->Divide(h_ping,h_chi2,1,1,"B");


h_purity->Draw("E");
 h_purity->GetXaxis()->SetLabelSize(0.050);
 h_purity->GetYaxis()->SetLabelSize(0.050);
 h_purity->SetLabelFont(42, "XYZ"); 
 h_purity->SetTitleFont(42, "XYZ");
 h_purity->GetXaxis()->SetTitleColor(1);
 h_purity->GetYaxis()->SetTitleColor(1);
 h_purity->GetXaxis()->SetTitleSize(0.06);
 h_purity->GetYaxis()->SetTitleSize(0.06);
 h_purity->GetXaxis()->SetTitle(xtitle);
 h_purity->GetYaxis()->SetTitle("");
 h_purity->SetTitleOffset(0.9,"X");
 h_purity->SetTitleOffset(0.6,"Y");
 h_purity->SetLabelOffset(0.01,"Y");
 h_purity->SetNdivisions(509, "XYZ"); 
 h_purity->SetLineColor(kRed);
 h_purity->SetLineStyle(1);
 h_purity->SetLineWidth(3);
 h_purity->SetMinimum(0.);
 h_purity->SetMaximum(1.);
 h_purity->SetTitle("Vertex Reconstruction efficiency as a function of the decay length");

 h_efficacity->Draw("Esame"); 
 h_efficacity->SetLineColor(kBlue);
 h_efficacity->SetLineStyle(1);
 h_efficacity->SetLineWidth(3);


  leg = new TLegend(0.15,0.2,0.35,0.45);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->SetTextFont(42);
  leg->SetTextSize(0.035);
  leg->SetHeader("MC"+dof+" #tilde{#chi}^{0} #rightarrow tqq");
  leg->AddEntry(h_efficacity," efficiency","LE");
  leg->AddEntry(h_purity," purity","LE");
  leg->Draw();


 c1->Update();
}
