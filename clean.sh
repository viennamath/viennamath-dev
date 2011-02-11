#!/bin/bash

rm *.*~
rm viennamath/*.*~
rm viennamath/operations/*.*~
rm viennamath/old/*.*~
rm tests/*.*~
rm examples/*.*~
rm doc/*.*~

cd tests
./clean.sh
