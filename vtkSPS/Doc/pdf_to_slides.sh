#!/bin/bash

# Check if the correct number of arguments is provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <pdf_file> <output_dir>"
    exit 1
fi

# Assign input arguments to variables
PDF_FILE="$1"
OUTPUT_DIR="$2"

# Check if the PDF file exists
if [ ! -f "$PDF_FILE" ]; then
    echo "Error: PDF file '$PDF_FILE' not found!"
    exit 1
fi

# Create the output directory if it doesn't exist
mkdir -p "$OUTPUT_DIR"

# Convert each page of the PDF to a high-resolution image
pdftoppm -png -r 300 "$PDF_FILE" "$OUTPUT_DIR/page"

# Now, crop each page into 4 individual slides
for PAGE in "$OUTPUT_DIR"/page-*.png; do
    # Get the page number from the filename (for example, page-001.png -> 001)
    BASENAME=$(basename "$PAGE" .png)

    # Get the image dimensions (assuming it's landscape, i.e., width > height)
    WIDTH=$(identify -format "%w" "$PAGE")
    HEIGHT=$(identify -format "%h" "$PAGE")

    # Calculate the dimensions for each quarter (slide)
    HALF_WIDTH=$(( WIDTH / 2 ))
    HALF_HEIGHT=$(( HEIGHT / 2 ))

    # Crop into 4 slides (1st: top-left, 2nd: top-right, 3rd: bottom-left, 4th: bottom-right)
    convert "$PAGE" -crop "${HALF_WIDTH}x${HALF_HEIGHT}+0+0" "$OUTPUT_DIR/${BASENAME}_slide_1.png"
    convert "$PAGE" -crop "${HALF_WIDTH}x${HALF_HEIGHT}+${HALF_WIDTH}+0" "$OUTPUT_DIR/${BASENAME}_slide_2.png"
    convert "$PAGE" -crop "${HALF_WIDTH}x${HALF_HEIGHT}+0+${HALF_HEIGHT}" "$OUTPUT_DIR/${BASENAME}_slide_3.png"
    convert "$PAGE" -crop "${HALF_WIDTH}x${HALF_HEIGHT}+${HALF_WIDTH}+${HALF_HEIGHT}" "$OUTPUT_DIR/${BASENAME}_slide_4.png"
    
    # Optionally remove the full page image
    rm "$PAGE"
done

echo "PNG slides have been extracted to $OUTPUT_DIR"
