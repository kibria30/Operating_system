#!/bin/bash

directory="/home/iit/Desktop/BSSE1430/os"
#echo "Enter directory name (with path):"
#read directory

files=$(find "$directory" -type f -name "*.c" -o -name "*.cpp")

for file in $files; do
    echo "Filename: $(basename "$file"), Size: $(du -h "$file" | cut -f1), Lines: $(wc -l < "$file") "
    
done