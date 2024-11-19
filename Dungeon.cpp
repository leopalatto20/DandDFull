#include "Dungeon.h"

Dungeon::Dungeon() {
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

void Dungeon::recursiveDFS(unsigned int index) {
    rooms.recursiveDFS(index);
}
