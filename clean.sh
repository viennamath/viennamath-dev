#!/bin/bash

rm *.*~
rm viennamath/*.*~
rm viennamath/operations/*.*~
rm viennamath/old/*.*~
rm tests/*.*~
rm tests/src/*.*~
rm examples/*.*~
rm doc/*.*~

cd tests
./clean.sh
