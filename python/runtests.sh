#!/bin/bash

# this script copies the dynamic library for the ACEtk python module
# and runs all the unit tests it can find

rm ACEtk.*.so
cp ../build/ACEtk.*.so .
python -m unittest discover -v -p "Test*"
