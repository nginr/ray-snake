#ifndef SNAKE_H
#define SNAKE_H

#include <assert.h>
#include <raylib.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define DA_INIT_CAP 25
#define ARRAY_LEN(xs) sizeof((xs)) / sizeof((xs)[0])

typedef struct {
    Vector2 *items;
    size_t   count;
    size_t   capacity;
} node;

typedef enum { UP, DOWN, LEFT, RIGHT } Direction;

typedef struct Snake {
    node      body;
    Direction dir;
    Texture2D tex[3];
} Snake;

#define da_append(da, item)                                                    \
    do {                                                                       \
        if ((da)->count >= (da)->capacity) {                                   \
            (da)->capacity =                                                   \
                (da)->capacity == 0 ? DA_INIT_CAP : (da)->capacity * 2;        \
            (da)->items =                                                      \
                realloc((da)->items, (da)->capacity * sizeof(*(da)->items));   \
            assert((da)->items != NULL && "Buy more RAM lol");                 \
        }                                                                      \
        (da)->items[(da)->count++] = (item);                                   \
    } while (0)

#define da_push(da, item)                                                      \
    do {                                                                       \
        if ((da)->count >= (da)->capacity) {                                   \
            (da)->capacity =                                                   \
                (da)->capacity == 0 ? DA_INIT_CAP : (da)->capacity * 2;        \
            (da)->items =                                                      \
                realloc((da)->items, (da)->capacity * sizeof(*(da)->items));   \
            assert((da)->items != NULL && "Buy more RAM lol");                 \
        }                                                                      \
        memmove(&(da)->items[1], &(da)->items[0],                              \
                (da)->count * sizeof(*(da)->items));                           \
        (da)->items[0] = (item);                                               \
        (da)->count++;                                                         \
    } while (0)

#define da_popback(da)                                                         \
    do {                                                                       \
        if ((*da).count > 0)                                                   \
            (*da).count--;                                                     \
    } while (0)

void init_rand_snake(Snake *s, size_t init_size, size_t cellCount);
void update_snake(Snake *s);
void draw_snake(Snake *s, size_t cellBlock);
void destroy_snake(Snake *s);
void control_snake(Snake *s);

Vector2 direction(Direction d);

#endif // !SNAKE_H
