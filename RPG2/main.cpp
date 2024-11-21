#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Game.hpp"

using namespace std;

const int WIDTH = 1200; // screen width
const int HEIGHT = 720; // screen height

Game* game = NULL;

int main(int argc, char* argv[])
{
    game = new Game();


    const int FPS = 30;
    const int timeBWframes = 1000 / FPS;

    game->init("Untitled Plumber Game", WIDTH, HEIGHT, false);

    while (game->running())
    {
        int startTicks = SDL_GetTicks();

        game->handleEvents();
        if (game->getGameState() == 1)
        {
            game->update();
        }

        game->render();

        //// MANAGE FPS ////
        int deltaTicks = SDL_GetTicks() - startTicks;
        if (deltaTicks < timeBWframes)
            SDL_Delay(timeBWframes - deltaTicks);
    }

    game->clean();

    return  0;
}

