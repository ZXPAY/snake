#ifndef SNAKE_H
#define SNAKE_H

#define START_X_POS         0
#define START_Y_POS         2
#define AREA_L              50
#define AREA_H              50

#define REFRESH_SCREEN_TIME 100


enum {
    DIR_NONE,
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT,
}DIR_ENUM;

/* Define the default value */
#define SNAKE_DEFAULT_DIR   DIR_RIGHT
#define SNAKE_DEFAULT_X     (1)
#define SNAKE_DEFAULT_Y     (1)

typedef uint8_t snake_dir_t;

typedef struct _snake_pos_t {
    uint32_t x;
    uint32_t y;
}snake_pos_t;

typedef struct _snake_t {
    snake_dir_t dir;
    snake_pos_t pos;
    uint32_t score;
}snake_t;

void init_snake(snake_t *snake) {
    snake->dir = DIR_RIGHT;   // defaule direction
    snake->pos.x = SNAKE_DEFAULT_X;
    snake->pos.y = SNAKE_DEFAULT_Y;
    
}

#endif /* AREA_H */
