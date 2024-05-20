#!/bin/bash
check_file_type() {
    local BASE_FILE=$(basename "$1")
    local FILE_TYPE=$(file --mime-type -b "$1")

    case $FILE_TYPE in
        image/jpeg|image/png|image/gif|image/bmp|image/webp|image/svg+xml)
            mv "$1" "$2/Images"
            echo "Moved file $BASE_FILE to Images"
            ;;
        audio/mpeg|audio/wav|audio/x-wav|audio/ogg|audio/flac) 
            mv "$1" "$2/Media"
            echo "Moved file $BASE_FILE to Media"
            ;;
        video/mp4|video/avi|video/mpeg|video/quicktime)
            mv "$1" "$2/Media"
            echo "Moved file $BASE_FILE to Media"
            ;;
        application/zip|application/x-rar-compressed|application/x-tar|application/x-rar|application/x-7z-compressed|application/x-gzip)
            mv "$1" "$2/ZIP"
            echo "Moved file $BASE_FILE to ZIP"
            ;;
        text/plain|text/html|text/css|text/xml|application/pdf)
            mv "$1" "$2/Text"
            echo "Moved file $BASE_FILE to Text"
            ;;
        application/vnd.openxmlformats-officedocument.wordprocessingml.document)
            mv "$1" "$2/Text"
            echo "Moved file $BASE_FILE to Text"
            ;;
        image/vnd.adobe.photoshop)
            mv "$1" "$2/Photoshop"
            echo "Moved file $BASE_FILE to Photoshop"
            ;;
        *)
            mv "$1" "$2/Executables"
            echo "Moved file $BASE_FILE to Executables"
            ;;
    esac
}

create_subdirectories() {
    local DIRECTORIES=("Images" "Media" "ZIP" "Text" "Photoshop" "Executables")

    for FOLDER in "${DIRECTORIES[@]}"; do
        local DIR_PATH="$1/$FOLDER"

        if [ ! -d "$DIR_PATH" ]; then
            mkdir -p "$DIR_PATH"
            echo "Created: $DIR_PATH"
        fi
    done
}