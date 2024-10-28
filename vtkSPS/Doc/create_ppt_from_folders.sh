#!/bin/bash

# Create an array to store all folder names
folders=()

# Find all directories, handling spaces correctly
while IFS= read -r -d '' folder; do
    if [ "$folder" != "." ]; then  # Skip the current directory
        folders+=("$folder")
    fi
done < <(find . -type d -print0 | sort -z)

# Call the Python script with all folders as arguments
python create_ppt_from_folders.py "output_presentation.pptx" "${folders[@]}"
