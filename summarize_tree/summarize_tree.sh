#!/bin/bash

dir=$1

# use the find function to find either directories or files, then pipe the output to wc to count 
# the total lines in the output. Which should be the amount of files or directories found
echo "There were $(find $dir -type d | wc --lines) directories."
echo "There were $(find $dir -type f | wc --lines) regular files."
