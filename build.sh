#!/bin/bash

cmake .

rm -rf bin/include
mkdir bin/include

(cd LotusEngine/src && find . -name '*.hpp' -print | tar --create --files-from -) | (cd bin/include && tar xvfp -)

make