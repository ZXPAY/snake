#include <stdbool.h>

/* keyboard interrupt usage API */
void init_intHandler(void);
bool isInt(void);
__attribute__((weak)) void SIGINT_cb(void);

