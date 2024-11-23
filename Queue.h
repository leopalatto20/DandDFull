#pragma once
#include "QueueNode.h"
#include <new>

using namespace std;

template <typename T>
class Queue {
private:
    QueueNode<T> *front;
    QueueNode<T> *back;
public:
    Queue() : front(nullptr), back(nullptr) {
    }
    ~Queue() {
        deleteQueue();
    }
    void deleteQueue() {
        QueueNode<T> *current = front;
        while(current) {
            QueueNode<T> *temp = current->next;
            delete current;
            current = temp;
        }
        front = nullptr;
        back = nullptr;
    }
    bool enqueue(T data) {
        QueueNode<T> *newNode = new(nothrow) QueueNode<T>(data);
        if(!newNode)
            return false;
        if(!front) {
            front = newNode;
            back = newNode;
            return true;
        }
        back->next = newNode;
        back = newNode;
        return true;
    }
    bool dequeue() {
        if(!front)
            return false;
        if(front == back) {
            delete front;
            front = nullptr;
            back = nullptr;
            return true;
        }
        QueueNode<T> *temp = front->next;
        delete front;
        front = temp;
        return true;
    }
    T* getFront() {
        if(!front)
            return nullptr;
        return &front->data;
    }
    bool isEmpty() {
        return !front;
    }
    bool priorityQueue(T data) {
        QueueNode<T> *newNode = new(nothrow) QueueNode<T>(data);
        if(!newNode)
            return false;
        if(!front) {
            front = newNode;
            back = newNode;
            return true;
        }
        newNode->next = front;
        front = newNode;
        return true;
    }
};