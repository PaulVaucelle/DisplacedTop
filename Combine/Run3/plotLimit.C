#include "/opt/sbg/cms/ui2_data1/pvaucell/CMSSW_10_6_30_FLY/src/FlyingTop/FlyingTop/test/PlotCMS.h"

void plot(std::vector<double> xValues,
          std::vector<double> median,
          std::vector<double> down68,
          std::vector<double> up68,
          std::vector<double> down95,
          std::vector<double> up95) {

    // std::vector<double> xValues = {200,300,400,500};
    // std::vector<double> median = {0.0396, 0.0493 ,0.1221,  0.2939};
    // std::vector<double> down68 = { 0.0207, 0.0257, 0.0634,0.1527};
    // std::vector<double> up68 =   { 0.0761, 0.0961,0.2359, 0.5681};
    // std::vector<double> down95 = { 0.0114, 0.0146, 0.0358, 0.0861};
    // std::vector<double> up95 =   {0.1199, 0.1495, 0.3701,0.8913};

    std::vector<double> SM =   {1, 1,1,1,1,1,1,1,1};
    const int N = xValues.size();

    // On construit les graphes TGraph pour les zones
    TGraph* band95 = new TGraph(2*N);
    TGraph* band68 = new TGraph(2*N);
    TGraph* gMedian = new TGraph(N);
    TGraph* gSM = new TGraph(N);
    // Remplissage des graphes
    for (int i = 0; i < N; ++i) {
        band95->SetPoint(i,         xValues[i], up95[i]);
        band95->SetPoint(2*N - 1 - i, xValues[i], down95[i]);

        band68->SetPoint(i,         xValues[i], up68[i]);
        band68->SetPoint(2*N - 1 - i, xValues[i], down68[i]);

        gMedian->SetPoint(i, xValues[i], median[i]);
        gSM->SetPoint(i, xValues[i], SM[i]);
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
    pad->Draw();
    pad->cd();
    band95->Draw("AF");
    band95->GetYaxis()->SetRangeUser(0, 1.0);
    band95->SetTitle("");
    band95->GetYaxis()->SetTitleOffset(1.6);
    band68->Draw("F same");
    gMedian->Draw("L same");
    gSM->Draw("L same");

    // Axes
    band95->GetXaxis()->SetTitle("M_{#tilde{#mu}} [GeV]");
    band95->GetYaxis()->SetTitle("#frac{#sigma^{Exp}_{#tilde{#mu}#tilde{#mu}}}{#sigma^{th}_{#tilde{#mu}#tilde{#mu}}}    ");

    // Légende (optionnelle)
    TLegend* leg = new TLegend(0.5, 0.7, 0.7, 0.88);
    // leg->AddEntry(gSM, "RPV-Model", "l");
    leg->AddEntry(gMedian, "Expected Median", "l");
    leg->AddEntry(band68, "68% CL", "f");
    leg->AddEntry(band95, "95% CL", "f");
    leg->Draw();

    PlotCMSv2(pad, "2018", false); // Appel de la fonction PlotCMS pour ajouter le texte CMS
    c->SaveAs("brazilian_plot.pdf"); // au cas où tu veux le sauvegarder
    return;
}
