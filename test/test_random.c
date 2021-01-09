#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand(time(NULL));
    int x;
    for(int i=0;i<10;i++) {
        x = rand();
        printf("%d\n", x);
    }
}

