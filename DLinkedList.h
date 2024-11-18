#pragma once
#include "DLinkedNode.h"
#include <iostream>

using namespace std;

template <typename T>
class DLinkedList {
private:
    DLinkedNode<T> *head;
public:
    DLinkedList() : head(nullptr) {
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
            return true;
        }
        current->next = newNode;
        newNode->prev = current;
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
            return true;
        }
        if(current->next)
            current->next->prev = current->prev;
        current->prev->next = current->next;
        delete current;
        return true;
    }
    void printInOrder() {
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
    T* returnFromNumber(int num) {
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
    bool contains(T data) {
        DLinkedNode<T> *current = head;
        while(current) {
            if(current->data == data)
                return true;
            current = current->next;
        }
        return false;
    }
    bool insertSorted(T data) {
        DLinkedNode<T> *newNode = new(nothrow) DLinkedNode<T>(data);
        if(!newNode)
            return false;
        if(!head) {
            head = newNode;
            return true;
        }
        if(data < head->data) {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
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
        return true;
    }

    class Iterator {
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
};