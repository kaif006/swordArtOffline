#include "Entity.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <queue>

using namespace std;



class Enemy : public Entity
{
	int life;
	float speed;
	int mode; // 1 attack, 2 damage

public:
	Enemy(double x, double y, SDL_Texture* tex);
	void followPlayer(Player& player, Map& map);
	void getHit();
	int getAlife();
	void setMode(int m);
	int getMode();
};