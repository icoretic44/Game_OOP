#include "Laser.h"

Laser::Laser(Vector2 newPosition, int newSpeed)
{
    position = newPosition;
    speed = newSpeed;
    color = {243, 216, 63, 255};
    active = true;
}

void Laser::draw()
{
    if(active)
        DrawRectangle(position.x, position.y, 4, 15, color);
}

Rectangle Laser::getRect()
{
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 4;
    rect.height = 15;
    return rect;
}

void Laser::update()
{
    position.y += speed;
    if(active)
    {
        if(position.y > GetScreenHeight() - 70 || position.y < 10)
            active = false;
    }
}