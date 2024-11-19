#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Vec2d.hpp"

class Game;

class Player : public Entity
{
    int animeSpeed;
    int animeFrames;
    Vec2d velocity;
    int animeState;
    int lastDirection; // 1 = right   -1 = left

public:
    Player(double x, double y, SDL_Texture* tex, int f, int s);

    void animate() override;

    void onFloor(Map* map, int tileSize, int dx, int dy);

    void playerControls(Map* map);

};