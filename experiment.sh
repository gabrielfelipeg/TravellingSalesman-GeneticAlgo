#!/bin/bash

make clean
make

./run 10 1000 2000 >out10.csv
./run 20 1000 2000 >out20.csv
./run 50 1000 2000 >out50.csv
./run 100 1000 2000 >out100.csv
./run 150 1000 2000 >out150.csv

Rscript plot.R