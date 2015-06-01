#!/bin/bash

clear

echo "Running cmake..."
cmake .

echo "Building executable..."
make all

echo "Running executable..."
./Lotus