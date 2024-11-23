#pragma once
#include "Vertex.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Stack.h"
#include "Queue.h"

using namespace std;

template <typename T>
class Graph {
private:
    unsigned int size;
    Vertex<T> *vertexes;
    void clearVisited() {
        for(unsigned int i = 0; i < size; i++)
            for(auto connection : vertexes[i].adjacents)
                vertexes[connection].visited = false;
    }
    bool isValidNumber(const string &str) {
        for(int i = 0; i < str.length(); i++) {
            if(!isdigit(str[i]))
                return false;
        }
        return true;
    }
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
        return vertexes[vertex1].connect(vertex2);
    }
    bool disconnect(unsigned int vertex1, unsigned int vertex2) {
        if(!vertexes)
            return false;
        if(!vertexes[vertex1].adjacents.contains(vertex2))
            return false;
        return vertexes[vertex1].adjacents.deleteData(vertex2);
    }
    void print() {
        for(unsigned int i = 0; i < size; i++) {
            cout << "[" << i << "]" << vertexes[i].data << ": ";
            vertexes[i].adjacents.print();
        }
    }
    unsigned int getSize() {
        return this->size;
    }

    bool createFromCSV(const string &fileName) {
        ifstream file(fileName);
        if(!file.is_open())
            return false;
        string line;
        getline(file, line);
        if(line != "Grafo") {
            cerr << "El archivo no es un grafo.\n";
            return false;
        }
        if(!getline(file, line)) {
            cerr << "El archivo no contiene el tamaño del grafo.\n";
            return false;
        }
        stringstream ss(line);
        unsigned int size;
        string numStr;
        ss >> numStr;
        if(!isValidNumber(numStr))
            return false;
        size = stoi(numStr);
        if(!createGraph(size))
            return false;
        unsigned int vertexIndex = 0;
        while(getline(file, line)) {
            stringstream ss(line);
            unsigned int adjacentVertex;
            while(ss >> numStr) {
                if(!isValidNumber(numStr))
                    return false;
                adjacentVertex = stoi(numStr);
                if(!connect(vertexIndex, adjacentVertex))
                    return false;
            }
            vertexIndex++;
        }
        file.close();
        return true;
    }
    T* getFromIndex(unsigned int index) {
        if(!vertexes)
            return nullptr;
        if(index >= size)
            return nullptr;
        return &vertexes[index].data;
    }
    bool DFS(unsigned int startVertex) {
        Stack<unsigned int> stack;
        if(!size || startVertex >= size)
            return false;
        clearVisited();
        cout << "DFS: (" << startVertex << "): ";
        if(!stack.push(startVertex))
            return false;
        vertexes[startVertex].visited = true;

        while(!stack.isEmpty()) {
            unsigned int currentVertex = *stack.getTop();
            cout << currentVertex << " ";
            stack.pop();

            for(auto connection : vertexes[currentVertex].adjacents) {
                if(!vertexes[connection].visited) {
                    if(!stack.push(connection))
                        return false;
                    vertexes[connection].visited = true;
                }
            }
        }
        cout << endl;
        return true;
    }
    bool BFS(unsigned int startVertex) {
        Queue<unsigned int> queue;
        if(!size || startVertex >= size)
            return false;
        clearVisited();
        cout << "BFS: (" << startVertex << "): ";
        if(!queue.enqueue(startVertex))
            return false;
        vertexes[startVertex].visited = true;

        while(!queue.isEmpty()) {
            unsigned int currentVertex = *queue.getFront();
            cout << currentVertex << " ";
            queue.dequeue();

            for(auto connection : vertexes[currentVertex].adjacents) {
                if(!vertexes[connection].visited) {
                    if(!queue.enqueue(connection))
                        return false;
                    vertexes[connection].visited = true;
                }
            }
        }
        cout << endl;
        return true;
    }
};