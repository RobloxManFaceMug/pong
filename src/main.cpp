#include "objects.h"

// TODO: add a variable that stores mouse position
// then when mouse is clicked check if it is in the
// box coordinates, only then change box's state

Ball ball;
Paddle Player1;
Cpu CPU;

// Modifiable variables
int PointsToWin = 3;
int StartingVelocity = 5;
int Difficulty = 0;     // 0 - 2P, 1 - easy, 2 - normal, 3 - hard

int MainMenu() {

    Vector2 MousePos;

    while (!IsKeyDown(KEY_ENTER)) {
        BeginDrawing();
    
        // Text
        DrawText("pong but awesome", 190, 100, 100, WHITE);
        DrawText("press ENTER to start", GetScreenWidth()/2-140, GetScreenHeight()-100, 25, WHITE);

        // Points to win box
        DrawText("Points to win", 210, 290, 40, WHITE);
        DrawRectangle(210, 350, 200, 75, WHITE);
        DrawText(TextFormat("%i", PointsToWin), 290, 352, 80, BLACK);

        // Starting velocity box
        DrawText("Starting velocity", 870, 290, 40,  WHITE);
        DrawRectangle(870, 350, 200, 75, WHITE);
        DrawText(TextFormat("%i", StartingVelocity), 960, 352, 80, BLACK);

        // Difficulty box
        DrawText("CPU difficulty", 500, 440, 40, WHITE);
        DrawRectangle(210, 500, 200, 75, WHITE);
        DrawRectangle(430, 500, 200, 75, WHITE);
        DrawRectangle(650, 500, 200, 75, WHITE);
        DrawRectangle(870, 500, 200, 75, WHITE);
        
        // check for clicks
        MousePos = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            
            // Points to win
            if (CheckCollisionPointRec(MousePos, {210, 350, 200, 75})) {
                if (PointsToWin >= 9) {
                    PointsToWin = 1;
                }
                else {
                    PointsToWin++;
                }
            }

            // Starting velocity
            else if (CheckCollisionPointRec(MousePos, {870, 350, 200, 75})) {
                if (StartingVelocity >= 20) {
                    StartingVelocity = 3;
                }
                else {
                    StartingVelocity++;
                }
            }
        }

        EndDrawing();
    }
    return 1;
}

int main(void)
{

    // Initialization
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Pong but Awesome");

    SetTargetFPS(60);

    // Main menu, duh
    MainMenu();

    // Objects initialization
    ball.x_pos = screenWidth/2;
    ball.y_pos = screenHeight/2;
    ball.radius = 20;
    ball.ResetVel = StartingVelocity;

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

    ball.Reset();

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
        DrawText(TextFormat("%i", P1Score), screenWidth/4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", P2Score), 3*screenWidth/4 - 20, 20, 80, WHITE);

        EndDrawing();

    }

    // De-Initialization
    CloseWindow();

    return 0;
}