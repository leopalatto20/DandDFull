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
    unsigned int currentRoom;
public:
    Dungeon();
    ~Dungeon();
    bool createRoom(unsigned int index, Monster &monster);
    bool createDungeon(const string &fileName);
    void printRooms();
    unsigned int getSize();
    bool DFS(unsigned int index);
    bool BFS(unsigned int index);
    bool createRoute(unsigned int startIndex, unsigned int endIndex);
    void printPath();
    Room* currentRoomPath();
    bool goForward();
};