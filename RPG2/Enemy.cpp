#include "Enemy.hpp"

Enemy::Enemy(double x, double y, SDL_Texture* tex) : Entity(x, y, tex), life(100) {}

float Enemy::heuristic(int x1, int y1, int x2, int y2) 
{
    return std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

vector<Node*> Enemy::aStar(Map& map, Node start, Node goal) 
{
    priority_queue<Node*, vector<Node*>, CompareNode> openList;
    unordered_map<Node, float, NodeHash> gScore; // Keeps track of gCosts
    unordered_set<Node, NodeHash> closedList; // Keeps track of visited nodes

    start.gCost = 0;
    start.hCost = heuristic(start.x, start.y, goal.x, goal.y);
    openList.push(new Node(start));
    gScore[start] = start.gCost;

    while (!openList.empty()) 
    {
        Node* current = openList.top();
        openList.pop();

        if (*current == goal) 
        {
            // Goal reached, reconstruct path
            vector<Node*> path;
            while (current != nullptr) 
            {
                path.push_back(current);
                current = current->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        closedList.insert(*current);

        // Check neighbors
        vector<Node> neighbors = 
        {
            {current->x + 1, current->y}, {current->x - 1, current->y},
            {current->x, current->y + 1}, {current->x, current->y - 1}
        };

        for (Node& neighbor : neighbors) {
            if (neighbor.x < 0 || neighbor.y < 0 || neighbor.x >= map.getWidth() || neighbor.y >= map.getHeight())
                continue; // Out of bounds

            // Assign movement cost based on tile type
            int movementCost = (map.getMapData()[neighbor.y][neighbor.x] == 1) ? INT_MAX : 1;
            if (movementCost == INT_MAX) continue; // Skip walls

            float tentativeGCost = current->gCost + movementCost;

            if (closedList.find(neighbor) != closedList.end() && tentativeGCost >= gScore[neighbor]) {
                continue; // Skip if already in closed list and no better path
            }

            if (gScore.find(neighbor) == gScore.end() || tentativeGCost < gScore[neighbor]) {
                neighbor.gCost = tentativeGCost;
                neighbor.hCost = heuristic(neighbor.x, neighbor.y, goal.x, goal.y);
                neighbor.parent = current;

                gScore[neighbor] = neighbor.gCost;
                openList.push(new Node(neighbor));
            }
        }
    }

    return {};
}
    
    

void Enemy::followPlayer(Player& player, Map& map) 
{
    // Check if the player is in range
    if (abs(player.getPosition().x - position.x) > 20 || abs(player.getPosition().y - position.y) > 20) 
    {
        return; // Player is out of range
    }

    Node start = { position.x / 32, position.y / 32 };
    Node goal = { player.getPosition().x / 32, player.getPosition().y / 32 };

    std::vector<Node*> path = aStar(map, start, goal);

    if (!path.empty() && path.size() > 1) 
    {
        Node* nextStep = path[1]; // Get the next node on the path
        position.x = nextStep->x * 32;
        position.y = nextStep->y * 32;
    }
}
