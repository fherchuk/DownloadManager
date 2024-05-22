#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "monitor.h"

extern char* directory;

void initialize(size_t* buffer) {
    printf("Enter the path to your downloads folder: ");
    if (fgets(directory, *buffer, stdin) != NULL) {
        size_t len = strlen(directory);
        (len > 0 && (directory)[len - 1] == '\n') ? (directory[len - 1] = '\0') : 0;
        printf("Download Directory: %s\n", directory);
    }
    else {
        printf("Error reading input\n");
        return;
    }
    printf("Monitoring directory: %s\n", directory);
}

void cleanup(void) {
    (directory != NULL) ? (free(directory), directory = NULL) : 0;
}