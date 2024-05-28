#include "Game.h"
#include <iostream>

Game::Game()
{
    InitAudioDevice();
    highscore = 0;
    lastTimeAlienFire = 0.0;
    initGame();
    explosionSound = LoadSound("sounds/explosion.mp3");
}

Game::~Game()
{
    Alien::UnloadImage();

    UnloadMusicStream(music);
    UnloadSound(explosionSound);

    CloseAudioDevice();
}

void Game::draw()
{
    spaceship.draw();

    for(auto& laser: spaceship.lasers)
    {
        laser.draw();
    }

    for(auto& alien: aliens)
    {
        alien.draw();
    }

    for(auto& laser: alienLaser)
    {
        laser.draw();
    }
}

void Game::update()
{
    if(run)
    {
        for(auto& laser: spaceship.lasers)
        {
            laser.update();
        }
        moveAliens();
        alienShootLaser();

        for(auto&laser: alienLaser)
        {
            laser.update();
        }

        checkForCollisions();
        deleteInactiveLaser();
    }
    else if(IsKeyDown(KEY_ENTER))
    {
        reset();
        initGame();
    }

}

void Game::handleInput()
{
    if(run)
    {
        if(IsKeyDown(KEY_LEFT))       spaceship.moveLeft();
        else if(IsKeyDown(KEY_RIGHT)) spaceship.moveRight();
        else if(IsKeyDown(KEY_SPACE)) spaceship.fireLaser();
    }

}

void Game::deleteInactiveLaser()
{
    for(auto pos = spaceship.lasers.begin(); pos != spaceship.lasers.end();)
    {
        // inactive laser
        if(!pos->active)
            pos = spaceship.lasers.erase(pos);
        else 
            ++pos;
    }

    for(auto pos = alienLaser.begin(); pos != alienLaser.end();)
    {
        // inactive laser
        if(!pos->active)
            pos = alienLaser.erase(pos);
        else 
            ++pos;
    }
}

std::vector<Alien> Game::createAlien()
{
    aliens.clear();
    std::vector<Alien> aliens;
    srand(time(NULL));
    for(int row = 0; row < 4; row++)
    {
        for(int col = 0; col < 11; col++)
        {
            float x = 75 + col*55;
            float y = 110 + row*55;
            aliens.push_back(Alien(rand()%3 + 1, {x,y}));
        }
    }
    return aliens;
}

void Game::moveAliens()
{
    for(auto& alien: aliens)
    {
        if(alien.position.x + alien.image[alien.type - 1].width > GetScreenWidth() - 10)
        {
            alienDirection = -1;
            moveDownAliens(4);
        }
        if(alien.position.x < 10)
        {
            alienDirection = 1;
            moveDownAliens(4);
        }
        alien.update(alienDirection);
    }
}

void Game::moveDownAliens(int distance)
{
    for(auto& alien: aliens)
        alien.position.y += distance;
}

void Game::alienShootLaser()
{
    if(GetTime() - lastTimeAlienFire >= (double) 5/(2.5*level) && !aliens.empty())
    {
        int randomId = GetRandomValue(0,aliens.size() - 1);
        Alien& alien = aliens[randomId];

        alienLaser.push_back(Laser({alien.position.x + alien.image[alien.type - 1].width/2 , alien.position.y + alien.image[alien.type - 1].height}, 4));
        lastTimeAlienFire = GetTime();
    }
}

void Game::checkForCollisions()
{
    //check remain buff time of spaceship
    if(spaceship.isBuffed && GetTime() - spaceship.buffTime >= 2)
    {
        spaceship.isBuffed = false;
        spaceship.buffTime = 0.0;
    }

    // spaceship's laser
    for(auto& laser: spaceship.lasers)
    {
        auto it = aliens.begin();
        while (it != aliens.end())
        {
            if(CheckCollisionRecs(it->getRect() , laser.getRect()))
            {
                //calculate score
                score += 100*( it->getType() + level);
                checkHighScore();

                PlaySound(explosionSound);

                it = aliens.erase(it);
                laser.active = false;
            }
            else
                it++;
        }
    }

    // alien's laser
    for(auto& laser: alienLaser)
    {
        if(!spaceship.isBuffed && CheckCollisionRecs(laser.getRect(),spaceship.getRect()))
        {
            laser.active = false;
            spaceship.lives --;
            spaceship.buffTime = GetTime();
            spaceship.isBuffed = true;
            if(spaceship.lives == 0)
            {
                gameOver();
                return;
            }
        }
    }

    // alien touch the spaceship
    for(auto& alien : aliens)
    {
        if(CheckCollisionRecs(alien.getRect(),spaceship.getRect()))
        {
            gameOver();
            return;
        }
    }

    // check if player win the game
    if(aliens.empty())
        nextLevel();
}

void Game::gameOver()
{
    run = false;

    music = LoadMusicStream("sounds/gameOverMusic.mp3");
    PlayMusicStream(music);

}

void Game::reset()
{
    spaceship.reset();
    aliens.clear();
    alienLaser.clear();

}

void Game::nextLevel()
{
    int templv = level;
    int tempScore = score;
    initGame();
    level = ++templv;
    score = tempScore;
}

void Game::initGame()
{
    aliens = createAlien();
    alienDirection = 1;
    spaceship.lives = 3;
    run = true;
    score = 0;
    level = 1;

    music = LoadMusicStream("sounds/music.mp3");
    PlayMusicStream(music);
}

void Game::checkHighScore()
{
    if(score > highscore)
        highscore = score;
}
