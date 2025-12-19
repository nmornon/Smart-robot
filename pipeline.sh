#!/bin/bash

ALGO="./programmes/code_algo";
DEST="./programmes/code_elec";

make clean -C $ALGO
make -C $ALGO

make clean -C $DEST
make -C $DEST

echo "debut resolution"
debut=$(date +%s%N)

$ALGO/bin/textEnInstruction $1 | $DEST/bin/robot 

fin=$(date +%s%N)
duree=$((fin - debut))
secondes=$((duree / 1000000000))
millisecondes=$(( (duree / 100000) % 1000 ))
echo "Temps d'exécution : ${secondes}.$(printf "%03d" $millisecondes) secondes"
