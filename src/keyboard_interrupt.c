#include <stdio.h>
#include <assert.h>
#include <signal.h>

#include "keyboard_interrupt.h"

/* C catch ctrl-c interrupt */
static volatile int keepRunning = 1;

static void intHandler(int sig) {
    assert(sig==2);
    printf("interrupt signal detect : %d\n", sig);
    keepRunning = 0;
}

void init_intHandler(void) {
    signal(SIGINT, intHandler);
}

bool isInt(void) {
    return keepRunning;
}

