#include "RenderWindow.hpp"


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

    SDL_Texture* floorTexture = loadTexture("C:\\Users\\pc\\Documents\\Coding\\sprites\\Fire_4_16x16.png");
    SDL_Rect srcRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = 32;
    srcRect.h = 32;

    for (int i = startY; i < endY; i++)
    {
        for (int j = startX; j < endX; j++)
        {
            SDL_Rect tile = { j * tileSize - camera.x, i * tileSize - camera.y, tileSize, tileSize };
            if (map.getMapData()[i][j] == 1) // wall
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &tile);
            }
            else // floor
            {
                //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderCopy(renderer, floorTexture, &srcRect, &tile);
            }

        }
    }
}


void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}

SDL_Renderer* RenderWindow::getRenderer()
{
    return renderer;
}