#!/bin/bash

clear

echo "Deleting cmake files ..."
rm -rf CMakeFiles/
rm CMakeCache.txt
rm cmake_install.cmake

echo "Deleting executable..."
rm Lotus