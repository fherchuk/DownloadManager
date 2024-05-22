#ifndef STATEHANDLE_H
#define STATEHANDLE_H

#include <stddef.h>
#include "monitor.h"
#include "sorter.h"
#include "interface.h"

typedef enum {
    STATE_INITIALIZE,
    STATE_SORT,
    STATE_MONITOR,
    STATE_CLEANUP,
    STATE_EXIT,
    STATE_ERROR
} ProgramState;

void initialize(size_t* buffer);
void sort();
void MonitorDirectory();
void cleanup();

ProgramState handleInitialize(size_t* buffer);
ProgramState handleSort();
ProgramState handleMonitor();
ProgramState handleCleanup();

void stateHandler(size_t* buffer);

#endif