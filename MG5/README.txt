For the event generation of the signal sample, 
MadGraph5\_aMC@NLO tool is used, version 2.9.15. The events are generated at LO+1Jet.
PDF : PDF4LHC15_nlo_mc ID : 90500
UFO Model (Private) : DisplacedTopUDD 
Phenomenological paper : https://arxiv.org/abs/2212.06678 
See PDF : Tutorial_MC_production_for_DisplacedTop.pdf in the same directory
Note : Becareful, some commands in the tutorial might not be correct for everyone so I will give the things that i do :

# In CMSSW_XX_YY_ZZ/src/

export V0_CMS_SW_DIR=/cvmfs/cms.cern.ch
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700

eval `scramv1 runtime -sh`

export PYTHONPATH=$PYTHONPATH:/opt/glite/lib64/python:/opt/fpconst/lib/python2.4/site-packages
export PYTHONPATH=${PYTHONPATH}:${GLITE_LOCATION}/lib64
cmsenv

# then in your MG5 directory :

export PYTHIA8DATA=$PWD/HEPTools/pythia8/share/Pythia8/xmldoc/

export LHAPDF_DATA_PATH=$PWD/HEPTools/lhapdf6/share/LHAPDF

python ./bin/mg5

# For the Madgraph command :

 import model DisplacedTopUDD --modelname
 generate p p  > sl2+ sl2- / h01 h02 a0 n1 n2 n3 n4, (sl2+ > n2 mu+, n2\
 > t d s / sd1 sd1~ sd2 sd2~ sd3 sd3~ sd4 sd4~ sd5 sd5~ sd6 sd6~), (sl\
2- > n2 mu-, n2 > t d s / sd1 sd1~ sd2 sd2~ sd3 sd3~ sd4 sd4~ sd5 sd5~\
 sd6 sd6~) 

add process p p  > sl2+ sl2- j / h01 h02 a0 n1 n2 n3 n4, (sl2+ > n2 mu+, n2\
 > t d s / sd1 sd1~ sd2 sd2~ sd3 sd3~ sd4 sd4~ sd5 sd5~ sd6 sd6~), (sl\
2- > n2 mu-, n2 > t d s / sd1 sd1~ sd2 sd2~ sd3 sd3~ sd4 sd4~ sd5 sd5~\
 sd6 sd6~) 

output BetaGamma_RPV_bino_300__250_50_1j -f

# If you are only looking at the XS, you only need to generate the smuons:

generate p p > sl2+ sl2- / h01 h02 a0 n1 n2 n3 n4

add process p p > sl2+ sl2- j / h01 h02 a0 n1 n2 n3 n4

# Then, you have to change the param_card.dat file to the one needed for the model using the param card provided:
# Check for the mass of the smuon 100013 and  neutralino (neutralino has to be below smuon :D ).
# You should check also of the SELMIX block, it has to be unitary and you can change it to have mixing of left and right or only Left or only Right, see below

## Mixing : 

###################################
## INFORMATION FOR SELMIX
###################################
BLOCK SELMIX # 
      1 1 7.071070e-01 # rrl1x1
      1 4 7.071070e-01 # rrl1x4
      2 2 7.071070e-01 # rrl2x2
      2 5 7.071070e-01 # rrl2x5
      3 3 7.071070e-01 # rrl3x3
      3 6 7.071070e-01 # rrl3x6
      4 1 -7.071070e-01 # rrl4x1
      4 4 7.071070e-01 # rrl4x4
      5 2 -7.071070e-01 # rrl5x2
      5 5 7.071070e-01 # rrl5x5
      6 3 -7.071070e-01 # rrl6x3
      6 6 7.071070e-01 # rrl6x6

## Full left and Full Right :

###################################
## INFORMATION FOR SELMIX
###################################
BLOCK SELMIX # 
      1 1 0 # rrl1x1
      1 4 0 # rrl1x4
      2 2 1 # rrl2x2
      2 5 0 # rrl2x5
      3 3 0 # rrl3x3
      3 6 0 # rrl3x6
      4 1 0 # rrl4x1
      4 4 0 # rrl4x4
      5 2 0 # rrl5x2
      5 5 1 # rrl5x5
      6 3 0 # rrl6x3
      6 6 0 # rrl6x6

# When it is done, you can generate the events by copy-pasting this:

launch
shower=Pythia8
0
set nevents 10000
set ebeam1 7000
set ebeam2 7000
set pdlabel lhapdf
set lhaid 90500
set use_syst True
set ickkw 1
set xqcut 30.0
set asrwgtflavor = 5
0
exit

# when you are running with the mixing part with the commands given, you would need to multiply by 2 to get the correct XS,
# because you generate only LR or RL with this command but you want the XS for RL+LR
