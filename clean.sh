#!/bin/bash

rm -rf bin
mkdir bin

rm cmake_install.cmake
rm CMakeCache.txt
rm -rf CMakeFiles
rm Makefile

rm LotusEngine/cmake_install.cmake
rm -rf LotusEngine/CMakeFiles
rm LotusEngine/Makefile

rm Sandbox/cmake_install.cmake
rm -rf Sandbox/CMakeFiles
rm Sandbox/Makefile