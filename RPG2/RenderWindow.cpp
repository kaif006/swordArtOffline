#include "RenderWindow.hpp"
#include "Enemy.hpp"


using namespace std;

RenderWindow::RenderWindow()
{}

RenderWindow::RenderWindow(const char* title, int width, int height, bool fullScreen) : window(NULL), renderer(NULL)
{
    int flags = 0;
    if (fullScreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
    if (window == NULL)
    {
        cout << "Failed to initialize window" << SDL_GetError() << endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* file_path)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, file_path);

    if (texture == NULL)
    {
        cout << "Failed to load texture" << SDL_GetError() << endl;
    }
    return texture;
}

void RenderWindow::cleanUp()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::renderEntity(Entity& entity, SDL_Rect& camera, float scale)
{
    SDL_Rect src; // source rect
    src.x = entity.getCurrentFrame().x;
    src.y = entity.getCurrentFrame().y;
    src.w = entity.getCurrentFrame().w;
    src.h = entity.getCurrentFrame().h;

    SDL_Rect des; // destination rect
    des.x = entity.getPosition().x - camera.x;
    des.y = entity.getPosition().y - camera.y;
    des.w = entity.getCurrentFrame().w * scale;
    des.h = entity.getCurrentFrame().h * scale;

    SDL_RenderCopy(renderer, entity.getTexture(), &src, &des);
}

void RenderWindow::renderEnemy(Enemy& enemy, SDL_Rect& camera)
{
    SDL_Rect des;
    des.x = enemy.getPosition().getX() - camera.x;
    des.y = enemy.getPosition().getY() - camera.y;
    des.w = 64;
    des.h = 64;

    SDL_Texture* frame1 = loadTexture("C:\\Users\\pc\\Documents\\Coding\\sprites\\2D Pixel Dungeon Asset Pack\\Character_animation\\monsters_idle\\skull\\v2\\skull_v2_1.png");
    SDL_Texture* frame2 = loadTexture("C:\\Users\\pc\\Documents\\Coding\\sprites\\2D Pixel Dungeon Asset Pack\\Character_animation\\monsters_idle\\skull\\v2\\skull_v2_2.png");
    SDL_Texture* frame3 = loadTexture("C:\\Users\\pc\\Documents\\Coding\\sprites\\2D Pixel Dungeon Asset Pack\\Character_animation\\monsters_idle\\skull\\v2\\skull_v2_3.png");
    SDL_Texture* frame4 = loadTexture("C:\\Users\\pc\\Documents\\Coding\\sprites\\2D Pixel Dungeon Asset Pack\\Character_animation\\monsters_idle\\skull\\v2\\skull_v2_4.png");


    int frameIndex = (SDL_GetTicks() / 200) % 4;

    SDL_Texture* currentFrame = nullptr;
    switch (frameIndex)
    {
    case 0:
        currentFrame = frame1;
        break;
    case 1:
        currentFrame = frame2;
        break;
    case 2:
        currentFrame = frame3;
        break;
    case 3:
        currentFrame = frame4;
        break;
    }

    SDL_RenderCopy(renderer, currentFrame, nullptr, &des);


    
}

void RenderWindow::renderBG(SDL_Texture* tex)
{
    SDL_RenderCopy(renderer, tex, NULL, NULL);
}

void RenderWindow::renderMap(Map& map, SDL_Rect& camera)
{
    int tileSize = 32;

    int startX = (camera.x / tileSize) - 1;
    int startY = (camera.y / tileSize) - 1;
    int endX = ((camera.x + camera.w) / tileSize) + 1;
    int endY = ((camera.y + camera.h) / tileSize) + 1;


    if (startX < 0) startX = 0;
    if (startY < 0) startY = 0;
    if (endX > map.getWidth()) endX = map.getWidth();
    if (endY > map.getHeight()) endY = map.getHeight();

    SDL_Rect tileRect;
    tileRect.x = 0 * tileSize - camera.x;
    tileRect.y = 0 * tileSize - camera.y;
    tileRect.w = tileSize;
    tileRect.h = tileSize;;

    SDL_Texture* floorTex = loadTexture("C:\\Users\\pc\\Documents\\Coding\\sprites\\BitLands\\Tileset\\Tileset.png");
    
    SDL_Rect floorSrc1 { 288, 64, 16, 16 };
    SDL_Rect floorSrc2 { 304, 64, 16, 16 };
    SDL_Rect floorSrc3 { 320, 64, 16, 16 };

    
    SDL_Rect floorTopSrc{ 288, 16, 16, 16 };
    SDL_Rect floorBottomSrc{ 288, 96, 16, 16 };
    SDL_Rect floorRightSrc{ 384, 64, 16, 16 };
    SDL_Rect floorLeftSrc{ 272, 64, 16, 16 };
    SDL_Rect floorTopLSrc{ 272, 16, 16, 16 };// top left
    SDL_Rect floorTopRSrc{ 384, 16, 16, 16 };// top right
    SDL_Rect floorBotLSrc{ 272, 96, 16, 16 };// bottom left 
    SDL_Rect floorBotRSrc{ 384, 96, 16, 16 };// bottom right

    SDL_Rect waterRect;
    waterRect.x = 0 * tileSize - camera.x;
    waterRect.y = 0 * tileSize - camera.y;
    waterRect.w = 32;
    waterRect.h = 32;

    SDL_Texture* waterTex = loadTexture("C:\\Users\\pc\\Documents\\Coding\\sprites\\lava2.jpg");

    SDL_Rect waterSrc;
    waterSrc.x = 16 * static_cast<int>((SDL_GetTicks() / 800) % 2) + 112;
    waterSrc.y = 32;
    waterSrc.w = 16;
    waterSrc.h = 16;


    for (int i = startY; i < endY; i++)
    {
        for (int j = startX; j < endX; j++)
        {
            SDL_Rect tile = { j * tileSize - camera.x, i * tileSize - camera.y, tileSize, tileSize };
            if (map.getMapData()[i][j] == 1) // wall
            {
                SDL_RenderCopy(renderer, waterTex, &waterSrc, &tile);
            }
            else // floor
            {
                bool top = (i > 0) && (map.getMapData()[i - 1][j] == 1);
                bool bottom = (i < map.getHeight() - 1) && (map.getMapData()[i + 1][j] == 1);
                bool left = (j > 0) && (map.getMapData()[i][j - 1] == 1);
                bool right = (j < map.getWidth() - 1) && (map.getMapData()[i][j + 1] == 1);

                if (top && left)
                {
                    SDL_RenderCopy(renderer, floorTex, &floorTopLSrc, &tile);
                }

                else if (top && right)
                {
                    SDL_RenderCopy(renderer, waterTex, &waterSrc, &tile);
                    SDL_RenderCopy(renderer, floorTex, &floorTopRSrc, &tile);
                }
                else if (bottom && left)
                {
                    SDL_RenderCopy(renderer, waterTex, &waterSrc, &tile);
                    SDL_RenderCopy(renderer, floorTex, &floorBotLSrc, &tile);
                }
                else if (bottom && right)
                {
                    SDL_RenderCopy(renderer, waterTex, &waterSrc, &tile);
                    SDL_RenderCopy(renderer, floorTex, &floorBotRSrc, &tile);
                }
                else if (top)
                {
                    SDL_RenderCopy(renderer, waterTex, &waterSrc, &tile);
                    SDL_RenderCopy(renderer, floorTex, &floorTopSrc, &tile);
                }
                else if (bottom)
                {
                    SDL_RenderCopy(renderer, waterTex, &waterSrc, &tile);
                    SDL_RenderCopy(renderer, floorTex, &floorBottomSrc, &tile);
                }
                else if (left)
                {
                    SDL_RenderCopy(renderer, waterTex, &waterSrc, &tile);
                    SDL_RenderCopy(renderer, floorTex, &floorLeftSrc, &tile);
                }
                else if (right)
                {
                    SDL_RenderCopy(renderer, waterTex, &waterSrc, &tile);
                    SDL_RenderCopy(renderer, floorTex, &floorRightSrc, &tile);
                }
                else
                {
                    int tileIndex = (i * map.getWidth() + j) % 3;
                    SDL_Rect* currentSrc = nullptr;
                    switch (tileIndex)
                    {
                    case 0:
                        currentSrc = &floorSrc1;
                        break;
                    case 1:
                        currentSrc = &floorSrc2;
                        break;
                    case 2:
                        currentSrc = &floorSrc3;
                        break;
                    }
                    SDL_RenderCopy(renderer, floorTex, currentSrc, &tile);
                }
            }

        }
    }
}

void RenderWindow::renderHealth(Player* player, SDL_Rect& camera)
{
    int totalHealth = 100;
    int spacing = 20;
    int healthRemaining = int(player->getHealth() / 20);

    SDL_Rect des;
    des.w = 32;
    des.h = 32;

    SDL_Texture* healthTex = loadTexture("C:\\Users\\pc\\Documents\\Coding\\sprites\\Sprout Lands - Sprites - Basic pack\\Objects\\Egg_item.png");

    for (int i = 0; i < healthRemaining; i++) {
        des.x = 10 + (i * spacing);
        des.y = 10;
        SDL_RenderCopy(renderer, healthTex, NULL, &des);
    }

}

void RenderWindow::renderTitle()
{
    SDL_Texture* titleTex = loadTexture("C:\\Users\\pc\\Documents\\Coding\\sprites\\titleScreen2.jpg");
    SDL_Rect des;
    des.x = 0;
    des.y = 0;
    des.w = 1200;
    des.h = 720;

    SDL_RenderCopy(renderer, titleTex, NULL, &des);

}

void RenderWindow::renderGameOver()
{
    SDL_Texture* titleTex = loadTexture("C:\\Users\\pc\\Documents\\Coding\\sprites\\deadScreen.jpg");
    SDL_Rect des;
    des.x = 0;
    des.y = 0;
    des.w = 1200;
    des.h = 720;

    SDL_RenderCopy(renderer, titleTex, NULL, &des);

}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}

SDL_Renderer* RenderWindow::getRenderer()
{
    return renderer;
}