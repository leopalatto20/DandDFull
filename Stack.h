#pragma once
#include <new>
#include "StackNode.h"

using namespace std;

template <typename T>
class Stack {
private:
    StackNode<T> *top;
public:
    Stack() : top(nullptr) {
    }
    ~Stack() {
        deleteStack();
    }
    void deleteStack() {
        StackNode<T> *current = top;
        while(current) {
            StackNode<T> *temp = current->next;
            delete current;
            current = temp;
        }
        top = nullptr;
    }
    bool isEmpty() {
        return !top;
    }
    bool push(T data) {
        StackNode<T> *newNode = new(nothrow) StackNode<T>(data);
        if(!newNode)
            return false;
        newNode->next = top;
        top = newNode;
        return true;
    }
    bool pop() {
        if(!top)
            return false;
        StackNode<T> *temp = top;
        top = temp->next;
        delete temp;
        return true;
    }
    T* getTop() {
        if(!top)
            return nullptr;
        return &top->data;
    }
};