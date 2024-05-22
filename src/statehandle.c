#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "statehandle.h"

extern char* directory;

ProgramState handleInitialize(size_t* buffer) {
    initialize(buffer);
    return STATE_SORT;
}
ProgramState handleSort() {
    sort();
    return STATE_MONITOR;
}
ProgramState handleMonitor() {
    MonitorDirectory();
    return STATE_CLEANUP;
}
ProgramState handleCleanup() {
    cleanup();
    return STATE_EXIT;
}

void stateHandler(size_t* buffer) {
    ProgramState state = STATE_INITIALIZE;
    ProgramState nextState;

    while (state != STATE_EXIT && state != STATE_ERROR) {
        switch (state) {
        case STATE_INITIALIZE:
            nextState = handleInitialize(buffer);
            break;
        case STATE_SORT:
            nextState = handleSort();
            break;
        case STATE_MONITOR:
            nextState = handleMonitor();
            break;
        case STATE_CLEANUP:
            nextState = handleCleanup();
            break;
        default:
            nextState = STATE_ERROR;
            break;
        }
        state = nextState;
    }

    (state == STATE_ERROR) ? fprintf(stderr, "AN ERROR HAS OCCCURED. DOWNLOAD MANAGER CRASHED\n") : 0;
}