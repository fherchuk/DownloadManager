#ifndef SORTER_H
#define SORTER_H

void sort();
void createDirectories();
void moveFile(const char* srcPath, const char* destDir, const char* fileName);
void checkFileType(const char* filePath, int* fileCount);

#endif