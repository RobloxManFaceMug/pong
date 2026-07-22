#include "objects.h"
#include "menu.h"
#include <time.h>

Ball ball;
Paddle Player1;
Cpu CPU;

// Modifiable variables
int PointsToWin = 3;
int StartingVelocity = 5;
int Difficulty = 2;     // 0 - 2P, 1 - easy, 2 - normal, 3 - hard
int GameIsOver = 0;
int LongTimeCheckerFirstTimePlayer = 1;
int VariableThatIsUsedWhenYouTakeTooLong = 0;
float MasterVolume = 0.4f;

int MainMenu() {

    Vector2 MousePos;

    InitAudioDevice();
    SetMasterVolume(MasterVolume);

    Sound snd_select = LoadSound("resources/SFX/snd_select.wav");
    // Sound snd_get_ready = LoadSound("resources/SFX/snd_get_ready.mp3");
    // Sound snd_game_start = LoadSound("resources/SFX/snd_game_start.wav");

    Music music = LoadMusicStream("resources/music/stealth.mp3");

    PlayMusicStream(music);

    SetMusicVolume(music, 1.0f);      // Default audio volume [0.0f..1.0f]


    while (!IsKeyDown(KEY_ENTER)) {
        BeginDrawing();
        
        UpdateMusicStream(music);
        
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
        DrawText("DUEL", 260, 518, 40, BLACK);
        DrawRectangle(430, 500, 200, 75, WHITE);
        DrawText("EASY", 475, 518, 40, BLACK);
        DrawRectangle(650, 500, 200, 75, WHITE);
        DrawText("NORMAL", 670, 518, 40, BLACK);
        DrawRectangle(870, 500, 200, 75, WHITE);
        DrawText("HARD", 915, 518, 40, BLACK);
        
        // check for clicks
        MousePos = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            // Points to win
            if (CheckCollisionPointRec(MousePos, {210, 350, 200, 75})) {
                PlaySound(snd_select);
                if (PointsToWin >= 9) {
                    PointsToWin = 1;
                }
                else {
                    PointsToWin++;
                }
            }

            // Starting velocity
            else if (CheckCollisionPointRec(MousePos, {870, 350, 200, 75})) {
                PlaySound(snd_select);
                if (StartingVelocity >= 20) {
                    StartingVelocity = 3;
                }
                else {
                    StartingVelocity++;
                }
            }

            // 2 player mode
            else if (CheckCollisionPointRec(MousePos, {210, 500, 200, 75})) {
                Difficulty = 0;
                PlaySound(snd_select);
            }

            // easy mode
            else if (CheckCollisionPointRec(MousePos, {430, 500, 200, 75})) {
                Difficulty = 1;
                PlaySound(snd_select);
            }

            // normal mode
            else if (CheckCollisionPointRec(MousePos, {650, 500, 200, 75})) {
                Difficulty = 2;
                PlaySound(snd_select);
            }

            // hard mode
            else if (CheckCollisionPointRec(MousePos, {870, 500, 200, 75})) {
                Difficulty = 3;
                PlaySound(snd_select);
            }
        }

        EndDrawing();
    }
    UnloadMusicStream(music);
    UnloadSound(snd_select);
    CloseAudioDevice();

    // WaitTime(0.25);

    // BeginDrawing();
    // ClearBackground(BLACK);
    // DrawText("3", GetScreenWidth()/2, GetScreenHeight()/2, 50, WHITE);
    // WaitTime(1);
    // DrawText("2", GetScreenWidth()/2, GetScreenHeight()/2, 50, WHITE);
    // WaitTime(1);
    // DrawText("1", GetScreenWidth()/2, GetScreenHeight()/2, 50, WHITE);
    // WaitTime(1);
    // DrawText("GO", GetScreenWidth()/2, GetScreenHeight()/2, 50, WHITE);
    // WaitTime(1);
    // EndDrawing();

    return 0;
}

void StartTimer() {

    InitAudioDevice();
    Sound snd_get_ready = LoadSound("resources/SFX/snd_get_ready.mp3");
    Sound snd_game_start = LoadSound("resources/SFX/snd_game_start.wav");
    int FrameCounter = 0;       // Amount of frames passed
    bool PlayedAlready = 0;
    const char *CurrentText = "3";      // Current displayed text
    int FontSize = 800;
    float WidthDivider = 4.0;
    int WaitFrames = 45;        // Amount of frames before next number

    PlaySound(snd_get_ready);
    while(FrameCounter <= WaitFrames*4) {
        BeginDrawing();
        ClearBackground(BLACK);

        // Displaying the text
        DrawText(CurrentText, GetScreenWidth()/2 - FontSize/WidthDivider, GetScreenHeight()/2 - FontSize/2.25, FontSize, WHITE);

        // Change text based on frames passed
        if ((FrameCounter >= WaitFrames) && (FrameCounter < WaitFrames*2)) {
            CurrentText = "2";
        }
        else if ((FrameCounter >= WaitFrames*2) && (FrameCounter < WaitFrames*3)) {
            CurrentText = "1";
        }
        else if (FrameCounter >= WaitFrames*3) {
           CurrentText = "GO";
           WidthDivider = 1.55;
            if (!PlayedAlready) {
                PlaySound(snd_game_start);
                PlayedAlready = 1;
            }
        }
        EndDrawing();
        FrameCounter++;
    }
    UnloadSound(snd_get_ready);
    UnloadSound(snd_game_start);
    CloseAudioDevice();
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

    // Timer before game start
    StartTimer();

    // Initialize music
    InitAudioDevice();
    SetMasterVolume(MasterVolume);
    Sound snd_paddle_bump = LoadSound("resources/SFX/snd_paddle_bump.wav");
    Sound snd_score = LoadSound("resources/SFX/snd_score.wav");
    Sound snd_victory = LoadSound("resources/SFX/snd_victory.mp3");
    Sound snd_defeat = LoadSound("resources/SFX/snd_defeat.mp3");
    Sound snd_win_duel = LoadSound("resources/SFX/snd_win_duel.mp3");
    Sound snd_yourtakingtoolong = LoadSound("resources/SFX/snd_yourtakingtoolong.mp3");
    Sound snd_too_fast = LoadSound("resources/SFX/snd_too_fast.mp3");
    Music music;
    
    if (Difficulty = 0) {
        music = LoadMusicStream("resources/music/Violet Tactics.mp3");
    }
    else {
        music = LoadMusicStream("resources/music/Catswing.mp3");
    }

    PlayMusicStream(music);

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
        ball.UpdateBall(snd_score);
        Player1.UpdatePaddle();
    
        UpdateMusicStream(music);

        // Update CPU based on difficulty
        switch (Difficulty) {
            case 0:
                CPU.UpdatePlayer2();
                break;
            case 1:
                CPU.UpdateCPUEasy(ball.y_pos, ball.x_pos);
                break;
            case 2:
                CPU.UpdateCPUNormal(ball.y_pos, ball.x_pos);
                break;
            case 3:
                CPU.UpdateCPUHard(ball.y_pos);
                break;
        }

        // Collision
        if(CheckCollisionCircleRec(Vector2{ball.x_pos, ball.y_pos}, ball.radius, Rectangle{(Player1.x_pos + Player1.width - 1), Player1.y_pos, 1, Player1.height})) {
            ball.vel_x = (ball.vel_x + 1)*-1;
            if (ball.vel_y > 0) {
                ball.vel_y += 1;
            }
            else {
                ball.vel_y -= 1;
            }
            if (((abs(ball.vel_y) == 10 && StartingVelocity < 8) || (abs(ball.vel_y) == 15 && StartingVelocity < 13 && StartingVelocity >= 8))) {
                PlaySound(snd_too_fast);
            }
            PlaySound(snd_paddle_bump);
        }

        if(CheckCollisionCircleRec(Vector2{ball.x_pos, ball.y_pos}, ball.radius, Rectangle{CPU.x_pos, CPU.y_pos, 1, CPU.height})) {
            ball.vel_x = (ball.vel_x + 1)*-1;
            if (ball.vel_y > 0) {
                ball.vel_y += 1;
            }
            else {
                ball.vel_y -= 1;
            }
            if (((abs(ball.vel_y) == 10 && StartingVelocity < 8) || (abs(ball.vel_y) == 15 && StartingVelocity < 13 && StartingVelocity >= 8))) {
                PlaySound(snd_too_fast);
            }
            PlaySound(snd_paddle_bump);
        }

        // Pretending we have actual movement
        ClearBackground(BLACK);

        // win condition
        if (P1Score >= PointsToWin) 
        {   
            GameIsOver = 1;
            ball.vel_x = 0;
            ball.vel_y = 0;
            Player1.speed = 0;
            CPU.speed = 0;
            DrawText("P1 WINS", screenWidth/2 - 150*2, screenHeight/2 - 60, 150, WHITE);
            if (LongTimeCheckerFirstTimePlayer) {
                // game over SFX based on difficulty
                switch (Difficulty) {
                    case 0:
                        PauseMusicStream(music);
                        PlaySound(snd_win_duel);
                        LongTimeCheckerFirstTimePlayer = 0;
                        break;
                    default:
                        PauseMusicStream(music);
                        PlaySound(snd_victory);
                        LongTimeCheckerFirstTimePlayer = 0;
                }
            }
            // else if (GameIsOver && !LongTimeCheckerFirstTimePlayer) {
            //     VariableThatIsUsedWhenYouTakeTooLong++;
            //     if (VariableThatIsUsedWhenYouTakeTooLong > 600){
            //         PlaySound(snd_yourtakingtoolong);
            //     }
            // }
        }

        if (P2Score >= PointsToWin) 
        {   
            GameIsOver = 1;
            ball.vel_x = 0;
            ball.vel_y = 0;
            Player1.speed = 0;
            CPU.speed = 0;
            DrawText("P2 WINS", screenWidth/2 - 150*2, screenHeight/2 - 60, 150, WHITE);
            if (LongTimeCheckerFirstTimePlayer) {
                // game over SFX based on difficulty
                if (Difficulty = 0) {
                    PauseMusicStream(music);
                    PlaySound(snd_win_duel);
                    LongTimeCheckerFirstTimePlayer = 0;
                    }
                else {
                    PauseMusicStream(music);
                    PlaySound(snd_defeat);
                    LongTimeCheckerFirstTimePlayer = 0;
                    }
            }
        }

        // Drawing shapes
        if (!GameIsOver) {
            ball.DrawBall();
        }
        Player1.DrawPaddle();
        // Player1.DrawHitbox();
        CPU.DrawPaddle();
        DrawLine(screenWidth/2, 0, screenWidth/2, screenHeight, WHITE);
        DrawText(TextFormat("%i", P1Score), screenWidth/4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", P2Score), 3*screenWidth/4 - 20, 20, 80, WHITE);

        EndDrawing();

    }

    // De-Initialization
    UnloadSound(snd_defeat);
    UnloadSound(snd_paddle_bump);
    UnloadSound(snd_score);
    UnloadSound(snd_victory);
    UnloadSound(snd_yourtakingtoolong);
    UnloadSound(snd_too_fast);
    UnloadSound(snd_win_duel);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}