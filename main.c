#include <math.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "food.h"

#define GREEN_BACKGROUND                                                       \
    CLITERAL(Color) { 173, 204, 95, 255 }

const int cellBlock = 25;
const int cellCount = 25;

int main(void) {
    srand(time(NULL));
    const int   windowWall = cellBlock * cellCount;
    const char *windowName = "Snake";

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(windowWall, windowWall, windowName);
    SetTargetFPS(60);

    Food fs[Count_FoodType];
    rand_foods(fs, Count_FoodType, cellBlock);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GREEN_BACKGROUND);

        draw_foods(fs, Count_FoodType, cellBlock);

        EndDrawing();
    }

    destroy_foods(fs, Count_FoodType);
    CloseWindow();
    return 0;
}
