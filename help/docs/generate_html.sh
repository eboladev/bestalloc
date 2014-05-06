#!/bin/bash

for rst_file in *.rst
do
    html_file=${rst_file%.*}.html
    echo "Generating '${html_file}'..."
    rst2html.py $rst_file ${html_file}
done


