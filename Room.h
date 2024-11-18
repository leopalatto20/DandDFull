#pragma once
#include "Monster.h"

class Room {
public:
    Monster monster;
    Room();
    Room(Monster monster);
    ~Room();
    friend ostream &operator << (ostream &os, Room &room);;
};