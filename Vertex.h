#pragma once
#include "DLinkedList.h"

template <typename T>
class Vertex {
public:
    T data;
    bool visited;
    DLinkedList<unsigned int> adjacents;
    Vertex() : visited(false) {
    }
    bool connect(unsigned int &vertex) {
        return adjacents.insertEnd(vertex);
    }
    bool disconnect(unsigned int &vertex) {
        return adjacents.deleteData(vertex);
    }
};