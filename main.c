#include <math.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GREEN_BACKGROUND                                                       \
    CLITERAL(Color) { 173, 204, 95, 255 }

typedef enum FoodType {
    Fry     = -5,
    Apple   = -2,
    Egg     = 1,
    Mice    = 5,
    Rodent  = 10,
    Chicken = 20,
    Rabbit  = 25,
    Pig     = 30,
    NotFood
} FoodType;

const char *foodpaths[] = {
    "assets/sprites/fries25x25.png",  "assets/sprites/apple25x25.png",
    "assets/sprites/egg25x25.png",    "assets/sprites/mice25x25.png",
    "assets/sprites/rodent25x25.png", "assets/sprites/chicken25x25.png",
    "assets/sprites/rabbit25x25.png", "assets/sprites/pig25x25.png",
};

const int FOODVALS[]  = {-5, -2, 1, 5, 10, 20, 25, 30};
const int foodvalsize = 8;

typedef struct Food {
    Vector2   pos;
    FoodType  ft;
    Texture2D tex;
} Food;

Food make_food(Vector2 pos, FoodType ft);
Food rand_food();
void draw_food(Food *f);
void destroy_food(Food *f);

void rand_foods(Food *fs, int count);
void draw_foods(Food *fs, int count);
void destroy_foods(Food *fs, int count);

bool        isfoodtype(int val);
const int   foodtype2index(FoodType ft);
const char *foodtype2char(FoodType ft);
const char *foodtype2path(FoodType ft);

void gen_food_texture(Food *f);

Texture2D ftindex2texture(int index);

const int cellBlock = 25;
const int cellCount = 25;

int main(void) {
    srand(time(NULL));
    const int   windowWall = cellBlock * cellCount;
    const char *windowName = "Snake";

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(windowWall, windowWall, windowName);
    SetTargetFPS(60);

    Food fs[foodvalsize];
    rand_foods(fs, foodvalsize);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GREEN_BACKGROUND);

        draw_foods(fs, foodvalsize);

        EndDrawing();
    }

    destroy_foods(fs, foodvalsize);
    CloseWindow();
    return 0;
}

///////// Public Functions
Food rand_food() {
    int x    = rand() % 25;
    int y    = rand() % 25;
    int ft_n = rand() % foodvalsize;

    Vector2  p  = {x, y};
    FoodType ft = FOODVALS[ft_n];
    return (Food) {p, ft, ftindex2texture(ft_n)};
}

Food make_food(Vector2 pos, FoodType ft) {
    return (Food) {pos, ft, ftindex2texture(foodtype2index(ft))};
}

void draw_food(Food *f) {
    DrawTexture(f->tex, f->pos.x * cellBlock, f->pos.y * cellBlock, WHITE);
}

void destroy_food(Food *f) { UnloadTexture(f->tex); }

void _rand_food(Food *f) {
    int x    = rand() % cellBlock;
    int y    = rand() % cellBlock;
    int ft_n = rand() % foodvalsize;
    f->pos   = (Vector2) {x, y};
    f->ft    = FOODVALS[ft_n];
    f->tex   = ftindex2texture(ft_n);
}

void rand_foods(Food *fs, int count) {
    for (int i = 0; i < count; i++) {
        _rand_food(&fs[i]);
    }
}

void draw_foods(Food *fs, int count) {
    for (int i = 0; i < count; i++) {
        draw_food(&fs[i]);
    }
}

void destroy_foods(Food *fs, int count) {
    for (int i = count - 1; i >= 0; --i) {
        destroy_food(&fs[i]);
    }
}

void gen_food_texture(Food *f) {
    int   index = foodtype2index(f->ft);
    Image i     = LoadImage(foodpaths[index]);
    f->tex      = LoadTextureFromImage(i);
    UnloadImage(i);
}

///////// Helper Functions
Texture2D ftindex2texture(int index) {
    Image     i   = LoadImage(foodpaths[index]);
    Texture2D tex = LoadTextureFromImage(i);
    UnloadImage(i);
    return tex;
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
        case NotFood:
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
        case NotFood:
            break;
    }
    return "";
}

const int foodtype2index(FoodType ft) {
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
        case NotFood:
            break;
    }
    return -1;
}

const char *foodtype2path(FoodType ft) { return foodpaths[foodtype2index(ft)]; }
