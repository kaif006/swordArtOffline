#include "Entity.hpp"


Entity::Entity(double x, double y, SDL_Texture* tex) :texture(tex)
{
    position.x = x;
    position.y = y;

}

Vec2d& Entity::getPosition()
{
    return position;
}

SDL_Texture* Entity::getTexture()
{
    return texture;
}

SDL_Rect Entity::getCurrentFrame() const
{
    return currentFrame;
}

void Entity::animate() {}

//void Entity::followPlayer(Player& player, Map& map){}

bool Entity::checkCollision(const Entity& other) const
{
    const SDL_Rect a = currentFrame;
    const SDL_Rect b = other.getCurrentFrame();

    if (a.x + a.w > b.x && a.x < b.x + b.w && a.y + a.h > b.y && a.y < b.y + b.h)
        return true;
    else { return false;; }
}
