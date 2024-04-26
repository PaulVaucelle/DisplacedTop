The Displaced Top Analysis makes use of the Toolkit for Multivariate Analysis (TMVA) with Root (https://root.cern.ch/download/doc/tmva/TMVAUsersGuide.pdf).
There are several MVA methods available : Boosted Decision Tree (BDT), Support Vector Machine (SVM), Neural Network (NN), ...
It has been found that BDTs are working great for the analysis and therefore the usage of BDTs will be described in more details (it is not really different to use SVM or NN, one can easily check in the documentation)

For IPHC People, you can find my workspace at : /opt/sbg/cms/ui2_data1/pvaucell/LLTopAna/MVA/AnalysisCode/

* You need a specific versionof root to use TMVA : source /libcern/root/6.24.06/centos7.6-x86_64/bin/thisroot.sh

* There are two files to look at to produce the .xml file that will contain the weights (<=> the BDT): 

    - TreeReader.C : This code will produce the inputs for the training. You will need one input for the Signal and another one for the background. You can also prepare another input for the signal and the background
      if you want a separate samples between the training and the testing. Both training and testing steps are done when launching the next file (TMVAPaul.C). The input files are basically root files where BDT variables
      are stored. PS : do not forget to copy the TreeReader.h, runscript.C and runTraining.py
      
          - runscript.C is the script to launch the TreeReader.C file, you have to select the samples that you want in this runscript.C file.
            !!! Please look at the parameters at the top of the runscript.C file as it will define  what type of BDT you want (EVT-TRK_VTX and the path)!!!
      
          - runTraining.py allows to merge some input files together (if you want to merge signal benchmark together of background samples) 
--------------------------------
To run the runscript.C :

  - root
  - .L TreeReader.C
  - .L runscript.C
The output will of the following form : "output_"+BDT+"_"+Type+"_"+sample+".root"
where:
  "BDT" is either EVT, TRK or VTX
  "Type" is either SIG or BKG
  "sample" is the sample on which you ran to generate the input
-------------------------------

  - The second file is TMVAPaul.C that is used for the training and testing (both are performed, no need to do anything)
  - 
        - You have multiple choices for the inputs, either you have one for the signal and one for the background, therfore the same samples
          will be used for the training and testing (but not on the same events), or you can specify one sample for the training and one for the testing for signal and background
    
        - The inputs are the outputfile of runscript.C
    
        - Don't forget to change the outptufile of TMVAPaul.C :D
    
        - Select the variables you want for the BDT
    
        - You can assign a weight to each samples (the reweighting is already performed in TreeReader.C, check the end of the file "Scale")

        - You can define spcific cuts for each sample, i already put what is needed
    
        - You can choose the number of events you want to traina nd test on. It's really useful, especially when the inputs have really large stats and you don't want to run on all the stat.
    
        - You don't need to change the other parameters of the BDT (PrepareTrainingAndTestTree and BookMethod)
    
        - Other methods are commented (SVM, BDT with other parameters, NN), you can try them at the same time
    
        - When the training (and testing) is done, you will get a GUI where several plots can be shown.
    
        - !!! At this point, the final .xml file is already stored in : /opt/sbg/cms/ui2_data1/pvaucell/LLTopAna/MVA/AnalysisCode/dataset/weights/"name".xml
    
        - You are done ! :D

- If you want to re-open the GUI, you can do :
    - root
    - 
    - TMVA::TMVAGui( "'training-name'.root" )
    - 
 - You can change the FoM for the (cut efficiency plot)
     - root
     - 
     - TMVA::mvaeffs("dataset","training-name.root",Ns,Nb,true,"S/B")
     - S/B being the FoM,Ns and Nb being the number of signal and background events
        
