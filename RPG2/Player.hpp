#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Vec2d.hpp"

class Game;
class Enemy;

class Player : public Entity
{
    int animeSpeed;
    int animeFrames;
    Vec2d velocity;
    int animeState;
    int lastDirection; // 1 = right   -1 = left
    int health;

    bool collision(Map& map, double x, double y);

public:
    Player(double x, double y, SDL_Texture* tex, int f, int s);

    void animate() override;

    void playerControls(Map* map);

    void keepInMap(Map& map);

    void attack(Enemy* enemy);

    void getHit(Enemy* enemy);

    int getHealth();

};