#include "raylib.h"
#include <iostream>

int P1Score = 0;
int P2Score = 0;

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

        if (y_pos + radius >= GetScreenHeight() || y_pos - radius <= 0) {
            vel_y *= -1;
        }
        if (x_pos + radius >= GetScreenWidth()) {

            P1Score++;
            Reset();
        }
        
        if (x_pos - radius <= 0) {
            P2Score++;
            Reset();
        }
    }

    void Reset(){
        x_pos = GetScreenWidth()/2;
        y_pos = GetScreenHeight()/2;

        int direction_choice[2] = {-1, 1};
        vel_x *= direction_choice[GetRandomValue(0,1)];
        vel_y *= direction_choice[GetRandomValue(0,1)];
    }
};

class Paddle {
    public:
        float x_pos, y_pos;
        float width, height;
        int speed;

    void DrawPaddle() {
        DrawRectangle(x_pos, y_pos, width, height, WHITE);
    }

    void UpdatePaddle () {
        if (IsKeyDown(KEY_A)) {
            y_pos -= speed;
        }
        if (IsKeyDown(KEY_D)) {
            y_pos += speed;
        }
        StayInBounds();
    }

    protected: void StayInBounds() {

        if (y_pos + height >= GetScreenHeight()) 
        {
            y_pos = GetScreenHeight() - height;
        }

        if (y_pos <= 0) 
        {
            y_pos = 0;
        }
    }
};

class Cpu: public Paddle {
    public: void UpdateCPU(int ball_y_pos) {
        if (y_pos + height/2 > ball_y_pos)
        {
            y_pos -= speed;
        }
        if (y_pos + height/2 < ball_y_pos)
        {
            y_pos += speed;
        }
        StayInBounds();
    }
};

Ball ball;
Paddle Player1;
Cpu CPU;

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
            ball.vel_x *= -1;
        }

        if(CheckCollisionCircleRec(Vector2{ball.x_pos, ball.y_pos}, ball.radius, Rectangle{CPU.x_pos, CPU.y_pos, CPU.width, CPU.height})) {
            ball.vel_x *= -1;
        }

        // Pretending we have actual movement
        ClearBackground(BLACK);

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