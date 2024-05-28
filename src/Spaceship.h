#ifndef SPACESHIP_H
#define SPACESHIP_H
#include <raylib.h>
#include "Laser.h"
#include <vector>

class Spaceship
{
    private:
        Vector2 position;
        double lastFireTime;
        
    public:
        std::vector<Laser> lasers;
        int lives;
        Texture2D image;
        Sound laserSound;
        float buffTime;
        bool isBuffed;
        int level;

        Spaceship();
        ~Spaceship();
        void draw();
        void moveLeft();
        void moveRight();
        void fireLaser();
        Rectangle getRect();
        void reset();
};

#endif