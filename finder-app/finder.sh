#!/bin/bash

if [ $# -ne 2 ] 
then
    echo "Enter a filesdir and a searchstr as arguments"
    exit 1
fi

filesdir=$1
searchstr=$2

if [ ! -d "$filesdir" ] 
then
    echo "The given filesdir argument is not a valid directory"
    exit 1
fi

file_count=0
match_count=0

search_files() {
    local dir=$1

    for file in "$dir"/*; do
        if [ -f "$file" ]; then
            ((file_count++))
            lines=$(grep -F "$searchstr" "$file" | wc -l)
            ((match_count += lines))
        elif [ -d "$file" ]; then
            search_files "$file"
        fi
    done
}

search_files "$filesdir"

echo "The number of files are $file_count and the number of matching lines are $match_count"