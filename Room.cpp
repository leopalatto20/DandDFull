#include "Room.h"

Room::Room() {
}
Room::Room(Monster monster) : monster(monster) {
}

Room::~Room() {
}

ostream &operator<<(ostream &os, Room &room) {
    os << "Cuarto con: " << room.monster << "| conectado con cuartos: ";
    return os;
}