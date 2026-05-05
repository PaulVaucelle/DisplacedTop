// Include ROOT headers
#include <TFile.h>
#include <TH1.h>
#include <TString.h>
#include <iostream>
#include <vector>
#include <sys/stat.h>
#include <fstream>
// #include "/opt/sbg/cms/ui2_data1/pvaucell/CMSSW_11_3_4/src/HiggsAnalysis/CombinedLimit/data/RPV_UDD_2018/PlotCMS.h"

// !! Plot with Lines instead of filled areas
void PlotLimit_Msmu_vs_Mneu(
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
        TString CTAU,
        bool Unblind,
        bool getlimitplot = false
)
    {
        int INDEX = 0;
        // Pas très jolie jolie mais on :D
        if (CTAU == "001") INDEX = 0;
        else if (CTAU == "003") INDEX = 1;
        else if (CTAU == "010") INDEX = 2;
        else if (CTAU == "030") INDEX = 3;
        else if (CTAU == "100") INDEX = 4;
        else if (CTAU == "300") INDEX = 5;
        else if (CTAU == "1000") INDEX = 6;

        std::vector<double> SM =   {1, 1,1,1,1,1,1,1,1};
        const int N = 34; // Nombre de points à tracer, ici 34 pour chaque valeur de ctau

                    
        // const int xbin = 14;
        // const int ybin = 14;
        // double xedges[xbin+1] = { 180, 200, 230, 250, 280, 300, 330,350,380,400,430,450,480,500,530}; // Ctau edges in cm
        // double yedges[ybin+1] = {180, 200, 230, 250, 280, 300, 330,350,380,400,430,450,480,500,530}; // 

        const int xbin = 33;
        const int ybin = 33;
        double xedges[xbin+1] = { 175,185,195,205,215,225,235,245,255,265,275,285,295,305,315,325,335,345,355,365,375,385,395,405,415,425,435,445,455,465,475,485,495,505}; // Ctau edges in cm
        double yedges[ybin+1] = { 175,185,195,205,215,225,235,245,255,265,275,285,295,305,315,325,335,345,355,365,375,385,395,405,415,425,435,445,455,465,475,485,495,505}; // 

        // On construit les graphes TGraph pour les zones
        TH2F* band95Up = new TH2F("band95Up","",xbin,xedges,ybin ,yedges);
        TH2F* band95Down = new TH2F("band95Down","",xbin,xedges,ybin ,yedges);
        TH2F* band68Up = new TH2F("band68Up","",xbin,xedges,ybin ,yedges);
        TH2F* band68Down = new TH2F("band68Down","",xbin,xedges,ybin ,yedges);
        TH2F* gObserved = new TH2F("gObserved","",xbin,xedges,ybin ,yedges);
        TH2F* gMedian = new TH2F("Median","",xbin,xedges,ybin ,yedges);
        TH2F* gSM = new TH2F("gSM","",xbin,xedges,ybin ,yedges);

        TH2F* gSET = nullptr; // Pour le cas où on ne trace pas gSM

        // Remplissage des graphes

        for (unsigned int i = 0+34*INDEX; i < 34+34*INDEX ; i++)
            {
                // band95Up->SetPoint(i,neuValues[i],smuValues[i], up95[i]);
                // band95Down->SetPoint(i,neuValues[i], smuValues[i], down95[i]);

                // band68Up->SetPoint(i,neuValues[i],   smuValues[i], up68[i]);
                // band68Down->SetPoint(i,neuValues[i], smuValues[i], down68[i]);

                // gMedian->SetPoint(i,neuValues[i], smuValues[i], median[i]);
                // gObserved->SetPoint(i,neuValues[i], smuValues[i], ObservedLimit[i]);
                // gSM->SetPoint(i, smuValues[i],smuValues[i], 1);

                band95Up->Fill(neuValues[i],smuValues[i], up95[i]);
                band95Down->Fill(neuValues[i],smuValues[i], down95[i]);

                band68Up->Fill(neuValues[i],smuValues[i], up68[i]);
                band68Down->Fill(neuValues[i],smuValues[i], down68[i]);

                gMedian->Fill(neuValues[i],smuValues[i], median[i]);
                gObserved->Fill(neuValues[i],smuValues[i], ObservedLimit[i]);
                }

        // Style
        
        // band95Up->SetLineWidth(2);
        // band95Up->SetLineStyle(1);
        // band95Up->SetLineColor(kYellow);

        // band95Down->SetLineWidth(2);
        // band95Down->SetLineStyle(2);
        // band95Down->SetLineColor(kYellow);


        // band68Up->SetLineWidth(2);
        // band68Up->SetLineStyle(1);
        // band68Up->SetLineColor(kGreen);

        // band68Down->SetLineWidth(2);
        // band68Down->SetLineStyle(2);
        // band68Down->SetLineColor(kGreen);

        gSET = gMedian;
        if (getlimitplot)
            {
            gSET = band95Up; // On utilise gObserved si on veut le plot des limites
            }
        
        if (Unblind)
            {
                gSET = gObserved; // On utilise gObserved si on veut le plot des limites
            }
        
        // gMedian->SetLineWidth(2);
        // gMedian->SetLineStyle(10);
        // gMedian->SetLineColor(kBlack);

        gSET->SetLineWidth(2);
        gSET->SetLineStyle(10);
        gSET->SetLineColor(kBlack);

        // Dessin
        TCanvas* c = new TCanvas("c", "Brazilian Plot", 800, 600);
        c->cd();
        TPad* pad = new TPad("pad", "pad", 0, 0, 1, 1);
        pad->SetBottomMargin(0.15);
        pad->SetLeftMargin(0.15);
        pad->SetRightMargin(0.15);
        pad->SetTopMargin(0.075);
        // pad->SetLogx(true);
        // pad->SetLogz(true);
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
        gStyle->SetPalette(kViridis);
        gStyle->SetPadTickX(1); gStyle->SetPadTickY(1);

        TString DrawOption = "COLZ "; // Points only
        if (N > 1) DrawOption = "COLZ "; // Lines and points if more than one point
        // band95Up->Draw(DrawOption);
        // band95Up->SetTitle("");
        // band95Down->Draw(DrawOption+"same");
        // band68Up->Draw(DrawOption+"same");
        // band68Down->Draw(DrawOption+"same");

        // gMedian->Draw(DrawOption);
        gSET->Draw(DrawOption);

        // if (Unblind)
        //     {
        //     gObserved->SetLineWidth(2);
        //     gObserved->SetLineStyle(1);
        //     gObserved->SetLineColor(kBlack);
        //     gObserved->SetMarkerStyle(20);
        //     gObserved->SetMarkerColor(kBlack);
        //     gObserved->Draw("LP same");
        //     }
        // Axes

        // gMedian->GetXaxis()->SetTitle("c#tau [cm]");
        // gMedian->GetYaxis()->SetTitle("M_{#tilde{#chi}} [GeV]");
        // gMedian->GetZaxis()->SetTitle("Median Expected Limit");
        // gMedian->GetXaxis()->SetTitleOffset(1.6);
        // gMedian->GetZaxis()->SetTitleOffset(1.3);
        // gMedian->GetZaxis()->SetRangeUser(0.,1);

        gSET->GetXaxis()->SetTitle("M_{#tilde{#chi}} [GeV]");
        gSET->GetYaxis()->SetTitle("M_{#tilde{#mu}} [GeV]");
                TString textZ = "Median Expected Limit";
        if (getlimitplot)
            {
                textZ = "Expected Limit";
            }
        gSET->GetZaxis()->SetTitle(textZ);
        gSET->GetXaxis()->SetTitleOffset(1.6);
        gSET->GetZaxis()->SetTitleOffset(1.3);
        gSET->GetZaxis()->SetRangeUser(0.,1);

        PlotCMSv4(pad,YEAR, true); // Appel de la fonction PlotCMS pour ajouter le texte CMS // Appel de la fonction PlotCMS pour ajouter le texte CMS
        TString outfileName = "Msmu_vs_Mneu_" + YEAR + "_ctau" + CTAU + ".pdf";
                if (getlimitplot)
            {
                outfileName = "Limit_Msmu_vs_Mneu_" + YEAR + "_ctau" + CTAU + ".pdf";
            }
        c->SaveAs(outfileName); // au cas où tu veux le sauvegarder




        // Dessin
        TCanvas* c2 = new TCanvas("c2", "Brazilian Plot", 800, 600);
        c2->cd();
        TPad* pad2 = new TPad("pad2", "pad2", 0, 0, 1, 1);
        pad2->SetBottomMargin(0.15);
        pad2->SetLeftMargin(0.15);
        pad2->SetRightMargin(0.15);
        pad2->SetTopMargin(0.075);
        // pad->SetLogx(true);
        // pad->SetLogz(true);
        pad2->Draw();
        pad2->cd();

        // Créer un TGraph2D avec les bins non vides
        TGraph2D* g2d = new TGraph2D();
        int idx = 0;

        for (int ix = 1; ix <= gSET->GetNbinsX(); ++ix) {
            for (int iy = 1; iy <= gSET->GetNbinsY(); ++iy) {
                double content = gSET->GetBinContent(ix, iy);
                if (content == 0) continue;

                double x = gSET->GetXaxis()->GetBinCenter(ix);
                double y = gSET->GetYaxis()->GetBinCenter(iy);
                g2d->SetPoint(idx++, x, y, content);
            }
        }

        // Définir une grille fine pour interpolation
        int nBinsX = 100; // Tu peux ajuster ça pour la finesse
        int nBinsY = 100;

        double xMin = gSET->GetXaxis()->GetXmin()+5;
        double xMax = gSET->GetXaxis()->GetXmax()-5;
        double yMin = gSET->GetYaxis()->GetXmin()+5;
        double yMax = gSET->GetYaxis()->GetXmax()-5;

        TH2F* hInterp = new TH2F("hInterp", "", 
                                nBinsX, xMin, xMax, 
                                nBinsY, yMin, yMax);

        // Remplir avec les valeurs interpolées
        for (int iy = 1; iy <= nBinsY; ++iy ) {
            for (int ix = 1; ix <= nBinsX; ++ix) {
                double x = hInterp->GetXaxis()->GetBinCenter(ix);
                double y = hInterp->GetYaxis()->GetBinCenter(iy);
                if (y<x)continue;
                double z = g2d->Interpolate(x, y);
                hInterp->SetBinContent(ix, iy, z);
            }
        }

        // Dessin en 2D lissé
        gStyle->SetNumberContours(100); // rend le gradient plus smooth
        hInterp->Draw("COLZ");
        hInterp->GetXaxis()->SetTitle("M_{#tilde{#chi}} [GeV]");
        hInterp->GetYaxis()->SetTitle("M_{#tilde{#mu}} [GeV]");
        hInterp->GetZaxis()->SetTitle(textZ);
        hInterp->GetXaxis()->SetTitleOffset(1.6);
        hInterp->GetZaxis()->SetTitleOffset(1.3);
        hInterp->GetZaxis()->SetRangeUser(0.,1);
        PlotCMSv4(pad2,YEAR, true); // Appel de la fonction PlotCMS pour ajouter le texte CMS // Appel de la fonction PlotCMS pour ajouter le texte CMS
        // g2d->Draw("surf1"); // ou "col" si tu préfères une vue 2D "lissée"
        // g2d->Draw("tri1"); // interpolation par triangulation
        c2->Update();
        TString outfileName2 = "Msmu_vs_Mneu_Interpolate_" + YEAR + "_ctau" + CTAU + ".pdf";
        if (getlimitplot)
            {
                outfileName2 = "Limit_Msmu_vs_Mneu_Interpolate_" + YEAR + "_ctau" + CTAU + ".pdf";
            }
        c2->SaveAs(outfileName2); // au cas où tu veux le sauvegarder
    return;
                    
                
    }