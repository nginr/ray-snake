#include "snake.h"
#include <raylib.h>
#include <raymath.h>
#include <stddef.h>

#define SNAKE_COLOR                                                            \
    (Color) { 43, 51, 24, 255 }

#define SNAKE_HEAD_COLOR                                                       \
    (Color) { 50, 70, 24, 255 }

void init_rand_snake(Snake *s, size_t init_size, size_t cellCount) {
    assert(cellCount >= 2 * init_size &&
           "Cell count cannot be less than snake size!");

    s->dir = (Direction)rand() % 4;

    size_t x = init_size + (rand() % (cellCount - 2 * init_size));
    size_t y = init_size + (rand() % (cellCount - 2 * init_size));

    da_append(&s->body, ((Vector2) {x, y}));
    switch (s->dir) {
        case UP: {
            da_append(&s->body, ((Vector2) {x, y + 1}));
            da_append(&s->body, ((Vector2) {x, y + 2}));
            break;
        }
        case DOWN: {
            da_append(&s->body, ((Vector2) {x, y - 1}));
            da_append(&s->body, ((Vector2) {x, y - 2}));
            break;
        }
        case LEFT: {
            da_append(&s->body, ((Vector2) {x + 1, y}));
            da_append(&s->body, ((Vector2) {x + 2, y}));
            break;
        }
        case RIGHT: {
            da_append(&s->body, ((Vector2) {x - 1, y}));
            da_append(&s->body, ((Vector2) {x - 2, y}));
            break;
        }
    }
}

void update_snake(Snake *s) {
    da_popback(&s->body);
    Vector2 d = direction(s->dir);
    Vector2 h = Vector2Add(s->body.items[0], d);
    da_push(&s->body, h);
}

void draw_snake(Snake *s, size_t cellBlock) {
    for (size_t i = 0; i < s->body.count; ++i) {
        int x = s->body.items[i].x;
        int y = s->body.items[i].y;
        if (i == 0) {
            DrawRectangle(x * cellBlock, y * cellBlock, cellBlock, cellBlock,
                          SNAKE_HEAD_COLOR);
        } else {
            DrawRectangle(x * cellBlock, y * cellBlock, cellBlock, cellBlock,
                          SNAKE_COLOR);
        }
    }
}

void destroy_snake(Snake *s) { free(s->body.items); }

Vector2 direction(Direction d) {
    switch (d) {
        case UP: {
            return (Vector2) {0, -1};
        }
        case DOWN: {
            return (Vector2) {0, 1};
        }
        case LEFT: {
            return (Vector2) {-1, 0};
        }
        case RIGHT: {
            return (Vector2) {1, 0};
        }
    }
    return (Vector2) {0, 0};
}

void control_snake(Snake *s) {
    switch (GetKeyPressed()) {
        case KEY_UP: {
            if (s->dir != DOWN)
                s->dir = UP;
            break;
        }
        case KEY_DOWN: {
            if (s->dir != UP)
                s->dir = DOWN;
            break;
        }
        case KEY_LEFT: {
            if (s->dir != RIGHT)
                s->dir = LEFT;
            break;
        }
        case KEY_RIGHT: {
            if (s->dir != LEFT)
                s->dir = RIGHT;
            break;
        }
    }
}
