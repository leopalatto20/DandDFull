#pragma once
#include "Vertex.h"
#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
class Graph {
private:
    unsigned int size;
    Vertex<T> *vertexes;
public:
    Graph() : vertexes(nullptr), size(0) {
    }
    ~Graph() {
        deleteGraph();
    }
    void deleteGraph() {
        if(vertexes) {
            delete[] vertexes;
            vertexes = nullptr;
            size = 0;
        }
    }
    bool createGraph(unsigned int size) {
        if(vertexes || !size)
            return false;
        vertexes = new(nothrow) Vertex<T>[size];
        if(!vertexes)
            return false;
        this->size = size;
        return true;
    }
    bool setVertex(unsigned int index, T data) {
        if(index >= size)
            return false;
        vertexes[index].data = data;
        return true;
    }
    bool connect(unsigned int vertex1, unsigned int vertex2) {
        if(vertex1 >= size || vertex2 >= size)
            return false;
        if(!vertexes)
            return false;
        if(vertexes[vertex1].adjacents.contains(vertex2))
            return false;
        if(!vertexes[vertex1].connect(vertex2))
            return false;
        return true;
    }
    bool disconnect(unsigned int vertex1, unsigned int vertex2) {
        if(!vertexes)
            return false;
        if(!vertexes[vertex1].adjacents.contains(vertex2))
            return false;
        if(!vertexes[vertex1].adjacents.deleteData(vertex2))
            return false;
        return true;
    }
    void print() {
        for(unsigned int i = 0; i < size; i++) {
            cout << "[" << i << "]" << vertexes[i].data << ": ";
            vertexes[i].adjacents.print();
        }
    }
    int getSize() {
        return this->size;
    }
};