#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "snake.h"

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
    snake_createBody(snake, &snake->head->pos);
    snake->map[snake->head->pos.x][snake->head->pos.y] = SNAKE_ASCII_HEAD;
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
}

bool isCollision(snake_t *snake) {
    snake_body_t *head = snake->head;
    snake_body_t *temp = head;
    
    while(temp != NULL) {
        assert(head!=NULL);
        assert(temp!=NULL);

        temp = temp->next;
    }
    return false;
}

void snake_Handler(snake_t *snake) {
    if(snake->gameover) {
        return;
    }
    if((snake->head->pos.x == snake->food.x) && (snake->head->pos.y == snake->food.y)) {
        // Get the food
        snake->map[snake->food.x][snake->food.y] = skNONE;
        snake_GenerateFood(snake);
        snake->score++;
        snake_pos_t body_pos;
        snake_body_t *tail = snake->head;
        while(tail->next != NULL) {
            tail = tail->next;
        }
        memcpy(&body_pos, &tail->pos, sizeof(snake_pos_t));
        switch (snake->dir) {
            case DIR_UP:
                body_pos.y--;
                break;
            case DIR_DOWN:
                body_pos.y++;
                break;
            case DIR_LEFT:
                body_pos.x--;
                break;
            case DIR_RIGHT:
                body_pos.x++;
                break;
            default:
                break;
        }
        snake_createBody(snake, &body_pos);
    }
    if(isCollision(snake)) {
        snake->gameover = true;
        snake_gameover_cb(snake);
        return;
    }
}

void snake_MoveHandler(snake_t *snake) {
    if(snake->gameover) {
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
    snake_pos_t *col_pos = malloc(snake->body_length*sizeof(snake_pos_t));
    assert(col_pos!=NULL);
    memset(col_pos, 0, snake->body_length*sizeof(snake_pos_t));
    int cnt = 0;
    for(uint32_t i=0;i<snake->body_length;i++) {
        temp = temp->next;   // next body object
        assert(temp!=NULL);
        memcpy(&col_pos[cnt++], &temp->pos, sizeof(snake_pos_t));
        if(i==0) {
            memcpy(&temp->pos, &last_pos, sizeof(snake_pos_t));
        }
        else {
            memcpy(&temp->pos, &col_pos[cnt-2], sizeof(snake_pos_t));
        }
        snake->map[temp->pos.x][temp->pos.y] = SNAKE_BODY;
        if(i==snake->body_length-1) { // tail
            snake->map[temp->pos.x][temp->pos.y] = SNAKE_ASCII_NONE;
        }
    }
    free(col_pos);
    // Handle the linklist
    snake->map[snake->head->pos.x][snake->head->pos.y] = SNAKE_HEAD;
    
    if((snake->head->pos.x < 0) || (snake->head->pos.y < 0) || (snake->head->pos.x >= AREA_L) || (snake->head->pos.y >= AREA_H)) {
        snake->gameover = true;
        snake_gameover_cb(snake);
        return;
    }
    
    snake_Handler(snake);
}

void snake_DirHandler(snake_t *snake, snake_direction dir) {
    if(snake->gameover) {
        return;
    }
    if(dir == DIR_NONE) return;
    snake->dir = dir;
}

__attribute__((weak)) void snake_gameover_cb(snake_t *snake) {
    while(true);
}
