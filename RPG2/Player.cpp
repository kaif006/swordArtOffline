#include "Player.hpp"
#include "Enemy.hpp"

Player::Player(double x, double y, SDL_Texture* tex, int f, int s)
    : Entity(x, y, tex), animeFrames(f), animeSpeed(s), health(100)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32; // player Width
    currentFrame.h = 27; // player height

    animeState = 0;
    lastDirection = 1; // 1 = right   -1 = left

}

void Player::animate()
{
    switch (animeState)
    {
    case 0: // idle right
        currentFrame.y = 0;
        currentFrame.x = currentFrame.w * static_cast<int>((SDL_GetTicks() / animeSpeed) % animeFrames);
        break;
    case 1: // run right
        currentFrame.y = 32;
        currentFrame.x = currentFrame.w * static_cast<int>((SDL_GetTicks() / animeSpeed) % animeFrames);
        break;
    case 2: // run left
        currentFrame.y = 32;
        currentFrame.x = currentFrame.w * static_cast<int>((SDL_GetTicks() / animeSpeed) % animeFrames) + 128;
        break;
    case 3: // idle left
        currentFrame.y = 0;
        currentFrame.x = currentFrame.w * static_cast<int>((SDL_GetTicks() / animeSpeed) % animeFrames) + 128;
        break;
    case 4: // lolz
        currentFrame.y = 288;
        currentFrame.x = currentFrame.w * static_cast<int>((SDL_GetTicks() / animeSpeed) % animeFrames);
        break;
    }
}

bool Player::collision(Map& map, double x, double y)
{
    vector<vector<int>> mapData = map.getMapData();
    int nextX = x / 32;
    int nextY = y / 32;

    if (mapData[nextY][nextX] == 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}


void Player::playerControls(Map* map)
{
    const Uint8* state = SDL_GetKeyboardState(NULL);

    velocity.x = 0;

    if (velocity.x == 0)
    {
        if (lastDirection == 1)
        {
            animeState = 0; // idle right
        }
        else if (lastDirection == -1)
        {
            animeState = 3; // idle left 
        }

    }

    if (state[SDL_SCANCODE_A]) //MOVE LEFT
    {
        velocity.x = -10;
        if (collision(*map, position.x - 1, position.y))
        {
            position.x += velocity.x;
            animeState = 2; // run left
            lastDirection = -1;
        }
        
        //onFloor(map, 32, -32, 0);
    }
    if (state[SDL_SCANCODE_D]) //MOVE Right
    {
        velocity.x = 10;
        if (collision(*map, position.x + 120, position.y))
        {
            position.x += velocity.x;
            animeState = 1; // run right
            lastDirection = 1;
        }
        
        //onFloor(map, 32, 32, 0);
    }
    if (state[SDL_SCANCODE_W]) // move up
    {
        velocity.y = -10;
        if (collision(*map, position.x, position.y - 1))
        {
            position.y += velocity.y;
            animeState = 1; // run right
            lastDirection = 1;
        }
    }
    if (state[SDL_SCANCODE_S]) // move down
    {
        velocity.y = 10;
        if (collision(*map, position.x, position.y + 130))
        {
            position.y += velocity.y;
            animeState = 2; // run left
            lastDirection = -1;
        }
        
    }
}

void Player::keepInMap(Map& map)
{

}

void Player::attack(Enemy* enemy)
{
    Vec2d enemyPos(enemy->getPosition().getX(), enemy->getPosition().getY()); // add half of height and width of enemy
    if (int(position.dist(enemyPos)) < 100)
    {
        const Uint8* state = SDL_GetKeyboardState(NULL);
        static bool attackPressed = false;
        if (state[SDL_SCANCODE_SPACE]) 
        {
            if (!attackPressed) 
            {
                attackPressed = true;
                animeState = 4;
                enemy->getHit();
            }
        }
        else 
        {
            attackPressed = false;
        } 
    }
}

void Player::getHit(Enemy* enemy)
{
    Vec2d enemyPos(enemy->getPosition().getX(), enemy->getPosition().getY());
    const Uint32 damageInterval = 5000;
    Uint32 currentTime = SDL_GetTicks();
    Uint32 lastDamageTime = 0;
    if (int(position.dist2(enemyPos)) < 50)
    {
        enemy->setMode(1);
        if (currentTime - lastDamageTime >= damageInterval)
        {
            enemy->setMode(1);
            health -= 10;
            lastDamageTime = currentTime;
            if (health <= 0)
            {
                health = 0;
                cout << "DEAD" << endl;
            }
        }
    }
    enemy->setMode(0);
}

int Player::getHealth()
{
    return health;
}



