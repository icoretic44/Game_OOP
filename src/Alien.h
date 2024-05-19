#ifndef ALIEN_H
#define ALIEN_H
#include <raylib.h>
#include "Laser.h"

class Alien
{
    public:
        static Texture2D image[3];
        static int imageId[3];
        int type;
        Vector2 position;
        
        Alien(int t, Vector2 pos);
        int getType();
        void update(int direction);
        void draw();
        Rectangle getRect();
        static void UnloadImage();
};

#endif