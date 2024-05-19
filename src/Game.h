#pragma once 
#include <vector>
#include "Spaceship.h"
#include "Alien.h"
class Game
{
    private:
        std::vector<Alien> aliens;
        std::vector<Laser> alienLaser;
        int alienDirection;
        int lastTimeAlienFire;
        Sound explosionSound;
        
        void deleteInactiveLaser();
        std::vector<Alien> createAlien();
        void moveAliens();
        void moveDownAliens(int distance);
        void alienShootLaser();
        void checkForCollisions();
        void gameOver();
        void reset();
        void nextLevel();
        void initGame();
        void checkHighScore();

    public:
        Spaceship spaceship;
        bool run;
        int score;
        int level;
        int highscore;
        Music music;

        Game();
        ~Game();
        void draw();
        void update();
        void handleInput();      
};