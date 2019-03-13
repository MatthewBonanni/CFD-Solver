#!/bin/bash
./bin/solve
OUTFILE=$(ls data -t | head -n1)
python3 src/plot.py $OUTFILE