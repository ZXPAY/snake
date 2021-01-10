/* Include standard library */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

#include <conio.h>
#include "snake.h"
#include "debug_printf.h"
#include "keyboard_interrupt.h"

#ifdef _WIN32
#include <Windows.h>
#endif

void start_snake_thread(void);
void terminate_thread(void);

void clear_screen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/* Define the snake structure */
snake_t snake;

DWORD WINAPI task_update_map(LPVOID Param) {
    while(true) {
        printf("\e[?25l");
        printf("score: %d, gameover: %d" , snake.score, snake.gameover);
        putchar('\n');
        for(uint32_t i=0;i<AREA_L+2;i++) putchar('=');
        putchar('\n');
        assert(snake.score>0);
        for(uint32_t y=0;y<AREA_H;y++) {
            putchar('=');
            for(uint32_t x=0;x<AREA_L;x++) {
                putchar(snake.map[x][y]);
            }
            printf("=\n");
        }
        for(uint32_t i=0;i<AREA_H+2;i++) putchar('=');
        putchar('\n');
#ifdef DEBUG
        DEBUG_INFO("Dir: %d\n", snake.dir);
        DEBUG_INFO("head: %d, %d\n", snake.head->pos.x, snake.head->pos.y);
        snake_body_t *body;
        body = snake.head;
        for(uint32_t i=0;i<snake.body_length;i++) {
            body = body->next;
            DEBUG_INFO("body[%d]: %d, %d\n", i, body->pos.x, body->pos.y);
        }
#endif
        Sleep(REFRESH_SCREEN_TIME);
        clear_screen();
    }
}

DWORD WINAPI task_snakeMove(LPVOID Param) {
    while(true) {
        snake_MoveHandler(&snake);
        Sleep(600-SNAKE_SPEED);
    }
}

DWORD WINAPI task_keyin(LPVOID Param) {
    while(true) {
        snake_direction dir = DIR_NONE;
        switch(getch()) {
            case 72:    // up
                dir = DIR_UP;
                break;
            case 80:   // down
                dir = DIR_DOWN;
                break;
            case 75:   // left
                dir = DIR_LEFT;
                break;
            case 77:   // right
                dir = DIR_RIGHT;
                break;
        }
        snake_DirHandler(&snake, dir);
    }
}

static HANDLE ThreadHandle_update_map;
static DWORD ThreadId_update_map;
static HANDLE ThreadHandle_snakeMove;
static DWORD ThreadId_snakeMove;
static HANDLE ThreadHandle_keyin;
static DWORD ThreadId_keyin;

int main(void) {
    srand(time(NULL));
    init_intHandler();      // Handler ctrl-c

    /* Initialize the snake */
    init_snake(&snake);
    start_snake_thread();

    /* main loop */
    while(isInt()) {
        if(snake.gameover) {
            break;
        }        
    }
    clear_screen();
    printf("program stop ...\n");
    printf("your score: %d\n", snake.score);
    system("pause");
    return 0;
}

void start_snake_thread(void) {
    /* Define the thread for updating map */
    ThreadHandle_update_map = CreateThread(NULL, 0, task_update_map, NULL, 0, &ThreadId_update_map);
    (void)ThreadHandle_update_map;

    /* Define the thread for moving the snake */
    ThreadHandle_snakeMove = CreateThread(NULL, 0, task_snakeMove, NULL, 0, &ThreadId_snakeMove);
    (void)ThreadHandle_snakeMove;

    /* Define the thread for handling keyboard key input */
    ThreadHandle_keyin = CreateThread(NULL, 0, task_keyin, NULL, 0, &ThreadId_keyin);
    (void)ThreadHandle_keyin;
}

void terminate_thread(void) {
    fflush(stdin);
    fflush(stdout);
    TerminateThread(ThreadHandle_keyin, ThreadId_keyin);
    TerminateThread(ThreadHandle_update_map, ThreadId_update_map);
    TerminateThread(ThreadHandle_snakeMove, ThreadId_snakeMove);
}

void snake_gameover_cb(snake_t *snake) {
    terminate_thread();
}

void SIGINT_cb(void) {
    terminate_thread();
}
