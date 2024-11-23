#pragma once
#include <iostream>
#include "Spell.h"
#include "MonsterCatalogue.h"
#include "DLinkedList.h"

using namespace std;

class Player {
private:
    string name;
    string build;
    DLinkedList<Monster> defeatedMonsters;
    DLinkedList<Spell> playerSpells;
    Spell defaultAttack;
    int maxSpells;
    int hp;
    int mp;
    int maxHp;
    double damageMultiplier;
public:
    Player(string name, string build);
    ~Player();
    void showInfo();
    void showSpells();
    int getMaxSpells();
    bool checkForDuplicateSpells(Spell spell);
    bool addSpell(Spell &spell);
    bool loadStats();
    bool addMonster(Monster &monster);
    int getSpellDamage(unsigned int spellNum);
    int getHp();
    void setHp(int hp);
    int getMp();
    void setMp(int mp);
    int getMaxHp();
    void setMaxHp(int maxHp);
    double getDamageMultiplier();
    void setDamageMultiplier(double damageMultiplier);
};