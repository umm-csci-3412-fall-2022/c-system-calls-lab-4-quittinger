#!/bin/bash

dir=$1

echo "There were $(find $dir -type d | wc --lines) directories."
echo "There were $(find $dir -type f | wc --lines) regular files."
