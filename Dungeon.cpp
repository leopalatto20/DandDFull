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

bool Dungeon::createDungeon() {
    ifstream file(DUNGEON);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo." << endl;
        return false;
    }

    string line;
    getline(file, line);
    if (line != "Grafo") {
        cerr << "El archivo no es un Grafo" << endl;
        return false;
    }

    unsigned int size;
    getline(file, line);
    stringstream ss(line);
    ss >> size;

    if (size == 0) {
        return false;
    }

    if (!rooms.createGraph(size)) {
        return false;
    }

    unsigned int vertexIndex = 0;
    while (getline(file, line)) {
        stringstream ss(line);

        int adjacentVertex;
        while (ss >> adjacentVertex) {
            if (!rooms.connect(vertexIndex, adjacentVertex)) {
                return false;
            }
        }
        vertexIndex++;
    }

    file.close();
    return true;
}

unsigned int Dungeon::getSize() {
    return rooms.getSize();
}