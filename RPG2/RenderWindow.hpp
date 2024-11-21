#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <random>
#include "Entity.hpp"
#include "Map.hpp"

class Enemy;

class RenderWindow
{
private:
    SDL_Renderer* renderer;
    SDL_Window* window;
public:
    RenderWindow();
    RenderWindow(const char* title, int width, int height, bool fullScreen);
    SDL_Texture* loadTexture(const char* file_path);
    void cleanUp();
    void clear();
    void renderEntity(Entity& entity, SDL_Rect& camera, float scale = 1.0f);
    void renderEnemy(Enemy& enemy, SDL_Rect& camera);
    void renderBG(SDL_Texture* tex);
    void renderMap(Map& map, SDL_Rect& camera);
    void renderHealth(Player* player, SDL_Rect& camera);
    void renderTitle();
    void renderGameOver();
    void display();
    SDL_Renderer* getRenderer();

};