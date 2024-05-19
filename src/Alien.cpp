#include "Alien.h"

Texture2D Alien::image[3] = {};
int Alien::imageId[3] = {0,0,0};

Alien::Alien(int t, Vector2 pos)
{
    type = t;
    position = pos;

    if(imageId[type - 1] == 0)
    {
        if(type == 1)
            image[type - 1] = LoadTexture("graphics/alien_1.png");
        else if(type == 2)
            image[type - 1] = LoadTexture("graphics/alien_2.png");
        else 
            image[type - 1] = LoadTexture("graphics/alien_3.png");
        imageId[type - 1] = 1;
    }
    
}

int Alien::getType()
{
    return type;
}

void Alien::update(int direction)
{
    position.x += direction;
}

void Alien::draw()
{
    DrawTextureV(image[type - 1], position, WHITE);
}

Rectangle Alien::getRect()
{
    return {position.x, position.y, float(image[type - 1].width), float(image[type - 1].height)};
}

void Alien::UnloadImage()
{
    for(int i = 0; i < 2; i++)
        UnloadTexture(image[i]);
}
