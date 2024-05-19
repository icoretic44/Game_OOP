#include <raylib.h>
#include <string>
#include "Game.h"

Color black = Color{ 0, 0, 0, 255 };
Color yellow = Color{ 253, 249, 0, 255 };
//set screen width, height
int offset = 50;
const int screenWidth = 650;
const int screenHeight = 600;
//initialize font of text
Font font;

std::string FormatWithLeadingZeros(int number, int width);
void gamestart();
void gameMenu();

int main()
{
    InitWindow(screenWidth + offset, screenHeight + 2*offset, "Space Invaders!");
    gameMenu();
    CloseWindow();
    return 0;
}

std::string FormatWithLeadingZeros(int number, int width) {
    std::string numberText = std::to_string(number);
    int leadingZeros = width - numberText.length();
    numberText = std::string(leadingZeros, '0') + numberText;
    return numberText;
}
void gamestart()
{

    //initialize font of text
    font = LoadFontEx("font/monogram.ttf", 64, 0, 0);
    SetTargetFPS(60);

    Game game;

    // check if window is opened
    while (!WindowShouldClose())
    {
        UpdateMusicStream(game.music);

        //update game frame
        game.handleInput();
        game.update();

        BeginDrawing();
        ClearBackground(black);

        DrawRectangleRoundedLines({10,10,680,680}, 0.18f, 20, 2, yellow);
        DrawLineEx({20,620}, {680,620}, 3, yellow);
        if(!game.run)
            DrawTextEx(font, "Press Enter to play again!", {110,640}, 34, 2, yellow);
        else
        {
            std::string levelText = "LEVEL " + FormatWithLeadingZeros(game.level, 2);
            DrawTextEx(font, levelText.c_str(),{500, 640}, 34, 2, yellow);
        }
        // display player's lives left
        for(int i = 0; i < game.spaceship.lives ; i++)
        {
            float x = 50.0 *(i+1);
            DrawTextureV(game.spaceship.image, {x, 645}, WHITE);
        }

        //display player's score
        DrawTextEx(font, "SCORE:", {50,15}, 34, 2, yellow);
        std::string scoreText = FormatWithLeadingZeros(game.score, 5);
        DrawTextEx(font, scoreText.c_str(), {50, 40}, 34, 2, yellow);

        //display player's highscore
        DrawTextEx(font, "HIGH-SCORE", {480, 15}, 34, 2, yellow);
        std::string highscoreText = FormatWithLeadingZeros(game.highscore, 5);
        DrawTextEx(font, highscoreText.c_str(), {480, 40}, 34, 2, yellow);

        //draw game frame
        game.draw();

        EndDrawing();
    }
}

void gameMenu()
{

    Texture2D aliens[3];
    aliens[0] = LoadTexture("graphics/alien_1.png");
    aliens[1] = LoadTexture("graphics/alien_2.png");
    aliens[2] = LoadTexture("graphics/alien_3.png");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(black);

        DrawRectangleRoundedLines({10,10,680,680}, 0.18f, 20, 2, yellow);

        //decorations
        DrawTextEx(font, "SPACE INVADERS", {140,80},50, 2, yellow);
        DrawLineEx({20,580}, {680,580}, 3, yellow);
        DrawTextEx(font, "<- : MOVE LEFT", {200,590}, 25, 2, yellow);
        DrawTextEx(font, "-> : MOVE RIGHT", {200,620}, 25, 2, yellow);
        DrawTextEx(font, "SPACE : FIRE LASER", {200,650}, 25, 2, yellow);
        DrawTextureV(aliens[0],{50,420},WHITE);
        DrawTextureV(aliens[2],{620,100},WHITE);
        DrawTextureV(aliens[2],{220,220},WHITE);
        DrawTextureV(aliens[1],{340,500},WHITE);
        DrawTextureV(aliens[1],{150,42},WHITE);
        DrawTextureV(aliens[0],{500,300},WHITE);
        DrawTextureV(aliens[2],{630,490},WHITE);
        DrawTextureV(aliens[1],{70,190},WHITE);

        //create play button
        Rectangle playButton;
        playButton.x = 190;
        playButton.y = 300;
        playButton.height = 100;
        playButton.width = 300;
        if(CheckCollisionPointRec(GetMousePosition(),playButton))
        {
            DrawRectangleLines(190,300,300,100,WHITE);
            DrawTextEx(font, "PLAY", {280, 330}, 50, 2, WHITE);
        }

        else
        {
            DrawRectangleLines(190,300,300,100,yellow);
            DrawTextEx(font, "PLAY", {280, 330}, 50, 2, yellow);
        }

        //check if player click on the play button
        if(CheckCollisionPointRec(GetMousePosition(),playButton) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            gamestart();
            break;
        }

        EndDrawing();
    }
    
}
