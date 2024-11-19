#include "Map.hpp"


Map::Map(int width, int height)
    : width(width), height(height) {

    srand(static_cast<unsigned>(time(0)));

    mapData.resize(height, vector<int>(width, 1));
}

Map::Map() : width(75), height(75)
{
    srand(static_cast<unsigned>(time(0)));

    mapData.resize(height, vector<int>(width, 1));
}

void Map::generateRoomsAndCorridors()
{
    int numRooms = 10 + rand() % 11; //  a num bw 10 and 20

    for (int i = 0; i < numRooms; ++i)
    {
        int roomWidth = 10 + rand() % 11; // rando width bw 10 and 20
        int roomHeight = 10 + rand() % 11; // rando height bw 10 and 20


        int x = rand() % (width - roomWidth - 1) + 1;
        int y = rand() % (height - roomHeight - 1) + 1;

        Room newRoom = { x, y, roomWidth, roomHeight };

        if (!overlaps(newRoom))
        {
            rooms.push_back(newRoom);
            for (int j = x; j < x + roomWidth; ++j)
            {
                for (int k = y; k < y + roomHeight; ++k)
                {
                    mapData[k][j] = 0;
                }
            }
        }
    }

    for (int i = 1; i < rooms.size(); ++i)
    {
        connectRooms(rooms[i - 1], rooms[i]);
    }
}


bool Map::overlaps(const Room& newRoom) const
{
    for (const Room& room : rooms)
    {
        if (newRoom.x < room.x + room.w &&
            newRoom.x + newRoom.w > room.x &&
            newRoom.y < room.y + room.h &&
            newRoom.y + newRoom.h > room.y)
        {
            return true; // overlap
        }
    }
    return false; // no overlao
}

void Map::connectRooms(const Room& roomA, const Room& roomB)
{
    int centerAx = roomA.x + roomA.w / 2;
    int centerAy = roomA.y + roomA.h / 2;
    int centerBx = roomB.x + roomB.w / 2;
    int centerBy = roomB.y + roomB.h / 2;


    if (rand() % 2 == 0)
    {
        // horizontal then vert
        for (int x = centerAx; x != centerBx; x += (centerBx > centerAx ? 1 : -1))
        {
            mapData[centerAy][x] = 0;
            mapData[centerAy + 1][x] = 0;
            mapData[centerAy - 1][x] = 0;
            mapData[centerAy + 2][x] = 0;
            mapData[centerAy - 2][x] = 0;
        }
        for (int y = centerAy; y != centerBy; y += (centerBy > centerAy ? 1 : -1))
        {
            mapData[y][centerBx] = 0;
            mapData[y][centerBx + 1] = 0;
            mapData[y][centerBx - 1] = 0;
            mapData[y][centerBx + 2] = 0;
            mapData[y][centerBx - 2] = 0;
        }
    }
    else
    {
        // vert then horizontal
        for (int y = centerAy; y != centerBy; y += (centerBy > centerAy ? 1 : -1))
        {
            mapData[y][centerAx] = 0;
            mapData[y][centerAx + 1] = 0;
            mapData[y][centerAx - 1] = 0;
            mapData[y][centerAx + 2] = 0;
            mapData[y][centerAx - 2] = 0;
        }
        for (int x = centerAx; x != centerBx; x += (centerBx > centerAx ? 1 : -1))
        {
            mapData[centerBy][x] = 0;
            mapData[centerBy + 1][x] = 0;
            mapData[centerBy - 1][x] = 0;
            mapData[centerBy + 2][x] = 0;
            mapData[centerBy - 2][x] = 0;
        }
    }
}


const vector<vector<int>>& Map::getMapData() const
{
    return mapData;
}

int Map::getWidth()
{
    return width;
}

int Map::getHeight()
{
    return height;
}

const vector<Map::Room>& Map::getRooms()
{
    return rooms;
}
