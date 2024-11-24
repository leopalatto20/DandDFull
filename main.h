#pragma once
#include "MonsterCatalogue.h"
#include "Dungeon.h"
#include "Player.h"
#include "SpellShop.h"
#include <ctime>

using namespace std;

unsigned int getNumericInput();
bool isValidNumber(const string &str);
bool buySpells(Player &player, SpellShop &spellShop);
bool fightMonster(Player &player, Monster &monster);
void healPlayer(Player &player);
void levelPlayerUp(Player &player);
int d10Roll();
int twoD20Roll();