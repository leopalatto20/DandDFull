#pragma once
#include <iostream>

using namespace std;

class Spell {
private:
    string name;
    int damage;
    int mpCost;
public:
    Spell();
    ~Spell();
    Spell(string name, int damage, int mpCost);
    friend ostream &operator << (ostream &os, Spell &spell);
    bool operator == (Spell &spell);
    bool operator != (Spell &spell);
    bool operator < (Spell &spell);
    int getMpCost();
    int getDamage();
};