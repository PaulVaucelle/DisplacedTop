// Include ROOT headers
#include <TFile.h>
#include <TH1.h>
#include <TString.h>
#include <iostream>
#include <vector>
#include <sys/stat.h>
#include <fstream>
#include <string>
// #include "/opt/sbg/cms/ui2_data1/pvaucell/CMSSW_11_3_4/src/HiggsAnalysis/CombinedLimit/data/RPV_UDD_2018/PlotCMS.h"

// !! Plot with Lines instead of filled areas
void PlotLimit_Mneu_vs_ctau(
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
        double MSMU,
        bool Unblind,
        bool getlimitplot = false
)
    {

        int N = 1; // Nombre de points à tracer, ici N dépend de la masse de smuon choisie
        if (MSMU == 200) N = 1;
        else if (MSMU == 250) N = 3;
        else if (MSMU == 300) N = 4;
        else if (MSMU == 350) N = 5;
        else if (MSMU == 400) N = 6;
        else if (MSMU == 450) N = 7;
        else if (MSMU == 500) N = 8;
            
        // const int xbin = 7;
        // const int ybin = 13;
        // double xedges[xbin+1] = { 0.1, 0.3, 1.0, 3.0, 10.0, 30.0, 100.0, 300.0}; // Ctau edges in cm
        // double yedges[ybin+1] = {180, 200, 230, 250, 280, 300, 330,350,380,400,430,450,480,500}; // Mneu edges in GeV

        
        const int xbin = 7;
        double xedges[xbin+1] = { 0.05,0.15,0.45,1.55,4.45,15.55,44.45,155.55}; // Ctau edges in cm
        const int ybin = 33;
        double yedges[ybin+1] = { 175,185,195,205,215,225,235,245,255,265,275,285,295,305,315,325,335,345,355,365,375,385,395,405,415,425,435,445,455,465,475,485,495,505}; // 
        
        // const int xbin = 999;
        //         double xedges[xbin+1] ;//= { 0.1, 0.3, 1.0, 3.0, 10.0, 30.0, 95, 105.0}; // Ctau edges in cm

        // for (unsigned int k = 0 ; k <= 1000; k++)
        //     {
        //         xedges[k]=0.05+ k*0.1; // Ctau edges in cm, de 0.05 à 100 cm
        //         // std::cout << "xedges[" << k << "] = " << xedges[k] << std::endl;
        //     }

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
        double DM = 0.0; //
        for (unsigned int i = 0; i < smuValues.size() ; i++)
            {
                int j = 0;
                if (smuValues[i] != MSMU) continue; // On ne trace que pour la valeur de MSMU donnée
                DM = smuValues[i] - neuValues[i]; // Calcul de la masse du DM
                if (DM < 0){std::cout << "DM is negative for smu: " << smuValues[i] << " and neu: " << neuValues[i] << std::endl; continue;}
                // std::cout << "Processing Limit for  signal: " << smuValues[i] 
                          //           << ", NEU: " << neuValues[i] 
                          //           << ", Ctau: " << ctauValues[i] 
                          //           << ", DM: " << DM 
                          //           << std::endl;
                // band95Up->SetPoint(j,ctauValues[i]*0.1,neuValues[i], up95[i]);
                // band95Down->SetPoint(j,ctauValues[i]*0.1,neuValues[i], down95[i]);

                // band68Up->SetPoint(j,ctauValues[i]*0.1,neuValues[i], up68[i]);
                // band68Down->SetPoint(j,ctauValues[i]*0.1,neuValues[i], down68[i]);

                // gMedian->SetPoint(j,ctauValues[i]*0.1,neuValues[i], median[i]);
                // gObserved->SetPoint(j,ctauValues[i]*0.1,neuValues[i], ObservedLimit[i]);
                // gSM->SetPoint(i, smuValues[i],smuValues[i], 1);

                
                band95Up->Fill(ctauValues[i]*0.1,neuValues[i], up95[i]);
                band95Down->Fill(ctauValues[i]*0.1,neuValues[i], down95[i]);

                band68Up->Fill(ctauValues[i]*0.1,neuValues[i], up68[i]);
                band68Down->Fill(ctauValues[i]*0.1,neuValues[i], down68[i]);

                gMedian->Fill(ctauValues[i]*0.1,neuValues[i], median[i]);
                gObserved->Fill(ctauValues[i]*0.1,neuValues[i], ObservedLimit[i]);
                // std::cout<<"ctauValues[i]*0.1 "<< ctauValues[i]*0.1 << std::endl;
                    
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
        pad->SetLogx(true);
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

        TString DrawOption = "COLZ text"; // Points only
        if (N > 1) DrawOption = "COLZ text"; // Lines and points if more than one point
        
                gSET->Draw(DrawOption);

        gSET->GetXaxis()->SetTitle("c#tau [cm]");
        gSET->GetYaxis()->SetTitle("M_{#tilde{#chi}} [GeV]");
                TString textZ = "Median Expected Limit";
        if (getlimitplot)
            {
                textZ = "Expected Limit";
            }
        gSET->GetZaxis()->SetTitle(textZ);
        gSET->GetXaxis()->SetTitleOffset(1.6);
        gSET->GetZaxis()->SetTitleOffset(1.3);
        gSET->GetZaxis()->SetRangeUser(0.,1);
        gSET->GetXaxis()->SetRangeUser(0.05,100.05);

        //  // !!  ---------------------
        // // Créer un TGraph2D avec les bins non vides
        // TGraph2D* g2d = new TGraph2D();
        // int idx = 0;

        // for (int ix = 1; ix <= gSET->GetNbinsX()+1; ++ix) {
        //     for (int iy = 1; iy <= gSET->GetNbinsY(); ++iy) {
        //         double content = gSET->GetBinContent(ix, iy);
        //         if (content == 0) continue;

        //         double x = gSET->GetXaxis()->GetBinCenter(ix);
        //         double y = gSET->GetYaxis()->GetBinCenter(iy);
        //         g2d->SetPoint(idx++, x, y, content);
        //         std::cout << "Processing bin: " << x 
        //                   << ", NEU: " << y 
        //                   << std::endl;
        //     }
        // }

        // // Définir une grille fine pour interpolation
        // int nBinsX = 100; // Tu peux ajuster ça pour la finesse
        // int nBinsY = 100;

        // double xMin = gSET->GetXaxis()->GetXmin();
        // double xMax = gSET->GetXaxis()->GetXmax();
        // double yMin = gSET->GetYaxis()->GetXmin()+5;
        // double yMax = gSET->GetYaxis()->GetXmax()-5;

        // TH2F* hInterp = new TH2F("hInterp", "", 
        //                         nBinsX, xMin, xMax, 
        //                         nBinsY, yMin, yMax);

        // // Remplir avec les valeurs interpolées
        // for (int ix = 1; ix <= nBinsX; ++ix) {
        //     for (int iy = 1; iy <= nBinsY; ++iy  ) {

        //         double x = hInterp->GetXaxis()->GetBinCenter(ix);
        //         double y = hInterp->GetYaxis()->GetBinCenter(iy);
        //         if (MSMU == 200 && y>185)continue;
        //         double z = g2d->Interpolate(x, y);
        //                 //         std::cout << "Processing bin v2: " << x 
        //                 //   << ", NEU: " << y 
        //                 //   << std::endl;
        //         hInterp->SetBinContent(ix, iy, z);
        //     }
        // }

        // // Dessin en 2D lissé
        // gStyle->SetNumberContours(100); // rend le gradient plus smooth
        // hInterp->Draw("COLZ");
        // hInterp->GetXaxis()->SetTitle("c#tau [cm]");
        // hInterp->GetYaxis()->SetTitle("M_{#tilde{#chi}} [GeV]");
        // hInterp->GetZaxis()->SetTitle(textZ);
        // hInterp->GetXaxis()->SetTitleOffset(1.6);
        // hInterp->GetZaxis()->SetTitleOffset(1.3);
        // hInterp->GetZaxis()->SetRangeUser(0.,1);

        // // !!  ---------------------

        PlotCMSv4(pad,YEAR, true); // Appel de la fonction PlotCMS pour ajouter le texte CMS
        TString OUTMSMU = std::to_string(MSMU);
        TString outfileName = "Mneu_vs_ctau_" + YEAR + "_MSMU" + OUTMSMU + ".pdf";
        if (getlimitplot)
            {
                outfileName = "Limit_Mneu_vs_ctau_" + YEAR + "_MSMU" + OUTMSMU + ".pdf";
            }
        c->Update();
        c->SaveAs(outfileName); //
        // c->SaveAs("Mneu_vs_ctau_" + YEAR + "_MSMU" + OUTMSMU + ".root"); //

        return;
                    
                

                
    }