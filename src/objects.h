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
        void UpdateBall();
        void Reset();
        // void DrawOver();
};

class Paddle {
    public:
        float x_pos, y_pos;
        float width, height;
        int speed;

        void DrawPaddle();
        void UpdatePaddle();

    protected:
        void StayInBounds();
};

class Cpu: public Paddle {
    public: 
        void UpdateCPU(int ball_y_pos);
};


#endif