#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "snake.h"

void init_snake(snake_t *snake) {
    snake->dir = DIR_RIGHT;   // defaule direction
    snake->pos.x = SNAKE_DEFAULT_X;
    snake->pos.y = SNAKE_DEFAULT_Y;
    snake->score = 1;
    snake->food.x = 0;
    snake->food.y = 0;
    snake->food.gen_flag = false;
    snake->gameover = false;
    memset(snake->map, skNONE, sizeof(snake->map));
    snake->map[snake->pos.x][snake->pos.y] = SNAKE;
    snake_GenerateFood(snake);
}

void snake_GenerateFood(snake_t *snake) {
    snake->food.x = rand() % AREA_L;
    snake->food.y = rand() % AREA_H;
    snake->food.gen_flag = true;
    snake->map[snake->food.x][snake->food.y] = FOOD;
}

void snake_Handler(snake_t *snake) {
    if(snake->gameover) {
        snake_gameover_cb(snake);
        return;
    }
    if((snake->pos.x == snake->food.x) && (snake->pos.y == snake->food.y)) {
        snake->map[snake->food.x][snake->food.y] = skNONE;
        snake_GenerateFood(snake);
        snake->score++;
    }
}

void snake_MoveHandler(snake_t *snake) {
    if(snake->gameover) {
        snake_gameover_cb(snake);
        return;
    }
    snake->map[snake->pos.x][snake->pos.y] = skNONE;
    switch (snake->dir) {
        case DIR_UP:
            snake->pos.y--;
            break;
        case DIR_DOWN:
            snake->pos.y++;
            break;
        case DIR_LEFT:
            snake->pos.x--;
            break;
        case DIR_RIGHT:
            snake->pos.x++;
            break;
        default:
            break;
    }
    if((snake->pos.x < 0) || (snake->pos.y < 0) || (snake->pos.x >= AREA_L) || (snake->pos.y >= AREA_H)) {
        snake->gameover = true;
    }
    snake->map[snake->pos.x][snake->pos.y] = SNAKE;
}

void snake_DirHandler(snake_t *snake, snake_direction dir) {
    if(snake->gameover) {
        snake_gameover_cb(snake);
        return;
    }
    if(dir == DIR_NONE) return;
    snake->dir = dir;
}

__attribute__((weak)) void snake_gameover_cb(snake_t *snake) {
    while(true);
}
