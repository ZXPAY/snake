#include <signal.h>

#include "keyboard_interrupt.h"

/* C catch ctrl-c interrupt */
static volatile int keepRunning = 1;

static void intHandler(int sig) {
    keepRunning = 0;
}

void init_intHandler(void) {
    signal(SIGINT, intHandler);
}



bool isInt(void) {
    return keepRunning;
}

