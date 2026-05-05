#!/bin/bash

# # Par défaut (2018, ctau 100, blind)
# ./RunCombine.sh -c 100 -d

# # Pour 2016PRE, ctau 300, en mode unblind
# ./RunCombine.sh -y 2016PRE -c 300 -u 

# # Pour 2017, ctau 500, blind
# ./RunCombine.sh --year 2017 --ctau 500

# L'option debug permet de toruner sur 7 signaux seulement

# === Valeurs par défaut ===
YEAR="2018"
CTAU="ALL"
BLIND=true
DEBUG=false
# === Parse les arguments ===
while [[ $# -gt 0 ]]; do
    case "$1" in
        -y|--year)
            YEAR="$2"
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
    "2022A") YEARCor="2022A" ;;
    "2022B") YEARCor="2022B" ;;
    "2023A") YEARCor="2023A" ;;
    "2023B") YEARCor="2023B" ;;
    "2024") YEARCor="2024" ;;
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

SignalSet=(

    "RPV_${YEARCor}_Msmu-200_Mchi-180_ct-${CTAU}"
    "RPV_${YEARCor}_Msmu-250_Mchi-200_ct-${CTAU}"
    "RPV_${YEARCor}_Msmu-300_Mchi-250_ct-${CTAU}"
    "RPV_${YEARCor}_Msmu-350_Mchi-250_ct-${CTAU}"
    "RPV_${YEARCor}_Msmu-400_Mchi-250_ct-${CTAU}"
    "RPV_${YEARCor}_Msmu-450_Mchi-250_ct-${CTAU}"
    "RPV_${YEARCor}_Msmu-500_Mchi-350_ct-${CTAU}"
)

if $DEBUG; then
    echo "=== Valeurs de masses ==="
    echo "SMU_VALUES = ${SMU_VALUES[*]}"
    echo "NEU_VALUES = ${NEU_VALUES[*]}"
    echo "CTAU_VALUES = ${CTAU_VALUES[*]}"
    echo "SignalSet = ${SignalSet[*]}"
    # Boucle sur les signaux
    FIRST=true
    for SIGNAL in "${SignalSet[@]}"; do
        if $FIRST; then
            cd "$SIGNAL" || { echo "Échec du cd vers $SIGNAL"; kill $$; }
            FIRST=false
        else
            cd "../$SIGNAL" || { echo "Échec du cd vers $SIGNAL"; kill $$; }
        fi

        echo "=== Exécution dans $(pwd) ==="

        if $BLIND; then
            source ./CombineCommandBlind.sh
        else
            source ./CombineCommandUnBlind.sh
        fi
    done
else
    # === Boucle sur tous les samples ===
    FIRST=true
    for SMU in "${SMU_VALUES[@]}"; do
    for NEU in "${NEU_VALUES[@]}"; do
        for CTAU_VAL in "${CTAU_VALUES[@]}"; do

        # Filtrage si un ctau spécifique est demandé
        if [[ "$CTAU" != "ALL" && "$CTAU" != "$CTAU_VAL" ]]; then
            continue
        fi

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

        if [[ "$YEARCor" == "2024" ]]; then
            SIGNAL="RPV_${YEARCor}_Par-ct-${CTAU_VAL}-MChi-${NEU}-MSmu-${SMU}"
        else
            SIGNAL="RPV_${YEARCor}_Msmu-${SMU}_Mchi-${NEU}_ct-${CTAU_VAL}"
        fi
        # Change de dossier seulement si le dossier existe
        

        if $FIRST; then
            cd "$SIGNAL" || { echo "Échec du cd vers $SIGNAL";kill $$; }
            FIRST=false
        else
            cd "../$SIGNAL" || { echo "Échec du cd vers $SIGNAL"; kill $$; }
        fi

        echo "=== Exécution dans $(pwd) ==="

        if $BLIND; then
            source ./CombineCommandBlind.sh
        else
            source ./CombineCommandUnBlind.sh
        fi
 

        done
    done
    done

fi

cd ..



