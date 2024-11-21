#pragma once 
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <random>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Tile.hpp"
#include "Map.hpp"
#include "Enemy.hpp"
#include "Vec2d.hpp"

using namespace std;

class Game
{
protected:
    bool isRunning;
    RenderWindow window;
    vector <Entity*> entities;
    Player* player;
    Map map;
    static SDL_Rect camera;
    Mix_Music* backgroundMusic;
    int gameState; // 0 title, 1 game, 2 game over

public:
    Game();
    ~Game();
    void init(const char* title, int width, int height, bool fullScreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    void spawnEnemies();
    int getGameState();

    bool running();
};