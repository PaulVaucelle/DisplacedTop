#!/bin/bash

# Usage:
# ./combine_cards.sh YEARSTRING VAR SMUON MASSNEU CTAU

YEARSTRING=$1   # "1623" ou "1624"
VAR=$2          # ex: MET             Plots[0]="STW_6Bins"; Plots[0]="VtxBDT_Ave";  Plots[0]="EventBDT";
SMUON=$3        # ex: 500
NEU=$4          # ex: 100
CTAU=$5         # ex: 10

# Répertoire de base
BASE="/opt/sbg/cms/ui2_data1/pvaucell/CMSSW_11_3_4/src/HiggsAnalysis/CombinedLimit/data"

# On définit les années selon YEARSTRING
if [ "$YEARSTRING" == "1623" ]; then
    YEARS=("2016preVFP" "2016" "2017" "2018" "2022A" "2022B" "2023A" "2023B")
elif [ "$YEARSTRING" == "1624" ]; then
    YEARS=("2016preVFP" "2016" "2017" "2018" "2022A" "2022B" "2023A" "2023B" "2024")
else
    echo "Erreur: YEARSTRING doit être 1623 ou 1624"
    # exit 1
fi

# Construction des chemins pour chaque datacard
CARDS=()
for Y in "${YEARS[@]}"; do
    if [[ "$Y" == "2016"* || "$Y" == "2017" || "$Y" == "2018" ]]; then
        RUN="Run2"
        CARD="${BASE}/RPV_${RUN}/ABCD_MUMU_DM_OS_2p4_2Vtx_${VAR}/RPV_${Y}_smu${SMUON}_neu${NEU}_ctau${CTAU}/datacard.txt"

    elif [[ "$Y" == "2022"* || "$Y" == "2023"* ]]; then
        RUN="Run3"
        CARD="${BASE}/RPV_${RUN}/ABCD_MUMU_DM_OS_2p4_2Vtx_${VAR}/RPV_${Y}_Msmu-${SMUON}_Mchi-${NEU}_ct-${CTAU}/datacard.txt"

    elif [[ "$Y" == "2024" ]]; then
        RUN="Run3"
        CARD="${BASE}/RPV_${RUN}/ABCD_MUMU_DM_OS_2p4_2Vtx_${VAR}/RPV_${Y}_Par-ct-${CTAU}-MChi-${NEU}-MSmu-${SMUON}/datacard.txt"
    fi
 
    if [ -f "$CARD" ]; then
        CARDS+=("era${Y}=${CARD}")
    else
        echo "⚠️ Datacard introuvable pour ${Y} : $CARD"
    fi
done

# Vérif qu'on a au moins 2 cartes
if [ ${#CARDS[@]} -lt 2 ]; then
    echo "Erreur: trop peu de cartes trouvées pour faire un combine"
    # exit 1
fi

# Nom de sortie
OUTCARD="datacard.txt"

# CombineCards
echo "➡️ CombineCards.py ${CARDS[@]} > ${OUTCARD}"
combineCards.py "${CARDS[@]}" > "${OUTCARD}"

# # text2workspace
# echo "➡️ text2workspace.py ${OUTCARD} -o ${OUTWS}"
# text2workspace.py "${OUTCARD}" -o "${OUTWS}"

echo "✅ Datacards combinées : ${OUTCARD}"
# echo "✅ Workspace généré : ${OUTWS}"
