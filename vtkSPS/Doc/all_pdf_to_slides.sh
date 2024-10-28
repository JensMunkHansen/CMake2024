#!/bin/bash

find . -name "*.pdf" -exec sh -c '
    for file do
        filename=$(basename "$file" .pdf)
        ./pdf_to_slides.sh "$file" "$filename"
    done
' sh {} +
