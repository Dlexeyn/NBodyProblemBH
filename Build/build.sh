#!/bin/bash

qmake ../NBodyProblemBH.pro

make

cp ../Data/s2.txt s2.txt
cp ../Data/s38.txt s38.txt
cp ../Data/s55.txt s55.txt
