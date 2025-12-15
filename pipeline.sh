#!/bin/bash

make clean -C ./code_algo
make -C ./code_algo

ALGO="./code_algo/bin/textEnInstruction";
DEST="./code_elec/code_fin/fichier.txt";

$ALGO $1 > $DEST;
