#pragma once
#include <iostream>
#include "Spell.h"
#include "DLinkedList.h"

class SpellShop {
private:
    DLinkedList<Spell> spellList;
    bool isValidNumber(const string &str);
public:
    bool loadSpells();
    Spell* buyByNumber(int num);
    void printInOrder();
    bool deleteSpell(Spell &spell);
    void deleteShop();
};