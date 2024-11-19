#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Vec2d.hpp"
#include "Map.hpp"

class Player;

class Entity
{
protected:
    Vec2d position;
    SDL_Rect currentFrame;
    SDL_Texture* texture;
public:
    Entity(double x, double y, SDL_Texture* tex);

    Vec2d& getPosition();
    SDL_Texture* getTexture();
    SDL_Rect getCurrentFrame() const;

    virtual void animate();
    bool checkCollision(const Entity& other) const;
    virtual void followPlayer(Player& player, Map& map);
};