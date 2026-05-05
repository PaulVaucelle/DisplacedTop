// Include ROOT headers
#include <TFile.h>
#include <TH1.h>
#include <TString.h>
#include <iostream>
#include <vector>
#include <sys/stat.h>
#include <fstream>
#include "/opt/sbg/cms/ui2_data1/pvaucell/CMSSW_14_0_20/src/FlyingTop/FlyingTop/test/MCWeights.h"

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

        float UncIntLumi24 = 0.025 ;
        float UncIntLumi23 = 0.013 ;
        float UncIntLumi22 = 0.014 ;

        if (year == "2024")
            {
                LUMIVal = std::to_string(1 + UncIntLumi24);
            }
        else if (year == "2023A" || year == "2023B")
            {
                LUMIVal = std::to_string(1 + UncIntLumi23);
            }
        else if (year == "2022A" || year == "2022B")
            {
                LUMIVal = std::to_string(1 + UncIntLumi22);
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
        TString DATACARDNAME = "datacard_template.txt";
        if (year == "2024"){ DATACARDNAME = "datacard_template_2024.txt";}
        
        std::ifstream infile(DATACARDNAME);
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
            while ((pos = line.find("mu-XXX")) != std::string::npos)
                line.replace(pos + 3, 3, smu_val);
            while ((pos = line.find("PLOT")) != std::string::npos)
                line.replace(pos, 4, Plot);
            while ((pos = line.find("hi-YYY")) != std::string::npos)
                line.replace(pos + 3, 3, neu_val);
            while ((pos = line.find("LUMIUNC")) != std::string::npos)
                line.replace(pos , 7, LUMIVal);
            while ((pos = line.find("XSUNC")) != std::string::npos)
                line.replace(pos , 5, XSVal);
            if (extra)
                {
                    while ((pos = line.find("ct-ZZZ")) != std::string::npos)
                    line.replace(pos + 3, 3, ctau_val);
                }
            else
                {
                    while ((pos = line.find("ct-ZZZ")) != std::string::npos)
                    line.replace(pos + 3, 3, ctau_val);
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

void RunAllGatherHistograms() {
    // !! // $$ Global Paths 
    TString GlobalPath = "/opt/sbg/cms/ui2_data1/pvaucell/CMSSW_14_0_20/src/FlyingTop/FlyingTop/test/";
    TString CombinePath = "/opt/sbg/cms/ui2_data1/pvaucell/CMSSW_11_3_4/src/HiggsAnalysis/CombinedLimit/data/";
    // !! // Parameters to change
    bool GetToys = true;// true if you want to get toys for the datacards
    TString Channel = "MUMU";// MUMU ou EMU although EMU does not work, you need to make some adjustement in some parameters :DD
    TString ctau ="001";
    TString YEAR = "1623"; // "1623" "1624"
    int Method = 2; // 0 : STW, 1 : AveBDTVtx , 2 : EvtBDT

    // !! // ------------------- Additional parameters -------------------
    // !! // !! No need to change them except if changes have been made in the production/histograms for the combine fit
    TString nVtx = "2Vtx";
    TString etamax = "2p4"; 
    TString Sign = "OS";
    std::vector<TString> Plots = {""};
    TString MU = "DM";
    // !! ------------ Samples ------------------ 

    TString YEARCor = YEAR;
    if (YEAR == "1623") YEARCor = "1623";
    if (YEAR == "1624") YEARCor = "1624";


    std::vector<TString> SignalSet;


             SignalSet={

                            "RPV_"+YEARCor+"_Msmu-200_Mchi-180_ct-001","RPV_"+YEARCor+"_Msmu-250_Mchi-180_ct-001","RPV_"+YEARCor+"_Msmu-250_Mchi-200_ct-001",
                            "RPV_"+YEARCor+"_Msmu-250_Mchi-230_ct-001","RPV_"+YEARCor+"_Msmu-300_Mchi-180_ct-001","RPV_"+YEARCor+"_Msmu-300_Mchi-200_ct-001","RPV_"+YEARCor+"_Msmu-300_Mchi-250_ct-001","RPV_"+YEARCor+"_Msmu-300_Mchi-280_ct-001",
                            "RPV_"+YEARCor+"_Msmu-350_Mchi-180_ct-001","RPV_"+YEARCor+"_Msmu-350_Mchi-200_ct-001","RPV_"+YEARCor+"_Msmu-350_Mchi-250_ct-001","RPV_"+YEARCor+"_Msmu-350_Mchi-300_ct-001","RPV_"+YEARCor+"_Msmu-350_Mchi-330_ct-001",
                            "RPV_"+YEARCor+"_Msmu-400_Mchi-180_ct-001","RPV_"+YEARCor+"_Msmu-400_Mchi-200_ct-001","RPV_"+YEARCor+"_Msmu-400_Mchi-250_ct-001","RPV_"+YEARCor+"_Msmu-400_Mchi-300_ct-001","RPV_"+YEARCor+"_Msmu-400_Mchi-350_ct-001",
                            "RPV_"+YEARCor+"_Msmu-400_Mchi-380_ct-001","RPV_"+YEARCor+"_Msmu-450_Mchi-180_ct-001","RPV_"+YEARCor+"_Msmu-450_Mchi-200_ct-001","RPV_"+YEARCor+"_Msmu-450_Mchi-250_ct-001","RPV_"+YEARCor+"_Msmu-450_Mchi-300_ct-001",
                            "RPV_"+YEARCor+"_Msmu-450_Mchi-350_ct-001","RPV_"+YEARCor+"_Msmu-450_Mchi-400_ct-001","RPV_"+YEARCor+"_Msmu-450_Mchi-430_ct-001",
                            "RPV_"+YEARCor+"_Msmu-500_Mchi-180_ct-001","RPV_"+YEARCor+"_Msmu-500_Mchi-200_ct-001","RPV_"+YEARCor+"_Msmu-500_Mchi-250_ct-001","RPV_"+YEARCor+"_Msmu-500_Mchi-300_ct-001","RPV_"+YEARCor+"_Msmu-500_Mchi-350_ct-001","RPV_"+YEARCor+"_Msmu-500_Mchi-400_ct-001","RPV_"+YEARCor+"_Msmu-500_Mchi-450_ct-001",
                            "RPV_"+YEARCor+"_Msmu-500_Mchi-480_ct-001",

                            "RPV_"+YEARCor+"_Msmu-200_Mchi-180_ct-003","RPV_"+YEARCor+"_Msmu-250_Mchi-180_ct-003","RPV_"+YEARCor+"_Msmu-250_Mchi-200_ct-003",
                            "RPV_"+YEARCor+"_Msmu-250_Mchi-230_ct-003","RPV_"+YEARCor+"_Msmu-300_Mchi-180_ct-003","RPV_"+YEARCor+"_Msmu-300_Mchi-200_ct-003","RPV_"+YEARCor+"_Msmu-300_Mchi-250_ct-003","RPV_"+YEARCor+"_Msmu-300_Mchi-280_ct-003",
                            "RPV_"+YEARCor+"_Msmu-350_Mchi-180_ct-003","RPV_"+YEARCor+"_Msmu-350_Mchi-200_ct-003","RPV_"+YEARCor+"_Msmu-350_Mchi-250_ct-003","RPV_"+YEARCor+"_Msmu-350_Mchi-300_ct-003","RPV_"+YEARCor+"_Msmu-350_Mchi-330_ct-003",
                            "RPV_"+YEARCor+"_Msmu-400_Mchi-180_ct-003","RPV_"+YEARCor+"_Msmu-400_Mchi-200_ct-003","RPV_"+YEARCor+"_Msmu-400_Mchi-250_ct-003","RPV_"+YEARCor+"_Msmu-400_Mchi-300_ct-003","RPV_"+YEARCor+"_Msmu-400_Mchi-350_ct-003",
                            "RPV_"+YEARCor+"_Msmu-400_Mchi-380_ct-003","RPV_"+YEARCor+"_Msmu-450_Mchi-180_ct-003","RPV_"+YEARCor+"_Msmu-450_Mchi-200_ct-003","RPV_"+YEARCor+"_Msmu-450_Mchi-250_ct-003","RPV_"+YEARCor+"_Msmu-450_Mchi-300_ct-003",
                            "RPV_"+YEARCor+"_Msmu-450_Mchi-350_ct-003","RPV_"+YEARCor+"_Msmu-450_Mchi-400_ct-003","RPV_"+YEARCor+"_Msmu-450_Mchi-430_ct-003","RPV_"+YEARCor+"_Msmu-500_Mchi-180_ct-003",
                            "RPV_"+YEARCor+"_Msmu-500_Mchi-200_ct-003","RPV_"+YEARCor+"_Msmu-500_Mchi-250_ct-003","RPV_"+YEARCor+"_Msmu-500_Mchi-300_ct-003","RPV_"+YEARCor+"_Msmu-500_Mchi-350_ct-003","RPV_"+YEARCor+"_Msmu-500_Mchi-400_ct-003","RPV_"+YEARCor+"_Msmu-500_Mchi-450_ct-003",
                            "RPV_"+YEARCor+"_Msmu-500_Mchi-480_ct-003",

                            "RPV_"+YEARCor+"_Msmu-200_Mchi-180_ct-010","RPV_"+YEARCor+"_Msmu-250_Mchi-180_ct-010","RPV_"+YEARCor+"_Msmu-250_Mchi-200_ct-010",
                            "RPV_"+YEARCor+"_Msmu-250_Mchi-230_ct-010","RPV_"+YEARCor+"_Msmu-300_Mchi-180_ct-010","RPV_"+YEARCor+"_Msmu-300_Mchi-200_ct-010","RPV_"+YEARCor+"_Msmu-300_Mchi-250_ct-010","RPV_"+YEARCor+"_Msmu-300_Mchi-280_ct-010",
                            "RPV_"+YEARCor+"_Msmu-350_Mchi-180_ct-010","RPV_"+YEARCor+"_Msmu-350_Mchi-200_ct-010","RPV_"+YEARCor+"_Msmu-350_Mchi-250_ct-010","RPV_"+YEARCor+"_Msmu-350_Mchi-300_ct-010","RPV_"+YEARCor+"_Msmu-350_Mchi-330_ct-010",
                            "RPV_"+YEARCor+"_Msmu-400_Mchi-180_ct-010","RPV_"+YEARCor+"_Msmu-400_Mchi-200_ct-010","RPV_"+YEARCor+"_Msmu-400_Mchi-250_ct-010","RPV_"+YEARCor+"_Msmu-400_Mchi-300_ct-010","RPV_"+YEARCor+"_Msmu-400_Mchi-350_ct-010",
                            "RPV_"+YEARCor+"_Msmu-400_Mchi-380_ct-010","RPV_"+YEARCor+"_Msmu-450_Mchi-180_ct-010","RPV_"+YEARCor+"_Msmu-450_Mchi-200_ct-010","RPV_"+YEARCor+"_Msmu-450_Mchi-250_ct-010","RPV_"+YEARCor+"_Msmu-450_Mchi-300_ct-010",
                            "RPV_"+YEARCor+"_Msmu-450_Mchi-350_ct-010","RPV_"+YEARCor+"_Msmu-450_Mchi-400_ct-010","RPV_"+YEARCor+"_Msmu-450_Mchi-430_ct-010","RPV_"+YEARCor+"_Msmu-500_Mchi-180_ct-010",
                            "RPV_"+YEARCor+"_Msmu-500_Mchi-200_ct-010","RPV_"+YEARCor+"_Msmu-500_Mchi-250_ct-010","RPV_"+YEARCor+"_Msmu-500_Mchi-300_ct-010","RPV_"+YEARCor+"_Msmu-500_Mchi-350_ct-010","RPV_"+YEARCor+"_Msmu-500_Mchi-400_ct-010","RPV_"+YEARCor+"_Msmu-500_Mchi-450_ct-010",
                            "RPV_"+YEARCor+"_Msmu-500_Mchi-480_ct-010",

                            "RPV_"+YEARCor+"_Msmu-200_Mchi-180_ct-030","RPV_"+YEARCor+"_Msmu-250_Mchi-180_ct-030","RPV_"+YEARCor+"_Msmu-250_Mchi-200_ct-030",
                            "RPV_"+YEARCor+"_Msmu-250_Mchi-230_ct-030","RPV_"+YEARCor+"_Msmu-300_Mchi-180_ct-030","RPV_"+YEARCor+"_Msmu-300_Mchi-200_ct-030","RPV_"+YEARCor+"_Msmu-300_Mchi-250_ct-030","RPV_"+YEARCor+"_Msmu-300_Mchi-280_ct-030",
                            "RPV_"+YEARCor+"_Msmu-350_Mchi-180_ct-030","RPV_"+YEARCor+"_Msmu-350_Mchi-200_ct-030","RPV_"+YEARCor+"_Msmu-350_Mchi-250_ct-030","RPV_"+YEARCor+"_Msmu-350_Mchi-300_ct-030","RPV_"+YEARCor+"_Msmu-350_Mchi-330_ct-030",
                            "RPV_"+YEARCor+"_Msmu-400_Mchi-180_ct-030","RPV_"+YEARCor+"_Msmu-400_Mchi-200_ct-030","RPV_"+YEARCor+"_Msmu-400_Mchi-250_ct-030","RPV_"+YEARCor+"_Msmu-400_Mchi-300_ct-030","RPV_"+YEARCor+"_Msmu-400_Mchi-350_ct-030",
                            "RPV_"+YEARCor+"_Msmu-400_Mchi-380_ct-030","RPV_"+YEARCor+"_Msmu-450_Mchi-180_ct-030","RPV_"+YEARCor+"_Msmu-450_Mchi-200_ct-030","RPV_"+YEARCor+"_Msmu-450_Mchi-250_ct-030","RPV_"+YEARCor+"_Msmu-450_Mchi-300_ct-030",
                            "RPV_"+YEARCor+"_Msmu-450_Mchi-350_ct-030","RPV_"+YEARCor+"_Msmu-450_Mchi-400_ct-030","RPV_"+YEARCor+"_Msmu-450_Mchi-430_ct-030","RPV_"+YEARCor+"_Msmu-500_Mchi-180_ct-030",
                            "RPV_"+YEARCor+"_Msmu-500_Mchi-200_ct-030","RPV_"+YEARCor+"_Msmu-500_Mchi-250_ct-030","RPV_"+YEARCor+"_Msmu-500_Mchi-300_ct-030","RPV_"+YEARCor+"_Msmu-500_Mchi-350_ct-030","RPV_"+YEARCor+"_Msmu-500_Mchi-400_ct-030","RPV_"+YEARCor+"_Msmu-500_Mchi-450_ct-030",
                            "RPV_"+YEARCor+"_Msmu-500_Mchi-480_ct-030",

                            "RPV_"+YEARCor+"_Msmu-200_Mchi-180_ct-100","RPV_"+YEARCor+"_Msmu-250_Mchi-180_ct-100","RPV_"+YEARCor+"_Msmu-250_Mchi-200_ct-100",
                            "RPV_"+YEARCor+"_Msmu-250_Mchi-230_ct-100","RPV_"+YEARCor+"_Msmu-300_Mchi-180_ct-100","RPV_"+YEARCor+"_Msmu-300_Mchi-200_ct-100","RPV_"+YEARCor+"_Msmu-300_Mchi-250_ct-100","RPV_"+YEARCor+"_Msmu-300_Mchi-280_ct-100",
                            "RPV_"+YEARCor+"_Msmu-350_Mchi-180_ct-100","RPV_"+YEARCor+"_Msmu-350_Mchi-200_ct-100","RPV_"+YEARCor+"_Msmu-350_Mchi-250_ct-100","RPV_"+YEARCor+"_Msmu-350_Mchi-300_ct-100","RPV_"+YEARCor+"_Msmu-350_Mchi-330_ct-100",
                            "RPV_"+YEARCor+"_Msmu-400_Mchi-180_ct-100","RPV_"+YEARCor+"_Msmu-400_Mchi-200_ct-100","RPV_"+YEARCor+"_Msmu-400_Mchi-250_ct-100","RPV_"+YEARCor+"_Msmu-400_Mchi-300_ct-100","RPV_"+YEARCor+"_Msmu-400_Mchi-350_ct-100",
                            "RPV_"+YEARCor+"_Msmu-400_Mchi-380_ct-100","RPV_"+YEARCor+"_Msmu-450_Mchi-180_ct-100","RPV_"+YEARCor+"_Msmu-450_Mchi-200_ct-100","RPV_"+YEARCor+"_Msmu-450_Mchi-250_ct-100","RPV_"+YEARCor+"_Msmu-450_Mchi-300_ct-100",
                            "RPV_"+YEARCor+"_Msmu-450_Mchi-350_ct-100","RPV_"+YEARCor+"_Msmu-450_Mchi-400_ct-100","RPV_"+YEARCor+"_Msmu-450_Mchi-430_ct-100","RPV_"+YEARCor+"_Msmu-500_Mchi-180_ct-100",
                            "RPV_"+YEARCor+"_Msmu-500_Mchi-200_ct-100","RPV_"+YEARCor+"_Msmu-500_Mchi-250_ct-100","RPV_"+YEARCor+"_Msmu-500_Mchi-300_ct-100","RPV_"+YEARCor+"_Msmu-500_Mchi-350_ct-100","RPV_"+YEARCor+"_Msmu-500_Mchi-400_ct-100","RPV_"+YEARCor+"_Msmu-500_Mchi-450_ct-100",
                            "RPV_"+YEARCor+"_Msmu-500_Mchi-480_ct-100",

                            "RPV_"+YEARCor+"_Msmu-200_Mchi-180_ct-300","RPV_"+YEARCor+"_Msmu-250_Mchi-180_ct-300","RPV_"+YEARCor+"_Msmu-250_Mchi-200_ct-300",
                            "RPV_"+YEARCor+"_Msmu-250_Mchi-230_ct-300","RPV_"+YEARCor+"_Msmu-300_Mchi-180_ct-300","RPV_"+YEARCor+"_Msmu-300_Mchi-200_ct-300","RPV_"+YEARCor+"_Msmu-300_Mchi-250_ct-300","RPV_"+YEARCor+"_Msmu-300_Mchi-280_ct-300",
                            "RPV_"+YEARCor+"_Msmu-350_Mchi-180_ct-300","RPV_"+YEARCor+"_Msmu-350_Mchi-200_ct-300","RPV_"+YEARCor+"_Msmu-350_Mchi-250_ct-300","RPV_"+YEARCor+"_Msmu-350_Mchi-300_ct-300","RPV_"+YEARCor+"_Msmu-350_Mchi-330_ct-300",
                            "RPV_"+YEARCor+"_Msmu-400_Mchi-180_ct-300","RPV_"+YEARCor+"_Msmu-400_Mchi-200_ct-300","RPV_"+YEARCor+"_Msmu-400_Mchi-250_ct-300","RPV_"+YEARCor+"_Msmu-400_Mchi-300_ct-300","RPV_"+YEARCor+"_Msmu-400_Mchi-350_ct-300",
                            "RPV_"+YEARCor+"_Msmu-400_Mchi-380_ct-300","RPV_"+YEARCor+"_Msmu-450_Mchi-180_ct-300","RPV_"+YEARCor+"_Msmu-450_Mchi-200_ct-300","RPV_"+YEARCor+"_Msmu-450_Mchi-250_ct-300","RPV_"+YEARCor+"_Msmu-450_Mchi-300_ct-300",
                            "RPV_"+YEARCor+"_Msmu-450_Mchi-350_ct-300","RPV_"+YEARCor+"_Msmu-450_Mchi-400_ct-300","RPV_"+YEARCor+"_Msmu-450_Mchi-430_ct-300","RPV_"+YEARCor+"_Msmu-500_Mchi-180_ct-300",
                            "RPV_"+YEARCor+"_Msmu-500_Mchi-200_ct-300","RPV_"+YEARCor+"_Msmu-500_Mchi-250_ct-300","RPV_"+YEARCor+"_Msmu-500_Mchi-300_ct-300","RPV_"+YEARCor+"_Msmu-500_Mchi-350_ct-300","RPV_"+YEARCor+"_Msmu-500_Mchi-400_ct-300","RPV_"+YEARCor+"_Msmu-500_Mchi-450_ct-300",
                            "RPV_"+YEARCor+"_Msmu-500_Mchi-480_ct-300",

                            "RPV_"+YEARCor+"_Msmu-200_Mchi-180_ct-1000","RPV_"+YEARCor+"_Msmu-250_Mchi-180_ct-1000","RPV_"+YEARCor+"_Msmu-250_Mchi-200_ct-1000",
                            "RPV_"+YEARCor+"_Msmu-250_Mchi-230_ct-1000","RPV_"+YEARCor+"_Msmu-300_Mchi-180_ct-1000","RPV_"+YEARCor+"_Msmu-300_Mchi-200_ct-1000","RPV_"+YEARCor+"_Msmu-300_Mchi-250_ct-1000","RPV_"+YEARCor+"_Msmu-300_Mchi-280_ct-1000",
                            "RPV_"+YEARCor+"_Msmu-350_Mchi-180_ct-1000","RPV_"+YEARCor+"_Msmu-350_Mchi-200_ct-1000","RPV_"+YEARCor+"_Msmu-350_Mchi-250_ct-1000","RPV_"+YEARCor+"_Msmu-350_Mchi-300_ct-1000","RPV_"+YEARCor+"_Msmu-350_Mchi-330_ct-1000",
                            "RPV_"+YEARCor+"_Msmu-400_Mchi-180_ct-1000","RPV_"+YEARCor+"_Msmu-400_Mchi-200_ct-1000","RPV_"+YEARCor+"_Msmu-400_Mchi-250_ct-1000","RPV_"+YEARCor+"_Msmu-400_Mchi-300_ct-1000","RPV_"+YEARCor+"_Msmu-400_Mchi-350_ct-1000",
                            "RPV_"+YEARCor+"_Msmu-400_Mchi-380_ct-1000","RPV_"+YEARCor+"_Msmu-450_Mchi-180_ct-1000","RPV_"+YEARCor+"_Msmu-450_Mchi-200_ct-1000","RPV_"+YEARCor+"_Msmu-450_Mchi-250_ct-1000","RPV_"+YEARCor+"_Msmu-450_Mchi-300_ct-1000",
                            "RPV_"+YEARCor+"_Msmu-450_Mchi-350_ct-1000","RPV_"+YEARCor+"_Msmu-450_Mchi-400_ct-1000","RPV_"+YEARCor+"_Msmu-450_Mchi-430_ct-1000","RPV_"+YEARCor+"_Msmu-500_Mchi-180_ct-1000",
                            "RPV_"+YEARCor+"_Msmu-500_Mchi-200_ct-1000","RPV_"+YEARCor+"_Msmu-500_Mchi-250_ct-1000","RPV_"+YEARCor+"_Msmu-500_Mchi-300_ct-1000","RPV_"+YEARCor+"_Msmu-500_Mchi-350_ct-1000","RPV_"+YEARCor+"_Msmu-500_Mchi-400_ct-1000","RPV_"+YEARCor+"_Msmu-500_Mchi-450_ct-1000",
                            "RPV_"+YEARCor+"_Msmu-500_Mchi-480_ct-1000"
            };
    
        
    // !! ---------------------------------------------
    if (Method == 0)
        {
            Plots[0]="STW_6Bins";
        }
    else if (Method == 1)
        {
            Plots[0]="VtxBDT_Ave";
        }
    else if (Method == 2)
        {
            Plots[0]="EventBDT";
        }

    // !!  Loop over all regions to gather all histos into one file
    int count = 0;   
    int countParent = 0; 
    int Total = 0;
    int TotalParent = 0;

    // Vérifier si le répertoire existe
    struct stat sb;
    int returnCode1 = -10;     
    int returnCode2 = -10; 
    TString ParentDirectory = CombinePath+"RPV_Run2Run3/ABCD_"+Channel+"_"+MU+"_"+Sign+"_"+etamax+"_"+nVtx+"_"+Plots[0]+"/";
    TString Directory = CombinePath+"RPV_Run2Run3/ABCD_"+Channel+"_"+MU+"_"+Sign+"_"+etamax+"_"+nVtx+"_"+Plots[0]+"/";



    for (unsigned int l = 0 ; l < SignalSet.size() ; l++) // Create Combine repo for each benchmark
        {
            Directory = CombinePath+"RPV_Run2Run3/ABCD_"+Channel+"_"+MU+"_"+Sign+"_"+etamax+"_"+nVtx+"_"+Plots[0]+"/"+SignalSet[l]+"/";
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
                    smu_val = getVal(SignalSet[l],"mu-",false);// to get both Msmu and MSmu
                    neu_val = getVal(SignalSet[l],"hi-", false);// to get both chi and Chi
                    ctau_val = getVal(SignalSet[l],"ct-", false);
                }
            else 
                {
                    smu_val = getVal(SignalSet[l],"mu-",false);
                    neu_val = getVal(SignalSet[l],"hi-",false);
                    ctau_val = getVal(SignalSet[l],"ct-", true);
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

            // returnCode1 = gSystem->Exec("cp datacard.txt "+Directory);
            // if (returnCode1 == 0) {
            //     std::cout << "cp datacard.txt executed successfully!" << std::endl; count++;   
            // } else {
            //     std::cout << "cp datacard.txt failed with return code: " << returnCode1 << std::endl;
            // }
            
            // !! 
            returnCode1 = gSystem->Exec("cp CombineCommandBlind.sh "+Directory);
            if (returnCode1 == 0) {
                std::cout << "cp CombineCommandBlind.sh executed successfully!" << std::endl; count++;   
            } else {
                std::cout << "cp CombineCommandBlind.sh failed with return code: " << returnCode1 << std::endl;
            }

            // !! 
            returnCode1 = gSystem->Exec("cp CombineCommandUnBlind.sh "+Directory);
            if (returnCode1 == 0) {
                std::cout << "cp CombineCommandUnBlind.sh executed successfully!" << std::endl; count++;   
            } else {
                std::cout << "cp CombineCommandUnBlind.sh failed with return code: " << returnCode1 << std::endl;
            }

            // !! 
            returnCode1 = gSystem->Exec("cp CombineDataCards.sh "+Directory);
            if (returnCode1 == 0) {
                std::cout << "cp CombineDataCards.sh executed successfully!" << std::endl; count++;   
            } else {
                std::cout << "cp CombineDataCards.sh failed with return code: " << returnCode1 << std::endl;
            }

            Total = Total + 4; // 5 files copied for each benchmark

        } // CCreate Combine repo for each benchmark

        // !! 
        returnCode1 = gSystem->Exec("cp RunCombineRun2Run3.sh "+ParentDirectory);
        if (returnCode1 == 0) {
            std::cout << "cp  RunCombineRun2Run3.sh  executed successfully!" << std::endl; countParent++;   
        } else {
            std::cout << "cp  RunCombineRun2Run3.sh  failed with return code: " << returnCode1 << std::endl;
        }

        // !! 
        returnCode1 = gSystem->Exec("cp RunCombineDatacards.sh "+ParentDirectory);
        if (returnCode1 == 0) {
            std::cout << "cp  RunCombineDatacards.sh  executed successfully!" << std::endl; countParent++;   
        } else {
            std::cout << "cp  RunCombineDatacards.sh  failed with return code: " << returnCode1 << std::endl;
        }

        // !! 
        returnCode1 = gSystem->Exec("cp RunPlotLimitRun2Run3.C "+ParentDirectory);
        if (returnCode1 == 0) {
            std::cout << "cp RunPlotLimitRun2Run3.C executed successfully!" << std::endl;countParent++; 
        } else {
            std::cout << "cp RunPlotLimitRun2Run3.C failed with return code: " << returnCode1 << std::endl;
        }

        // !! 
        returnCode1 = gSystem->Exec("cp PlotLimit_Msmu_vs_Mneu.C "+ParentDirectory);
        if (returnCode1 == 0) {
            std::cout << "cp PlotLimit_Msmu_vs_Mneu.C executed successfully!" << std::endl;countParent++; 
        } else {
            std::cout << "cp PlotLimit_Msmu_vs_Mneu.C failed with return code: " << returnCode1 << std::endl;
        }

        returnCode1 = gSystem->Exec("cp PlotLimit1D_Msmu_Mneu_vs_ctau.C "+ParentDirectory);
        if (returnCode1 == 0) {
            std::cout << "cp PlotLimit1D_Msmu_Mneu_vs_ctau.C executed successfully!" << std::endl;countParent++; 
        } else {
            std::cout << "cp PlotLimit1D_Msmu_Mneu_vs_ctau.C failed with return code: " << returnCode1 << std::endl;
        }

        // !! 
        returnCode1 = gSystem->Exec("cp PlotLimit_Mneu_vs_ctau.C "+ParentDirectory);
        if (returnCode1 == 0) {
            std::cout << "cp PlotLimit_Mneu_vs_ctau.C executed successfully!" << std::endl;countParent++; 
        } else {
            std::cout << "cp PlotLimit_Mneu_vs_ctau.C failed with return code: " << returnCode1 << std::endl;
        }

        // !! 
        returnCode1 = gSystem->Exec("cp PlotLimit_DM_vs_ctau.C "+ParentDirectory);
        if (returnCode1 == 0) {
            std::cout << "cp PlotLimit_DM_vs_ctau.C executed successfully!" << std::endl;countParent++; 
        } else {
            std::cout << "cp PlotLimit_DM_vs_ctau.C failed with return code: " << returnCode1 << std::endl;
        }

        // !! 
        returnCode1 = gSystem->Exec("cp PlotLimit_coupling.C "+ParentDirectory);
        if (returnCode1 == 0) {
            std::cout << "cp PlotLimit_coupling.C executed successfully!" << std::endl;countParent++; 
        } else {
            std::cout << "cp PlotLimit_coupling.C failed with return code: " << returnCode1 << std::endl;
        }

        // !! 
        returnCode1 = gSystem->Exec("cp PlotLimit1D.C "+ParentDirectory);
        if (returnCode1 == 0) {
            std::cout << "cp PlotLimit1D.C executed successfully!" << std::endl;countParent++; 
        } else {
            std::cout << "cp PlotLimit1D.C failed with return code: " << returnCode1 << std::endl;
        }

        // !! 
        returnCode1 = gSystem->Exec("cp PlotLimit1D_XS.C "+ParentDirectory);
        if (returnCode1 == 0) {
            std::cout << "cp PlotLimit1D_XS.C executed successfully!" << std::endl;countParent++; 
        } else {
            std::cout << "cp PlotLimit1D_XS.C failed with return code: " << returnCode1 << std::endl;
        }
    TotalParent = TotalParent + 10;
        

    std::cout << " !!//----------------------------------------------------------------//" << std::endl;
    std::cout << " !!// Total number of files copied for each benchmark: " << count << "sur "<<Total<<std::endl;
    std::cout << " !!// Total number of files copied for the parent directory: " << countParent <<" sur "<<TotalParent<< std::endl;
    std::cout << " !!//----------------------------------------------------------------//" << std::endl;
}// End of Gather Histograms


