#include <math.h>
#include <raylib.h>

#define GREEN_BACKGROUND CLITERAL(Color) { 173, 204, 95, 255 }

const int cellBlock = 25;
const int cellCount = 25;

int main(void) {
    const int windowWall = cellBlock*cellCount;
    const char *windowName = "Snake";

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(windowWall, windowWall, windowName);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GREEN_BACKGROUND);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
