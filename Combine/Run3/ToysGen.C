#include <iostream>
#include <TFile.h>
#include <TH1.h>
#include <TF1.h>
#include <TCanvas.h>    
#include <TLatex.h>
#include <TNamed.h>
#include <TString.h>
#include <TMath.h>


void ToysGen(TString Var, TString Channel, TString Year) {
 
  // HTL_VtxBDT_Ave_Corr 
  // HTL_EventBDT_Corr
  // HTL_STW_6Bins_Corr 
  // !! Parameters to change
    // !! §§ ---------------------
    // TString Var = "HTL_EventBDT_Corr"; // SI VTX ou EVT BDT borne : -1,1, SI STW borne : 1,8 
    // TString Channel = "MUMU"; // Channel name : "EMU", "MUMU"
    // TString Year= "2018"; // Year : "2016PRE", "2016POST", "2017", "2018"
    // !! §§ ---------------------


  TString outputfileName = "hsolveToys";
  TString outHistoName = "hToys";
 long nToys = 100000000;
  bool SpecificFit = false; // Si true, utilise un fit spécifique, sinon fit exponentiel décroissant par défaut
  float NormIntegral = 1.0;
  int nbin = 10; // Nombre de bins de l'histogramme à générer
  float xmin = -1.0;
  float xmax = 1.0;
  float BinEdgesSTW[7] = {1,2,3,4,5,6,7};
  float BinEdgesAveBDT[11] = {-1,-0.8,-0.6,-0.4,-0.2,0.,0.2,0.4,0.6,0.8,1};
  float binEdgesEvtBDT[11] = {-1,-0.8,-0.6,-0.4,-0.2,0.,0.2,0.4,0.6,0.8,1};
  float* binEdges = nullptr;
  float par0 = 1.0;
  float par1 = 1.0;
  float par2 = 1.0;
  float par3 = 1.0;
  float par4 = 1.0;

  if (Var == "HTL_STW_6Bins_Corr") // Pas besoin
    {
        xmin = 1.0;
        xmax = 7;
        nbin = 6; // Nombre de bins pour STW
        binEdges = BinEdgesSTW; // Tableau des bords de bins pour STW
        outputfileName = "hsolveToys_"+Var+"_Data_"+Channel+"_"+Year; // Nom du fichier de sortie pour STW
        SpecificFit = false;

        // !! MuMu
        if (Year == "2024")
            {
                par0 = 698.852;
                par1 = 1.07438;
                NormIntegral = 290.157;
                nToys = 1000000; // Nombre de toys pour STW
            }
        else if (Year == "2023B")
            {
                par0 = 60.7423;
                par1 = 1.34285;
                NormIntegral = 33.8861;  
                nToys = 1000000; // Nombre de toys pour STW  
            }
        else if (Year == "2023A")
            {
                par0 = 131.051;
                par1 = 1.13072;
                NormIntegral = 57.4572; 
                nToys = 1000000; // Nombre de toys pour STW   
            }
        else if (Year == "2022B")
            {
                par0 = 246.106;
                par1 = 1.3519;
                NormIntegral = 189.433; 
                nToys = 1000000; // Nombre de toys pour STW   
            }
        else if (Year == "2022A")
            {
                par0 = 10.9289;
                par1 = 9.9999;
                NormIntegral = 20.4106; 
                nToys = 1000000; // Nombre de toys pour STW   
            }
    }
else if (Var == "HTL_VtxBDT_Ave_Corr")
    {
        xmin = -1.0;
        xmax = 1.0;
        nbin = 10; // Nombre de bins pour BDT
        binEdges = BinEdgesAveBDT; // Tableau des bords de bins pour VTX BDT
        outputfileName = "hsolveToys_"+Var+"_Data_"+Channel+"_"+Year;
        SpecificFit = false;
        // !! MuMu
        if (Year == "2024")
            {
                par0 = 3.873;
                par1 = 0.244078;

                NormIntegral = 319.593;
                nToys = 1000000; // Nombre de toys pour STW
            }
        else if (Year == "2023B")
            {
                par0 = 0.226693;
                par1 = 0.226693;

                NormIntegral = 164.066;  
                nToys = 1000000; // Nombre de toys pour STW  
            }
        else if (Year == "2023A")
            {
                par0 = 2.09043;
                par1 = 0.359927;

                NormIntegral = 52.8422; 
                nToys = 1000000; // Nombre de toys pour STW   
            }
        else if (Year == "2022B")
            {
                par0 = 4.26726;
                par1 = 0.28879;

                NormIntegral = 80.32; 
                nToys = 1000000; // Nombre de toys pour STW   
            }
        else if (Year == "2022A")
            {
                par0 = 2.04796;
                par1 =  1;

                NormIntegral = 80.32; 
                nToys = 1000000; // Nombre de toys pour STW   
            }
    }
else if (Var == "HTL_EventBDT_Corr")
    {
        xmin = -1.0;
        xmax = 1.0;
        nbin = 10; // Nombre de bins pour EVT BDT
        binEdges = binEdgesEvtBDT; // Tableau des bords de bins pour EVT BDT
        outputfileName = "hsolveToys_"+Var+"_Data_"+Channel+"_"+Year;
        // !! MuMu
        if (Year == "2024")
            {
                par0 = 0.00596189;
                par1 = 0.0845651;

                NormIntegral = 284.627;

                nToys = 5000000000; // Nombre de toys pour STW


            }
        else if (Year == "2023B")
            {
                par0 = 1.38502;
                par1 = 0.282893;
                NormIntegral = 34.3317;

                nToys = 1000000; // Nombre de toys pour STW 

            }
        else if (Year == "2023A")
            {
                par0 = 0.637821;
                par1 = 0.208901;
                NormIntegral = 56.2897; 

                nToys = 1000000; // Nombre de toys pour STW  


            }
        else if (Year == "2022B")
            {
                par0 = 0.0177421;
                par1 = 0.0987367;

                NormIntegral = 182.612; 

                nToys = 1000000; // Nombre de toys pour STW 


            }
        else if (Year == "2022A")
            {
                par0 = 6.23691;
                par1 = 0.999527;


                NormIntegral = 15.3446; 

                nToys = 1000000; // Nombre de toys pour STW 

  
            }
    }

  // !! §§ ---------------------

// !! -------------- !!
// !! -------------- !!
// !! -------------- !!
    // Définir la fonction (PDF)
    TF1* pdf = new TF1("pdf", "[0]*exp(-x/[1])", xmin,xmax); // ici une exponentielle entre 0 et 10
    pdf->SetParameter(0, par0); // lambda < 0 pour décroissance
    pdf->SetParameter(1, par1); //tau 
    if (SpecificFit)
        {
            pdf = new TF1("pdf", "[0]*exp(-x/[1])+ [4]*[2]/([2]+(x-[3])**2)", xmin, xmax); // Utiliser la fonction crystalBall
            pdf->SetParameter(0, par0); // lambda < 0 pour décroissance
            pdf->SetParameter(1, par1); //tau 
            pdf->SetParameter(2, par2); // LorentzNorm
            pdf->SetParameter(3, par3); //LorentzShift
            pdf->SetParameter(4, par4); // Scale
        }

// !! -------------- !!
// !! -------------- !!
// !! -------------- !!


    // Important : s'assurer que la fonction est positive
    if (pdf->Eval(pdf->GetXmin()) <= 0 || pdf->Eval(pdf->GetXmax()) <= 0) {
        std::cout << "Attention : la fonction n'est pas strictement positive sur le domaine !" << std::endl;
        return;
    }



    // Créer un histogramme pour les jouets
    TH1D* hToys = new TH1D("hToys", "Toys from TF1 PDF", nbin, binEdges); // Utiliser les bords de bins définis
    hToys->SetName(outHistoName); // Nom de l'histogramme
    

    // Générer les jouets
    for (int i = 0; i < nToys; ++i) {
        double x = pdf->GetRandom(); // tirage selon la forme de la fonction
        hToys->Fill(x);
    }

    hToys->Scale(1.0 / hToys->Integral()); // Normaliser l'histogramme à l'intégrale de 1
    hToys->Scale(NormIntegral); // Normaliser à l'intégrale souhaitée

    TH1F* hToys_NormUp = (TH1F*)hToys->Clone(); // Utiliser les bords de bins définis
    TH1F* hToys_NormDown =(TH1F*) hToys->Clone(); // Utiliser les bords de bins définis

    hToys_NormUp->Scale(1.5); // Normaliser l'histogramme
    hToys_NormDown->Scale(0.5); // Normaliser à l'intégrale souhaitée

    // hsolveToysNormUp 
    // hsolveToysNormDown 
    
        // Sauvegarde dans un fichier
    TFile* outFile = new TFile(outputfileName+".root", "RECREATE");
    hToys->Write();
    pdf->Write(); // si tu veux la récupérer plus tard
    outFile->Close();

            // Sauvegarde dans un fichier
    TFile* outFileUp = new TFile(outputfileName+"_NormUp.root", "RECREATE");
    hToys_NormUp->Write();
    pdf->Write(); // si tu veux la récupérer plus tard
    outFileUp->Close();


        // Sauvegarde dans un fichier
    TFile* outFileDown = new TFile(outputfileName+"_NormDown.root", "RECREATE");
    hToys_NormDown->Write();
    pdf->Write(); // si tu veux la récupérer plus tard
    outFileDown->Close();


    std::cout << " Toys générés et sauvegardés dans " << outputfileName << std::endl;
}
