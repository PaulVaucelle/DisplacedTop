// Incl
//  ROOT headers
#include <TFile.h>
#include <TH1.h>
#include <TString.h>
#include <iostream>
#include <vector>
#include <sys/stat.h>
#include <fstream>
#include "/opt/sbg/cms/ui2_data1/pvaucell/CMSSW_10_6_30_FLY/src/FlyingTop/FlyingTop/test/MCWeights.h"

// !! && $$ ££ -- Function to store the signal parameters in a txt file
TString getVal(TString str, const TString& key, bool extra)
    {
        int pos = str.Index(key);
        if (pos == -1) return "";  // clé non trouvée
        if (extra) 
            {            
                TSubString sub = str(pos + key.Length(),4);//no need of this extra loop, i'm just dumb :D
                return sub;
            }  //4  caractères juste après la clé}
        else{
            TSubString sub = str(pos + key.Length(),3);
            return sub;  // 3 caractères juste après la clé
        }
    }
// !! && $$ ££ -- Function to change a datacard according to the signal parameters

void replaceInDatacard(TString Signal,bool extra , bool UseToys = true, TString Plot= "")
    {
        // Lire les valeurs de params.txt
        std::ifstream paramfile(Signal+".txt");
        if (!paramfile.is_open()) {
            std::cerr << "Erreur : impossible d'ouvrir le fichier des parametres du signal" << std::endl;
            return;
        }

        // on recupere les parametres du signal
        std::string year, smu_val, neu_val, ctau_val;
        std::string LUMIVal = "1.025"; // LUMIUNC
        std::string XSVal = "1.037"; // XSUNC
        std::getline(paramfile, year);
        std::getline(paramfile, smu_val);
        std::getline(paramfile, neu_val);
        std::getline(paramfile, ctau_val);
        paramfile.close();

        // LUMIUNC 1.025 
        // XSUNC 1.037

        float UncIntLumi18 = 0.025 ;
        float UncIntLumi17 = 0.023 ;
        float UncIntLumi16 = 0.012 ;
        if (year == "2018")
            {
                LUMIVal = std::to_string(1 + UncIntLumi18);
            }
        else if (year == "2017")
            {
                LUMIVal = std::to_string(1 + UncIntLumi17);
            }
        else if (year == "2016preVFP" || year == "2016")
            {
                LUMIVal = std::to_string(1 + UncIntLumi16);
            }
        else
            {
                std::cerr << "Erreur : année non reconnue" << std::endl;
                return;
            }

        PDFWeight PDFW(0);// 0 : 50%R 50% L; -1: Left et 1 Right
        float SMU_VAL = std::stof(smu_val);
        float XS = 0.001*PDFW.GetXS(SMU_VAL);// the parmaeter is the mass of the smuon
        float XS_up = 0.001*PDFW.GetXSUp(SMU_VAL);
        float ratioXS = XS_up/XS;
        XSVal = std::to_string(ratioXS);
        // float XS_down = 0.001*PDFW.GetXSDown(200);
        

        // Lire le template datacard
        std::ifstream infile("datacard_template.txt");
        if (!infile.is_open()) {
            std::cerr << "Erreur : impossible d'ouvrir datacard.txt" << std::endl;
            return;
        }

        // La datacard qui sera copiee
        std::ofstream outfile("datacard.txt");
        if (!outfile.is_open()) {
            std::cerr << "Erreur : impossible d'ecrire datacard.txt" << std::endl;
            return;
        }

        std::string line;
        while (std::getline(infile, line)) {
            size_t pos;
            while ((pos = line.find("YEAR")) != std::string::npos)
                line.replace(pos, 4, year);
            while ((pos = line.find("PLOT")) != std::string::npos)
                line.replace(pos, 4, Plot);
            while ((pos = line.find("smuXXX")) != std::string::npos)
                line.replace(pos + 3, 3, smu_val);
            while ((pos = line.find("neuYYY")) != std::string::npos)
                line.replace(pos + 3, 3, neu_val);
            while ((pos = line.find("LUMIUNC")) != std::string::npos)
                line.replace(pos , 7, LUMIVal);
            while ((pos = line.find("XSUNC")) != std::string::npos)
                line.replace(pos , 5, XSVal);
            if (extra)
                {
                    while ((pos = line.find("ctauZZZ")) != std::string::npos)
                    line.replace(pos + 4, 3, ctau_val);
                }
            else
                {
                    while ((pos = line.find("ctauZZZ")) != std::string::npos)
                    line.replace(pos + 4, 3, ctau_val);
                }
            if (UseToys)
                {
                    while ((pos = line.find("DD")) != std::string::npos)
                        line.replace(pos, 5, "hToys");
                }


                outfile << line << std::endl;
            }
        infile.close();
        outfile.close();
        std::cout << "Datacard mise a jour avec les parametres du signal " << Signal << std::endl;
        }



// Function to gather histograms from different files into one

// We take all the signal samples with all the systematics and the data samples
// We take the histograms for the different regions
// We gather them into one file for each region =>  input for datacards of Combine

void RunGatherHistograms() {
    // !! // $$ Global Paths 
    TString GlobalPath = "/opt/sbg/cms/ui2_data1/pvaucell/CMSSW_10_6_30_FLY/src/FlyingTop/FlyingTop/test/";
    TString CombinePath = "/opt/sbg/cms/ui2_data1/pvaucell/CMSSW_11_3_4/src/HiggsAnalysis/CombinedLimit/data/";
    // !! // Parameters to change
    bool GetToys = true;// true if you want to get toys for the datacards
    TString Channel = "MUMU";// MUMU ou EMU
    TString ctau ="001";
    TString YEAR = "2018";
    int Method = 2; // 0 : STW, 1 : AveBDTVtx , 2 : EvtBDT
    bool debug = false; // set to flase to run on all the signal samples
    bool Extrapolate = false; // true if you want to extrapolate to some specific values of Int Luminosity
    float scaleLumi = 1; // !! 5 =>  To scale lumi up to 400 fb-1 if extrapolate to 2024, 3.33 for 2023, else put 1 :D
    TString ExtraData = "Corr";
    bool TestOnEMU = false; // true if you want to test on EMU data
        if (TestOnEMU)
        {
            ExtraData = "BDT100_Corr";
        }
    // !! // ------------------- Additional parameters -------------------
    // !! // !! No need to change them except if changes have been made in the production/histograms for the combine fit
    TString nVtx = "2Vtx";
    TString etamax = "2p4"; 
    TString Sign = "OS";
    std::vector<TString> Plots = {""};
    TString MU = "DM";
 
    
    // !! Production directories 
    TString ProdSignal              = "Signal_"+YEAR+"_L1";// SYST_ctau100"  ou SYST_EMU_ctau100"
    TString ProdSignalJECUp         = "Signal_"+YEAR+"_JECUp";
    TString ProdSignalJECDown       = "Signal_"+YEAR+"_JECDown";
    TString ProdSignalJERUp         = "Signal_"+YEAR+"_JERUp";
    TString ProdSignalJERDown       = "Signal_"+YEAR+"_JERDown";
    TString ProdData                = "DATA_EMU_"+YEAR+"_03_02_2025";
    TString Date                    = "03_02_2025"; // Date of the production of the data

    if (YEAR == "2017" || YEAR == "2016PRE" || YEAR == "2016POST")
        {
            Date = "30_03_2025"; // Date of the production of the data
        }

    if (Channel == "EMU")
        {
            ProdSignal = "SYST_EMU_ctau100";
            ProdData = "";
        }
    if (Channel == "MUMU") // !! Production direcotries relative to the year and the global path :D
        {
            ProdSignal              = "Signal_"+YEAR+"_L1";
            ProdSignalJECUp         = "Signal_"+YEAR+"_JECUp";
            ProdSignalJECDown       = "Signal_"+YEAR+"_JECDown";
            ProdSignalJERUp         = "Signal_"+YEAR+"_JERUp";
            ProdSignalJERDown       = "Signal_"+YEAR+"_JERDown";


            ProdData =  "DATA_MUMU_"+YEAR+"_"+Date;
        }
    if (YEAR == "2017" || YEAR == "2016PRE" || YEAR == "2016POST")
        {
            ProdSignal = "Signal_"+YEAR; // Date of the production of the data
        }
    std::vector<TString> ProdSignalSyst = {
        ProdSignal, 
        ProdSignal,ProdSignal, //lumi
        ProdSignal,ProdSignal, // L1
        ProdSignal,ProdSignal, //Trigger
        ProdSignal,ProdSignal, //Pu
        ProdSignal,ProdSignal, // TopPt
        ProdSignal,ProdSignal, // PDF
        ProdSignalJECUp, ProdSignalJECDown,  // JEC
        ProdSignalJERUp, ProdSignalJERDown, // JER
        ProdSignal, ProdSignal, //MuonISO
        ProdSignal, ProdSignal, //MuonID
        ProdSignal, ProdSignal //VtwWeight


        };

    if (TestOnEMU)
        {
            ProdData = "DATA_EMU_"+YEAR+"_03_02_2025";
        }
    // !! ------------ Samples ------------------ 

    TString YEARCor = YEAR;
    if (YEAR == "2016PRE") YEARCor = "2016preVFP";
    if (YEAR == "2016POST") YEARCor = "2016";
    if (YEAR == "2017") YEARCor = "2017";
    if (YEAR == "2018") YEARCor = "2018";

    std::vector<TString> SignalSet;

    if (debug)
        {
            SignalSet ={
            "RPV_"+YEARCor+"_smu200_neu180_ctau"+ctau,
            "RPV_"+YEARCor+"_smu250_neu200_ctau"+ctau,
            "RPV_"+YEARCor+"_smu300_neu200_ctau"+ctau,
            "RPV_"+YEARCor+"_smu350_neu250_ctau"+ctau,
            "RPV_"+YEARCor+"_smu400_neu250_ctau"+ctau,
            "RPV_"+YEARCor+"_smu450_neu250_ctau"+ctau,
            "RPV_"+YEARCor+"_smu500_neu350_ctau"+ctau
            };

        }
    else
        {
             SignalSet={

            "RPV_"+YEARCor+"_smu200_neu180_ctau001","RPV_"+YEARCor+"_smu250_neu180_ctau001","RPV_"+YEARCor+"_smu250_neu200_ctau001",
            "RPV_"+YEARCor+"_smu250_neu230_ctau001","RPV_"+YEARCor+"_smu300_neu180_ctau001","RPV_"+YEARCor+"_smu300_neu200_ctau001","RPV_"+YEARCor+"_smu300_neu250_ctau001","RPV_"+YEARCor+"_smu300_neu280_ctau001",
            "RPV_"+YEARCor+"_smu350_neu180_ctau001","RPV_"+YEARCor+"_smu350_neu200_ctau001","RPV_"+YEARCor+"_smu350_neu250_ctau001","RPV_"+YEARCor+"_smu350_neu300_ctau001","RPV_"+YEARCor+"_smu350_neu330_ctau001",
            "RPV_"+YEARCor+"_smu400_neu180_ctau001","RPV_"+YEARCor+"_smu400_neu200_ctau001","RPV_"+YEARCor+"_smu400_neu250_ctau001","RPV_"+YEARCor+"_smu400_neu300_ctau001","RPV_"+YEARCor+"_smu400_neu350_ctau001",
            "RPV_"+YEARCor+"_smu400_neu380_ctau001","RPV_"+YEARCor+"_smu450_neu180_ctau001","RPV_"+YEARCor+"_smu450_neu200_ctau001","RPV_"+YEARCor+"_smu450_neu250_ctau001","RPV_"+YEARCor+"_smu450_neu300_ctau001",
            "RPV_"+YEARCor+"_smu450_neu350_ctau001","RPV_"+YEARCor+"_smu450_neu400_ctau001","RPV_"+YEARCor+"_smu450_neu430_ctau001","RPV_"+YEARCor+"_smu500_neu180_ctau001","RPV_"+YEARCor+"_smu500_neu200_ctau001",
            "RPV_"+YEARCor+"_smu500_neu250_ctau001","RPV_"+YEARCor+"_smu500_neu300_ctau001","RPV_"+YEARCor+"_smu500_neu350_ctau001","RPV_"+YEARCor+"_smu500_neu400_ctau001","RPV_"+YEARCor+"_smu500_neu450_ctau001",
            "RPV_"+YEARCor+"_smu500_neu480_ctau001",

                "RPV_"+YEARCor+"_smu200_neu180_ctau003","RPV_"+YEARCor+"_smu250_neu180_ctau003","RPV_"+YEARCor+"_smu250_neu200_ctau003",
            "RPV_"+YEARCor+"_smu250_neu230_ctau003","RPV_"+YEARCor+"_smu300_neu180_ctau003","RPV_"+YEARCor+"_smu300_neu200_ctau003","RPV_"+YEARCor+"_smu300_neu250_ctau003","RPV_"+YEARCor+"_smu300_neu280_ctau003",
            "RPV_"+YEARCor+"_smu350_neu180_ctau003","RPV_"+YEARCor+"_smu350_neu200_ctau003","RPV_"+YEARCor+"_smu350_neu250_ctau003","RPV_"+YEARCor+"_smu350_neu300_ctau003","RPV_"+YEARCor+"_smu350_neu330_ctau003",
            "RPV_"+YEARCor+"_smu400_neu180_ctau003","RPV_"+YEARCor+"_smu400_neu200_ctau003","RPV_"+YEARCor+"_smu400_neu250_ctau003","RPV_"+YEARCor+"_smu400_neu300_ctau003","RPV_"+YEARCor+"_smu400_neu350_ctau003",
            "RPV_"+YEARCor+"_smu400_neu380_ctau003","RPV_"+YEARCor+"_smu450_neu180_ctau003","RPV_"+YEARCor+"_smu450_neu200_ctau003","RPV_"+YEARCor+"_smu450_neu250_ctau003","RPV_"+YEARCor+"_smu450_neu300_ctau003",
            "RPV_"+YEARCor+"_smu450_neu350_ctau003","RPV_"+YEARCor+"_smu450_neu400_ctau003","RPV_"+YEARCor+"_smu450_neu430_ctau003","RPV_"+YEARCor+"_smu500_neu180_ctau003","RPV_"+YEARCor+"_smu500_neu200_ctau003",
            "RPV_"+YEARCor+"_smu500_neu250_ctau003","RPV_"+YEARCor+"_smu500_neu300_ctau003","RPV_"+YEARCor+"_smu500_neu350_ctau003","RPV_"+YEARCor+"_smu500_neu400_ctau003","RPV_"+YEARCor+"_smu500_neu450_ctau003",
            "RPV_"+YEARCor+"_smu500_neu480_ctau003",

                "RPV_"+YEARCor+"_smu200_neu180_ctau010","RPV_"+YEARCor+"_smu250_neu180_ctau010","RPV_"+YEARCor+"_smu250_neu200_ctau010",
            "RPV_"+YEARCor+"_smu250_neu230_ctau010","RPV_"+YEARCor+"_smu300_neu180_ctau010","RPV_"+YEARCor+"_smu300_neu200_ctau010","RPV_"+YEARCor+"_smu300_neu250_ctau010","RPV_"+YEARCor+"_smu300_neu280_ctau010",
            "RPV_"+YEARCor+"_smu350_neu180_ctau010","RPV_"+YEARCor+"_smu350_neu200_ctau010","RPV_"+YEARCor+"_smu350_neu250_ctau010","RPV_"+YEARCor+"_smu350_neu300_ctau010","RPV_"+YEARCor+"_smu350_neu330_ctau010",
            "RPV_"+YEARCor+"_smu400_neu180_ctau010","RPV_"+YEARCor+"_smu400_neu200_ctau010","RPV_"+YEARCor+"_smu400_neu250_ctau010","RPV_"+YEARCor+"_smu400_neu300_ctau010","RPV_"+YEARCor+"_smu400_neu350_ctau010",
            "RPV_"+YEARCor+"_smu400_neu380_ctau010","RPV_"+YEARCor+"_smu450_neu180_ctau010","RPV_"+YEARCor+"_smu450_neu200_ctau010","RPV_"+YEARCor+"_smu450_neu250_ctau010","RPV_"+YEARCor+"_smu450_neu300_ctau010",
            "RPV_"+YEARCor+"_smu450_neu350_ctau010","RPV_"+YEARCor+"_smu450_neu400_ctau010","RPV_"+YEARCor+"_smu450_neu430_ctau010","RPV_"+YEARCor+"_smu500_neu180_ctau010","RPV_"+YEARCor+"_smu500_neu200_ctau010",
            "RPV_"+YEARCor+"_smu500_neu250_ctau010","RPV_"+YEARCor+"_smu500_neu300_ctau010","RPV_"+YEARCor+"_smu500_neu350_ctau010","RPV_"+YEARCor+"_smu500_neu400_ctau010","RPV_"+YEARCor+"_smu500_neu450_ctau010",
            "RPV_"+YEARCor+"_smu500_neu480_ctau010",

                "RPV_"+YEARCor+"_smu200_neu180_ctau030","RPV_"+YEARCor+"_smu250_neu180_ctau030","RPV_"+YEARCor+"_smu250_neu200_ctau030",
            "RPV_"+YEARCor+"_smu250_neu230_ctau030","RPV_"+YEARCor+"_smu300_neu180_ctau030","RPV_"+YEARCor+"_smu300_neu200_ctau030","RPV_"+YEARCor+"_smu300_neu250_ctau030","RPV_"+YEARCor+"_smu300_neu280_ctau030",
            "RPV_"+YEARCor+"_smu350_neu180_ctau030","RPV_"+YEARCor+"_smu350_neu200_ctau030","RPV_"+YEARCor+"_smu350_neu250_ctau030","RPV_"+YEARCor+"_smu350_neu300_ctau030","RPV_"+YEARCor+"_smu350_neu330_ctau030",
            "RPV_"+YEARCor+"_smu400_neu180_ctau030","RPV_"+YEARCor+"_smu400_neu200_ctau030","RPV_"+YEARCor+"_smu400_neu250_ctau030","RPV_"+YEARCor+"_smu400_neu300_ctau030","RPV_"+YEARCor+"_smu400_neu350_ctau030",
            "RPV_"+YEARCor+"_smu400_neu380_ctau030","RPV_"+YEARCor+"_smu450_neu180_ctau030","RPV_"+YEARCor+"_smu450_neu200_ctau030","RPV_"+YEARCor+"_smu450_neu250_ctau030","RPV_"+YEARCor+"_smu450_neu300_ctau030",
            "RPV_"+YEARCor+"_smu450_neu350_ctau030","RPV_"+YEARCor+"_smu450_neu400_ctau030","RPV_"+YEARCor+"_smu450_neu430_ctau030","RPV_"+YEARCor+"_smu500_neu180_ctau030","RPV_"+YEARCor+"_smu500_neu200_ctau030",
            "RPV_"+YEARCor+"_smu500_neu250_ctau030","RPV_"+YEARCor+"_smu500_neu300_ctau030","RPV_"+YEARCor+"_smu500_neu350_ctau030","RPV_"+YEARCor+"_smu500_neu400_ctau030","RPV_"+YEARCor+"_smu500_neu450_ctau030",
            "RPV_"+YEARCor+"_smu500_neu480_ctau030",

            "RPV_"+YEARCor+"_smu200_neu180_ctau100","RPV_"+YEARCor+"_smu250_neu180_ctau100","RPV_"+YEARCor+"_smu250_neu200_ctau100",
            "RPV_"+YEARCor+"_smu250_neu230_ctau100","RPV_"+YEARCor+"_smu300_neu180_ctau100","RPV_"+YEARCor+"_smu300_neu200_ctau100","RPV_"+YEARCor+"_smu300_neu250_ctau100","RPV_"+YEARCor+"_smu300_neu280_ctau100",
            "RPV_"+YEARCor+"_smu350_neu180_ctau100","RPV_"+YEARCor+"_smu350_neu200_ctau100","RPV_"+YEARCor+"_smu350_neu250_ctau100","RPV_"+YEARCor+"_smu350_neu300_ctau100","RPV_"+YEARCor+"_smu350_neu330_ctau100",
            "RPV_"+YEARCor+"_smu400_neu180_ctau100","RPV_"+YEARCor+"_smu400_neu200_ctau100","RPV_"+YEARCor+"_smu400_neu250_ctau100","RPV_"+YEARCor+"_smu400_neu300_ctau100","RPV_"+YEARCor+"_smu400_neu350_ctau100",
            "RPV_"+YEARCor+"_smu400_neu380_ctau100","RPV_"+YEARCor+"_smu450_neu180_ctau100","RPV_"+YEARCor+"_smu450_neu200_ctau100","RPV_"+YEARCor+"_smu450_neu250_ctau100","RPV_"+YEARCor+"_smu450_neu300_ctau100",
            "RPV_"+YEARCor+"_smu450_neu350_ctau100","RPV_"+YEARCor+"_smu450_neu400_ctau100","RPV_"+YEARCor+"_smu450_neu430_ctau100","RPV_"+YEARCor+"_smu500_neu180_ctau100","RPV_"+YEARCor+"_smu500_neu200_ctau100",
            "RPV_"+YEARCor+"_smu500_neu250_ctau100","RPV_"+YEARCor+"_smu500_neu300_ctau100","RPV_"+YEARCor+"_smu500_neu350_ctau100","RPV_"+YEARCor+"_smu500_neu400_ctau100","RPV_"+YEARCor+"_smu500_neu450_ctau100",
            "RPV_"+YEARCor+"_smu500_neu480_ctau100",

                "RPV_"+YEARCor+"_smu200_neu180_ctau300","RPV_"+YEARCor+"_smu250_neu180_ctau300","RPV_"+YEARCor+"_smu250_neu200_ctau300",
            "RPV_"+YEARCor+"_smu250_neu230_ctau300","RPV_"+YEARCor+"_smu300_neu180_ctau300","RPV_"+YEARCor+"_smu300_neu200_ctau300","RPV_"+YEARCor+"_smu300_neu250_ctau300","RPV_"+YEARCor+"_smu300_neu280_ctau300",
            "RPV_"+YEARCor+"_smu350_neu180_ctau300","RPV_"+YEARCor+"_smu350_neu200_ctau300","RPV_"+YEARCor+"_smu350_neu250_ctau300","RPV_"+YEARCor+"_smu350_neu300_ctau300","RPV_"+YEARCor+"_smu350_neu330_ctau300",
            "RPV_"+YEARCor+"_smu400_neu180_ctau300","RPV_"+YEARCor+"_smu400_neu200_ctau300","RPV_"+YEARCor+"_smu400_neu250_ctau300","RPV_"+YEARCor+"_smu400_neu300_ctau300","RPV_"+YEARCor+"_smu400_neu350_ctau300",
            "RPV_"+YEARCor+"_smu400_neu380_ctau300","RPV_"+YEARCor+"_smu450_neu180_ctau300","RPV_"+YEARCor+"_smu450_neu200_ctau300","RPV_"+YEARCor+"_smu450_neu250_ctau300","RPV_"+YEARCor+"_smu450_neu300_ctau300",
            "RPV_"+YEARCor+"_smu450_neu350_ctau300","RPV_"+YEARCor+"_smu450_neu400_ctau300","RPV_"+YEARCor+"_smu450_neu430_ctau300","RPV_"+YEARCor+"_smu500_neu180_ctau300","RPV_"+YEARCor+"_smu500_neu200_ctau300",
            "RPV_"+YEARCor+"_smu500_neu250_ctau300","RPV_"+YEARCor+"_smu500_neu300_ctau300","RPV_"+YEARCor+"_smu500_neu350_ctau300","RPV_"+YEARCor+"_smu500_neu400_ctau300","RPV_"+YEARCor+"_smu500_neu450_ctau300",
            "RPV_"+YEARCor+"_smu500_neu480_ctau300",

                "RPV_"+YEARCor+"_smu200_neu180_ctau1000","RPV_"+YEARCor+"_smu250_neu180_ctau1000","RPV_"+YEARCor+"_smu250_neu200_ctau1000",
            "RPV_"+YEARCor+"_smu250_neu230_ctau1000","RPV_"+YEARCor+"_smu300_neu180_ctau1000","RPV_"+YEARCor+"_smu300_neu200_ctau1000","RPV_"+YEARCor+"_smu300_neu250_ctau1000","RPV_"+YEARCor+"_smu300_neu280_ctau1000",
            "RPV_"+YEARCor+"_smu350_neu180_ctau1000","RPV_"+YEARCor+"_smu350_neu200_ctau1000","RPV_"+YEARCor+"_smu350_neu250_ctau1000","RPV_"+YEARCor+"_smu350_neu300_ctau1000","RPV_"+YEARCor+"_smu350_neu330_ctau1000",
            "RPV_"+YEARCor+"_smu400_neu180_ctau1000","RPV_"+YEARCor+"_smu400_neu200_ctau1000","RPV_"+YEARCor+"_smu400_neu250_ctau1000","RPV_"+YEARCor+"_smu400_neu300_ctau1000","RPV_"+YEARCor+"_smu400_neu350_ctau1000",
            "RPV_"+YEARCor+"_smu400_neu380_ctau1000","RPV_"+YEARCor+"_smu450_neu180_ctau1000","RPV_"+YEARCor+"_smu450_neu200_ctau1000","RPV_"+YEARCor+"_smu450_neu250_ctau1000","RPV_"+YEARCor+"_smu450_neu300_ctau1000",
            "RPV_"+YEARCor+"_smu450_neu350_ctau1000","RPV_"+YEARCor+"_smu450_neu400_ctau1000","RPV_"+YEARCor+"_smu450_neu430_ctau1000","RPV_"+YEARCor+"_smu500_neu180_ctau1000","RPV_"+YEARCor+"_smu500_neu200_ctau1000",
            "RPV_"+YEARCor+"_smu500_neu250_ctau1000","RPV_"+YEARCor+"_smu500_neu300_ctau1000","RPV_"+YEARCor+"_smu500_neu350_ctau1000","RPV_"+YEARCor+"_smu500_neu400_ctau1000","RPV_"+YEARCor+"_smu500_neu450_ctau1000",
            "RPV_"+YEARCor+"_smu500_neu480_ctau1000"
            };
        }

    TString DataSet[1]={ "DoubleMuon_UL2018_MiniAODv2_GT36-v1"
    };
    if (YEAR == "2016PRE") DataSet[0] = "DoubleMuon_Run2016-HIPM_UL2016_MiniAODv2";
    if (YEAR == "2016POST") DataSet[0] = "DoubleMuon_Run2016-UL2016_MiniAODv2";
    if (YEAR == "2017") DataSet[0] = "DoubleMuon_Run2017-UL2017_MiniAODv2";

    if (TestOnEMU)
        {

            if (YEAR == "2016PRE") DataSet[0] = "MuonEG_Run2016-HIPM_UL2016_MiniAODv2";
            if (YEAR == "2016POST") DataSet[0] = "MuonEG_Run2016-UL2016_MiniAODv2";
            if (YEAR == "2017") DataSet[0] = "MuonEG_Run2017-UL2017_MiniAODv2";
            if (YEAR == "2018") DataSet[0] = "MuonEG-Run2018-UL2018_MiniAODv2_GT36-v1";
        }

    // !! ---------------------------------------------

    // TString YearSyst = YEAR;
    // if (YEAR == "2016PRE") YearSyst = "2016preVFP";
    // if (YEAR == "2016POST") YearSyst = "2016";
    // if (YEAR == "2017") YearSyst = "2017";
    // if (YEAR == "2018") YearSyst = "2018";

    // !! Systematics 
    std::vector<TString> SYST= {
        "",
        "Lumi"+YEARCor+"Up", "Lumi"+YEARCor+"Down",
        "L1"+YEARCor+"Up", "L1"+YEARCor+"Down",
        "Trigger"+YEARCor+"Up", "Trigger"+YEARCor+"Down",
        "PU"+YEARCor+"Up", "PU"+YEARCor+"Down",
        "TopPtUp", "TopPtDown",
        // "PDFUp", "PDFDown",
        // "ScaleUp", "ScaleDown",
        "XSUp", "XSDown",
        "JEC"+YEARCor+"Up", "JEC"+YEARCor+"Down",
        "JER"+YEARCor+"Up", "JER"+YEARCor+"Down",
        "MuonISO"+YEARCor+"Up", "MuonISO"+YEARCor+"Down", 
        "MuonID"+YEARCor+"Up", "MuonID"+YEARCor+"Down",
        "Vtx"+YEARCor+"Up", "Vtx"+YEARCor+"Down"
    };


    // !! Name of the histograms to gather from the ABCD regions (can be changed)

    TString htitleA = "2Vtx_LowCHI2_Lowpt_BDT_diffBin_A";
    TString htitleB = "2Vtx_HighCHI2_Lowpt_BDT_diffBin_B";
    TString htitleC = "2Vtx_LowCHI2_Highpt_BDT_diffBin_C";
    TString htitleD = "2Vtx_HighCHI2_Highpt_BDT_diffBin_D";

    TString HistoPrediData = "HTL_STW_8Bins_Corr_Data";

    // !!  Name of the output file (that will be an input of the datacards so do not change the name)
    std::vector<TString> REGIONS = {

        "tightlowlowpt_control_region",    //A
        "looselooselowlowpt_control_region",   //B
        "tighthighpt_signal_region",   //C
        "looselooselowpt_control_region"    //D

        };

    if (Method == 0)
        {
            htitleA = "hData_CRtightlowlowpt_TLVtx_SumtrackWeight_6Bins";//
            htitleB = "hData_CRlooselooselowlowpt_TLVtx_SumtrackWeight_6Bins";//
            htitleC = "hData_CRtighthighpt_TLVtx_SumtrackWeight_6Bins";//
            htitleD = "hData_CRlooselooselowpt_TLVtx_SumtrackWeight_6Bins";//
            HistoPrediData = "HTL_STW_6Bins_Corr_Data_";
            Plots[0]="STW_6Bins";
            GetToys = true;
        }
    else if (Method == 1)
        {
            htitleA = "hData_CRtightlowlowpt_2Vtx_NEWMVA_Ave";//
            htitleB = "hData_CRlooselooselowlowpt_2Vtx_NEWMVA_Ave";//
            htitleC = "hData_CRtighthighpt_2Vtx_NEWMVA_Ave";//
            htitleD = "hData_CRlooselooselowpt_2Vtx_NEWMVA_Ave";//
            HistoPrediData = "HTL_VtxBDT_Ave_Corr_Data_";
            Plots[0]="VtxBDT_Ave";
            GetToys = true;
        }
    else if (Method == 2)
        {
            htitleA = "2Vtx_VtxVtx_EVT_MVA_tightlowlowpt";//
            htitleB = "2Vtx_VtxVtx_EVT_MVA_looselooselowlowpt";//
            htitleC = "2Vtx_VtxVtx_EVT_MVA_tighthighpt";//
            htitleD = "2Vtx_VtxVtx_EVT_MVA_looselooselowpt";//  
            HistoPrediData = "HTL_EventBDT_Corr_Data_"; //HTL_EventBDT_Corr_Data_ but empty last bin in mumu 
            GetToys = true;
            Plots[0]="EventBDT";
            if (TestOnEMU)
                {
                    GetToys = true;
                }
        }
    if (Extrapolate) Plots[0]= Plots[0]+"_Extrapolate";

    // !!  Loop over all regions to gather all histos into one file
        int count = 0;   
        int countParent = 0; 
        int Total = 0;
        int TotalParent = 0;

        for (unsigned int i = 2 ; i < 3 ; i++) // There are 4 regions to loop over for the 2 Vtx category : ABCD but it's too lonng to take into account all 4 regions
            {
                TString outputFileName = REGIONS[i]+".root";
                TFile* outputFile = new TFile(outputFileName, "RECREATE");

                for (unsigned int j = 0 ; j < SYST.size(); j++) // loop over the systematics for signal samples
                    {
                        TString Prod = ProdSignalSyst[j];
                        for (unsigned int l = 0 ; l < SignalSet.size() ; l++) // loop over the signal samples
                            {
                                TString Signal = SignalSet[l];
                                TString file = GlobalPath+Prod+"/histofile_HT100_"+MU+"_"+Sign+"_"+etamax+"_"+Signal+"_"+SYST[j]+".root";
                                if (j == 0) {file = GlobalPath+Prod+"/histofile_HT100_"+MU+"_"+Sign+"_"+etamax+"_"+Signal+".root";}
                                TString shortname = Signal+"_"+SYST[j];
                                if (SYST[j] == "") shortname = Signal;
                                std::cout << shortname << std::endl;
                                
                                // Open each file
                                TFile* inputFile = TFile::Open(file);

                                if (!inputFile || inputFile->IsZombie()) {
                                    std::cerr << "Error opening file: " << file << std::endl;
                                    continue;
                                }

                                TString samplehtitleA = shortname+"_"+htitleA;//+"_"
                                TString samplehtitleB = shortname+"_"+htitleB;//+"_"
                                TString samplehtitleC = shortname+"_"+htitleC;//+"_"
                                TString samplehtitleD = shortname+"_"+htitleD;//+"_"

                                std::vector<TString> HistoNames = {
                                    
                                        samplehtitleA, 
                                        samplehtitleB, 
                                        samplehtitleC,
                                        samplehtitleD                                    
                                    };
                                

                                inputFile->cd();
                                TH1F* hist = (TH1F*)gROOT->FindObject(HistoNames[i]) ; 

                                if (!hist) {
                                    std::cerr << "Error retrieving histogram: " << HistoNames[i] << " from file: " << file << std::endl;
                                    inputFile->Close();
                                    continue;//continue
                                }

                                // Optionally clone the histogram if you want to keep it after closing the file
                                TH1F* histClone = (TH1F*)hist->Clone();
                                histClone->SetDirectory(outputFile); // Attach to output file directory
                                histClone->SetName(Signal+"_"+REGIONS[i]+"_"+SYST[j]);
                                if (Extrapolate)
                                    {
                                        histClone->Scale(scaleLumi);
                                    }

                                outputFile->cd();
                                // Write the histogram to the output file
                                histClone->Write();

                                inputFile->Close();
                                    
                            }  // loop over signal samples

                    } /// loop over the systematics for signal samples
                        
                for (unsigned int j = 0 ; j < 1 ; j++) // loop over the data samples
                    {
                        TString DATA = DataSet[j];
                        TString file = GlobalPath+ProdData+"/histofile_HT100_DM_"+Sign+"_"+etamax+"_"+DATA+"_"+ExtraData+".root";
                        if (TestOnEMU)
                            {
                                file = GlobalPath+ProdData+"/histofile_HT100_EM_"+Sign+"_"+etamax+"_"+DATA+"_"+ExtraData+".root";
                            }
                        TString shortname = DATA;
                        std::cout << shortname << std::endl;

                        // Open each file
                        TFile* inputFile = TFile::Open(file);

                        if (!inputFile || inputFile->IsZombie()) {
                            std::cerr << "Error opening file: " << file << std::endl;
                            continue;
                        }
                       
                        TString samplehtitleA = shortname+"_"+htitleA;//+"_"
                        TString samplehtitleB = shortname+"_"+htitleB;//+"_"
                        TString samplehtitleC = shortname+"_"+htitleC;//+"_"
                        TString samplehtitleD = shortname+"_"+htitleD;//+"_"
                    
                        std::vector<TString> HistoNames = {
                            
                                samplehtitleA, 
                                samplehtitleB, 
                                samplehtitleC,
                                samplehtitleD
                            
                            };
                        
                        // Retrieve the histogram
                        inputFile->cd();
                        TH1F* hist = (TH1F*)gROOT->FindObject(HistoNames[i]) ; //= (TH1F*)inputFile->Get(HistoNames[m]);
                        // std::cout << "Getting  histogram: " << HistoNames[m] << " from file: " << file << std::endl;
                        if (!hist) {
                            std::cerr << "Error retrieving histogram: " << HistoNames[i] << " from file: " << file << std::endl;
                            inputFile->Close();
                            continue;
                        }

                            TH1F* histClone2 = (TH1F*)hist->Clone();
                            histClone2->SetDirectory(outputFile);
                            histClone2->SetName("data_obs");
                            if (Extrapolate)
                                    {
                                        histClone2->Scale(scaleLumi);
                                    }
                            outputFile->cd();
                            histClone2->Write();


                        // Optionally clone the histogram if you want to keep it after closing the file
                        TH1F* histClone = (TH1F*)hist->Clone();
                        histClone->SetDirectory(outputFile); // Attach to output file directory
                        //Change name of the histograms to suit the datacards
                        histClone->SetName(DATA+"_"+REGIONS[i]+"_"+SYST[j]);

                        outputFile->cd();
                        // Write the histogram to the output file
                        histClone->Write();

                        inputFile->Close();      
                    }// Loop over data samples

            // for (unsigned int m = 0 ; m < Plots.size() ; m++)
            //     {
                // !! // Get the histograms
                    // ABCD_EMU__VTXBDT_2Vtx
                    // Open each file
                    TString file2 = GlobalPath+"ABCDReader/MUMU/"+YEAR+"/ABCD__"+HistoPrediData+YEAR+".root";//ABCD_EMU__VTXBDT_2Vtx ou ABCD_EMU__STW_2VtxAll
                    // if (Method == 2) file2 = GlobalPath+"ABCDReader/MUMU/"+YEAR+"/ABCD_MUMU__"+HistoPrediData+YEAR+".root";
                    if (TestOnEMU)
                        {
                            file2 = GlobalPath+"ABCDReader/EMU/"+YEAR+"/ABCD_EMU__"+HistoPrediData+YEAR+".root";
                        }
                    TFile* inputFile2 = TFile::Open(file2);

                    if (!inputFile2 || inputFile2->IsZombie()) {
                        std::cerr << "Error opening file2: " << file2 << std::endl;
                        continue;
                    }

                    inputFile2->cd();
                    TH1F* hist3 = (TH1F*)gROOT->FindObject("hsolve") ; //= (TH1F*)inputFile->Get(HistoNames[m]);
                    if (!hist3) {
                            std::cerr << "Error retrieving histogram: hsolve  from file: " << file2 << std::endl;
                            inputFile2->Close();
                            continue;
                        }

                    TH1F* DDUp = (TH1F*)hist3->Clone("DD_NormUp");
                    TH1F* DDDown = (TH1F*)hist3->Clone("DD_NormDown");
                    const unsigned int nbin = hist3->GetNbinsX(); 
                    for (unsigned int i =0 ; i < nbin; i++) {
                        double Yerr = hist3->GetBinError(i);
                        DDUp->SetBinContent(i,hist3->GetBinContent(i)*1.5);
                        DDDown->SetBinContent(i,hist3->GetBinContent(i)*0.5);
                    }

                    TH1F* histClone3 = (TH1F*)hist3->Clone();                
                    histClone3->SetDirectory(outputFile);
                    histClone3->SetName("DD");
                    if (Extrapolate)
                    {
                        histClone3->Scale(scaleLumi);
                    }
                    
                    DDUp->SetDirectory(outputFile);
                    DDUp->SetName("DD_NormUp");
                    if (Extrapolate)
                    {
                        DDUp->Scale(scaleLumi);
                    }
                    
                    DDDown->SetDirectory(outputFile);
                    DDDown->SetName("DD_NormDown");
                    if (Extrapolate)
                    {
                        DDDown->Scale(scaleLumi);
                    }
                    outputFile->cd();
                    histClone3->Write();
                    DDUp->Write();
                    DDDown->Write();
                    inputFile2->Close();
                // }
            // !! --end
            // !! // Get the Toys histograms

            if (GetToys)
                {
                            TString file3 = GlobalPath+"ABCDReader/Combine/hsolveToys_"+HistoPrediData+"MUMU_"+YEAR+".root";
                            if (TestOnEMU)
                                {
                                    file3 = GlobalPath+"ABCDReader/Combine/hsolveToys_"+HistoPrediData+"EMU_"+YEAR+".root";
                                }

                            // Open each file
                            TFile* inputFile3 = TFile::Open(file3);

                            if (!inputFile3 || inputFile3->IsZombie()) {
                                std::cerr << "Error opening file3: " << file3 << std::endl;
                                continue;
                            }

                            inputFile3->cd();
                            TH1F* hist4 = (TH1F*)gROOT->FindObject("hToys") ; //= (TH1F*)inputFile->Get(HistoNames[m]);
                            if (!hist4) {
                                    std::cerr << "Error retrieving histogram: hToys  from file: " << file3 << std::endl;
                                    inputFile3->Close();
                                    continue;
                                }
                            TH1F* histClone4 = (TH1F*)hist4->Clone();
                            histClone4->SetDirectory(outputFile);
                            histClone4->SetName("hToys");
                            if (Extrapolate)
                                {
                                    histClone4->Scale(scaleLumi);
                                }
                            outputFile->cd();
                            histClone4->Write();
                            inputFile3->Close();
                        

                    // !! // Get the Toys NormUp histograms
                            TString file_NormUp = GlobalPath+"ABCDReader/Combine/hsolveToys_"+HistoPrediData+"MUMU_"+YEAR+"_NormUp.root";
                            if (TestOnEMU)
                                {
                                    file_NormUp = GlobalPath+"ABCDReader/Combine/hsolveToys_"+HistoPrediData+"EMU_"+YEAR+"_NormUp.root";
                                }
                            // Open each file
                            TFile* inputFile_NormUp = TFile::Open(file_NormUp);

                            if (!inputFile_NormUp|| inputFile_NormUp->IsZombie()) {
                                std::cerr << "Error opening file_NormUp: " << file_NormUp << std::endl;
                                continue;
                            }

                            inputFile_NormUp->cd();
                            TH1F* hist_NormUp= (TH1F*)gROOT->FindObject("hToys") ; //= (TH1F*)inputFile->Get(HistoNames[m]);
                            if (!hist_NormUp) {
                                    std::cerr << "Error retrieving histogram: hToys  from file: " << file_NormUp << std::endl;
                                    inputFile_NormUp->Close();
                                    continue;
                                }
                            TH1F* histClone_NormUp = (TH1F*)hist_NormUp->Clone();
                            histClone_NormUp->SetDirectory(outputFile);
                            histClone_NormUp->SetName("hToys_NormUp");
                            if (Extrapolate)
                                {
                                    hist_NormUp->Scale(scaleLumi);
                                }
                            outputFile->cd();
                            histClone_NormUp->Write();
                            inputFile_NormUp->Close();
                    // !! // Get the Toys NormDown histograms

                            TString file_NormDown = GlobalPath+"ABCDReader/Combine/hsolveToys_"+HistoPrediData+"MUMU_"+YEAR+"_NormDown.root";
                            if (TestOnEMU)
                                {
                                    file_NormDown = GlobalPath+"ABCDReader/Combine/hsolveToys_"+HistoPrediData+"EMU_"+YEAR+"_NormDown.root";
                                }
                            // Open each file
                            TFile* inputFile_NormDown = TFile::Open(file_NormDown);

                            if (!inputFile_NormDown|| inputFile_NormDown->IsZombie()) {
                                std::cerr << "Error opening file_NormDown: " << file_NormDown << std::endl;
                                continue;
                            }

                            inputFile_NormDown->cd();
                            TH1F* hist_NormDown= (TH1F*)gROOT->FindObject("hToys") ; //= (TH1F*)inputFile->Get(HistoNames[m]);
                            if (!hist_NormDown) {
                                    std::cerr << "Error retrieving histogram: hToys_NormDown  from file: " << file_NormDown << std::endl;
                                    inputFile_NormDown->Close();
                                    continue;
                                }
                            TH1F* histClone_NormDown = (TH1F*)hist_NormDown->Clone();
                            histClone_NormDown->SetDirectory(outputFile);
                            histClone_NormDown->SetName("hToys_NormDown");
                            if (Extrapolate)
                                {
                                    histClone_NormDown->Scale(scaleLumi);
                                }
                            outputFile->cd();
                            histClone_NormDown->Write();
                            inputFile_NormDown->Close();
                    // !! --end
                }



                outputFile->Close();
                std::cout << "Histograms have been gathered and saved in " << outputFileName << std::endl;
                

            // Vérifier si le répertoire existe
            struct stat sb;
            int returnCode1 = -10;     
            int returnCode2 = -10; 
            TString ParentDirectory = CombinePath+"RPV_Run2/ABCD_"+Channel+"_"+MU+"_"+Sign+"_"+etamax+"_"+nVtx+"_"+Plots[0]+"/";
            TString Directory = CombinePath+"RPV_Run2/ABCD_"+Channel+"_"+MU+"_"+Sign+"_"+etamax+"_"+nVtx+"_"+Plots[0]+"/";



            for (unsigned int l = 0 ; l < SignalSet.size() ; l++) // Create Combine repo for each benchmark
                {
                    Directory = CombinePath+"RPV_Run2/ABCD_"+Channel+"_"+MU+"_"+Sign+"_"+etamax+"_"+nVtx+"_"+Plots[0]+"/"+SignalSet[l]+"/";
                    if (TestOnEMU)
                        {
                            Directory = CombinePath+"RPV_Run2/ABCD_EMU_"+MU+"_"+Sign+"_"+etamax+"_"+nVtx+"_"+Plots[0]+"/"+SignalSet[l]+"/";
                        }
                    if (stat(Directory, &sb) == 0)
                        {
                            cout << "The path is valid!"<<std::endl;
                            cout<< " Copying the output file to the directory: " << Directory << std::endl;
                        }
                        
                    else
                        {
                            cout << "The Path is invalid! Creating the directory";
                            returnCode1 = gSystem->Exec("mkdir "+ParentDirectory);
                            if (returnCode1 == 0) {
                                std::cout << "mkdir parent executed successfully!" << std::endl;
                            } else {
                                std::cout << "mkdir parent failed with return code: " << returnCode1 << std::endl;
                            }
                            returnCode1 = gSystem->Exec("mkdir "+Directory);
                            if (returnCode1 == 0) {
                                std::cout << "mkdir children executed successfully!" << std::endl;
                            } else {
                                std::cout << "mkdir children failed with return code: " << returnCode1 << std::endl;
                            }
                        }

                    TString smu_val = "";
                    TString neu_val =  "";
                    TString ctau_val = "";

                    if (l <= 203)
                        {
                            smu_val = getVal(SignalSet[l],"smu",false);
                            neu_val = getVal(SignalSet[l],"neu", false);
                            ctau_val = getVal(SignalSet[l],"ctau", false);
                        }
                    else 
                        {
                            smu_val = getVal(SignalSet[l],"smu",false);
                            neu_val = getVal(SignalSet[l],"neu",false);
                            ctau_val = getVal(SignalSet[l],"ctau", true);
                        }
                    std::cout << "smu_val: " << smu_val << std::endl;
                    std::cout << "neu_val: " << neu_val << std::endl;
                    std::cout << "ctau_val: " << ctau_val << std::endl;

                    TString SignalFileName = SignalSet[l]+".txt";
                    std::ofstream SignalInfoFile(SignalFileName);
                    if (!SignalInfoFile.is_open()) {
                        std::cerr << "Erreur à l'ouverture du fichier" << std::endl;
                        return;
                    }

                    // Écriture dans le fichier
                    SignalInfoFile << YEARCor << std::endl;
                    SignalInfoFile << smu_val.Data() << std::endl;
                    SignalInfoFile << neu_val.Data() << std::endl;
                    SignalInfoFile << ctau_val.Data() << std::endl;
                    SignalInfoFile.close();

                    // !! 
                    returnCode1 = gSystem->Exec("cp "+SignalFileName+" "+Directory);
                    // Optionally, check the return code to see if the command was successful
                    if (returnCode1 == 0) {
                        std::cout << "cp info executed successfully!" << std::endl;  count++;    
                    } else {
                        std::cout << "cp info failed with return code: " << returnCode1 << std::endl;
                    }
                    
                    // !! 
                    returnCode1 = gSystem->Exec("cp "+outputFileName+" "+Directory);
                    // Optionally, check the return code to see if the command was successful
                    if (returnCode1 == 0) {
                        std::cout << "cp executed successfully!" << std::endl; count++;   
                    } else {
                        std::cout << "cp failed with return code: " << returnCode1 << std::endl;
                    }

                    // !! 
                    
                    if (l <= 203)
                        {
                            replaceInDatacard(SignalSet[l], false,GetToys, Plots[0]);
                        }
                    else 
                        {
                            replaceInDatacard(SignalSet[l], true,GetToys,Plots[0]);
                        }

                    returnCode1 = gSystem->Exec("cp datacard.txt "+Directory);
                    if (returnCode1 == 0) {
                        std::cout << "cp datacard.txt executed successfully!" << std::endl; count++;   
                    } else {
                        std::cout << "cp datacard.txt failed with return code: " << returnCode1 << std::endl;
                    }
                    
                    // // !! 
                    // returnCode1 = gSystem->Exec("cp CombineCommandBlind.sh "+Directory);
                    // if (returnCode1 == 0) {
                    //     std::cout << "cp CombineCommandBlind.sh executed successfully!" << std::endl; count++;   
                    // } else {
                    //     std::cout << "cp CombineCommandBlind.sh failed with return code: " << returnCode1 << std::endl;
                    // }

                    // // !! 
                    // returnCode1 = gSystem->Exec("cp CombineCommandUnBlind.sh "+Directory);
                    // if (returnCode1 == 0) {
                    //     std::cout << "cp CombineCommandUnBlind.sh executed successfully!" << std::endl; count++;   
                    // } else {
                    //     std::cout << "cp CombineCommandUnBlind.sh failed with return code: " << returnCode1 << std::endl;
                    // }

                    Total = Total + 5; // 5 files copied for each benchmark

                } // CCreate Combine repo for each benchmark

                // // !! 
                // returnCode1 = gSystem->Exec("cp RunCombine.sh "+ParentDirectory);
                // if (returnCode1 == 0) {
                //     std::cout << "cp  RunCombine.sh  executed successfully!" << std::endl; countParent++;   
                // } else {
                //     std::cout << "cp  RunCombine.sh  failed with return code: " << returnCode1 << std::endl;
                // }

                // // !! 
                // returnCode1 = gSystem->Exec("cp RunPlotLimit.C "+ParentDirectory);
                // if (returnCode1 == 0) {
                //     std::cout << "cp RunPlotLimit.C executed successfully!" << std::endl;countParent++; 
                // } else {
                //     std::cout << "cp RunPlotLimit.C failed with return code: " << returnCode1 << std::endl;
                // }

                // // !! 
                // returnCode1 = gSystem->Exec("cp PlotLimit_Msmu_vs_Mneu.C "+ParentDirectory);
                // if (returnCode1 == 0) {
                //     std::cout << "cp PlotLimit_Msmu_vs_Mneu.C executed successfully!" << std::endl;countParent++; 
                // } else {
                //     std::cout << "cp PlotLimit_Msmu_vs_Mneu.C failed with return code: " << returnCode1 << std::endl;
                // }

                // returnCode1 = gSystem->Exec("cp PlotLimit1D_Msmu_Mneu_vs_ctau.C "+ParentDirectory);
                // if (returnCode1 == 0) {
                //     std::cout << "cp PlotLimit1D_Msmu_Mneu_vs_ctau.C executed successfully!" << std::endl;countParent++; 
                // } else {
                //     std::cout << "cp PlotLimit1D_Msmu_Mneu_vs_ctau.C failed with return code: " << returnCode1 << std::endl;
                // }

                // // !! 
                // returnCode1 = gSystem->Exec("cp PlotLimit_Mneu_vs_ctau.C "+ParentDirectory);
                // if (returnCode1 == 0) {
                //     std::cout << "cp PlotLimit_Mneu_vs_ctau.C executed successfully!" << std::endl;countParent++; 
                // } else {
                //     std::cout << "cp PlotLimit_Mneu_vs_ctau.C failed with return code: " << returnCode1 << std::endl;
                // }

                // // !! 
                // returnCode1 = gSystem->Exec("cp PlotLimit_DM_vs_ctau.C "+ParentDirectory);
                // if (returnCode1 == 0) {
                //     std::cout << "cp PlotLimit_DM_vs_ctau.C executed successfully!" << std::endl;countParent++; 
                // } else {
                //     std::cout << "cp PlotLimit_DM_vs_ctau.C failed with return code: " << returnCode1 << std::endl;
                // }

                // // !! 
                // returnCode1 = gSystem->Exec("cp PlotLimit_coupling.C "+ParentDirectory);
                // if (returnCode1 == 0) {
                //     std::cout << "cp PlotLimit_coupling.C executed successfully!" << std::endl;countParent++; 
                // } else {
                //     std::cout << "cp PlotLimit_coupling.C failed with return code: " << returnCode1 << std::endl;
                // }

                // // !! 
                // returnCode1 = gSystem->Exec("cp PlotLimit1D.C "+ParentDirectory);
                // if (returnCode1 == 0) {
                //     std::cout << "cp PlotLimit1D.C executed successfully!" << std::endl;countParent++; 
                // } else {
                //     std::cout << "cp PlotLimit1D.C failed with return code: " << returnCode1 << std::endl;
                // }

                // // !! 
                // returnCode1 = gSystem->Exec("cp PlotLimit1D_XS.C "+ParentDirectory);
                // if (returnCode1 == 0) {
                //     std::cout << "cp PlotLimit1D_XS.C executed successfully!" << std::endl;countParent++; 
                // } else {
                //     std::cout << "cp PlotLimit1D_XS.C failed with return code: " << returnCode1 << std::endl;
                // }
            TotalParent = TotalParent + 9;
        }// loop over plots

    std::cout << " !!//----------------------------------------------------------------//" << std::endl;
    std::cout << " !!// Total number of files copied for each benchmark: " << count << "sur "<<Total<<std::endl;
    std::cout << " !!// Total number of files copied for the parent directory: " << countParent <<" sur "<<TotalParent<< std::endl;
    std::cout << " !!//----------------------------------------------------------------//" << std::endl;
}// End of Gather Histograms


