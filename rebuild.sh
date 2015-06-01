#!/bin/bash

./clean.sh

echo "Running cmake..."
cmake .

echo "Building executable..."
make all