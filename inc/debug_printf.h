#ifndef DEBUG_PRINTF_H
#define DEBUG_PRINTF_H

#include <stdio.h>

#ifdef DEBUG
#define DEBUG_INFO(INFO, args...) printf("[DEBUG]" INFO, ##args);
#else
#define DEBUG_INFO(INFO, args...) 
#endif

#endif /* DEBUG_PRINTF_H */
