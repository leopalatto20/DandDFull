#include "Dungeon.h"

Dungeon::Dungeon() { //todos mis caminos empiezan desde el primer cuarto
}

Dungeon::~Dungeon() {
}
void Dungeon::printRooms() {
    rooms.print();
}

bool Dungeon::createRoom(unsigned int index, Monster &monster) {
    Room newRoom(monster);
    return rooms.setVertex(index, newRoom);
}

bool Dungeon::createDungeon(const string &fileName) {
    return rooms.createFromCSV(fileName);
}

unsigned int Dungeon::getSize() {
    return rooms.getSize();
}

Monster* Dungeon::getMonster(unsigned int index) {
    Room *selectedRoom = rooms.getFromIndex(index);
    if(!selectedRoom)
        return nullptr;
    return &selectedRoom->monster;
}

void Dungeon::DFS(unsigned int index) {
    rooms.DFS(index);
}

bool Dungeon::createRoute(unsigned int startIndex, unsigned int endIndex) {
    if(!rooms.BFSPath(startIndex, endIndex, path))
        return false;
    if(path.getSize() <= 0)
        return false;
    printPath();
    return true;
}

void Dungeon::printPath() {
    path.print();
}