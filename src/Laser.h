#ifndef LASER_H
#define LASER_H
#include <raylib.h>

class Laser
{
    private:
        Vector2 position;
        int speed;
        Color color;
        

    public:
        bool active;

        Laser(Vector2 position, int speed);
        void update();
        void draw();
        Rectangle getRect();
};

#endif