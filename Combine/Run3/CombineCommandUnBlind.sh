ValidateDatacards.py datacard.txt
text2workspace.py datacard.txt -o workspace.root
combine -M AsymptoticLimits workspace.root -m 200 --rMin 0 --rMax 10  &> ExpectedLimit.txt
combine -M FitDiagnostics workspace.root -m 200 --rMin -1 --rMax 1
python ../../../test/diffNuisances.py fitDiagnosticsTest.root --all
combineTool.py -M Impacts -d workspace.root  -m 200  --robustFit 1 --doInitialFit  --rMin -1 --rMax 1 
combineTool.py -M Impacts -d workspace.root -m 200  --robustFit 1 --doFits  --rMin -1 --rMax 1
combineTool.py -M Impacts -d workspace.root -m 200  --robustFit 1 --output impacts.json --rMin -1 --rMax 1
plotImpacts.py -i impacts.json -o impacts
combine -M FitDiagnostics workspace.root -m 200 --saveShapes --saveWithUncertainties --rMin -1 --rMax 1
combine -M Significance workspace.root -m 200 
combine -M Significance workspace.root -m 200 --rMin -1 --rMax 2 -t -1 --expectSignal 1.
combine -M Significance workspace.root -m 200 --rMin -1 --rMax 5 -t -1 --expectSignal 1. --toysFrequentist
combine -M MultiDimFit workspace.root -n .part3E -m 200 --rMin -1 --rMax 1
combine -M MultiDimFit workspace.root -n .part3E -m 200 --algo grid --points 30 --rMin -1 --rMax 1
python /opt/sbg/cms/ui2_data1/pvaucell/CMSSW_11_3_4/src/CombineHarvester/CombineTools/scripts/plot1DScan.py higgsCombine.part3E.MultiDimFit.mH200.root -o single_scan
combine -M MultiDimFit workspace.root -n .part3E.freezeAll -m 200 --algo grid --points 30 --freezeParameters allConstrainedNuisances --rMin 0 --rMax 2
python /opt/sbg/cms/ui2_data1/pvaucell/CMSSW_11_3_4/src/CombineHarvester/CombineTools/scripts/plot1DScan.py higgsCombine.part3E.MultiDimFit.mH200.root --others 'higgsCombine.part3E.freezeAll.MultiDimFit.mH200.root:FreezeAll:2' -o freeze_first_attempt
combine -M MultiDimFit workspace.root -n .snapshot -m 200  --saveWorkspace
combine -M MultiDimFit higgsCombine.snapshot.MultiDimFit.mH200.root -n .freezeAll -m 200 --algo grid --points 30 --freezeParameters allConstrainedNuisances --snapshotName MultiDimFit --rMin 0 --rMax 2
python /opt/sbg/cms/ui2_data1/pvaucell/CMSSW_11_3_4/src/CombineHarvester/CombineTools/scripts/plot1DScan.py higgsCombine.snapshot.MultiDimFit.mH200.root --others 'higgsCombine.freezeAll.MultiDimFit.mH200.root:FreezeAll:2' -o freeze_second_attempt --breakdown Syst,Stat
python postFitPlot.py
python preFitPlot.py