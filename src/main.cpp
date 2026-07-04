#include "raylib.h"
#include <iostream>

class Ball {
    public:
        float x_pos, y_pos;
        int radius;
        int vel_x, vel_y;

    void DrawBall() {
        DrawCircle(x_pos, y_pos, radius, WHITE);
    }

    void UpdateBall() {
        x_pos += vel_x;
        y_pos += vel_y;
    }
};

Ball ball;

int main(void)
{
    // Initialization
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Pong but Awesome");

    SetTargetFPS(60);

    ball.x_pos = screenWidth/2;
    ball.y_pos = screenHeight/2;
    ball.radius = 20;
    ball.vel_x = 5;
    ball.vel_y = 5;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        
        // Drawing The Shapes
        ball.UpdateBall();
        ClearBackground(BLACK);
        ball.DrawBall();
        DrawRectangle(70, screenHeight/2 - 60, 25, 120, WHITE);
        DrawRectangle(screenWidth - 95, screenHeight/2 - 60, 25, 120, WHITE);
        DrawLine(screenWidth/2, 0, screenWidth/2, screenHeight, WHITE);
        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}