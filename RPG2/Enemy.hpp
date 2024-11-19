#include "Entity.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <cmath>

using namespace std;

// for A* path finding
struct Node 
{
    int x, y;
    float gCost = 0;
    float hCost = 0;
    Node* parent = nullptr;

    float fCost() const { return gCost + hCost; }

    bool operator == (const Node& other) const 
    {
        return x == other.x && y == other.y;
    }

    bool operator > (const Node& other) const 
    {
        return fCost() > other.fCost();
    }
};

// Hash function for Node
struct NodeHash
{
    std::size_t operator () (const Node& node) const 
    {
        return std::hash<int>()(node.x) ^ (std::hash<int>()(node.y) << 1);
    }
};

// Comparison function for priority queue
struct CompareNode 
{
    bool operator()(Node* a, Node* b) 
    {
        return a->fCost() > b->fCost();
    }
};


class Enemy : public Entity
{
	int life;
	int speed;

    vector<Node*> aStar(Map& map, Node start, Node goal);
    float heuristic(int x1, int y1, int x2, int y2);
public:
	Enemy(double x, double y, SDL_Texture* tex);
	void followPlayer(Player& player, Map& map);
};