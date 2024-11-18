#include "MonsterCatalogue.h"
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

MonsterCatalogue::MonsterCatalogue() : size(0){
}
MonsterCatalogue::~MonsterCatalogue() {
    deleteCatalogue();
}
void MonsterCatalogue::deleteCatalogue() {
    catalogue.deleteTable();
    size = 0;
}
bool MonsterCatalogue::addMonster(Monster &monster) {
    if(catalogue.insert(monster)) {
        size++;
        return true;
    }
    return false;
}
bool MonsterCatalogue::loadFromCsv() {
    if(!catalogue.createTable(HASH_SIZE, &Monster::hashMonster))
        return false;
    ifstream file(CSV);

    if(!file.is_open()) {
        return false;
    }
    string line;
    if(!getline(file, line)) { //Saltar la primer linea
        return false;
    }
    while(getline(file, line)) {
        string name, type, size, align, cell;
        double cr;
        int ac, hp;
        stringstream ss(line);
        int count(0);

        while(getline(ss, cell, ',')) {
            switch(count) {
                case 0: {
                    name = cell;
                    break;
                }
                case 1: {
                    if(!isValidDecimal(cell))
                        return false;
                    cr = stod(cell);
                    break;
                }
                case 2: {
                    type = cell;
                    break;
                }
                case 3: {
                    size = cell;
                    break;
                }
                case 4: {
                    if(!isValidNumber(cell))
                        return false;
                    ac = stoi(cell);
                    break;
                }
                case 5: {
                    if(!isValidNumber(cell))
                        return false;
                    hp = stoi(cell);
                    break;
                }
                case 6: {
                    align = cell;
                    break;
                }
                default: {
                    return false;
                }
            }
            count++;
        }
        Monster monster(name, cr, type, size, ac, hp, align);
        if(!addMonster(monster))
            return false;
    }
    file.close();
    return true;
}
Monster* MonsterCatalogue::getMonster() {
    Monster *foundMonster = catalogue.generateRandom();
    if(!foundMonster)
        return nullptr;
    return foundMonster;
}
bool MonsterCatalogue::isValidNumber(const string &str) {
    for(int i = 0; i < str.length(); i++) {
        if(!isdigit(str[i]))
            return false;
    }
    return true;
}
bool MonsterCatalogue::isValidDecimal(const string &str) {
    int decimalCount = 0;
    for(int i = 0; i < str.length(); i++) {
        if(str[i] == '.')
            decimalCount++;
        else if(!isdigit(str[i]))
            return false;
    }
    if(decimalCount > 1)
        return false;
    return true;
}
void MonsterCatalogue::print() {
    catalogue.print();
}