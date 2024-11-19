#pragma once
#include <vector>
#include <SDL.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

class Map
{
    int width;
    int height;
    vector<vector<int>> mapData;

    struct Room
    {
        int x, y, w, h;
    };

    vector<Room> rooms;
    bool overlaps(const Room& newRoom) const;
    void connectRooms(const Room& roomA, const Room& roomB);
public:
    Map(int width, int height);
    Map();
    void generateRoomsAndCorridors();
    const vector<vector<int>>& getMapData() const;
    int getWidth();
    int getHeight();
    const vector<Room>& getRooms();


};

