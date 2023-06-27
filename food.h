#ifndef FOOD_H
#define FOOD_H

#include <raylib.h>
#include <stddef.h>

typedef enum FoodType {
    Fry            = -5,
    Apple          = -2,
    Egg            = 1,
    Mice           = 5,
    Rodent         = 10,
    Chicken        = 20,
    Rabbit         = 25,
    Pig            = 30,
    Count_FoodType = 8,
    NOT_FOOD
} FoodType;

typedef struct Food {
    Vector2   pos;
    FoodType  ft;
    Texture2D tex;
} Food;

Food     make_food(Vector2 pos, FoodType ft);
Food     rand_food();
void     draw_food(Food *f, size_t cellBlock);
void     destroy_food(Food *f);
FoodType rand_ft();

void rand_foods(Food *fs, int count, size_t cellBlock);
void draw_foods(Food *fs, int count, size_t cellBlock);
void destroy_foods(Food *fs, int count);

bool        isfoodtype(int val);
const char *foodtype2char(FoodType ft);
const char *foodtype2path(FoodType ft);

void gen_food_texture(Food *f);

#endif // !FOOD_H
