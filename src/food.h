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
    bool      eaten;
    double    lifetime; // in seconds
} Food;

Food make_food(Vector2 pos, FoodType ft);
Food rand_food();
void draw_food(Food *f, size_t cellBlock);
void destroy_food(Food *f);
void update_food(Food *f, double duration);

FoodType rand_ft();

void rand_foods(Food *fs, int count, size_t cellCount,
                Texture2D *food_textures);
void draw_foods(Food *fs, int count, size_t cellBlock);
void destroy_foods(Food *fs, int count);
void update_foods(Food *fs, int count, double duration, size_t cellBlock,
                  size_t cellCount, Texture2D *food_textures);

bool        isfoodtype(int val);
const char *foodtype2char(FoodType ft);
const char *foodtype2path(FoodType ft);
const int   ft2index(FoodType ft);

Texture2D get_food_texture(FoodType ft, Texture2D *food_textures);

Texture2D gen_food_texture(FoodType ft);
void      gen_food_textures(Texture2D *food_textures);
double    gen_food_lifetime(FoodType ft);

void destroy_textures(Texture2D *food_textures);

#endif // !FOOD_H
