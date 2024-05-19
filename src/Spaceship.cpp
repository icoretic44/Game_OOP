#include "Spaceship.h"

Spaceship::Spaceship()
{
    image = LoadTexture("graphics/spaceship.png");
    position.x = (GetScreenWidth() - image.width)/2;
    position.y = (GetScreenHeight() - image.height - 100);
    lastFireTime = 0.0;
    laserSound = LoadSound("sounds/laser.mp3");
}

Spaceship::~Spaceship()
{
    UnloadTexture(image);
    UnloadSound(laserSound);
}

void Spaceship::draw()
{
    DrawTextureV(image, position, WHITE);
}

void Spaceship::moveLeft()
{
    position.x -= 7;
    if(position.x < 10)
        position.x = 10;
}

void Spaceship::moveRight()
{
    position.x += 7;
    if(position.x > GetScreenWidth() - image.width - 10)
        position.x = GetScreenWidth() - image.width - 10;
}

void Spaceship::fireLaser()
{
    // cooldown
    if(GetTime() - lastFireTime >= 0.25)
    {
        lasers.push_back(Laser({position.x + image.width/2 - 2,position.y}, -7));
        lastFireTime = GetTime();
        PlaySound(laserSound);
    }
}

Rectangle Spaceship::getRect()
{
    return {position.x, position.y, float(image.width), float(image.height)};
}

void Spaceship::reset()
{
    position.x = (GetScreenWidth() - image.width)/2;
    position.y = (GetScreenHeight() - image.height - 100);
    lasers.clear();
}
