#ifndef SNAKE_H
#define SNAKE_H

#define START_X_POS         0
#define START_Y_POS         2
#define AREA_L              20
#define AREA_H              20
#define SNAKE_ASCII         '+'
#define SNAKE_FOOD          '*'
#define SNAKE_NONE          ' '

#define REFRESH_SCREEN_TIME 10
#define SNAKE_SPEED_MAX     500
#define SNAKE_SPEED         300

typedef enum DIR_ENUM{
    DIR_NONE,
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT,
}snake_direction;

typedef enum SNAKE_INFO_ENUM{
    skNONE = SNAKE_NONE,
    SNAKE = SNAKE_ASCII,
    FOOD = SNAKE_FOOD,
}snake_info;

/* Define the default value */
#define SNAKE_DEFAULT_DIR   DIR_RIGHT
#define SNAKE_DEFAULT_X     (5)
#define SNAKE_DEFAULT_Y     (5)

typedef uint8_t snake_map_t;
typedef uint8_t snake_dir_t;
typedef uint32_t snake_speed_t;

typedef struct _snake_pos_t {
    int x;
    int y;
}snake_pos_t;
typedef struct _snake_food_t {
    int x;
    int y;
    uint8_t gen_flag;
}snake_food_t;

typedef struct _snake_t {
    snake_map_t map[AREA_L][AREA_H];
    snake_dir_t dir;
    snake_pos_t pos;
    snake_food_t food;
    snake_speed_t speed;
    uint32_t score;
    bool gameover;
}snake_t;

void init_snake(snake_t *snake);
void snake_GenerateFood(snake_t *snake);
void snake_MoveHandler(snake_t *snake);
void snake_Handler(snake_t *snake);
void snake_DirHandler(snake_t *snake, snake_direction dir);
__attribute__((weak)) void snake_gameover_cb(snake_t *snake); 

#endif /* SNAKE_H */
