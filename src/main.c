#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monitor.h"
#include "interface.h"
#include "sorter.h"
#include "statehandle.h"

char* directory;

int main()
{
    size_t buffer = 256;
    directory = (char*)malloc(buffer * sizeof(char));

    if (directory == NULL)
    {
        fprintf(stderr, "Failed Memory Allocation\n");
        return 1;
    }
    stateHandler(&buffer);

    return 0;
}