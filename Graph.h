#pragma once
#include <climits>

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
            vertexes[i].visited = false;
    }
    bool isValidNumber(const string &str) {
        for(int i = 0; i < str.length(); i++) {
            if(!isdigit(str[i]))
                return false;
        }
        return true;
    }
    DLinkedList<unsigned int> path;
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

    bool BFSPath(unsigned int startVertex, unsigned int endVertex, DLinkedList<unsigned int>& path) {
        Queue<unsigned int> queue;
        if(!size || startVertex >= size || endVertex >= size)
            return false;

        clearVisited();

        unsigned int *previous = new(nothrow) unsigned int[size];
        if(!previous)
            return false;
        for(unsigned int i = 0; i < size;  i++) {
            previous[i] = UINT_MAX;
        }
        if(!queue.enqueue(startVertex)) {
            delete[] previous;
            return false;
        }
        vertexes[startVertex].visited = true;

        while(!queue.isEmpty()) {
            unsigned int currentVertex = *queue.getFront();
            queue.dequeue();

            for(auto connection : vertexes[currentVertex].adjacents) {
                if(!vertexes[connection].visited) {
                    if(!queue.enqueue(connection)) {
                        delete[] previous;
                        return false;
                    }
                    vertexes[connection].visited = true;
                    previous[connection] = currentVertex;
                    if(connection == endVertex) {
                        Stack<unsigned int> stack;

                        unsigned int current = endVertex;
                        while(current != UINT_MAX) {
                            stack.push(current);
                            current = previous[current];
                        }
                        while(!stack.isEmpty()) {
                            path.insertEnd(*stack.getTop());
                            stack.pop();
                        }
                        delete[] previous;
                        return true;
                    }
                }
            }
        }
        delete[] previous;
        return false;
    }
};