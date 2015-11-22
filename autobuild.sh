#!/bin/bash

# This is from http://swarminglogic.com/article/2013_06_cpp_setup

commnd='find ./LotusEngine/src ./Sandbox/src
 -name "[!\.]*.cpp" -or
 -name "[!\.]*.h"   -or
 -name "[!\.]*.tpp" -or
 -name "SConscript*" -or
 -name "SConstruct"
 | xargs stat -t %Y | md5'

compileCmmnd='make'

md5sumStart=`eval $commnd`
clear
echo "Waiting for changes."

while [[ true ]]
do
    md5sumNow=$md5sumStart

    # Loop until some files have changed
    while [[ "$md5sumNow" = "$md5sumStart" ]]
    do
        sleep 0.5
        md5sumNow=`eval $commnd`
    done

    # Recompile
    clear
    $compileCmmnd
    compileOk=$?
    md5sumStart=`eval $commnd`

    # Report build ok, or failure (clear if former)
    if [[ $compileOk -eq 0 ]]
    then
        clear
        echo -e '[\033[1;32m Build OK\033[0m ]'
    else
        echo -e '[\033[0;31m Build Failed\033[0m ]'
    fi

    # Run executed command.
    if [[ $# -gt 0  &&  $compileOk -eq 0 ]]
    then
        if [[  -e ./$1 ]]
        then
            ./$1 ^
        else
            echo -e "[\033[0;31m Executable '$1' was not found!\033[0m ]";
        fi
    fi
done