#pragma once
#include "Monster.h"
#include "Graph.h"
#include "Room.h"
#include <fstream>
#include <sstream>

class Dungeon {
private:
    Graph<Room> rooms;
    DLinkedList<unsigned int> path;
public:
    Dungeon();
    ~Dungeon();
    bool createRoom(unsigned int index, Monster &monster);
    bool createDungeon(const string &fileName);
    void printRooms();
    unsigned int getSize();
    Monster* getMonster(unsigned int index);
    void DFS(unsigned int index);
    bool createRoute(unsigned int startIndex, unsigned int endIndex);
    void printPath();
};