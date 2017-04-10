#!/bin/sh

if [ ! -z "$1" ] ; then
    mkdir -p ./Release
    rm -r ./Release/*
    mkdir -p ./Release/M3LS_${1}
    cp ./C++/src/M3LS.cc ./Release/M3LS_${1}/M3LS.cpp
    cp ./C++/src/hidjoystickrptparser.cpp ./Release/M3LS_${1}/hidjoystickrptparser.cpp
    cp ./C++/include/M3LS.h ./Release/M3LS_${1}/M3LS.h
    cp ./C++/include/hidjoystickrptparser.h ./Release/M3LS_${1}/hidjoystickrptparser.h
    cp -r ./Arduino/examples ./Release/M3LS_${1}/
    cd Release
    zip -rq ./M3LS_${1}.zip ./M3LS_${1}
    cd ..
else
    echo "No version number provided!"
    exit 1
fi


