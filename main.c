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
    Eggs    = 1,
    Mice    = 5,
    Rodent  = 10,
    Chicken = 20,
    Rabbit  = 25,
    Pig     = 30,
    NotFood
} FoodType;

int       foodvals[]  = {-5, -2, 1, 5, 10, 20, 25, 30};
const int foodvalsize = sizeof(foodvals) / sizeof(foodvals[0]);

typedef struct Food {
    Vector2  pos;
    FoodType ft;
} Food;

Food rand_food();
Food make_food(Vector2 _pos, FoodType _ft);

void draw_food(Food _f);

bool  isfoodtype(int ft);
char *foodtype2char(FoodType ft);

const int cellBlock = 25;
const int cellCount = 25;

int main(void) {
    srand(time(NULL));
    const int   windowWall = cellBlock * cellCount;
    const char *windowName = "Snake";

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(windowWall, windowWall, windowName);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        Food f = rand_food();
        BeginDrawing();
        ClearBackground(GREEN_BACKGROUND);

        draw_food(f);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

///////// Public Functions
Food rand_food() {
    int      x    = rand() % 25;
    int      y    = rand() % 25;
    int      ft_n = rand() % foodvalsize;
    Vector2  p    = {x, y};
    FoodType ft   = foodvals[ft_n];
    return (Food) {p, ft};
}

Food make_food(Vector2 _pos, FoodType _ft) { return (Food) {_pos, _ft}; }

void draw_food(Food _f) {
    DrawRectangle(_f.pos.x * cellBlock, _f.pos.y * cellBlock, cellBlock,
                  cellBlock, BLACK);
}

///////// Helper Functions
bool isfoodtype(int ft) {
    switch (ft) {
        case Fry:
            return true;
        case Apple:
            return true;
        case Eggs:
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

char *foodtype2char(FoodType ft) {
    switch (ft) {
        case Fry:
            return "Fry";
        case Apple:
            return "Apple";
        case Eggs:
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
