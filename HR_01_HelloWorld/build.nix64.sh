#!/usr/bin/env bash

app_directory=${PWD##*/}
app_build_directory="$app_directory-build.nix64"

clean=false

astyle --options=.astylerc --recursive ./src/*.cpp,*.h

if $clean
then
  echo "Rebuld from clean start"
  rm -rf ./$app_build_directory
else
  echo "Non-clean build (but it's faster)"
fi

cd ../
mkdir -p ./$app_build_directory
 
cd $app_build_directory
cmake ../$app_directory -G "Unix Makefiles"
cmake --build .
./main

cd ../$app_directory
