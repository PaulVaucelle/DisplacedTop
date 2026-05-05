#!/bin/bash

# # Par défaut (2018, ctau 100, blind)
# ./RunCombine.sh -c 100 -d

# # Pour 2016PRE, ctau 300, en mode unblind
# ./RunCombine.sh -y 2016PRE -c 300 -u 

# # Pour 2017, ctau 500, blind
# ./RunCombine.sh --year 2017 --ctau 500

# L'option debug permet de toruner sur 7 signaux seulement

# === Valeurs par défaut ===
YEAR="1623"
CTAU="ALL"
BLIND=true
DEBUG=false

VAR="STW_6Bins"          # ex: MET             Plots[0]="STW_6Bins"; Plots[0]="VtxBDT_Ave";  Plots[0]="EventBDT";

# === Parse les arguments ===
while [[ $# -gt 0 ]]; do
    case "$1" in
        -y|--year)
            YEAR="$2"
            shift 2
            ;;
        -v|--var)
            VAR="$2"
            shift 2
            ;;
        -c|--ctau)
            CTAU="$2"
            shift 2
            ;;
        -u|--unblind)
            BLIND=false
            shift
            ;;
        -d|--debug)
            DEBUG=true  # Active le mode debug
            shift
            ;;
        -*)
            echo "Option inconnue: $1"
            kill $$
            ;;
        *)
            echo "Argument non reconnu: $1"
            kill $$
            ;;

    esac
done
# Allow for overwriting files => write ExpectedLimit.txt file that contains the expected limits
## Important: This will overwrite existing files without warning
## I don't know if this command works in every envrionment/ depending on users rights.
### but it works for me :D

set +o noclobber

# === Correction du nom d’année ===
case "$YEAR" in
    "1623") YEARCor="1623" ;;
    "1624") YEARCor="1624" ;;
    *) echo "Année invalide: $YEAR"  ;;
esac

# === Config affichée ===
echo "=== Configuration ==="
echo "YEAR     = $YEAR"
echo "YEARCor  = $YEARCor"
echo "CTAU     = $CTAU"
echo "BLIND    = $BLIND"
echo "======================"

# === Valeurs de masses ===
declare -a SMU_VALUES=(200 250 300 350 400 450 500)
declare -a NEU_VALUES=(180 200 230 250 280 300 330 350 380 400 430 450 480)
declare -a CTAU_VALUES=(001 003 010 030 100 300 1000)

# === Boucle sur tous les samples ===
FIRST=true
for SMU in "${SMU_VALUES[@]}"; do
for NEU in "${NEU_VALUES[@]}"; do
    for CTAU_VAL in "${CTAU_VALUES[@]}"; do

    # Filtrage si un ctau spécifique est demandé
    # if [[ "$CTAU" != "ALL" && "$CTAU" != "$CTAU_VAL" ]]; then
    #     continue
    # fi

    if [[ $SMU -eq 200 && $NEU -eq 180 ]]; then
        :
    elif [[ $SMU -eq 250 && ( $NEU -eq 180 || $NEU -eq 200 || $NEU -eq 230 ) ]]; then
        :
    elif [[ $SMU -eq 300 && ( $NEU -eq 180 || $NEU -eq 200 || $NEU -eq 250 || $NEU -eq 280 ) ]]; then
        :
    elif [[ $SMU -eq 350 && ( $NEU -eq 180 || $NEU -eq 200 || $NEU -eq 250 || $NEU -eq 300 || $NEU -eq 330 ) ]]; then
        :
    elif [[ $SMU -eq 400 && ( $NEU -eq 180 || $NEU -eq 200 || $NEU -eq 250 || $NEU -eq 300 || $NEU -eq 350 || $NEU -eq 380 ) ]]; then
        :
    elif [[ $SMU -eq 450 && ( $NEU -eq 180 || $NEU -eq 200 || $NEU -eq 250 || $NEU -eq 300 || $NEU -eq 350 || $NEU -eq 400 || $NEU -eq 430 ) ]]; then
        :
    elif [[ $SMU -eq 500 && ( $NEU -eq 180 || $NEU -eq 200 || $NEU -eq 250 || $NEU -eq 300 || $NEU -eq 350 || $NEU -eq 400 || $NEU -eq 450 || $NEU -eq 480 ) ]]; then
        :
    else
        continue  # skip les cas non valides
    fi
    

    SIGNAL="RPV_${YEARCor}_Msmu-${SMU}_Mchi-${NEU}_ct-${CTAU_VAL}"

    # if [[ "$YEARCor" == "2024" ]]; then
    #     SIGNAL="RPV_${YEARCor}_Par-ct-${CTAU_VAL}-MChi-${NEU}-MSmu-${SMU}"
    # else
    #     SIGNAL="RPV_${YEARCor}_Msmu-${SMU}_Mchi-${NEU}_ct-${CTAU_VAL}"
    # fi
    # Change de dossier seulement si le dossier existe
    

    if $FIRST; then
        cd "$SIGNAL" || { echo "Échec du cd vers $SIGNAL";kill $$; }
        FIRST=false
    else
        cd "../$SIGNAL" || { echo "Échec du cd vers $SIGNAL"; kill $$; }
    fi

    echo "=== Exécution dans $(pwd) ==="

    source ./CombineDataCards.sh $YEAR $VAR $SMU $NEU $CTAU_VAL

    done
done
done



cd ..



