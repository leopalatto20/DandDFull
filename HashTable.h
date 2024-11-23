#pragma once
#include "AvlTree.h"
#include <iostream>
#include <ctime>

using namespace std;

template <typename T>
class HashTable {
public:
    using HashFunction = unsigned int (*)(T&, unsigned int tableSize);
    HashTable() : table(nullptr), size(0), hashFunction(nullptr) {
    }
    ~HashTable() {
        deleteTable();
    }
    void deleteTable() {
        if(table) {
            delete[] table;
            table = nullptr;
            hashFunction = nullptr;
            size = 0;
        }
    }
    bool createTable(unsigned int size, HashFunction hashFunction) {
        if(table || !size || !hashFunction)
            return false;
        table = new(nothrow) AvlTree<T>[size];
        if(!table)
            return false;
        this->size = size;
        this->hashFunction = hashFunction;
        return true;
    }
    bool insert(T data) {
        if(!table)
            return false;
        unsigned int hashValue = getIndex(data);
        if(hashValue >= size)
            return false;
        return table[hashValue].insert(data);
    }
    bool deleteData(T data) {
        if(!table)
            return false;
        unsigned int hashValue = getIndex(data);
        if(hashValue >= size)
            return false;
        return table[hashValue].deleteData(data);
    }
    T* search(T data) {
        if(!table)
            return nullptr;
        unsigned int hashValue = getIndex(data);
        if(hashValue >= size)
            return nullptr;
        return table[hashValue].search(data);
    }
    void print() {
        unsigned int longest = 0;
        for(unsigned int i = 0; i < size; i++) {
            if(table[i].getSize() > longest)
                longest = table[i].getSize();
            cout << "Table[" << i << "]: " << table[i].getSize() << endl;
        }
        cout << "Biggest was: " << longest << endl;
    }
    T* generateRandom() {
        unsigned int randIndex = rand() % size;
        while(table[randIndex].getSize() <= 0)
            randIndex++; //si el arbol que se genero no tiene elementos, pasamos al siguiente
        unsigned int randItem = 1 + rand() % table[randIndex].getSize();
        return table[randIndex].searchInOrder(randItem);
    }
private:
    AvlTree<T> *table;
    unsigned int size;
    HashFunction hashFunction;
    unsigned int getIndex(T data) {
        if(!hashFunction)
            return size + 1; //damos un valor invalido que no es negativo para respetar el unsigned int
        return hashFunction(data, size);
    }
};