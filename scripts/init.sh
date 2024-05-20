#!/bin/bash
source scripts/file-sort.sh
PARENT_DIR="/mnt/e/downloads"
FILE_COUNT=$(ls -lA1 "$PARENT_DIR" | wc -l)

if [ ! -d "$PARENT_DIR" ]; then
  echo "Directory $PARENT_DIR does not exist."
  exit 1
fi

file_names=()
counter=0
for FILE in "$PARENT_DIR"/*; do
  if [ -f "$FILE" ]; then
    create_subdirectories "$PARENT_DIR"
    check_file_type "$FILE" "$PARENT_DIR" "$COUNTER"
    fi
done

echo "$FILE_COUNT Files Sorted."
echo "--- Download Sorting Complete! ---"