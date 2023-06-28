#include "food.h"

#include <raylib.h>
#include <stddef.h>
#include <stdlib.h>

///////// Public Functions
Food rand_food() {
    int  x = rand() % 25;
    int  y = rand() % 25;
    Food f = {0};
    f.pos  = (Vector2) {x, y};
    f.ft   = rand_ft();
    gen_food_texture(&f);
    return f;
}

Food make_food(Vector2 pos, FoodType ft) {
    Food f = {0};
    f.pos  = pos;
    f.ft   = ft;
    gen_food_texture(&f);
    return f;
}

void draw_food(Food *f, size_t cellBlock) {
    DrawTexture(f->tex, f->pos.x * cellBlock, f->pos.y * cellBlock, WHITE);
}

void destroy_food(Food *f) { UnloadTexture(f->tex); }

void _rand_food(Food *f, size_t cellBlock) {
    int x  = rand() % cellBlock;
    int y  = rand() % cellBlock;
    f->pos = (Vector2) {x, y};
    f->ft  = rand_ft();
    gen_food_texture(f);
}

void rand_foods(Food *fs, int count, size_t cellBlock) {
    for (int i = 0; i < count; i++) {
        _rand_food(&fs[i], cellBlock);
    }
}

void draw_foods(Food *fs, int count, size_t cellBlock) {
    for (int i = 0; i < count; i++) {
        draw_food(&fs[i], cellBlock);
    }
}

void destroy_foods(Food *fs, int count) {
    for (int i = count - 1; i >= 0; --i) {
        destroy_food(&fs[i]);
    }
}

void gen_food_texture(Food *f) {
    Image i = LoadImage(foodtype2path(f->ft));
    f->tex  = LoadTextureFromImage(i);
    UnloadImage(i);
}

///////// Helper Functions
FoodType rand_ft() {
    int randnum = rand() % Count_FoodType;
    switch (randnum) {
        case 0:
            return Fry;
        case 1:
            return Apple;
        case 2:
            return Egg;
        case 3:
            return Mice;
        case 4:
            return Rodent;
        case 5:
            return Chicken;
        case 6:
            return Rabbit;
        case 7:
            return Pig;
        case Count_FoodType:
            break;
    }
    return NOT_FOOD;
}

bool isfoodtype(int val) {
    switch (val) {
        case Fry:
            return true;
        case Apple:
            return true;
        case Egg:
            return true;
        case Mice:
            return true;
        case Rodent:
            return true;
        case Chicken:
            return true;
        case Rabbit:
            return true;
        case Pig:
            return true;
        case Count_FoodType:
            break;
    }
    return false;
}

const char *foodtype2char(FoodType ft) {
    switch (ft) {
        case Fry:
            return "Fry";
        case Apple:
            return "Apple";
        case Egg:
            return "Eggs";
        case Mice:
            return "Mice";
        case Rodent:
            return "Rodent";
        case Chicken:
            return "Chicken";
        case Rabbit:
            return "Rabbit";
        case Pig:
            return "Pig";
        case Count_FoodType:
            break;
        case NOT_FOOD:
            return "Not Food";
    }
    return "Unreachable";
}

const char *foodtype2path(FoodType ft) {
    switch (ft) {
        case Fry:
            return "assets/sprites/fries25x25.png";
        case Apple:
            return "assets/sprites/apple25x25.png";
        case Egg:
            return "assets/sprites/egg25x25.png";
        case Mice:
            return "assets/sprites/mice25x25.png";
        case Rodent:
            return "assets/sprites/rodent25x25.png";
        case Chicken:
            return "assets/sprites/chicken25x25.png";
        case Rabbit:
            return "assets/sprites/rabbit25x25.png";
        case Pig:
            return "assets/sprites/pig25x25.png";
        case Count_FoodType:
            break;
        case NOT_FOOD:
            return "Unreachable";
    }
    return "Unreachable";
}
