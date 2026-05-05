ValidateDatacards.py datacard.txt 
text2workspace.py datacard.txt -o workspace.root
combine -M AsymptoticLimits workspace.root -m 200 -t -1 --run blind --rMin 0 --rMax 10 &> ExpectedLimit.txt
