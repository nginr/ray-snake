#include "food.h"

#include <raylib.h>
#include <stddef.h>
#include <stdlib.h>

///////// Public Functions
Food rand_food() {
    int  x     = rand() % 25;
    int  y     = rand() % 25;
    Food f     = {0};
    f.pos      = (Vector2) {x, y};
    f.ft       = rand_ft();
    f.tex      = gen_food_texture(f.ft);
    f.eaten    = false;
    f.lifetime = gen_food_lifetime(f.ft);
    return f;
}

Food make_food(Vector2 pos, FoodType ft) {
    Food f     = {0};
    f.pos      = pos;
    f.ft       = ft;
    f.tex      = gen_food_texture(f.ft);
    f.eaten    = false;
    f.lifetime = gen_food_lifetime(f.ft);
    return f;
}

void draw_food(Food *f, size_t cellBlock) {
    if ((f->eaten == false) || (f->lifetime > 0.0)) {
        DrawTexture(f->tex, f->pos.x * cellBlock, f->pos.y * cellBlock, WHITE);
    }
}

void destroy_food(Food *f) {
    f->pos   = (Vector2) {0, 0};
    f->ft    = NOT_FOOD;
    f->eaten = false;
}

void _rand_food(Food *f, size_t cellCount, Texture2D *food_textures) {
    int x       = rand() % cellCount;
    int y       = rand() % cellCount;
    f->pos      = (Vector2) {x, y};
    f->ft       = rand_ft();
    f->tex      = get_food_texture(f->ft, food_textures);
    f->eaten    = false;
    f->lifetime = gen_food_lifetime(f->ft);
}

void rand_foods(Food *fs, int count, size_t cellCount,
                Texture2D *food_textures) {
    for (int i = 0; i < count; i++) {
        _rand_food(&fs[i], cellCount, food_textures);
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

void update_food(Food *f, double duration) { f->lifetime -= duration; }

void update_foods(Food *fs, int count, double duration, size_t cellBlock,
                  size_t cellCount, Texture2D *food_textures) {
    for (int i = 0; i < count; i++) {
        if ((fs[i].eaten == true) || (fs[i].lifetime < 0.0)) {
            _rand_food(&fs[i], cellCount, food_textures);
        } else {
            update_food(&fs[i], duration);
        }
    }
}

Texture2D get_food_texture(FoodType ft, Texture2D *food_textures) {
    return food_textures[ft2index(ft)];
}

Texture2D gen_food_texture(FoodType ft) {
    Image     i   = LoadImage(foodtype2path(ft));
    Texture2D tex = LoadTextureFromImage(i);
    UnloadImage(i);
    return tex;
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

double gen_food_lifetime(FoodType ft) {
    switch (ft) {
        case Fry:
            return 4.0;
        case Apple:
            return 6.0;
        case Egg:
            return 7.0;
        case Mice:
            return 3.5;
        case Rodent:
            return 4.0;
        case Chicken:
            return 4.5;
        case Rabbit:
            return 5.5;
        case Pig:
            return 12.0;
        case Count_FoodType:
        case NOT_FOOD:
            return 0.0;
    }
    return 0.0;
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

const int ft2index(FoodType ft) {
    switch (ft) {
        case Fry:
            return 0;
        case Apple:
            return 1;
        case Egg:
            return 2;
        case Mice:
            return 3;
        case Rodent:
            return 4;
        case Chicken:
            return 5;
        case Rabbit:
            return 6;
        case Pig:
            return 7;
        case Count_FoodType:
        case NOT_FOOD:
            break;
    }
    return -1;
}

FoodType index2ft(int value) {
    switch (value) {
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
        default:
            return NOT_FOOD;
    }
}

void gen_food_textures(Texture2D *food_textures) {
    for (int i = 0; i < Count_FoodType; i++) {
        FoodType ft      = index2ft(i);
        food_textures[i] = gen_food_texture(ft);
    }
}

void destroy_textures(Texture2D *food_textures) {
    for (int i = 0; i < Count_FoodType; i++) {
        UnloadTexture(food_textures[i]);
    }
}
