#pragma once
#include "DLinkedNode.h"
#include <iostream>

using namespace std;

template <typename T>
class DLinkedList {
private:
    DLinkedNode<T> *head;
    unsigned int size;
public:
    DLinkedList() : head(nullptr), size(0) {
    }
    ~DLinkedList() {
        deleteList();
    }
    void deleteList() {
        DLinkedNode<T> *current = head;
        while(current) {
            DLinkedNode<T> *temp = current->next;
            delete current;
            current = temp;
        }
        head = nullptr;
        size = 0;
    }
    bool insertEnd(T data) {
        DLinkedNode<T> *newNode = new(nothrow) DLinkedNode<T>(data);
        if(!newNode)
            return false;
        DLinkedNode<T> *current = head;
        while(current && current->next) {
            current = current->next;
        }
        if(!current) {
            head = newNode;
            size++;
            return true;
        }
        current->next = newNode;
        newNode->prev = current;
        size++;
        return true;
    }
    bool insertStart(T data) {
        DLinkedNode<T> *newNode = new(nothrow) DLinkedNode<T>(data);
        if(!newNode)
            return false;
        newNode->next = head;
        if(head) {
            head->prev = newNode;
        }
        head = newNode;
        size++;
        return true;
    }
    bool deleteData(T data) {
        DLinkedNode<T> *current = head;
        while(current && current->data != data) {
            current = current->next;
        }
        if(!current)
            return false;
        if(current == head) {
            DLinkedNode<T> *temp = head;
            head = head->next;
            delete temp;
            size--;
            return true;
        }
        if(current->next)
            current->next->prev = current->prev;
        current->prev->next = current->next;
        delete current;
        size--;
        return true;
    }
    void printInOrder() { //Mostrar la lista ligada en orden y con numeracion
        DLinkedNode<T> *current = head;
        int count(1);
        while(current) {
            cout << count << ". " << current->data << endl;
            current = current->next;
            count++;
        }
        cout << endl;
    }
    void print() {
        DLinkedNode<T> *current = head;
        while(current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
    T* returnFromNumber(unsigned int num) { //Recibe un numero y regresa el elemento que esta en ese indice
        unsigned int count(1);
        DLinkedNode<T> *current = head;
        while(current) {
            if(count == num)
                return &current->data;
            count++;
            current = current->next;
        }
        return nullptr;
    }
    bool contains(T data) { //Revisa si el elemento esta en la lista ligada
        DLinkedNode<T> *current = head;
        while(current) {
            if(current->data == data)
                return true;
            current = current->next;
        }
        return false;
    }
    bool insertSorted(T data) { //Inserta el dato en orden
        DLinkedNode<T> *newNode = new(nothrow) DLinkedNode<T>(data);
        if(!newNode)
            return false;
        if(!head) {
            head = newNode;
            size++;
            return true;
        }
        if(data < head->data) {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            size++;
            return true;
        }
        DLinkedNode<T> *current = head;
        while(current->next && current->next->data < data) {
            current = current->next;
        }
        newNode->next = current->next;
        newNode->prev = current->prev;
        if(current->next)
            current->next->prev = newNode;
        current->next = newNode;
        size++;
        return true;
    }

    class Iterator { //Iterador para listas ligadas
    public:
        Iterator(DLinkedNode<T> *node) : current(node) {
        }
        T& operator * () {
            return current->data;
        }
        Iterator& operator ++ () {
            if(current)
                current = current->next;
            return * this;
        }
        bool operator == (const Iterator &other) const {
            return current == other.current;
        }
        bool operator != (const Iterator &other) const {
            return current != other.current;
        }
    private:
        DLinkedNode<T> *current;
    };
    Iterator begin() {
        return Iterator(head);
    }
    Iterator end() {
        return Iterator(nullptr);
    }
    unsigned int getSize() { //Regresa el tamaño para cuando se necesite saberlo
        return this->size;
    }
};