/* Include standard library */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include <conio.h>
#include "snake.h"
#include "debug_printf.h"
#include "keyboard_interrupt.h"

#ifdef _WIN32
#include <Windows.h>
#endif

void clear_screen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/* Define the snake structure */
snake_t snake;

uint32_t c1 = 0;
uint32_t c2 = 0;
uint32_t c3 = 0;

DWORD WINAPI task_update_map(LPVOID Param){
    while(true) {
        c1++;
        Sleep(REFRESH_SCREEN_TIME);
    }
}
DWORD WINAPI task_keyin(LPVOID Param){
    while(true) {
        switch(getch()) {
            case 72:    // up
                DEBUG_INFO("up\n");
                snake.dir = DIR_UP;
                break;
            case 80:   // down
                DEBUG_INFO("down\n");
                snake.dir = DIR_DOWN;
                break;
            case 75:   // left
                DEBUG_INFO("left\n");
                snake.dir = DIR_LEFT;
                break;
            case 77:   // right
                DEBUG_INFO("right\n");
                snake.dir = DIR_DOWN;
                break;
        }
        
    }
}

int main(void) {
    printf("score %d\n" , 0);
    init_intHandler();      // Handler ctrl-c

    /* Initialize the snake */
    init_snake(&snake);
    
    /* Define the thread for updating map */
    DWORD ThreadId_update_map;
    HANDLE ThreadHandle_update_map;
    ThreadHandle_update_map = CreateThread(NULL, 0, task_update_map, NULL, 0, &ThreadId_update_map);
    (void)ThreadHandle_update_map;

    /* Define the thread for handling keyboard key input */
    DWORD ThreadId_keyin;
    HANDLE ThreadHandle_keyin;
    ThreadHandle_keyin = CreateThread(NULL, 0, task_keyin, NULL, 0, &ThreadId_keyin);
    (void)ThreadHandle_keyin;

    /* main loop */
    while(isInt()) {
        
    }
    
    printf("program stop ...\n");
    return 0;
}



