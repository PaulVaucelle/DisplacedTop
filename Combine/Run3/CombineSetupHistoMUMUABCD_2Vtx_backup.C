// Include ROOT headers
#include <TFile.h>
#include <TH1.h>
#include <TString.h>
#include <iostream>
#include <vector>
#include <sys/stat.h>

// Function to gather histograms from different files into one

// We take all the signal samples with all the systematics and the data samples
// We take the histograms for the different regions
// We gather them into one file for each region =>  input for datacards of Combine

void GatherHistograms() {

    TString GlobalPath = "/opt/sbg/cms/ui2_data1/pvaucell/CMSSW_10_6_30_FLY/src/FlyingTop/FlyingTop/test/";
    // !! // Parameters to change
    TString Channel = "MUMU";// MUMU ou EMU
    TString Variable = "NEWMVA_diffBin";// SumtrackWeight ou NEWMVA
    std::vector<TString> Plots = {"diffBin_NEWMVA_400fb"};//STW_2Vtx_
    TString file2 = "/opt/sbg/cms/ui2_data1/pvaucell/CMSSW_10_6_30_FLY/src/FlyingTop/FlyingTop/test/ABCDReader/EMU/ABCD_EMU__diffBin_BestBDT_Data_2018.root";//ABCD_EMU__VTXBDT_2Vtx ou ABCD_EMU__STW_2VtxAll
    //SumtrackWeight_diffBin // diffBin_STW_ // ABCD_EMU__diffBin_STW_Data_2018 // TLVtx
    // NEWMVA_diffBin // diffBin_NEWMVA_  // ABCD_EMU__diffBin_BestBDT_Data_2018 // 2Vtx
    // STW_SumdiffBin // diffBin_SumSTW_ //  ABCD_EMU__diffBin_SumSTW_Data_2018 // 2Vtx
    // STW_AvediffBin // diffBin_AveSTW_// ABCD_EMU__diffBin_AveSTW_Data_2018 // 2Vtx

    TString nVtx = "2Vtx";//2Vtx or 2VtxAll
    TString AltVtx = "2Vtx"; // !! problème here :TLVtxAll
    TString MU = "DM";
    TString ctau ="100";
    TString YEAR = "2018";
    float scaleLumi = 6.67; // !! To scale lumi up to 400 fb-1, else put 1 :D
    // !! // -------------------
    TString etamax = "2p4"; 
    TString Sign = "OS";
    // !! Production directories 
    TString ProdSignal              = "Signal_"+YEAR+"_L1";// SYST_CTAU100  ou SYST_EMU_CTAU100
    TString ProdSignalLumiUp        = "Signal_"+YEAR+"_LumiUp";
    TString ProdSignalLumiDown      = "Signal_"+YEAR+"_LumiDown";
    TString ProdSignalXSUp          = "Signal_"+YEAR+"_XSUp";
    TString ProdSignalXSDown        = "Signal_"+YEAR+"_XSDown";
    TString ProdSignalJECUp         = "Signal_"+YEAR+"_JECUp";
    TString ProdSignalJECDown       = "Signal_"+YEAR+"_JECDown";
    TString ProdSignalJERUp         = "Signal_"+YEAR+"_JERUp";
    TString ProdSignalJERDown       = "Signal_"+YEAR+"_JERDown";
    TString ProdData                = "DATA_EMU_"+YEAR+"_03_02_2025";

    if (Channel == "EMU")
        {
            ProdSignal = "SYST_EMU_CTAU100";
            ProdData = "";
        }
    if (Channel == "MUMU") // !! Production direcotries relative to the year and the global path :D
        {
            ProdSignal              = "Signal_"+YEAR+"_L1";
            // ProdSignalLumiUp        = "Signal_"+YEAR+"_LumiUp";
            // ProdSignalLumiDown      = "Signal_"+YEAR+"_LumiDown";
            // ProdSignalXSUp          = "Signal_"+YEAR+"_XSUp";
            // ProdSignalXSDown        = "Signal_"+YEAR+"_XSDown";
            ProdSignalJECUp         = "Signal_"+YEAR+"_JECUp";
            ProdSignalJECDown       = "Signal_"+YEAR+"_JECDown";
            ProdSignalJERUp         = "Signal_"+YEAR+"_JERUp";
            ProdSignalJERDown       = "Signal_"+YEAR+"_JERDown";
            //  ProdSignalRoccorDown       = "Signal_"+YEAR+"_RoccorDown";
            //MuonISOUp, MuonISODown, 
            //MuonIDUp, MuonIDDown, 
            //MuonTrigUp, MuonTrigDown

            ProdData =  "DATA_EMU_"+YEAR+"_03_02_2025";
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


        };


    // !! ----------------------------------------- 

    // !! ------------ Signal Samples ------------------ 
    //     TString SignalSet[34]={"RPV_"+YEAR+"_smu200_neu180_ctau"+ctau,"RPV_"+YEAR+"_smu250_neu180_ctau"+ctau,"RPV_"+YEAR+"_smu250_neu200_ctau"+ctau,
    // "RPV_"+YEAR+"_smu250_neu230_ctau"+ctau,"RPV_"+YEAR+"_smu300_neu180_ctau"+ctau,"RPV_"+YEAR+"_smu300_neu200_ctau"+ctau,"RPV_"+YEAR+"_smu300_neu250_ctau"+ctau,"RPV_"+YEAR+"_smu300_neu280_ctau"+ctau,
    // "RPV_"+YEAR+"_smu350_neu180_ctau"+ctau,"RPV_"+YEAR+"_smu350_neu200_ctau"+ctau,"RPV_"+YEAR+"_smu350_neu250_ctau"+ctau,"RPV_"+YEAR+"_smu350_neu300_ctau"+ctau,"RPV_"+YEAR+"_smu350_neu330_ctau"+ctau,
    // "RPV_"+YEAR+"_smu400_neu180_ctau"+ctau,"RPV_"+YEAR+"_smu400_neu200_ctau"+ctau,"RPV_"+YEAR+"_smu400_neu250_ctau"+ctau,"RPV_"+YEAR+"_smu400_neu300_ctau"+ctau,"RPV_"+YEAR+"_smu400_neu350_ctau"+ctau,
    // "RPV_"+YEAR+"_smu400_neu380_ctau"+ctau,"RPV_"+YEAR+"_smu450_neu180_ctau"+ctau,"RPV_"+YEAR+"_smu450_neu200_ctau"+ctau,"RPV_"+YEAR+"_smu450_neu250_ctau"+ctau,"RPV_"+YEAR+"_smu450_neu300_ctau"+ctau,
    // "RPV_"+YEAR+"_smu450_neu350_ctau"+ctau,"RPV_"+YEAR+"_smu450_neu400_ctau"+ctau,"RPV_"+YEAR+"_smu450_neu430_ctau"+ctau,"RPV_"+YEAR+"_smu500_neu180_ctau"+ctau,"RPV_"+YEAR+"_smu500_neu200_ctau"+ctau,
    // "RPV_"+YEAR+"_smu500_neu250_ctau"+ctau,"RPV_"+YEAR+"_smu500_neu300_ctau"+ctau,"RPV_"+YEAR+"_smu500_neu350_ctau"+ctau,"RPV_"+YEAR+"_smu500_neu400_ctau"+ctau,"RPV_"+YEAR+"_smu500_neu450_ctau"+ctau,
    // "RPV_"+YEAR+"_smu500_neu480_ctau"+ctau};


            std::vector<TString> SignalSet ={
    "RPV_"+YEAR+"_smu200_neu180_ctau"+ctau,
    "RPV_"+YEAR+"_smu250_neu200_ctau"+ctau,
    "RPV_"+YEAR+"_smu300_neu200_ctau"+ctau,
    "RPV_"+YEAR+"_smu350_neu250_ctau"+ctau,
    "RPV_"+YEAR+"_smu400_neu250_ctau"+ctau,
    "RPV_"+YEAR+"_smu450_neu250_ctau"+ctau,
    "RPV_"+YEAR+"_smu500_neu350_ctau"+ctau
    }
;
    // !! ---------------------------------------------


    // !! Systematics 
    std::vector<TString> SYST= {
        "",
        "LumiUp", "LumiDown",
        "L1Up", "L1Down",
        "TriggerUp", "TriggerDown",
        "PUUp", "PUDown",
        "TopPtUp", "TopPtDown",
        // "PDFUp", "PDFDown",
        // "ScaleUp", "ScaleDown",
        "XSUp", "XSDown",
        "JECUp", "JECDown",
        "JERUp", "JERDown",
        "MuonISOUp", "MuonISODown", 
        "MuonIDUp", "MuonIDDown"
    };

      TString DataSet[1]={ "MuonEG-Run2018-UL2018_MiniAODv2_GT36-v1"
    };

    // !! Name of the histograms to gather from the ABCD regions (can be changed)
    TString htitleA = "hData_CRtightlowlowpt_"+AltVtx+"_"+Variable;
    TString htitleB = "hData_CRlooselooselowlowpt_"+AltVtx+"_"+Variable;
    TString htitleC = "hData_CRtighthighpt_"+nVtx+"_"+Variable;
    TString htitleD = "hData_CRlooselooselowpt_"+nVtx+"_"+Variable;

    // !!  Name of the output file (that will be an input of the datacards so do not change the name)
    std::vector<TString> REGIONS = {

        "Tight_LowLowPT_2Vtx_control_region",    //A
        "LooseLoose_LowLowPT_2Vtx_control_region",   //B
        "Tight_HighPT_2Vtx_signal_region",   //C
        "LooseLoose_LowPT_2Vtx_control_region"    //D

        };


    // !!  Loop over all regions to gather all histos into one file

        for (unsigned int i = 0 ; i < REGIONS.size() ; i++) // There are 9 regions to loop over for the 2 Vtx category : ABCDEFGHI ( 2Vtx and 2VtxAll )
            {
                TString outputFileName = REGIONS[i]+".root";
                TFile* outputFile = new TFile(outputFileName, "RECREATE");

                for (unsigned int j = 0 ; j < SYST.size(); j++) // loop over the systematics for signal samples
                    {
                        TString Prod = ProdSignalSyst[j];
                        for (unsigned int l = 0 ; l < 7 ; l++) // loop over the signal samples
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

                                // 
                                // inputFile->ls();


                                htitleA = shortname+"_hData_CRtightlowlowpt_"+AltVtx+"_"+Variable;//+"_"
                                htitleB = shortname+"_hData_CRlooselooselowlowpt_"+AltVtx+"_"+Variable;//+"_"
                                htitleC = shortname+"_hData_CRtighthighpt_"+nVtx+"_"+Variable;//+"_"
                                htitleD = shortname+"_hData_CRlooselooselowpt_"+nVtx+"_"+Variable;//+"_"

                            
                                std::vector<TString> HistoNames = {
                                    
                                        htitleA, 
                                        htitleB, 
                                        htitleC,
                                        htitleD                                    
                                    };
                                
                                // Get the histograms
                                // for (unsigned int m = 0 ; m < HistoNames.size() ; m++)
                                //     {
                                        // Retrieve the histogram
                                        inputFile->cd();
                                        TH1F* hist = (TH1F*)gROOT->FindObject(HistoNames[i]) ; //= (TH1F*)inputFile->Get(HistoNames[m]);
                                        // std::cout << "Getting  histogram: " << HistoNames[m] << " from file: " << file << std::endl;
                                        if (!hist) {
                                            std::cerr << "Error retrieving histogram: " << HistoNames[i] << " from file: " << file << std::endl;
                                            inputFile->Close();
                                            continue;//continue
                                        }

                                        // Optionally clone the histogram if you want to keep it after closing the file
                                        TH1F* histClone = (TH1F*)hist->Clone();
                                        histClone->SetDirectory(outputFile); // Attach to output file directory
                                        histClone->SetName(Signal+"_"+REGIONS[i]+"_"+SYST[j]);
                                        histClone->Scale(scaleLumi);
                                        outputFile->cd();
                                        // Write the histogram to the output file
                                        histClone->Write();
                                    // } // loop over histos
                                    inputFile->Close();
                                    
                            }  // loop over signal samples

                    } /// loop over the systematics for signal samples
                        
                for (unsigned int j = 0 ; j < 1 ; j++) // loop over the data samples
                    {
                        TString DATA = DataSet[j];
                        TString file = GlobalPath+ProdData+"/histofile_HT100_EM_"+Sign+"_"+etamax+"_"+DATA+"_BDT100.root";
                        
                        TString shortname = DATA;
                        std::cout << shortname << std::endl;

                        // Open each file
                        TFile* inputFile = TFile::Open(file);

                        if (!inputFile || inputFile->IsZombie()) {
                            std::cerr << "Error opening file: " << file << std::endl;
                            continue;
                        }
                       

                        htitleA = shortname+"_hData_CRtightlowlowpt_"+AltVtx+"_"+Variable;//+"_"
                        htitleB = shortname+"_hData_CRlooselooselowlowpt_"+AltVtx+"_"+Variable;//+"_"
                        htitleC = shortname+"_hData_CRtighthighpt_"+nVtx+"_"+Variable;//+"_"
                        htitleD = shortname+"_hData_CRlooselooselowpt_"+nVtx+"_"+Variable;//+"_"
                    
                        std::vector<TString> HistoNames = {
                            
                                htitleA, 
                                htitleB, 
                                htitleC,
                                htitleD
                            
                            };
                        
                        // Get the histograms
                        // for (unsigned int m = 0 ; m < HistoNames.size() ; m++)
                            // {
                                // Retrieve the histogram
                                inputFile->cd();
                                TH1F* hist = (TH1F*)gROOT->FindObject(HistoNames[i]) ; //= (TH1F*)inputFile->Get(HistoNames[m]);
                                // std::cout << "Getting  histogram: " << HistoNames[m] << " from file: " << file << std::endl;
                                if (!hist) {
                                    std::cerr << "Error retrieving histogram: " << HistoNames[i] << " from file: " << file << std::endl;
                                    inputFile->Close();
                                    continue;
                                }
                            // if (REGIONS[i]=="Tight_1Vtx")
                            //     {
                                    TH1F* histClone2 = (TH1F*)hist->Clone();
                                    histClone2->SetDirectory(outputFile);
                                    histClone2->SetName("data_obs");
                                    outputFile->cd();
                                    histClone2->Write();
                                // }

                                // Optionally clone the histogram if you want to keep it after closing the file
                                TH1F* histClone = (TH1F*)hist->Clone();
                                histClone->SetDirectory(outputFile); // Attach to output file directory
                                //Change name of the histograms to suit the datacards
                                histClone->SetName(DATA+"_"+REGIONS[i]+"_"+SYST[j]);

                                outputFile->cd();
                                // Write the histogram to the output file
                                histClone->Write();
                            // } // loop over histos
                            inputFile->Close();      
                    }// Loop over data samples

            // for (unsigned int m = 0 ; m < Plots.size() ; m++)
            //     {
                // !! // Get the histograms
                    // ABCD_EMU__VTXBDT_2Vtx
                    // Open each file
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
                    // for (unsigned int i =0 ; i < nbin; i++) {
                    //     double Y = hist3->GetBinContent(i);
                    //     double Y_1 = 0 ;
                    //     if (Y <= 0 && (i == 12 || i == 14) ) {
                    //         Y_1 = hist3->GetBinContent(i-1);
                    //         histClone3->SetBinContent(i,Y_1);
                    //     }
                    //     else {
                    //         histClone3->SetBinContent(i,Y);
                    //     }
                    // }
                    
                    histClone3->SetDirectory(outputFile);
                    histClone3->SetName("DD");
                    histClone3->Scale(scaleLumi);
                    DDUp->SetDirectory(outputFile);
                    DDUp->SetName("DD_NormUp");
                    DDUp->Scale(scaleLumi);
                    DDDown->SetDirectory(outputFile);
                    DDDown->SetName("DD_NormDown");
                    DDDown->Scale(scaleLumi);
                    outputFile->cd();
                    histClone3->Write();
                    DDUp->Write();
                    DDDown->Write();
                    inputFile2->Close();
                // }
            // !! --end
            // !! // Get the Toys histograms
                    // TString file3 = "/opt/sbg/cms/ui2_data1/pvaucell/CMSSW_10_6_30_FLY/src/FlyingTop/FlyingTop/test/ABCDReader/EMU/hsolveToys.root";
                    
                    // // Open each file
                    // TFile* inputFile3 = TFile::Open(file3);

                    // if (!inputFile3 || inputFile3->IsZombie()) {
                    //     std::cerr << "Error opening file3: " << file3 << std::endl;
                    //     continue;
                    // }

                    // inputFile3->cd();
                    // TH1F* hist4 = (TH1F*)gROOT->FindObject("hToys") ; //= (TH1F*)inputFile->Get(HistoNames[m]);
                    // if (!hist4) {
                    //         std::cerr << "Error retrieving histogram: hToys  from file: " << file3 << std::endl;
                    //         inputFile3->Close();
                    //         continue;
                    //     }
                    // TH1F* histClone4 = (TH1F*)hist4->Clone();
                    // histClone4->SetDirectory(outputFile);
                    // histClone4->SetName("hToys");
                    // outputFile->cd();
                    // histClone4->Write();
                    // inputFile3->Close();
                // }

            // // !! // Get the Toys NormUp histograms
            //         TString file_NormUp = "/opt/sbg/cms/ui2_data1/pvaucell/CMSSW_10_6_30_FLY/src/FlyingTop/FlyingTop/test/ABCDReader/EMU/hsolveToysNormUp.root";
                    
            //         // Open each file
            //         TFile* inputFile_NormUp = TFile::Open(file_NormUp);

            //         if (!inputFile_NormUp|| inputFile_NormUp->IsZombie()) {
            //             std::cerr << "Error opening file_NormUp: " << file_NormUp << std::endl;
            //             continue;
            //         }

            //         inputFile_NormUp->cd();
            //         TH1F* hist_NormUp= (TH1F*)gROOT->FindObject("hToys_NormUp") ; //= (TH1F*)inputFile->Get(HistoNames[m]);
            //         if (!hist_NormUp) {
            //                 std::cerr << "Error retrieving histogram: hToys_NormUp  from file: " << file_NormUp << std::endl;
            //                 inputFile_NormUp->Close();
            //                 continue;
            //             }
            //         TH1F* histClone_NormUp = (TH1F*)hist_NormUp->Clone();
            //         histClone_NormUp->SetDirectory(outputFile);
            //         histClone_NormUp->SetName("hToys_NormUp");
            //         outputFile->cd();
            //         histClone_NormUp->Write();
            //         inputFile_NormUp->Close();
            // // !! // Get the Toys NormDown histograms
            //         TString file_NormDown = "/opt/sbg/cms/ui2_data1/pvaucell/CMSSW_10_6_30_FLY/src/FlyingTop/FlyingTop/test/ABCDReader/EMU/hsolveToysNormDown.root";
                    
            //         // Open each file
            //         TFile* inputFile_NormDown = TFile::Open(file_NormDown);

            //         if (!inputFile_NormDown|| inputFile_NormDown->IsZombie()) {
            //             std::cerr << "Error opening file_NormDown: " << file_NormDown << std::endl;
            //             continue;
            //         }

            //         inputFile_NormDown->cd();
            //         TH1F* hist_NormDown= (TH1F*)gROOT->FindObject("hToys_NormDown") ; //= (TH1F*)inputFile->Get(HistoNames[m]);
            //         if (!hist_NormDown) {
            //                 std::cerr << "Error retrieving histogram: hToys_NormDown  from file: " << file_NormDown << std::endl;
            //                 inputFile_NormDown->Close();
            //                 continue;
            //             }
            //         TH1F* histClone_NormDown = (TH1F*)hist_NormDown->Clone();
            //         histClone_NormDown->SetDirectory(outputFile);
            //         histClone_NormDown->SetName("hToys_NormDown");
            //         outputFile->cd();
            //         histClone_NormDown->Write();
            //         inputFile_NormDown->Close();
            // // !! --end


                outputFile->Close();
                std::cout << "Histograms have been gathered and saved in " << outputFileName << std::endl;
                
                TString Directory = "/opt/sbg/cms/ui2_data1/pvaucell/CMSSW_11_3_4/src/HiggsAnalysis/CombinedLimit/data/RPV_UDD_"+YEAR+"/ABCD_"+Channel+"_"+MU+"_"+Sign+"_"+etamax+"_"+nVtx+"_"+Plots[0]+"/";

            // Vérifier si le répertoire existe
            struct stat sb;
            int returnCode1 = -10;
            int returnCode2 = -10;
            if (stat(Directory, &sb) == 0)
                {
                    cout << "The path is valid!";
                    returnCode1 = gSystem->Exec("mv "+outputFileName+" "+Directory);
                // Optionally, check the return code to see if the command was successful
                    if (returnCode1 == 0) {
                    std::cout << "mv executed successfully!" << std::endl;
                } else {
                    std::cout << "mv failed with return code: " << returnCode1 << std::endl;
                }
            }
                
            else
                {
                    cout << "The Path is invalid! Creating the directory";
                    returnCode1 = gSystem->Exec("mkdir "+Directory);
                    returnCode2 = gSystem->Exec("mv "+outputFileName+" "+Directory);
                    if (returnCode1 == 0 && returnCode2 == 0) {
                        std::cout << "mk and mv executed successfully!" << std::endl;
                    } else {
                        std::cout << "mk and mv failed with return code: "<< returnCode1 << "and "<< returnCode2 << std::endl;
                    }
                }




        }// loop over plots
}// End of Gather Histograms
