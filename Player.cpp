#include "Player.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Player::Player(string name, string build) : name(name), build(build), maxSpells(0), hp(0), damageMultiplier(1.0) {
}

Player::~Player() {
}

bool Player::loadStats() {
    if(build == "strength") {
        this->maxSpells = 5;
        this->hp = 75;
        this->mp = 100;
        this->defaultAttack = Spell("Lions Claw", 15, 0);
        this->maxHp = 200;
        return true;
    }
    if(build == "dexterity") {
        this->maxSpells = 6;
        this->hp = 60;
        this->mp = 100;
        this->defaultAttack = Spell("Ichimonji", 10, 0);
        this->maxHp = 170;
        return true;
    }
    if(build == "intelligence") {
        this->maxSpells = 10;
        this->hp = 45;
        this->mp = 100;
        this->defaultAttack = Spell("Glintsote Pebble", 3, 0);
        this->maxHp = 120;
        return true;
    }
    return false;
}



void Player::showInfo() {
    cout << "Jugador: " << name << "\n";
    cout << "Clase: " << build << "\n";
    cout << "Hp: " << hp << "\n\n";
    cout << "Ataque default: " << defaultAttack << "\n";
    cout << "Lista de hechizos: \n";
    playerSpells.printInOrder();
    cout << "Monstruos derrotados: \n";
    defeatedMonsters.printInOrder();
}

void Player::showSpells() {
    playerSpells.printInOrder();
    cout << "Ataque default: " << defaultAttack << endl;
}

int Player::getMaxSpells() {
    return this->maxSpells;
}

bool Player::checkForDuplicateSpells(Spell spell) {
    return playerSpells.contains(spell);
}

bool Player::addSpell(Spell &spell) {
    return playerSpells.insertEnd(spell);
}

bool Player::addMonster(Monster &monster) {
    return defeatedMonsters.insertSorted(monster);
}

 int Player::getSpellDamage(int spellNum) {
    if(spellNum == 0)
        return defaultAttack.getDamage();
    Spell *spell = playerSpells.returnFromNumber(spellNum);
    if(!spell)
        return 0;
    int mpCost = spell->getMpCost();
    if(mp - mpCost < 0)
        return 0;
    mp -= spell->getMpCost();
    return spell->getDamage();
}

int Player::getHp() {
    return this->hp;
}

void Player::setHp(int hp) {
    this->hp = hp;
}

int Player::getMp() {
    return this->mp;
}

void Player::setMp(int mp) {
    this->mp = mp;
}

int Player::getMaxHp() {
    return this->maxHp;
}

void Player::setMaxHp(int maxHp) {
    this->maxHp = maxHp;
}

double Player::getDamageMultiplier() {
    return this->damageMultiplier;
}

void Player::setDamageMultiplier(double damageMultiplier) {
    this->damageMultiplier = damageMultiplier;
}