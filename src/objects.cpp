#include "objects.h"

int P1Score = 0;
int P2Score = 0;

// Ball class
void Ball::DrawBall() {
    DrawCircle(x_pos, y_pos, radius, WHITE);
}

void Ball::UpdateBall(Sound Score) {
    x_pos += vel_x;
    y_pos += vel_y;

    if (y_pos + radius >= GetScreenHeight() || y_pos - radius <= 0) {
        vel_y *= -1;
    }
    if (x_pos + radius >= GetScreenWidth()) {
        P1Score++;
        PlaySound(Score);
        Reset();
    }
        
    if (x_pos - radius <= 0) {
        P2Score++;
        PlaySound(Score);
        Reset();
    }
}

void Ball::Reset() {
    x_pos = GetScreenWidth()/2;
    y_pos = GetScreenHeight()/2;

    vel_x = ResetVel;
    vel_y = ResetVel;
    int direction_choice[2] = {-1, 1};
    vel_x *= direction_choice[GetRandomValue(0,1)];
    vel_y *= direction_choice[GetRandomValue(0,1)];
}

// Paddle class
void Paddle::DrawPaddle() {
    DrawRectangle(x_pos, y_pos, width, height, WHITE);
}

// void Paddle::DrawHitbox() {
//     DrawRectangle(x_pos + width - 1, y_pos, 1, height, RED);
// }

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

// Easy - tracks right half, entire paddle
// Medium - tracks 3/4 of the field, most of the paddle
// Hard - full tracking, only center
void Cpu::UpdatePlayer2() {
    if (IsKeyDown(KEY_LEFT)) {
        y_pos -= speed;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        y_pos += speed;
    }
    StayInBounds();
}
void Cpu::UpdateCPUEasy(int ball_y_pos, int ball_x_pos) {
    if (y_pos > ball_y_pos && ball_x_pos >= GetScreenWidth()/2)
    {
        y_pos -= speed;
    }
    if (y_pos + height < ball_y_pos && ball_x_pos >= GetScreenWidth()/2)
    {
        y_pos += speed;
    }
    StayInBounds();
}
void Cpu::UpdateCPUNormal(int ball_y_pos, int ball_x_pos) {
     if (y_pos + height/4 > ball_y_pos && ball_x_pos >= GetScreenWidth()/4)
    {
        y_pos -= speed;
    }
    if (y_pos + height/4*3 < ball_y_pos && ball_x_pos >= GetScreenWidth()/4)
    {
        y_pos += speed;
    }
    StayInBounds();
}
void Cpu::UpdateCPUHard(int ball_y_pos) {
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
