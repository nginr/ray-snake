#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "food.h"
#include "snake.h"

#define GREEN_BACKGROUND                                                       \
    CLITERAL(Color) { 173, 204, 95, 255 }

double    lastTime    = 0.0;
int       total_score = 0;
const int cellBlock   = 25;
const int cellCount   = 25;

bool check_snake_food_collision(Snake *sh, Food *fs, size_t count);
void draw_score(char *buffer, size_t buffer_size, Snake *s);

bool event_triggered(double duration);
void center_window(size_t win_w, size_t win_h);
void exit_menu(size_t windowWall);

int main(void) {
    srand(getpid() + time(NULL));
    const int   windowWall = cellBlock * cellCount;
    const char *windowName = "Snake";

    InitWindow(windowWall, windowWall, windowName);
    SetTargetFPS(60);
    center_window(windowWall, windowWall);

    Snake s = {0};
    Texture2D food_textures[Count_FoodType] = {0};
    Food  fs[Count_FoodType];

    init_rand_snake(&s, 3, cellCount);
    gen_food_textures(food_textures);
    rand_foods(fs, Count_FoodType, cellBlock, food_textures);

    char   buffer[256];
    double duration = 0.3;

    while (!WindowShouldClose()) {
        control_snake(&s);

        if (event_triggered(duration)) {
            if (check_snake_food_collision(&s, fs, Count_FoodType)) {
                total_score += s.previous_meal;
            }
            update_snake(&s);
            update_foods(fs, Count_FoodType, duration, cellBlock, cellCount, food_textures);
        }

        BeginDrawing();
        ClearBackground(GREEN_BACKGROUND);

        draw_foods(fs, Count_FoodType, cellBlock);
        draw_snake(&s, cellBlock);

        draw_score(buffer, 256, &s);

        EndDrawing();
    }

    destroy_snake(&s);
    destroy_foods(fs, Count_FoodType);
    destroy_textures(food_textures);
    CloseWindow();
    return 0;
}

void draw_score(char *buffer, size_t buffer_size, Snake *s) {
    snprintf(buffer, buffer_size, "Head: {%d, %d}", (int)s->body.items[0].x,
             (int)s->body.items[0].y);
    DrawText(buffer, 2 * cellBlock, 2 * cellBlock, 20, WHITE);

    snprintf(buffer, buffer_size, "%d", total_score);
    DrawText(buffer, 12 * cellBlock, 2 * cellBlock, 20, WHITE);

    snprintf(buffer, buffer_size, "%d", s->previous_meal);
    DrawText(buffer, 20 * cellBlock, 2 * cellBlock, 20, WHITE);
}

bool check_snake_food_collision(Snake *sh, Food *fs, size_t count) {
    Vector2 c = sh->body.items[0];
    Vector2 d = {0};
    for (size_t i = 0; i < count; i++) {
        if ((!fs[i].eaten) || (fs[i].lifetime >= 0.0)) {
            d = fs[i].pos;
            if (Vector2Equals(c, d)) {
                sh->ate           = true;
                fs[i].eaten       = true;
                sh->previous_meal = (int)fs[i].ft;
                return true;
            }
        }
    }
    return false;
}

bool event_triggered(double duration) {
    double curr_time = GetTime();
    if (curr_time - lastTime >= duration) {
        lastTime = curr_time;
        return true;
    }
    return false;
}

void center_window(size_t win_w, size_t win_h) {
    int monitor = GetCurrentMonitor();

    int m_w = GetMonitorWidth(monitor);
    int m_h = GetMonitorHeight(monitor);
    SetWindowPosition(m_w * 0.5 - win_w * 0.5, m_h * 0.5 - win_h * 0.5);
}

void exit_menu(size_t windowWall) {
    char exit_buffer[256] = "Are you sure you want to exit program? [Y/N]";
    DrawRectangle(0, windowWall * 0.5 - 2.5 * cellBlock, windowWall,
                  5 * cellBlock, BLACK);
    DrawText(exit_buffer, windowWall * 0.1, windowWall * 0.5, 20, WHITE);
}
