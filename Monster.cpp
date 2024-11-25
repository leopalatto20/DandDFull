#include "Monster.h"
#include <iostream>

using namespace std;

Monster::Monster() : name(" "), cr(0.0), type(" "), size(" "), ac(0), hp(0), align(" ") {
}

Monster::Monster(string name, double cr, string type, string size, int ac, int hp, string align) : name(name), cr(cr), type(type), size(size), ac(ac), hp(hp), align(align){
}

Monster::~Monster() {
}

bool Monster::operator < (Monster &monster) {
    return this->name < monster.name;
}

bool Monster::operator > (Monster &monster) {
    return this->name > monster.name;
}

bool Monster::operator == (Monster &monster) {
    return this->name == monster.name;
}

bool Monster::operator<=(Monster &monster) {
    return this->name <= monster.name;
}


int Monster::getAc() {
    return this->ac;
}

string Monster::getName() {
    return this->name;
}

ostream &operator <<(ostream &os, Monster &monster) {
    os << monster.name;
    return os;
}

int Monster::getHp() {
    return this->hp;
}

void Monster::setHp(int hp) {
    this->hp = hp;
}

string Monster::getType() {
    return this->type;
}

unsigned int Monster::hashMonster(Monster &monster, unsigned int tableSize) {
    string str;
    const int base = 53;
    unsigned int hashValue = 0, size = 0;
    str = monster.getName();
    size = str.size();
    for(unsigned int i = 0; i < size; i++)
        hashValue = hashValue * base + str[i];
    str = monster.getType();
    size = str.size();
    for(unsigned int i = 0; i < size; i++)
        hashValue = hashValue * base + str[i];
    hashValue = hashValue * base + monster.getHp();
    hashValue = hashValue * base + monster.getAc();
    return hashValue % tableSize;
}