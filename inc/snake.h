#ifndef SNAKE_H
#define SNAKE_H

#define START_X_POS         0
#define START_Y_POS         2
#define AREA_L              20
#define AREA_H              20
#define SNAKE_ASCII_HEAD    '+'
#define SNAKE_ASCII_BODY    'O'
#define SNAKE_ASCII_FOOD    '*'
#define SNAKE_ASCII_NONE    ' '

#define REFRESH_SCREEN_TIME 5
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
    skNONE     = SNAKE_ASCII_NONE,
    SNAKE_HEAD = SNAKE_ASCII_HEAD,
    SNAKE_BODY = SNAKE_ASCII_BODY,
    FOOD       = SNAKE_ASCII_FOOD,
}snake_info;

/* Define the default value */
#define SNAKE_DEFAULT_DIR   DIR_RIGHT
#define SNAKE_DEFAULT_X     (5)
#define SNAKE_DEFAULT_Y     (5)

typedef struct _snake_pos_ {
    int x;
    int y;
}snake_pos_t;

/* Linklist snake body type */
typedef struct _snake_body_ {
    snake_pos_t pos;
    struct _snake_body_ *next;
}snake_body_t;

typedef uint8_t snake_map_t;
typedef uint8_t snake_dir_t;
typedef uint32_t snake_speed_t;
typedef snake_pos_t snake_food_t;

typedef struct _snake_t {
    snake_map_t map[AREA_L][AREA_H];
    snake_dir_t dir;
    snake_food_t food;
    snake_speed_t speed;
    snake_body_t *head;
    uint32_t body_length;
    uint32_t score;
    bool gameover;
}snake_t;

void init_snake(snake_t *snake);
void snake_GenerateFood(snake_t *snake);
void snake_createBody(snake_t *snake, snake_pos_t *pos);
bool isCollision(snake_t *snake);
void snake_MoveHandler(snake_t *snake);
void snake_Handler(snake_t *snake);
void snake_DirHandler(snake_t *snake, snake_direction dir);
__attribute__((weak)) void snake_gameover_cb(snake_t *snake); 

#endif /* SNAKE_H */
