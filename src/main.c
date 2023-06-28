#include <math.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "food.h"
#include "snake.h"

#define GREEN_BACKGROUND                                                       \
    CLITERAL(Color) { 173, 204, 95, 255 }

double    lastTime  = 0.0;
const int cellBlock = 25;
const int cellCount = 25;

bool event_triggered(double duration);

int main(void) {
    srand(getpid() + time(NULL));
    const int   windowWall = cellBlock * cellCount;
    const char *windowName = "Snake";

    InitWindow(windowWall, windowWall, windowName);
    SetTargetFPS(60);

    Snake s = {0};
    Food  fs[Count_FoodType];

    init_rand_snake(&s, 3, cellCount);
    rand_foods(fs, Count_FoodType, cellBlock);

    char buffer[256];

    while (!WindowShouldClose()) {
        control_snake(&s);

        if (event_triggered(0.5)) {
            update_snake(&s);
        }

        BeginDrawing();
        ClearBackground(GREEN_BACKGROUND);

        snprintf(buffer, 100, "Head: {%d, %d}", (int)s.body.items[0].x,
                 (int)s.body.items[0].y);
        DrawText(buffer, 2 * cellBlock, 2 * cellBlock, 20, WHITE);

        draw_snake(&s, cellBlock);
        draw_foods(fs, Count_FoodType, cellBlock);

        EndDrawing();
    }

    destroy_snake(&s);
    destroy_foods(fs, Count_FoodType);
    CloseWindow();
    return 0;
}

bool event_triggered(double duration) {
    double curr_time = GetTime();
    if (curr_time - lastTime >= duration) {
        lastTime = curr_time;
        return true;
    }
    return false;
}
