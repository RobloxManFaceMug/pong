#include "raylib.h"

int MainMenu(int PointsToWin, int StartingVelocity) {

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
    int rtrn[2] = {PointsToWin, StartingVelocity};
    return 1;
}