#ifndef OBJECTS_H
#define OBJECTS_H

#include "raylib.h"
#include <iostream>

extern int P1Score;
extern int P2Score;

class Ball {
    public:
        float x_pos, y_pos;
        int radius;
        int vel_x, vel_y;
        int ResetVel;

        void DrawBall();
        void UpdateBall(Sound Score);
        void Reset();
        // void DrawOver();
};

class Paddle {
    public:
        float x_pos, y_pos;
        float width, height;
        int speed;

        void DrawPaddle();
        void DrawHitbox();
        void UpdatePaddle();
        void UpdateHitbox();

    protected:
        void StayInBounds();
};

class Cpu: public Paddle {
    private:
        int diff;
    public:
        void UpdatePlayer2();
        void UpdateCPUEasy(int ball_y_pos, int ball_x_pos);
        void UpdateCPUNormal(int ball_y_pos, int ball_x_pos);
        void UpdateCPUHard(int ball_y_pos);
        void SetDiff(int diff);
};


#endif