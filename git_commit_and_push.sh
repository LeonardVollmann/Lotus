#!/bin/bash

./clean.sh

git add .
git commit
git push origin master

./build.sh