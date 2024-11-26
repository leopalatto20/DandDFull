#include "Dungeon.h"

Dungeon::Dungeon() : currentRoom(0){
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

bool Dungeon::DFS(unsigned int index) {
    return rooms.DFS(index);
}
bool Dungeon::BFS(unsigned int index) {
    return rooms.BFS(index);
}

bool Dungeon::createRoute(unsigned int startIndex, unsigned int endIndex) {
    if(!rooms.BFSPath(startIndex, endIndex, path))
        return false;
    if(path.getSize() <= 0)
        return false;
    printPath();
    this->currentRoom = startIndex;
    return true;
}

void Dungeon::printPath() {
    path.print();
}

Room* Dungeon::currentRoomPath() {
    return rooms.getFromIndex(currentRoom);
}

bool Dungeon::goForward() {
    if (path.getSize() > 0) {
        auto it = path.begin();  // Inicializamos el iterador al inicio de la lista

        // Avanzamos hasta encontrar currentRoom en la lista
        while (it != path.end() && *it != currentRoom) {
            ++it;
        }

        // Si encontramos currentRoom, avanzamos al siguiente cuarto
        if (it != path.end()) {
            ++it;

            // Vemos si todavia se puede avanzar
            if (it != path.end()) {
                currentRoom = *it;
                return true;
            }
        }
    }
    return false;
}