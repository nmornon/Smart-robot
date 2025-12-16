#!/bin/bash

ALGO="./code_algo";
DEST="./code_elec";

make clean -C $ALGO
make -C $ALGO

make clean -C $DEST
make -C $DEST

$ALGO/bin/textEnInstruction $1 | $DEST/bin/robot ;
