#include "/opt/sbg/cms/ui2_data1/pvaucell/CMSSW_14_0_20/src/FlyingTop/FlyingTop/test/PlotCMS.h"

void plot_hToys()
{
        TString YEAR = "2024";
    // Ouvrir le fichier ROOT
    TFile *f = TFile::Open("hsolveToys_HTL_EventBDT_Corr_Data_MUMU_"+YEAR+".root");
    if (!f || f->IsZombie()) {
        printf("Erreur: impossible d'ouvrir le fichier.\n");
        return;
    }

    // Récupérer l'histogramme
    TH1F *h = (TH1F*)f->Get("hToys");
    if (!h) {
        printf("Erreur: histogramme hToys introuvable.\n");
        f->Close();
        return;
    }

    // Créer un canvas
    TCanvas *c1 = new TCanvas("c","",800,600);
    c1->SetFillColor(10);
    c1->SetFillStyle(4000);
    c1->SetBorderSize(2);
    c1->cd();
    TPad* pad1 = new TPad("pad1","This is pad1",0.01,0.03,0.99,0.99,21);
    pad1->SetFillColor(0);
    pad1->SetBorderMode(0);
    pad1->SetFrameFillColor(10);
    pad1->Draw();
    pad1->SetLogy(0);
    pad1->SetTopMargin(0.07);
    pad1->SetBottomMargin(0.15);
    pad1->SetRightMargin(0.04);
    pad1->SetLeftMargin(0.16);
    pad1->cd();
    // Enlever la boîte de stats
    gStyle->SetOptStat(0);

    // Modifier les titres
    h->SetTitle("");  // pas de titre
    h->GetXaxis()->SetTitle("Event BDT Score");
    h->GetYaxis()->SetTitle("Events");
    h->Draw("PE1same");
    h->SetMarkerStyle(20);
    h->SetMarkerSize(1);
    h->SetMarkerColor(kBlack);
    h->SetLineColor(kBlack);
    h->SetLineWidth(1);
    // Dessiner
    h->Draw();
    PlotCMSv4(pad1,YEAR,true);
    // Forcer l'affichage
    c1->Update();
    c1->SaveAs("hsolveToys_HTL_EventBDT_Corr_Data_MUMU_"+YEAR+".pdf");
    f->Close();
}
