#!/bin/bash

# clean
rm -rf build/

# compile
mkdir -p build/classes
javac src/* -d build/classes
