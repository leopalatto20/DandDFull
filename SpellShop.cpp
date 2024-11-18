#include "SpellShop.h"
#include <fstream>
#include <sstream>
#define SPELLS "Spells.csv"

using namespace std;

bool SpellShop::loadSpells() {
    ifstream file(SPELLS);

    if(!file.is_open()) {
        return false;
    }

    string line;

    if(!getline(file, line)) {
        file.close();
        return false;
    }

    while(getline(file, line)) {
        string cell, name;
        int damage, count(0), mpCost;
        stringstream ss(line);

        while(getline(ss, cell, ',')) {
            switch(count) {
                case 0: {
                    name = cell;
                    break;
                }
                case 1: {
                    if(!isValidNumber(cell))
                        return false;
                    damage = stoi(cell);
                    break;
                }
                case 2: {
                    if(!isValidNumber(cell))
                        return false;
                    mpCost = stoi(cell);
                    break;
                }
                default: {
                    return false;
                }
            }
            count++;
        }
        Spell spell(name, damage, mpCost);
        spellList.insertEnd(spell);
    }
    file.close();
    return true;
}

void SpellShop::printInOrder() {
    spellList.printInOrder();
}

Spell* SpellShop::buyByNumber(int num) {
    return spellList.returnFromNumber(num);
}

bool SpellShop::deleteSpell(Spell &spell) {
    return spellList.deleteData(spell);
}

bool SpellShop::isValidNumber(const string &str) {
    for(int i = 0; i < str.length(); i++) {
        if(!isdigit(str[i]))
            return false;
    }
    return true;
}

void SpellShop::deleteShop() {
    spellList.deleteList();
}