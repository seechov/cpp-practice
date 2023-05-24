#!/usr/bin/env bash

myproject_directory="astrology"
myproject_build_directory="astrology-build.nix64"

clean=false

astyle --options=.astylerc --recursive ./src/*.cpp,*.h

if $clean
then
  echo "Rebuld from clean start"
  rm -rf ./$myproject_build_directory
else
  echo "Non-clean build (but it's faster)"
fi

cd ../
mkdir -p ./$myproject_build_directory
 
cd $myproject_build_directory
cmake ../$myproject_directory -G "Unix Makefiles"
cmake --build .
./main

cd ../$myproject_directory
