#include "objects.h"

int P1Score = 0;
int P2Score = 0;

// Ball class
void Ball::DrawBall() {
    DrawCircle(x_pos, y_pos, radius, WHITE);
}

void Ball::UpdateBall() {
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

void Ball::Reset(){
    x_pos = GetScreenWidth()/2;
    y_pos = GetScreenHeight()/2;

    vel_x = ResetVel;
    vel_y = ResetVel;
    int direction_choice[2] = {-1, 1};
    vel_x *= direction_choice[GetRandomValue(0,1)];
    vel_y *= direction_choice[GetRandomValue(0,1)];
}

// void Ball::DrawOver(){
//     DrawCircle(x_pos, y_pos, radius, BLACK);
// }


// Paddle class
void Paddle::DrawPaddle() {
        DrawRectangle(x_pos, y_pos, width, height, WHITE);
}

void Paddle::UpdatePaddle() {
    if (IsKeyDown(KEY_A)) {
        y_pos -= speed;
    }
    if (IsKeyDown(KEY_D)) {
        y_pos += speed;
    }
    StayInBounds();
}

void Paddle::StayInBounds() {
    if (y_pos + height >= GetScreenHeight()) 
    {
        y_pos = GetScreenHeight() - height;
    }
    if (y_pos <= 0) 
    {
        y_pos = 0;
    }
}


// Cpu class
void Cpu::UpdateCPU(int ball_y_pos) {
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
