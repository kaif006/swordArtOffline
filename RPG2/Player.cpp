#include "Player.hpp"

Player::Player(double x, double y, SDL_Texture* tex, int f, int s)
    : Entity(x, y, tex), animeFrames(f), animeSpeed(s)
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


void Player::onFloor(Map* map, int tileSize, int dx, int dy)
{
    int playerX = getPosition().x;
    int playerY = getPosition().y;

    int newX = playerX + dx;
    int newY = playerY + dy;

    if (dx != 0)
    {
        if (dx > 0)
        {
            int rightEdgeX = (newX + 32) / tileSize;
            int bottomEdgeY = (playerY + 27 - 1) / tileSize;

            if (map->getMapData()[playerY / tileSize][rightEdgeX] == 1 || map->getMapData()[bottomEdgeY][rightEdgeX] == 1)
            {
                newX = (rightEdgeX * tileSize) - 32;
            }
        }
        else if (dx < 0)
        {
            int leftEdgeX = newX / tileSize;
            int bottomEdgeY = (playerY + 27 - 1) / tileSize;

            if (map->getMapData()[playerY / tileSize][leftEdgeX] == 1 || map->getMapData()[bottomEdgeY][leftEdgeX] == 1)
            {
                newX = (leftEdgeX + 1) * tileSize;
            }
        }

    }

    if (dy != 0)
    {
        if (dy > 0)
        {
            int bottomEdgeY = (newY + 27) / tileSize;
            int rightEdgeX = (newX + 32 - 1) / tileSize;

            if (map->getMapData()[bottomEdgeY][newX / tileSize] == 1 || map->getMapData()[bottomEdgeY][rightEdgeX] == 1)
            {
                newY = (bottomEdgeY * tileSize) - 27;
            }
        }
        else if (dy < 0)
        {
            int topEdgeY = newY / tileSize;
            int rightEdgeX = (newX + 32 - 1) / tileSize;

            if (map->getMapData()[topEdgeY][newX / tileSize] == 1 || map->getMapData()[topEdgeY][rightEdgeX] == 1)
            {
                newY = (topEdgeY + 1) * tileSize;
            }
        }
    }
    position.x = newX;
    position.y = newY;

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
        position.x += velocity.x;
        animeState = 2; // run left
        lastDirection = -1;
        //onFloor(map, 32, -32, 0);
    }
    if (state[SDL_SCANCODE_D]) //MOVE Right
    {
        velocity.x = 10;
        position.x += velocity.x;
        animeState = 1; // run right
        lastDirection = 1;
        //onFloor(map, 32, 32, 0);
    }
    if (state[SDL_SCANCODE_W]) // move up
    {
        velocity.y = -10;
        position.y += velocity.y;
        animeState = 1; // run right
        lastDirection = 1;
        //onFloor(map, 32, 0, 32);
    }
    if (state[SDL_SCANCODE_S]) // move down
    {
        velocity.y = 10;
        position.y += velocity.y;
        animeState = 2; // run left
        lastDirection = -1;
        //onFloor(map, 32, 0, -32);
    }
    if (state[SDL_SCANCODE_X]) //lolz
    {
        animeState = 4;
    }

}