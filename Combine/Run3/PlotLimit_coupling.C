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
void PlotLimit_coupling(
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
        double CTAU,
        double MSTOP,
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
            
        const int xbin = 33;
        const int ybin = 1000000;
        double xedges[xbin+1] = { 175,185,195,205,215,225,235,245,255,265,275,285,295,305,315,325,335,345,355,365,375,385,395,405,415,425,435,445,455,465,475,485,495,505}; //
        // double yedges[ybin+1] = {180, 200, 230, 250, 280, 300, 330,350,380,400,430,450,480,500}; // Mneu edges in GeV
        double lambdaedgemin = 0.000001; // Minimum value for RPV Coupling
        double lambdaedgemax = 1; // Maximum value for RPV Coupling

        // On construit les graphes TGraph pour les zones
        TH2F* band95Up = new TH2F("band95Up","",xbin,xedges,ybin ,lambdaedgemin,lambdaedgemax);
        TH2F* band95Down = new TH2F("band95Down","",xbin,xedges,ybin ,lambdaedgemin,lambdaedgemax);
        TH2F* band68Up = new TH2F("band68Up","",xbin,xedges,ybin ,lambdaedgemin,lambdaedgemax);
        TH2F* band68Down = new TH2F("band68Down","",xbin,xedges,ybin ,lambdaedgemin,lambdaedgemax);
        TH2F* gObserved = new TH2F("gObserved","",xbin,xedges,ybin ,lambdaedgemin,lambdaedgemax);
        TH2F* gMedian = new TH2F("Median","",xbin,xedges,ybin ,lambdaedgemin,lambdaedgemax);
        TH2F* gSM = new TH2F("gSM","",xbin,xedges,ybin ,lambdaedgemin,lambdaedgemax);

        TH2F* gSET = nullptr; // Pour le cas où on ne trace pas gSM

        TGraph* TrackerUp = new TGraph(N);
        TGraph* TrackerDown = new TGraph(N);

        // Remplissage des graphes
        double DM = 0.0; //
        double lambda__ = 0.0; // RPV Coupling
        double lambda__Min = 0.0; // RPV Coupling
        double lambda__Max = 0.0; // RPV Coupling
        int j = 0;
        for (unsigned int i = 0; i < smuValues.size() ; i++)
            {
                
                if (smuValues[i] != MSMU ) continue; // On ne trace que pour la valeur de MSMU donnée , || ctauValues[i] != CTAU
                DM = smuValues[i] - neuValues[i]; // Calcul de la masse du DM
                if (DM < 0){std::cout << "DM is negative for smu: " << smuValues[i] << " and neu: " << neuValues[i] << std::endl; continue;}
                j++;
                lambda__ = (0.9/(ctauValues[i]*0.1)) * pow(MSTOP / 100., 4)*pow(1/neuValues[i], 5); // RPV Coupling
                lambda__ = sqrt(lambda__);

                lambda__Min = (0.9/100.) * pow(MSTOP / 100., 4)*pow(1/neuValues[i], 5); // RPV Coupling
                lambda__Min = sqrt(lambda__Min);

                lambda__Max = (0.9/0.1) * pow(MSTOP / 100., 4)*pow(1/neuValues[i], 5); // RPV Coupling
                lambda__Max = sqrt(lambda__Max);

                if (lambda__ < 0){std::cout << "RPV Coupling is negative for smu: " << smuValues[i] << " and neu: " << neuValues[i] << std::endl; continue;}
                // band95Up->SetPoint(j,neuValues[i],lambda__, up95[i]);
                // band95Down->SetPoint(j,neuValues[i],lambda__, down95[i]);

                // band68Up->SetPoint(j,neuValues[i],lambda__, up68[i]);
                // band68Down->SetPoint(j,neuValues[i],lambda__, down68[i]);

                // gMedian->SetPoint(j,neuValues[i],lambda__, median[i]);
                // gObserved->SetPoint(j,neuValues[i],lambda__, ObservedLimit[i]);

                // std::cout << "smu: " << smuValues[i] 
                //           << ", neu: " << neuValues[i] 
                //           << ", ctau: " << ctauValues[i] 
                //           << ", lambda: " << lambda__ 
                //           << ", lambda Min: " << lambda__Min
                //           << ", lambda Max: " << lambda__Max
                //           << std::endl;

                 band95Up->Fill(neuValues[i],lambda__, up95[i]);
                band95Down->Fill(neuValues[i],lambda__, down95[i]);

                band68Up->Fill(neuValues[i],lambda__, up68[i]);
                band68Down->Fill(neuValues[i],lambda__, down68[i]);

                gMedian->Fill(neuValues[i],lambda__, median[i]);
                gObserved->Fill(neuValues[i],lambda__, ObservedLimit[i]);

                if (neuValues[i] == 0 || lambda__ == 0 || lambda__Min == 0 || lambda__Max == 0)
                    {
                        continue;
                    }
                TrackerUp->SetPoint(j,neuValues[i],lambda__Max);
                TrackerDown->SetPoint(j,neuValues[i],lambda__Min);


            }

        // // !!  checks !!//
        // std::cout<<"N = " << N << std::endl;
        // std::cout<<"TrackerUp->GetN() = " << TrackerUp->GetN() << std::endl;    
        // for (unsigned int m = 1 ; m <=TrackerUp->GetN() ; m++)
        //     {
        //         double x=0;
        //         double y=0;


        //         if (TrackerUp->GetY()[m] == 0 && TrackerUp->GetY()[m-1] > 0)
        //             {
        //                TrackerUp->SetPoint(m, TrackerUp->GetX()[m], TrackerUp->GetY()[m-1]);
        //             }
        //         if (TrackerDown->GetY()[m] == 0 && TrackerDown->GetY()[m-1] > 0)
        //             {
        //                TrackerDown->SetPoint(m, TrackerDown->GetX()[m], TrackerDown->GetY()[m-1]);
                       
        //             }
        //          TrackerUp->GetPoint(m,x,y);
        //         std::cout << "TrackerUp Point " << m << ": x = " << x << ", y = " << y << std::endl;
        //         TrackerDown->GetPoint(m,x,y);
        //         std::cout << "TrackerDown Point " << m << ": x = " << x << ", y = " << y << std::endl;
        //     } 



        // Style
        // band95->SetFillColor(kYellow);OUTMSMU
        // band95->SetLineColor(0);
        // band95Up->SetLineWidth(2);
        // band95Up->SetLineStyle(1);
        // band95Up->SetLineColor(kYellow);

        // band95Down->SetLineWidth(2);
        // band95Down->SetLineStyle(2);
        // band95Down->SetLineColor(kBlack);

        // // band68->SetFillColor(kGreen);
        // // band68->SetLineColor(0);
        // band68Up->SetLineWidth(2);
        // band68Up->SetLineStyle(1);
        // band68Up->SetLineColor(kBlack);

        // band68Down->SetLineWidth(2);
        // band68Down->SetLineStyle(2);
        // band68Down->SetLineColor(kBlack);


        gSET = gMedian;
        if (getlimitplot)
            {
            gSET = band95Up; // On utilise gObserved si on veut le plot des limites
            }
        
        if (Unblind)
            {
                gSET = gObserved; // On utilise gObserved si on veut le plot des limites
            }

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
        pad->SetLogy(true);
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

        // gSM->Draw("L same");
        gSET->Draw(DrawOption);
        gSET->GetXaxis()->SetTitle("M_{#tilde{#chi}} [GeV]");
        gSET->GetYaxis()->SetTitle("#lambda_{312}^{''}");

                TString textZ = "Median Expected Limit";
        if (getlimitplot)
            {
                textZ = "Expected Limit";
            }
        gSET->GetZaxis()->SetTitle(textZ);

        gSET->GetXaxis()->SetTitleOffset(1.6);
        gSET->GetZaxis()->SetTitleOffset(1.3);
        gSET->GetZaxis()->SetRangeUser(0.,1);
        gSET->GetXaxis()->SetRangeUser(160,500);
        if (N>= 3)
            {
                TrackerUp->SetMarkerStyle(20);
                TrackerUp->SetMarkerSize(2.5);
                TrackerUp->SetMarkerColor(kBlack);
                TrackerUp->SetLineWidth(2.);
                TrackerUp->SetLineStyle(1);
                TrackerUp->SetLineColor(kBlue);

                TrackerDown->SetMarkerStyle(20);
                TrackerDown->SetMarkerSize(2.5);
                TrackerDown->SetMarkerColor(kBlack);
                TrackerDown->SetLineWidth(2.);
                TrackerDown->SetLineStyle(1);
                TrackerDown->SetLineColor(kBlue);

                std::cout<< "Drawing TrackerUp and TrackerDown" << std::endl;
                gPad->cd();
                gPad->Update();
                
                // TrackerUp->Draw("L SAME");
                // TrackerDown->Draw("L SAME");
            }

        PlotCMSv4(pad,YEAR, true); // Appel de la fonction PlotCMS pour ajouter le texte CMS
        TString OUTMSMU = std::to_string(MSMU);
        TString OUTSTOP = std::to_string(MSTOP);
        // TString OUTCTAU = std::to_string(CTAU);
        TString outfileName = "3D_" + YEAR + "_MSMU" + OUTMSMU + "_MSTOP"+OUTSTOP+".pdf";//_CTAU"+OUTCTAU+"
        if (getlimitplot)
            {
                outfileName =  "Limit_3D_" + YEAR + "_MSMU" + OUTMSMU + "_MSTOP"+OUTSTOP+".pdf";//_CTAU"+OUTCTAU+"
            }
        c->Update();
        c->SaveAs(outfileName); // au cas où tu veux le sauvegarder
        delete band95Up;
        delete band95Down;
        delete band68Up;
        delete band68Down;
        delete gObserved;
        delete gMedian;
        delete gSM;
        // delete gSET;
        delete TrackerUp;
        delete TrackerDown;


    return;
                    
                
    }