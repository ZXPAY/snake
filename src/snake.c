#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "snake.h"
#include "debug_printf.h"
#include <Windows.h>

void init_snake(snake_t *snake) {
    snake->dir = DIR_RIGHT;   // defaule direction
    snake->score = 1;
    snake->food.x = 0;
    snake->food.y = 0;
    snake->gameover = false;
    memset(snake->map, skNONE, sizeof(snake->map));
    // initialize the snake head
    snake->body_length = 0;
    snake->head = (snake_body_t *)malloc(sizeof(snake_body_t));
    memset(snake->head, 0, sizeof(snake_body_t));
    snake->head->pos.x = SNAKE_DEFAULT_X;
    snake->head->pos.y = SNAKE_DEFAULT_Y;
    snake->map[snake->head->pos.x][snake->head->pos.y] = SNAKE;
    snake_GenerateFood(snake);
}

void snake_GenerateFood(snake_t *snake) {
    snake->food.x = rand() % AREA_L;
    snake->food.y = rand() % AREA_H;
    snake->map[snake->food.x][snake->food.y] = FOOD;
}

void snake_createBody(snake_t *snake, snake_pos_t *pos) {
    snake_body_t *temp = snake->head;
    // create new snake body
    snake_body_t *body = (snake_body_t *)malloc(sizeof(snake_body_t));
    memset(body, 0, sizeof(snake_body_t));
    memcpy(&body->pos, pos, sizeof(snake_pos_t));
    snake->body_length++;
    for(int i=0;i<snake->body_length;i++) {
        if(temp->next == NULL) {   // last linklist object
            temp->next = body;
        }
        else {
            temp = temp->next;
        }
    }
    Sleep(1000);
}

void snake_Handler(snake_t *snake) {
    if(snake->gameover) {
        snake_gameover_cb(snake);
        return;
    }
    if((snake->head->pos.x == snake->food.x) && (snake->head->pos.y == snake->food.y)) {
        // Get the food
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
    snake->map[snake->head->pos.x][snake->head->pos.y] = skNONE;
    snake_pos_t last_pos;
    memcpy(&last_pos, &snake->head->pos, sizeof(snake_pos_t));
    snake_body_t *temp = snake->head;
    switch (snake->dir) {
        case DIR_UP:
            snake->head->pos.y--;
            break;
        case DIR_DOWN:
            snake->head->pos.y++;
            break;
        case DIR_LEFT:
            snake->head->pos.x--;
            break;
        case DIR_RIGHT:
            snake->head->pos.x++;
            break;
        default:
            break;
    }
    for(uint32_t i=0;i<snake->body_length;i++) {
        temp = temp->next;   // next body object
        memcpy(&temp->pos, &last_pos, sizeof(snake_pos_t));
        memcpy(&last_pos, &temp->pos, sizeof(snake_pos_t));
    }
    if((snake->head->pos.x < 0) || (snake->head->pos.y < 0) || (snake->head->pos.x >= AREA_L) || (snake->head->pos.y >= AREA_H)) {
        snake->gameover = true;
    }
    // Handle the linklist
    snake->map[snake->head->pos.x][snake->head->pos.y] = SNAKE;
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
