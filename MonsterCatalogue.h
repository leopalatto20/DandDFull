#pragma once
#include "HashTable.h"
#include "Monster.h"
#define CSV "monsters.csv"
#define HASH_SIZE 100

class MonsterCatalogue {
private:
    HashTable<Monster> catalogue;
    bool isValidNumber(const string &str);
    bool isValidDecimal(const string &str);
    bool addMonster(Monster &monster);
    unsigned int size;
public:
    MonsterCatalogue();
    ~MonsterCatalogue();
    bool loadFromCsv();
    Monster* getMonster();
    void deleteCatalogue();
    void print();
};