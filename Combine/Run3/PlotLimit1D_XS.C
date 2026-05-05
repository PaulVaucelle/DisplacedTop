// Include ROOT headers
#include <TFile.h>
#include <TH1.h>
#include <TString.h>
#include <iostream>
#include <vector>
#include <sys/stat.h>
#include <fstream>
// #include "/opt/sbg/cms/ui2_data1/pvaucell/CMSSW_11_3_4/src/HiggsAnalysis/CombinedLimit/data/RPV_UDD_2018/PlotCMS.h"


void PlotLimit1D_XS(
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

        float XS[7] = {8.96,3.78,1.82,0.95,0.53,0.31,0.19};
        float PDFUncertainty[7]={1.8,2.1,2.4,2.7,2.9,3.2,3.5};//symetric
        float QCDScaleUncertaintyUp[7]={1.7,2.9,3.9,4.7,5.4,6.0,6.6};
        float QCDScaleUncertaintyDown[7]={1.9,2.9,3.7,4.3,4.9,5.4,5.9};
        float XSUp [7] = {1,1,1,1,1,1,1};
        float XSDown [7] = {1,1,1,1,1,1,1};


    for (unsigned int i = 0 ; i < 7; i++)
        {
             XSUp[i]= XS[i]+XS[i]*0.01*PDFUncertainty[i]+XS[i]*0.01*QCDScaleUncertaintyUp[i]; 
        }
    for (unsigned int i = 0 ; i < 7 ; i++)
        {
             XSDown[i]= XS[i]-XS[i]*0.01*PDFUncertainty[i]-XS[i]*0.01*QCDScaleUncertaintyDown[i]; 
        }


        std::vector<double> SM =   {1, 1,1,1,1,1,1,1,1};
        const int N = smuValues.size();

        // On construit les graphes TGraph pour les zones
        TGraph* band95 = new TGraph(2*N);
        TGraph* band68 = new TGraph(2*N);
        TGraph* gMedian = new TGraph(N);
        TGraph* gObserved = new TGraph(N);
        TGraph* gSM = new TGraph(N);
        TGraph* gXS = new TGraph(2*N);

        // Remplissage des graphes
        for (int i = 0; i < N; ++i) {
            band95->SetPoint(i,         smuValues[i], up95[i]*XS[i]);
            band95->SetPoint(2*N - 1 - i, smuValues[i], down95[i]*XS[i]);

            band68->SetPoint(i,         smuValues[i], up68[i]*XS[i]);
            band68->SetPoint(2*N - 1 - i, smuValues[i], down68[i]*XS[i]);

            gMedian->SetPoint(i, smuValues[i], median[i]*XS[i]);
            gObserved->SetPoint(i, smuValues[i], ObservedLimit[i]*XS[i]);
            gSM->SetPoint(i, smuValues[i], SM[i]*XS[i]);
        }

        // Style
        band95->SetFillColor(kYellow);
        band95->SetLineColor(0);
        band68->SetFillColor(kGreen);
        band68->SetLineColor(0);
        gMedian->SetLineWidth(2);
        gMedian->SetLineStyle(10);
        gMedian->SetLineColor(kBlack);

        gSM->SetLineWidth(2);
        gSM->SetLineColor(kRed);

        // Dessin
        TCanvas* c = new TCanvas("c", "Brazilian Plot", 800, 600);
        c->cd();
        TPad* pad = new TPad("pad", "pad", 0, 0, 1, 1);
        pad->SetBottomMargin(0.15);
        pad->SetLeftMargin(0.15);
        pad->SetRightMargin(0.05);
        pad->SetTopMargin(0.075);
        pad->Draw();
        pad->cd();
        band95->Draw("AF");
        std::cout << "Maximum of band95: " << band95->GetMaximum() << std::endl;
        band95->GetYaxis()->SetRangeUser(0, 15);
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
        band95->GetXaxis()->SetTitle("M_{#tilde{#mu}} [GeV]");
        band95->GetYaxis()->SetTitle("#sigma^{Exp}_{#tilde{#mu}#tilde{#mu}} [fb]");

        // Légende (optionnelle)
        TLegend* leg = new TLegend(0.5, 0.7, 0.7, 0.88);
        // leg->AddEntry(gSM, "RPV-Model", "l");
        if (Unblind)
            {
            leg->AddEntry(gObserved, "Observed Limit", "lp");
            }
        leg->AddEntry(gSM, "RPV-Model", "l");
        leg->AddEntry(gMedian, "Expected Median", "l");
        leg->AddEntry(band68, "68% CL", "f");
        leg->AddEntry(band95, "95% CL", "f");
        
        leg->Draw();

        PlotCMSv2(pad,YEAR, true); // Appel de la fonction PlotCMS pour ajouter le texte CMS
        c->SaveAs("XS_vs_Msmu.pdf"); // au cas où tu veux le sauvegarder
    return;
                    
                
    }