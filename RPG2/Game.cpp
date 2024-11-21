#include "Game.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Tile.hpp"
#include "Player.hpp"

Game::Game(): gameState(0)
{}

SDL_Rect Game::camera = { 0,0,1200,720 };

Game::~Game()
{
    for (Entity* entity : entities) {
        delete entity;
    }
    entities.clear();
    delete player;
}

void Game::init(const char* title, int width, int height, bool fullScreen)
{

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        window = RenderWindow(title, width, height, fullScreen);
        isRunning = true;
    }
    else { isRunning = false; }

    // for sound
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    backgroundMusic = Mix_LoadMUS("C:\\Users\\pc\\Documents\\Coding\\sprites\\the-suspicion-228728.mp3");
    Mix_Music* doom = Mix_LoadMUS("C:\\Users\\pc\\Documents\\Coding\\sprites\\Doom OST - E1M1 - At Doom's Gate [ ezmp3.cc ].mp3");
    Mix_PlayMusic(doom, -1);

    // generate map
    map.generateRoomsAndCorridors();

    // spawn player in map
    SDL_Texture* playerTex = window.loadTexture("C:\\Users\\pc\\Documents\\Coding\\sprites\\lancelot_.png");
    bool playerPlaced = false;
    for (int j = 0; j < map.getHeight() && !playerPlaced; j++)
    {
        for (int i = 0; i < map.getWidth(); i++)
        {
            if (map.getMapData()[j][i] == 0)
            {
                player = new Player(i * 32, j * 32, playerTex, 4, 190);
                playerPlaced = true;
                break;
            }
        }
    }

    // spawn eneies
    spawnEnemies();

}


void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_KEYDOWN:
        gameState = 1;

    default:
        break;
    }

}

void Game::update()
{
    player->animate();
    player->playerControls(&map);

    // Update camera as player moves
    camera.x = player->getPosition().x - (600 - 32); // minus half screen and player width
    camera.y = player->getPosition().y - (360 - 27); // minus half screen and player height

    // keep camera in map
    int tileSize = 32;
    if (camera.x < 0)
    {
        camera.x = 0;
    }
    else if (camera.x > map.getWidth() * tileSize - camera.w)
    {
        camera.x = map.getWidth() * tileSize - camera.w;
    }

    if (camera.y < 0)
    {
        camera.y = 0;
    }
    else if (camera.y > map.getHeight() * tileSize - camera.h)
    {
        camera.y = map.getHeight() * tileSize - camera.h;
    }

    for (Entity* entity : entities)
    {
        Enemy* enemy = static_cast<Enemy*>(entity);
        entity->followPlayer(*player, map);
        player->attack(enemy);
        if (enemy->getAlife() <= 0)
        {
            entities.erase(remove(entities.begin(), entities.end(), entity), entities.end());
        }   
        player->getHit(enemy);
    }

    if (player->getHealth() <= 0)
    {
        gameState = 2;
    }

    

}

void Game::render()
{
    window.clear();

    if (gameState == 0) 
    {
        window.renderTitle();
    }
    else if (gameState == 1) 
    {
        // render map
        window.renderMap(map, camera);

        window.renderEntity(*player, camera, 4.0f);

        for (Entity* entity : entities)
        {
            Enemy* enemy = static_cast<Enemy*>(entity);
            window.renderEnemy(*enemy, camera);
        }
        window.renderHealth(player, camera);
    }
    else if (gameState == 2)
    {
        window.renderGameOver();
    }

    window.display();
}


void Game::spawnEnemies()
{
    auto rooms = map.getRooms();
    SDL_Texture* enemyTex = window.loadTexture("C:\\Users\\pc\\Documents\\Coding\\sprites\\Mutated_Bat\\Idle_Fly.png");

    srand(static_cast<unsigned>(time(0)));

    for (const auto& room : rooms) 
    {
        int numEnemies = 2 + rand() % 4;

        for (int i = 0; i < numEnemies; ++i)
        {
            int enemyX = room.x + rand() % room.w;
            int enemyY = room.y + rand() % room.h;

            enemyX *= 32;
            enemyY *= 32;
            Enemy* enemy = new Enemy(enemyX, enemyY, enemyTex);

            entities.push_back(enemy);
            cout << "Enemy Spawned at (" << enemyX << ", " << enemyY << ")" << endl;
        }
    }
    cout << "total entities: " << entities.size() << endl;

}


void Game::clean()
{
    window.cleanUp();
}

int Game::getGameState()
{
    return gameState;
}

bool Game::running()
{
    return isRunning;
}
