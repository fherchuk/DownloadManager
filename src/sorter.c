#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include "sorter.h"

#ifdef _WIN32
#include <direct.h>
#define mkdir(dir, mode) _mkdir(dir)
#else
#include <sys/types.h>
#include <sys/stat.h>
#endif

#define MAX_PATH_LEN 256
#define MAX_FILENAME_LEN 256

extern char* directory;

void sort() {
    int fileCount = 0;
    DIR* dir = opendir(directory);

    if (dir == NULL) {
        printf("Directory %s does not exist.\n", directory);
        return;
    }

    createDirectories(directory);
    struct dirent* entry;

    while ((entry = readdir(dir)) != NULL) {
        char filePath[MAX_PATH_LEN];
        snprintf(filePath, sizeof(filePath), "%s/%s", directory, entry->d_name);
        struct stat path_stat;

        stat(filePath, &path_stat);
        if (S_ISREG(path_stat.st_mode)) {
            checkFileType(filePath, &fileCount);
        }
    }

    closedir(dir);

    printf("%d Files Sorted.\n", fileCount);
    printf("--- Download Sorting Complete! ---\n");
}

void createDirectories() {
    const char* subDirs[] = { "Images", "Media", "ZIP", "Text", "Photoshop", "Executables" };
    int numSubdirs = sizeof(subDirs) / sizeof(subDirs[0]);

    for (int i = 0; i < numSubdirs; i++) {
        char dirPath[MAX_PATH_LEN];
        snprintf(dirPath, sizeof(dirPath), "%s/%s", directory, subDirs[i]);

        struct stat st = { 0 };
        if (stat(dirPath, &st) == -1) {
            mkdir(dirPath, 0755);
            printf("Created: %s\n", dirPath);
        }
    }
}

void moveFile(const char* srcPath, const char* destDir, const char* fileName) {
    char destPath[MAX_PATH_LEN];
    snprintf(destPath, sizeof(destPath), "%s/%s", destDir, fileName);
    rename(srcPath, destPath);
    printf("Moved file %s to %s\n", fileName, destDir);
}

void checkFileType(const char* filePath, int* fileCount) {
    char baseFile[MAX_FILENAME_LEN];
    char extension[MAX_FILENAME_LEN];
    const char* delimiters = ".";
    char* token;

    char mutableFilePath[MAX_PATH_LEN];
    strncpy(mutableFilePath, filePath, MAX_PATH_LEN);
    mutableFilePath[MAX_PATH_LEN - 1] = '\0';

    char* fileName = strrchr(mutableFilePath, '/');
    if (fileName == NULL) {
        fileName = strrchr(mutableFilePath, '\\');
    }
    if (fileName == NULL) {
        fileName = mutableFilePath;
    }
    else {
        fileName++;
    }

    strncpy(baseFile, fileName, MAX_FILENAME_LEN);
    baseFile[MAX_FILENAME_LEN - 1] = '\0';
    token = strtok(baseFile, delimiters);

    while (token != NULL) {
        strncpy(extension, token, MAX_FILENAME_LEN);
        extension[MAX_FILENAME_LEN - 1] = '\0';
        token = strtok(NULL, delimiters);
    }

    const char* fileTypes[][2] = {
        {"jpg", "Images"}, {"jpeg", "Images"}, {"png", "Images"}, {"gif", "Images"}, {"bmp", "Images"}, {"webp", "Images"}, {"svg", "Images"}, {"mp3", "Media"}, {"wav", "Media"}, {"ogg", "Media"}, {"flac", "Media"}, {"mp4", "Media"}, {"avi", "Media"}, {"mpeg", "Media"}, {"mov", "Media"}, {"zip", "ZIP"}, {"rar", "ZIP"}, {"tar", "ZIP"}, {"7z", "ZIP"}, {"gz", "ZIP"}, {"txt", "Text"}, {"html", "Text"}, {"css", "Text"}, {"xml", "Text"}, {"pdf", "Text"}, {"docx", "Text"}, {"psd", "Photoshop"} };

    int numFileTypes = sizeof(fileTypes) / sizeof(fileTypes[0]);
    int isMatched = 0;

    for (int i = 0; i < numFileTypes; i++) {
        if (strcmp(extension, fileTypes[i][0]) == 0) {
            char destDir[MAX_PATH_LEN];
            snprintf(destDir, sizeof(destDir), "%s/%s", directory, fileTypes[i][1]);
            moveFile(filePath, destDir, fileName);
            (*fileCount)++;
            isMatched = 1;
            break;
        }
    }

    if (!isMatched) {
        char destDir[MAX_PATH_LEN];
        snprintf(destDir, sizeof(destDir), "%s/%s", directory, "Executables");
        moveFile(filePath, destDir, fileName);
        (*fileCount)++;
    }
}
