#include "Enemy.hpp"

Enemy::Enemy(double x, double y, SDL_Texture* tex) : Entity(x, y, tex), life(100), speed(4.0f), mode(2) {}
    
   
void Enemy::followPlayer(Player& player, Map& map)
{
    Vec2d playerPos(player.getPosition().getX() + 64, player.getPosition().getY() + 54); // add half of height and width of player

    if (position.dist(playerPos) > 250)
    {
        return;
    }

    Vec2d direction = playerPos - position;

    // normalize vector
    float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (magnitude != 0) 
    {
        direction /= magnitude;
    }

    position += direction * speed;
}

void Enemy::getHit()
{
    life -= 50;   
}

int Enemy::getAlife()
{
    return life;
}

void Enemy::setMode(int m)
{
    mode = m;
}

int Enemy::getMode()
{
    return mode;
}
