// Include ROOT headers
#include <TFile.h>
#include <TH1.h>
#include <TString.h>
#include <iostream>
#include <vector>
#include <sys/stat.h>
#include <fstream>
// #include "/opt/sbg/cms/ui2_data1/pvaucell/CMSSW_11_3_4/src/HiggsAnalysis/CombinedLimit/data/RPV_UDD_2018/PlotCMS.h"


void PlotLimit1D_Msmu_Mneu_ctau(
        std::vector<double> smuValues  ,
        std::vector<double> neuValues  ,
        std::vector<double> ctauValues  ,
        std::vector<double> ObservedLimit,
        std::vector<double> median ,
        std::vector<double> down68 ,
        std::vector<double> up68 ,
        std::vector<double> down95, 
        std::vector<double> up95 ,
        TString YEAR,
        bool Unblind
)
    {


        std::vector<double> SM =   {1, 1,1,1,1,1,1,1,1};
        const int N = 7;



        // On construit les graphes TGraph pour les zones
        TGraph* band95 = new TGraph(2*N);
        TGraph* band68 = new TGraph(2*N);
        TGraph* gMedian = new TGraph(N);
        TGraph* gObserved = new TGraph(N);
        TGraph* gSM = new TGraph(N);
        // TGraph* gSET = nullptr; // Pour le cas où on ne trace pas gSM
        // Remplissage des graphes
        for (unsigned int i = 0; i < 34 ; i++) {
            for (unsigned int j = 0; j < 7 ; j++) {

                band95->SetPoint(j,         ctauValues[i+j*34]*0.1, up95[i+j*34]);
                band95->SetPoint(2*N - 1 - j, ctauValues[i+j*34]*0.1, down95[i+j*34]);

                band68->SetPoint(j,         ctauValues[i+j*34]*0.1, up68[i+j*34]);
                band68->SetPoint(2*N - 1 - j, ctauValues[i+j*34]*0.1, down68[i+j*34]);

                gMedian->SetPoint(j, ctauValues[i+j*34]*0.1, median[i+j*34]);
                gObserved->SetPoint(j, ctauValues[i+j*34]*0.1, ObservedLimit[i+j*34]);
                gSM->SetPoint(j, ctauValues[i+j*34]*0.1, SM[j]);
                // std::cout << "i: " << i << ", j: " << j << ", ctauValues[i+j*34]*0.1: " << ctauValues[i+j*34]*0.1 << std::endl;


            }
                        // Style
                band95->SetFillColor(kYellow);
                band95->SetLineColor(0);
                band68->SetFillColor(kGreen);
                band68->SetLineColor(0);
                gMedian->SetLineWidth(2);
                gMedian->SetLineStyle(10);
                gMedian->SetLineColor(kBlack);

                // gSM->SetLineWidth(2);
                // gSM->SetLineColor(kRed);

                // Dessin
                TCanvas* c = new TCanvas("c", "Brazilian Plot", 800, 600);
                c->cd();
                TPad* pad = new TPad("pad", "pad", 0, 0, 1, 1);
                pad->SetBottomMargin(0.15);
                pad->SetLeftMargin(0.15);
                pad->SetRightMargin(0.05);
                pad->SetTopMargin(0.075);
                pad->SetLogx(true);
                pad->Draw();
                pad->cd();
                int stati=0;
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
                band95->Draw("AF");

                // std::cout << "Maximum of band95: " << band95->GetMaximum() << std::endl;
                band95->GetYaxis()->SetRangeUser(0, 1);
                band95->SetTitle("");
                band95->GetYaxis()->SetTitleOffset(1.6);
                band68->Draw("F same");
                gMedian->Draw("L same");
                gSM->Draw("L same");

                if (Unblind)
                    {
                    gObserved->SetLineWidth(2);
                    gObserved->SetLineStyle(1);
                    gObserved->SetLineColor(kBlack);
                    gObserved->SetMarkerStyle(20);
                    gObserved->SetMarkerColor(kBlack);
                    gObserved->Draw("LP same");
                    }

                // Axes
                band95->GetXaxis()->SetTitle("c#tau [cm]");
                band95->GetYaxis()->SetTitle("#frac{#sigma^{Exp}_{#tilde{#mu}#tilde{#mu}}}{#sigma^{th}_{#tilde{#mu}#tilde{#mu}}}    ");

                // Légende (optionnelle)
                TLegend* leg = new TLegend(0.5, 0.7, 0.7, 0.88);
                // leg->AddEntry(gSM, "RPV-Model", "l");
                if (Unblind)
                    {
                    leg->AddEntry(gObserved, "Observed Limit", "lp");
                    }
                leg->AddEntry(gMedian, "Expected Median", "l");
                leg->AddEntry(band68, "68% CL", "f");
                leg->AddEntry(band95, "95% CL", "f");
                
                leg->Draw();

                PlotCMSv2(pad,YEAR, true); // Appel de la fonction PlotCMS pour ajouter le texte CMS
                
                int smu = (int) smuValues[i];
                int neu = (int) neuValues[i];
                TString SMU = TString::Format("%d", smu);
                TString NEU = TString::Format("%d", neu);
                TString outfileName = "Msmu_"+SMU+"_Mneu_"+NEU+"_" + YEAR +".pdf";
                c->SaveAs(outfileName); // au cas où tu veux le sauvegarder
        }



    return;
                    
                
    }