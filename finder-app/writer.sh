#!/bin/bash

if [ $# -ne 2 ] 
then
    echo "Enter a writefile and a writestr as arguments"
    exit 1
fi

writefile=$1
writestr=$2

mkdir -p "$(dirname "$writefile")"
echo "$writestr" > "$writefile"

if [ ! -f "$writefile" ] 
then
    echo "Could not succesfully make file"
    exit 1
fi