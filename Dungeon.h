#pragma once
#include "Monster.h"
#include "Graph.h"
#include "Room.h"
#include <fstream>
#include <sstream>
#define DUNGEON "dungeon.txt"

class Dungeon {
private:
    Graph<Room> rooms;
public:
    Dungeon();
    ~Dungeon();
    bool createRoom(unsigned int index, Monster &monster);
    bool createDungeon();
    void printRooms();
    unsigned int getSize();
};