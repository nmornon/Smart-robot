#!/bin/bash

make clean -C ./code_algo
make -C ./code_algo

ALGO="./code_algo/bin/textEnInstruction";
DEST="./code_elec";

gcc -o $DEST/robot $DEST/main.c $DEST/lcd_bip.c $DEST/rgb_sensor.c $DEST/lecture_fichier.c $DEST/commande_final.c $DEST/configurer.c $DEST/pastille_detect.c -lwiringPi -lpthread -lwiringPiDev -lm;

$ALGO $1 | $DEST/robot ;
