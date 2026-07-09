#define RAYGUI_IMPLEMENTATION

#include "objects.h"

Ball ball;
Paddle Player1;
Cpu CPU;

int PointsToWin = 1;

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

    Player1.x_pos = 70;
    Player1.y_pos = GetScreenHeight()/2 - 60;
    Player1.width = 25;
    Player1.height = 120;
    Player1.speed = 12;

    CPU.x_pos = GetScreenWidth() - 95;
    CPU.y_pos = GetScreenHeight()/2 - 60;
    CPU.width = 25;
    CPU.height = 120;
    CPU.speed = 12;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        BeginDrawing();

        // Updating the objects
        ball.UpdateBall();
        Player1.UpdatePaddle();
        CPU.UpdateCPU(ball.y_pos);

        // Collision
        if(CheckCollisionCircleRec(Vector2{ball.x_pos, ball.y_pos}, ball.radius, Rectangle{Player1.x_pos, Player1.y_pos, Player1.width, Player1.height})) {
            ball.vel_x = (ball.vel_x + 1)*-1;
            if (ball.vel_y > 0) {
                ball.vel_y += 1;
            }
            else {
                ball.vel_y -= 1;
            }
        }

        if(CheckCollisionCircleRec(Vector2{ball.x_pos, ball.y_pos}, ball.radius, Rectangle{CPU.x_pos, CPU.y_pos, CPU.width, CPU.height})) {
            ball.vel_x = (ball.vel_x + 1)*-1;
            if (ball.vel_y > 0) {
                ball.vel_y += 1;
            }
            else {
                ball.vel_y -= 1;
            }
        }

        // Pretending we have actual movement
        ClearBackground(BLACK);

        // win condition
        if (P1Score >= PointsToWin) 
        {
            ball.vel_x = 0;
            ball.vel_y = 0;
            Player1.speed = 0;
            CPU.speed = 0;
            DrawText("P1 WINS", screenWidth/2 - 150*2, screenHeight/2 - 60, 150, WHITE);
        }

        if (P2Score >= PointsToWin) 
        {   
            ball.vel_x = 0;
            ball.vel_y = 0;
            Player1.speed = 0;
            CPU.speed = 0;
            DrawText("P2 WINS", screenWidth/2 - 150*2, screenHeight/2 - 60, 150, WHITE);
        }

        // Drawing shapes
        ball.DrawBall();
        Player1.DrawPaddle();
        CPU.DrawPaddle();
        DrawLine(screenWidth/2, 0, screenWidth/2, screenHeight, WHITE);
        DrawText(TextFormat("%i", P2Score), screenWidth/4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", P1Score), 3*screenWidth/4 - 20, 20, 80, WHITE);

        EndDrawing();

    }

    // De-Initialization
    CloseWindow();

    return 0;
}