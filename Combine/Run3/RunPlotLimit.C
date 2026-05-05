// Include ROOT headers
#include <TFile.h>
#include <TH1.h>
#include <TString.h>
#include <iostream>
#include <vector>
#include <sys/stat.h>
#include <fstream>
#include "/opt/sbg/cms/ui2_data1/pvaucell/CMSSW_14_0_20/src/FlyingTop/FlyingTop/test/PlotCMS.h"
#include "./PlotLimit1D.C"
#include "./PlotLimit1D_XS.C"
#include "./PlotLimit_DM_vs_ctau.C"
#include "./PlotLimit_Mneu_vs_ctau.C"
#include "./PlotLimit_Msmu_vs_Mneu.C"
#include "./PlotLimit_coupling.C"
#include "./PlotLimit1D_Msmu_Mneu_vs_ctau.C"

std::vector<double> parseCombineOutput(TString filename) {
    std::ifstream infile(filename);
    std::vector<double> results;
    std::vector<double> resutls;
    resutls.push_back(-1.);
    if (!infile.is_open()) {
        std::cerr << "Erreur : impossible d'ouvrir " << filename << std::endl;
        return resutls;
    }

    std::string line;
    std::map<std::string, float> limits;
    
    while (std::getline(infile, line)) {
        std::size_t found = line.find("Expected");
        if (found != std::string::npos) {
            std::istringstream iss(line);
            std::string label, percent, colon, r, lt;
            double value;
            iss >> label >> percent >> colon >> r >> lt >> value;
            // std::cout << "Processing line: " << line << std::endl;
            // std::cout<< " label : "<<label<<" percent : "<<percent<<" r : "<<r<<" lt : "<<lt<<" value : "<<value<<std::endl;
            // Exemple : "Expected 50.0%" → clé = "50.0%"
            limits[percent] = std::stod(lt);
            // std::cout << "Found: " << percent << " with value: " << lt << std::endl;
            results.push_back(std::stod(lt));

            // Expected  2.5%: r < 0.1234
            // Expected 16.0%: r < 0.2345
            // Expected 50.0%: r < 0.3456
            // Expected 84.0%: r < 0.4567
            // Expected 97.5%: r < 0.5678
        }
    }

        std::string line_Obs;
        while (std::getline(infile, line_Obs)) {
        std::size_t found = line.find("Observed");
        if (found != std::string::npos) {
            std::istringstream iss(line_Obs);
            std::string label, percent, colon, r, lt;
            double value;
            iss >> label >> percent >> colon >> r >> lt >> value;
            std::cout << "Processing line: " << line << std::endl;
            std::cout<< " label : "<<label<<" percent : "<<percent<<" r : "<<r<<" lt : "<<lt<<" value : "<<value<<std::endl;
            // limits[percent] = std::stod(lt);
            results.push_back(std::stod(lt));
            // Observed Limit: r < 1.6281
        }
    }
    // Affichage des résultats
    // for (const auto& kv : limits) {
    //     std::cout << kv.first << " : r < " << kv.second << std::endl;
    // }
    infile.close();
    return results;



}

void RunPlotLimit()
    {
    bool debug = false;
    TString ctau = "001"; // Default value for ctau for the debug mode
    TString YEAR = "2018"; // Default value for YEAR
    bool Unblind = false; // Set to true if you want to unblind the results
    bool getlimitplot = true; // Set to true if you want to get the limit plot instead of median expected
    
                    // !! ------------ Samples ------------------ 
    gROOT->SetBatch(kTRUE); 
    std::vector<TString> SignalSet;


    TString YEARCor = YEAR;
    if (YEAR == "2022A") YEARCor = "2022A";
    if (YEAR == "2022B") YEARCor = "2022B";
    if (YEAR == "2023A") YEARCor = "2023A";
    if (YEAR == "2023B") YEARCor = "2023B";
    if (YEAR == "2024") YEARCor = "2024";


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
    else if (YEAR == "2022A" || YEAR == "2022B" || YEAR == "2023A" || YEAR == "2023B" )
        {
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
        }
    else if (YEAR == "2024")
        {
                SignalSet={

                        "RPV_2024_Par-ct-001-MChi-180-MSmu-200","RPV_2024_Par-ct-001-MChi-180-MSmu-250","RPV_2024_Par-ct-001-MChi-200-MSmu-250","RPV_2024_Par-ct-001-MChi-230-MSmu-250",
                        "RPV_2024_Par-ct-001-MChi-180-MSmu-300","RPV_2024_Par-ct-001-MChi-200-MSmu-300","RPV_2024_Par-ct-001-MChi-250-MSmu-300","RPV_2024_Par-ct-001-MChi-280-MSmu-300",
                        "RPV_2024_Par-ct-001-MChi-180-MSmu-350","RPV_2024_Par-ct-001-MChi-200-MSmu-350","RPV_2024_Par-ct-001-MChi-250-MSmu-350","RPV_2024_Par-ct-001-MChi-300-MSmu-350","RPV_2024_Par-ct-001-MChi-330-MSmu-350",
                        "RPV_2024_Par-ct-001-MChi-180-MSmu-400","RPV_2024_Par-ct-001-MChi-200-MSmu-400","RPV_2024_Par-ct-001-MChi-250-MSmu-400","RPV_2024_Par-ct-001-MChi-300-MSmu-400","RPV_2024_Par-ct-001-MChi-350-MSmu-400","RPV_2024_Par-ct-001-MChi-380-MSmu-400",
                        "RPV_2024_Par-ct-001-MChi-180-MSmu-450","RPV_2024_Par-ct-001-MChi-200-MSmu-450","RPV_2024_Par-ct-001-MChi-250-MSmu-450","RPV_2024_Par-ct-001-MChi-300-MSmu-450","RPV_2024_Par-ct-001-MChi-350-MSmu-450","RPV_2024_Par-ct-001-MChi-400-MSmu-450","RPV_2024_Par-ct-001-MChi-430-MSmu-450",
                        "RPV_2024_Par-ct-001-MChi-180-MSmu-500","RPV_2024_Par-ct-001-MChi-200-MSmu-500","RPV_2024_Par-ct-001-MChi-250-MSmu-500","RPV_2024_Par-ct-001-MChi-300-MSmu-500","RPV_2024_Par-ct-001-MChi-350-MSmu-500","RPV_2024_Par-ct-001-MChi-400-MSmu-500","RPV_2024_Par-ct-001-MChi-450-MSmu-500","RPV_2024_Par-ct-001-MChi-480-MSmu-500"

                        "RPV_2024_Par-ct-003-MChi-180-MSmu-200","RPV_2024_Par-ct-003-MChi-180-MSmu-250","RPV_2024_Par-ct-003-MChi-200-MSmu-250","RPV_2024_Par-ct-003-MChi-230-MSmu-250",
                        "RPV_2024_Par-ct-003-MChi-180-MSmu-300","RPV_2024_Par-ct-003-MChi-200-MSmu-300","RPV_2024_Par-ct-003-MChi-250-MSmu-300","RPV_2024_Par-ct-003-MChi-280-MSmu-300",
                        "RPV_2024_Par-ct-003-MChi-180-MSmu-350","RPV_2024_Par-ct-003-MChi-200-MSmu-350","RPV_2024_Par-ct-003-MChi-250-MSmu-350","RPV_2024_Par-ct-003-MChi-300-MSmu-350","RPV_2024_Par-ct-003-MChi-330-MSmu-350",
                        "RPV_2024_Par-ct-003-MChi-180-MSmu-400","RPV_2024_Par-ct-003-MChi-200-MSmu-400","RPV_2024_Par-ct-003-MChi-250-MSmu-400","RPV_2024_Par-ct-003-MChi-300-MSmu-400","RPV_2024_Par-ct-003-MChi-350-MSmu-400","RPV_2024_Par-ct-003-MChi-380-MSmu-400",
                        "RPV_2024_Par-ct-003-MChi-180-MSmu-450","RPV_2024_Par-ct-003-MChi-200-MSmu-450","RPV_2024_Par-ct-003-MChi-250-MSmu-450","RPV_2024_Par-ct-003-MChi-300-MSmu-450","RPV_2024_Par-ct-003-MChi-350-MSmu-450","RPV_2024_Par-ct-003-MChi-400-MSmu-450","RPV_2024_Par-ct-003-MChi-430-MSmu-450",
                        "RPV_2024_Par-ct-003-MChi-180-MSmu-500","RPV_2024_Par-ct-003-MChi-200-MSmu-500","RPV_2024_Par-ct-003-MChi-250-MSmu-500","RPV_2024_Par-ct-003-MChi-300-MSmu-500","RPV_2024_Par-ct-003-MChi-350-MSmu-500","RPV_2024_Par-ct-003-MChi-400-MSmu-500","RPV_2024_Par-ct-003-MChi-450-MSmu-500","RPV_2024_Par-ct-003-MChi-480-MSmu-500"

                        "RPV_2024_Par-ct-010-MChi-180-MSmu-200","RPV_2024_Par-ct-010-MChi-180-MSmu-250","RPV_2024_Par-ct-010-MChi-200-MSmu-250","RPV_2024_Par-ct-010-MChi-230-MSmu-250",
                        "RPV_2024_Par-ct-010-MChi-180-MSmu-300","RPV_2024_Par-ct-010-MChi-200-MSmu-300","RPV_2024_Par-ct-010-MChi-250-MSmu-300","RPV_2024_Par-ct-010-MChi-280-MSmu-300",
                        "RPV_2024_Par-ct-010-MChi-180-MSmu-350","RPV_2024_Par-ct-010-MChi-200-MSmu-350","RPV_2024_Par-ct-010-MChi-250-MSmu-350","RPV_2024_Par-ct-010-MChi-300-MSmu-350","RPV_2024_Par-ct-010-MChi-330-MSmu-350",
                        "RPV_2024_Par-ct-010-MChi-180-MSmu-400","RPV_2024_Par-ct-010-MChi-200-MSmu-400","RPV_2024_Par-ct-010-MChi-250-MSmu-400","RPV_2024_Par-ct-010-MChi-300-MSmu-400","RPV_2024_Par-ct-010-MChi-350-MSmu-400","RPV_2024_Par-ct-010-MChi-380-MSmu-400",
                        "RPV_2024_Par-ct-010-MChi-180-MSmu-450","RPV_2024_Par-ct-010-MChi-200-MSmu-450","RPV_2024_Par-ct-010-MChi-250-MSmu-450","RPV_2024_Par-ct-010-MChi-300-MSmu-450","RPV_2024_Par-ct-010-MChi-350-MSmu-450","RPV_2024_Par-ct-010-MChi-400-MSmu-450","RPV_2024_Par-ct-010-MChi-430-MSmu-450",
                        "RPV_2024_Par-ct-010-MChi-180-MSmu-500","RPV_2024_Par-ct-010-MChi-200-MSmu-500","RPV_2024_Par-ct-010-MChi-250-MSmu-500","RPV_2024_Par-ct-010-MChi-300-MSmu-500","RPV_2024_Par-ct-010-MChi-350-MSmu-500","RPV_2024_Par-ct-010-MChi-400-MSmu-500","RPV_2024_Par-ct-010-MChi-450-MSmu-500","RPV_2024_Par-ct-010-MChi-480-MSmu-500"

                        "RPV_2024_Par-ct-030-MChi-180-MSmu-200","RPV_2024_Par-ct-030-MChi-180-MSmu-250","RPV_2024_Par-ct-030-MChi-200-MSmu-250","RPV_2024_Par-ct-030-MChi-230-MSmu-250",
                        "RPV_2024_Par-ct-030-MChi-180-MSmu-300","RPV_2024_Par-ct-030-MChi-200-MSmu-300","RPV_2024_Par-ct-030-MChi-250-MSmu-300","RPV_2024_Par-ct-030-MChi-280-MSmu-300",
                        "RPV_2024_Par-ct-030-MChi-180-MSmu-350","RPV_2024_Par-ct-030-MChi-200-MSmu-350","RPV_2024_Par-ct-030-MChi-250-MSmu-350","RPV_2024_Par-ct-030-MChi-300-MSmu-350","RPV_2024_Par-ct-030-MChi-330-MSmu-350",
                        "RPV_2024_Par-ct-030-MChi-180-MSmu-400","RPV_2024_Par-ct-030-MChi-200-MSmu-400","RPV_2024_Par-ct-030-MChi-250-MSmu-400","RPV_2024_Par-ct-030-MChi-300-MSmu-400","RPV_2024_Par-ct-030-MChi-350-MSmu-400","RPV_2024_Par-ct-030-MChi-380-MSmu-400",
                        "RPV_2024_Par-ct-030-MChi-180-MSmu-450","RPV_2024_Par-ct-030-MChi-200-MSmu-450","RPV_2024_Par-ct-030-MChi-250-MSmu-450","RPV_2024_Par-ct-030-MChi-300-MSmu-450","RPV_2024_Par-ct-030-MChi-350-MSmu-450","RPV_2024_Par-ct-030-MChi-400-MSmu-450","RPV_2024_Par-ct-030-MChi-430-MSmu-450",
                        "RPV_2024_Par-ct-030-MChi-180-MSmu-500","RPV_2024_Par-ct-030-MChi-200-MSmu-500","RPV_2024_Par-ct-030-MChi-250-MSmu-500","RPV_2024_Par-ct-030-MChi-300-MSmu-500","RPV_2024_Par-ct-030-MChi-350-MSmu-500","RPV_2024_Par-ct-030-MChi-400-MSmu-500","RPV_2024_Par-ct-030-MChi-450-MSmu-500","RPV_2024_Par-ct-030-MChi-480-MSmu-500"

                        "RPV_2024_Par-ct-100-MChi-180-MSmu-200","RPV_2024_Par-ct-100-MChi-180-MSmu-250","RPV_2024_Par-ct-100-MChi-200-MSmu-250","RPV_2024_Par-ct-100-MChi-230-MSmu-250",
                        "RPV_2024_Par-ct-100-MChi-180-MSmu-300","RPV_2024_Par-ct-100-MChi-200-MSmu-300","RPV_2024_Par-ct-100-MChi-250-MSmu-300","RPV_2024_Par-ct-100-MChi-280-MSmu-300",
                        "RPV_2024_Par-ct-100-MChi-180-MSmu-350","RPV_2024_Par-ct-100-MChi-200-MSmu-350","RPV_2024_Par-ct-100-MChi-250-MSmu-350","RPV_2024_Par-ct-100-MChi-300-MSmu-350","RPV_2024_Par-ct-100-MChi-330-MSmu-350",
                        "RPV_2024_Par-ct-100-MChi-180-MSmu-400","RPV_2024_Par-ct-100-MChi-200-MSmu-400","RPV_2024_Par-ct-100-MChi-250-MSmu-400","RPV_2024_Par-ct-100-MChi-300-MSmu-400","RPV_2024_Par-ct-100-MChi-350-MSmu-400","RPV_2024_Par-ct-100-MChi-380-MSmu-400",
                        "RPV_2024_Par-ct-100-MChi-180-MSmu-450","RPV_2024_Par-ct-100-MChi-200-MSmu-450","RPV_2024_Par-ct-100-MChi-250-MSmu-450","RPV_2024_Par-ct-100-MChi-300-MSmu-450","RPV_2024_Par-ct-100-MChi-350-MSmu-450","RPV_2024_Par-ct-100-MChi-400-MSmu-450","RPV_2024_Par-ct-100-MChi-430-MSmu-450",
                        "RPV_2024_Par-ct-100-MChi-180-MSmu-500","RPV_2024_Par-ct-100-MChi-200-MSmu-500","RPV_2024_Par-ct-100-MChi-250-MSmu-500","RPV_2024_Par-ct-100-MChi-300-MSmu-500","RPV_2024_Par-ct-100-MChi-350-MSmu-500","RPV_2024_Par-ct-100-MChi-400-MSmu-500","RPV_2024_Par-ct-100-MChi-450-MSmu-500","RPV_2024_Par-ct-100-MChi-480-MSmu-500"

                        "RPV_2024_Par-ct-300-MChi-180-MSmu-200","RPV_2024_Par-ct-300-MChi-180-MSmu-250","RPV_2024_Par-ct-300-MChi-200-MSmu-250","RPV_2024_Par-ct-300-MChi-230-MSmu-250",
                        "RPV_2024_Par-ct-300-MChi-180-MSmu-300","RPV_2024_Par-ct-300-MChi-200-MSmu-300","RPV_2024_Par-ct-300-MChi-250-MSmu-300","RPV_2024_Par-ct-300-MChi-280-MSmu-300",
                        "RPV_2024_Par-ct-300-MChi-180-MSmu-350","RPV_2024_Par-ct-300-MChi-200-MSmu-350","RPV_2024_Par-ct-300-MChi-250-MSmu-350","RPV_2024_Par-ct-300-MChi-300-MSmu-350","RPV_2024_Par-ct-300-MChi-330-MSmu-350",
                        "RPV_2024_Par-ct-300-MChi-180-MSmu-400","RPV_2024_Par-ct-300-MChi-200-MSmu-400","RPV_2024_Par-ct-300-MChi-250-MSmu-400","RPV_2024_Par-ct-300-MChi-300-MSmu-400","RPV_2024_Par-ct-300-MChi-350-MSmu-400","RPV_2024_Par-ct-300-MChi-380-MSmu-400",
                        "RPV_2024_Par-ct-300-MChi-180-MSmu-450","RPV_2024_Par-ct-300-MChi-200-MSmu-450","RPV_2024_Par-ct-300-MChi-250-MSmu-450","RPV_2024_Par-ct-300-MChi-300-MSmu-450","RPV_2024_Par-ct-300-MChi-350-MSmu-450","RPV_2024_Par-ct-300-MChi-400-MSmu-450","RPV_2024_Par-ct-300-MChi-430-MSmu-450",
                        "RPV_2024_Par-ct-300-MChi-180-MSmu-500","RPV_2024_Par-ct-300-MChi-200-MSmu-500","RPV_2024_Par-ct-300-MChi-250-MSmu-500","RPV_2024_Par-ct-300-MChi-300-MSmu-500","RPV_2024_Par-ct-300-MChi-350-MSmu-500","RPV_2024_Par-ct-300-MChi-400-MSmu-500","RPV_2024_Par-ct-300-MChi-450-MSmu-500","RPV_2024_Par-ct-300-MChi-480-MSmu-500"

                        "RPV_2024_Par-ct-1000-MChi-180-MSmu-200","RPV_2024_Par-ct-1000-MChi-180-MSmu-250","RPV_2024_Par-ct-1000-MChi-200-MSmu-250","RPV_2024_Par-ct-1000-MChi-230-MSmu-250",
                        "RPV_2024_Par-ct-1000-MChi-180-MSmu-300","RPV_2024_Par-ct-1000-MChi-200-MSmu-300","RPV_2024_Par-ct-1000-MChi-250-MSmu-300","RPV_2024_Par-ct-1000-MChi-280-MSmu-300",
                        "RPV_2024_Par-ct-1000-MChi-180-MSmu-350","RPV_2024_Par-ct-1000-MChi-200-MSmu-350","RPV_2024_Par-ct-1000-MChi-250-MSmu-350","RPV_2024_Par-ct-1000-MChi-300-MSmu-350","RPV_2024_Par-ct-1000-MChi-330-MSmu-350",
                        "RPV_2024_Par-ct-1000-MChi-180-MSmu-400","RPV_2024_Par-ct-1000-MChi-200-MSmu-400","RPV_2024_Par-ct-1000-MChi-250-MSmu-400","RPV_2024_Par-ct-1000-MChi-300-MSmu-400","RPV_2024_Par-ct-1000-MChi-350-MSmu-400","RPV_2024_Par-ct-1000-MChi-380-MSmu-400",
                        "RPV_2024_Par-ct-1000-MChi-180-MSmu-450","RPV_2024_Par-ct-1000-MChi-200-MSmu-450","RPV_2024_Par-ct-1000-MChi-250-MSmu-450","RPV_2024_Par-ct-1000-MChi-300-MSmu-450","RPV_2024_Par-ct-1000-MChi-350-MSmu-450","RPV_2024_Par-ct-1000-MChi-400-MSmu-450","RPV_2024_Par-ct-1000-MChi-430-MSmu-450",
                        "RPV_2024_Par-ct-1000-MChi-180-MSmu-500","RPV_2024_Par-ct-1000-MChi-200-MSmu-500","RPV_2024_Par-ct-1000-MChi-250-MSmu-500","RPV_2024_Par-ct-1000-MChi-300-MSmu-500","RPV_2024_Par-ct-1000-MChi-350-MSmu-500","RPV_2024_Par-ct-1000-MChi-400-MSmu-500","RPV_2024_Par-ct-1000-MChi-450-MSmu-500","RPV_2024_Par-ct-1000-MChi-480-MSmu-500"

            }; 
        } 

        std::vector<double> smuValues  ;
        std::vector<double> neuValues  ;
        std::vector<double> ctauValues  ;
        std::vector<double> ObservedLimit  ;
        std::vector<double> median ;
        std::vector<double> down68 ;
        std::vector<double> up68 ;
        std::vector<double> down95 ;
        std::vector<double> up95 ;

        std::vector<double> results;
        int returnCode1 = -10;
        for (unsigned int i = 0 ; i < SignalSet.size() ; i++)
            {

                    // Lire les valeurs de params.txt
                    std::ifstream paramfile("./"+SignalSet[i]+"/"+SignalSet[i]+".txt");
                    if (!paramfile.is_open()) {
                        std::cerr << "Erreur : impossible d'ouvrir le fichier des parametres du signal" << std::endl;
                        return;
                    }

                    // on recupere les parametres du signal
                    std::string year, smu_val, neu_val, ctau_val;
                    std::getline(paramfile, year);
                    std::getline(paramfile, smu_val);
                    std::getline(paramfile, neu_val);
                    std::getline(paramfile, ctau_val);
                    paramfile.close();

                std::cout << "Processing Limit for  signal: " << SignalSet[i] << std::endl;
                
                smuValues.push_back(std::stod(smu_val));
                neuValues.push_back(std::stod(neu_val));
                ctauValues.push_back(std::stod(ctau_val));

                // std::cout << "Signal: " << SignalSet[i] 
                //           << ", SMU: " << smuValues.back() 
                //           << ", NEU: " << neuValues.back() 
                //           << ", Ctau: " << ctauValues.back() 
                //           << std::endl;
                
                results = parseCombineOutput("./"+SignalSet[i]+"/ExpectedLimit.txt");
                down95.push_back(results[0]);
                down68.push_back(results[1]);
                median.push_back(results[2]);
                up68.push_back(results[3]);
                up95.push_back(results[4]);
                if (results.size() > 5) {
                    ObservedLimit.push_back(results[5]);
                } else {
                    ObservedLimit.push_back(-1.0); // Valeur par défaut si ObservedLimit n'est pas trouvé
                }

                // std::cout << "Signal: " << SignalSet[i] 
                //           << ", SMU: " << smuValues.back() 
                //           << ", NEU: " << neuValues.back() 
                //           << ", Ctau: " << ctauValues.back() 
                //           << ", Median: " << median.back() 
                //           << ", Down 68: " << down68.back() 
                //           << ", Up 68: " << up68.back() 
                //           << ", Down 95: " << down95.back() 
                //           << ", Up 95: " << up95.back() 
                //           << std::endl;
            }
    
    // Appel des fonctions de tracé
    if (debug)
        {
            PlotLimit1D( 
                smuValues,
                neuValues,
                ctauValues,
                ObservedLimit,
                median,
                down68,
                up68,
                down95,
                up95,
                YEAR,
                Unblind
            );

                PlotLimit1D_XS( 
                smuValues,
                neuValues,
                ctauValues,
                ObservedLimit,
                median,
                down68,
                up68,
                down95,
                up95,
                YEAR,
                Unblind
            );
        }


    if (!debug)
        {

                    PlotLimit1D_Msmu_Mneu_ctau( 
                        smuValues,
                        neuValues,
                        ctauValues,
                        ObservedLimit,
                        median,
                        down68,
                        up68,
                        down95,
                        up95,
                        YEAR,
                        Unblind
                    );

            std::vector<double> SMU = {200,250,300,350,400,450,500};
            std::vector<TString> CTAU = { "001","003","010","030","100","300","1000" };
            std::vector<double> dCTAU = { 1,3,10,30,100,300,1000 };
            double MSTOP = 1000; // Default value for MSTOP
            std::vector<double> MSTOPValues = {1000, 2000, 3000, 4000, 5000, 6000,7000,8000,9000,10000}; // Example values for MSTOP
            for (unsigned int i = 0; i <SMU.size(); i++)
                {
                    PlotLimit_Mneu_vs_ctau(
                        smuValues,
                        neuValues,
                        ctauValues,
                        ObservedLimit,
                        median,
                        down68,
                        up68,
                        down95,
                        up95,
                        YEAR,
                        SMU[i],
                        Unblind,
                        getlimitplot
                    );

                    PlotLimit_DM_vs_ctau(
                    smuValues,
                    neuValues,
                    ctauValues,
                    ObservedLimit,
                    median,
                    down68,
                    up68,
                    down95,
                    up95,
                    YEAR,
                    SMU[i],
                    Unblind,
                        getlimitplot
                    );
                    
                for (unsigned int j = 0; j < MSTOPValues.size(); j++)
                    {
                        PlotLimit_coupling(
                    smuValues,
                    neuValues,
                    ctauValues,
                    ObservedLimit,
                    median,
                    down68,
                    up68,
                    down95,
                    up95,
                    YEAR,
                    SMU[i],
                    dCTAU[0],
                            MSTOPValues[j],
                    Unblind,
                            getlimitplot
                        );
                    }

                }
            for (unsigned int i = 0; i < CTAU.size(); i++)
            {
                    PlotLimit_Msmu_vs_Mneu(
            smuValues,
            neuValues,
            ctauValues,
            ObservedLimit,
            median,
            down68,
            up68,
            down95,
            up95,
            YEAR,
            CTAU[i],
            Unblind,
                        getlimitplot
                    );
            }
        }



    }