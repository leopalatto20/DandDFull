#pragma once
#include "Monster.h"
#include "Graph.h"
#include "Room.h"
#include <fstream>
#include <sstream>

class Dungeon {
private:
    Graph<Room> rooms;
public:
    Dungeon();
    ~Dungeon();
    bool createRoom(unsigned int index, Monster &monster);
    bool createDungeon(const string &fileName);
    void printRooms();
    unsigned int getSize();
};