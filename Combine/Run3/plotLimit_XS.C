void plot(std::vector<double> xValues,
          std::vector<double> median,
          std::vector<double> down68,
          std::vector<double> up68,
          std::vector<double> down95,
          std::vector<double> up95) {
    // Valeurs fictives pour exemple
    // std::vector<double> xValues = {200,300,400,500};
    // std::vector<double> median = {0.0396, 0.0493 ,0.1221,  0.2939};
    // std::vector<double> down68 = { 0.0207, 0.0257, 0.0634,0.1527};
    // std::vector<double> up68 =   { 0.0761, 0.0961,0.2359, 0.5681};
    // std::vector<double> down95 = { 0.0114, 0.0146, 0.0358, 0.0861};
    // std::vector<double> up95 =   {0.1199, 0.1495, 0.3701,0.8913};

    float XS[7] = {8.96,3.78,1.82,0.95,0.53,0.31,0.19};
    float PDFUncertainty[7]={1.8,2.1,2.4,2.7,2.9,3.2,3.5};//symetric
    float QCDScaleUncertaintyUp[7]={1.7,2.9,3.9,4.7,5.4,6.0,6.6};
    float QCDScaleUncertaintyDown[7]={1.9,2.9,3.7,4.3,4.9,5.4,5.9};
    float XSUp [7] = {1,1,1,1,1,1,1};
    float XSDown [7] = {1,1,1,1,1,1,1};
    std::vector<double> SM =   {1, 1,1,1,1,1,1};

    for (unsigned int i = 0 ; i < 7; i++)
        {
             XSUp[i]= XS[i]+XS[i]*0.01*PDFUncertainty[i]+XS[i]*0.01*QCDScaleUncertaintyUp[i]; 
        }
    for (unsigned int i = 0 ; i < 7 ; i++)
        {
             XSDown[i]= XS[i]-XS[i]*0.01*PDFUncertainty[i]-XS[i]*0.01*QCDScaleUncertaintyDown[i]; 
        }

    const int N = xValues.size();

    // On construit les graphes TGraph pour les zones
    TGraph* band95 = new TGraph(2*N);
    TGraph* band68 = new TGraph(2*N);
    TGraph* gMedian = new TGraph(N);
    TGraph* gSM = new TGraph(N);
    TGraph* gXS = new TGraph(2*N);

    // Remplissage des graphes
    for (int i = 0; i < N; ++i) {
        band95->SetPoint(i,         xValues[i], up95[i]*XS[i]);
        band95->SetPoint(2*N - 1 - i, xValues[i], down95[i]*XS[i]);

        band68->SetPoint(i,         xValues[i], up68[i]*XS[i]);
        band68->SetPoint(2*N - 1 - i, xValues[i], down68[i]*XS[i]);

        gMedian->SetPoint(i, xValues[i], median[i]*XS[i]);
        gSM->SetPoint(i, xValues[i], SM[i]*XS[i]);

        gXS->SetPoint(i, xValues[i], XSUp[i]);
        gXS->SetPoint(2*N - 1 - i, xValues[i], XSDown[i]);
    }

    // Style
    band95->SetFillColor(kYellow);
    band95->SetLineColor(0);
    band68->SetFillColor(kGreen);
    band68->SetLineColor(0);
    gMedian->SetLineWidth(2);
    gMedian->SetLineColor(kBlack);
    gSM->SetLineWidth(2);
    gSM->SetLineColor(kRed);

    // gXS->SetFillColor(kBlue);
    gXS->SetFillColorAlpha(kBlue,0.3);
    gXS->SetLineColor(0);

    // Dessin
    TCanvas* c = new TCanvas("c", "Brazilian Plot", 800, 600);
    c->cd();
    TPad* pad = new TPad("pad", "pad", 0, 0, 1, 1);
    pad->SetBottomMargin(0.15);
    pad->SetLeftMargin(0.15);
    pad->SetRightMargin(0.05);
    pad->SetTopMargin(0.05);
    pad->Draw();
    pad->cd();
    band95->Draw("AF");
    band95->GetYaxis()->SetRangeUser(0, 10.0);
    band95->SetTitle("");
    band95->GetYaxis()->SetTitleOffset(1.6);
    band68->Draw("F same");
    gMedian->Draw("L same");
    gSM->Draw("L same");
    gXS->Draw("F same");
    // Axes
    band95->GetXaxis()->SetTitle("M_{#tilde{#mu}} [GeV]");
    band95->GetYaxis()->SetTitle("#sigma^{Exp}_{#tilde{#mu}#tilde{#mu}} [fb^{-1}]");

    // Légende (optionnelle)
    TLegend* leg = new TLegend(0.5, 0.7, 0.8, 0.88);
    leg->AddEntry(gSM, "RPV-Model", "l");
    leg->AddEntry(gMedian, "Expected Median", "l");
    leg->AddEntry(band68, "68% CL", "f");
    leg->AddEntry(band95, "95% CL", "f");
    leg->Draw();

    c->SaveAs("XSbrazilian_plot.pdf"); // au cas où tu veux le sauvegarder
    return;
}
