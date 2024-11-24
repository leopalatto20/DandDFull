#pragma once
#include "AvlNode.h"
#include <iostream>

using namespace std;

template <typename T>
class AvlTree {
private:
    AvlNode<T> *root;
    unsigned int size; //Se lleva registro del tamaño para no tener que calcularlo todo el tiempo
    int max(int num1, int num2) {
        if(num1 > num2)
            return num1;
        return num2;
    }
    int getFe(AvlNode<T> *node) {
        if(!node)
            return -1;
        return node->fe;
    }
    int getBalance(AvlNode<T> *node) {
        if(!node)
            return -1;
        return getFe(node->left) - getFe(node->right);
    }
    void balance(AvlNode<T> *&node) {
        int balance = getBalance(node);
        if(balance > 1) {
            int feLeft = getBalance(node->left);
            if(feLeft >= 0)
                node = rightRotate(node);
            else
                node = doubleRightRotate(node);
        }
        if(balance < -1) {
            int feRight = getBalance(node->right);
            if(feRight <= 0)
                node = leftRotate(node);
            else
                node = doubleLeftRotate(node);
        }
    }
    AvlNode<T>* rightRotate(AvlNode<T> *&node) {
        AvlNode<T> *newRoot = node->left;
        AvlNode<T> *temp = newRoot->right;
        newRoot->right = node;
        node->left = temp;
        return newRoot;
    }
    AvlNode<T>* leftRotate(AvlNode<T> *&node) {
        AvlNode<T> *newRoot = node->right;
        AvlNode<T> *temp = newRoot->left;
        newRoot->left = node;
        node->right = temp;
        return newRoot;
    }
    AvlNode<T>* doubleRightRotate(AvlNode<T> *&node) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    AvlNode<T>* doubleLeftRotate(AvlNode<T> *&node) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    void deleteTreeRec(AvlNode<T> *&node) {
        if(!node)
            return;
        deleteTreeRec(node->left);
        deleteTreeRec(node->right);
        delete node;
        node = nullptr;
    }
    bool insertRec(AvlNode<T> *&node, T data) {
        if(!node) {
            node = new(nothrow) AvlNode<T>(data);
            if(!node)
                return false;
            return true;
        }
        if(data < node->data) {
            if(insertRec(node->left, data)) {
                node->fe = 1 + max(getFe(node->left), getFe(node->right));
                balance(node);
                return true;
            }
            return false;
        }
        if(data > node->data) {
            if(insertRec(node->right, data)) {
                node->fe = 1 + max(getFe(node->left), getFe(node->right));
                balance(node);
                return true;
            }
            return false;
        }
        return false;
    }
    bool deleteDataRec(AvlNode<T> *&node, T data) {
        if(!node)
            return false;
        if(data < node->data) {
            if(!deleteDataRec(node->left, data))
                return false;
        }
        else if(data > node->data) {
            if(!deleteDataRec(node->right, data))
                return false;
        }
        else {
            if(!node->left)
                node = node->right;
            else if(!node->right)
                node = node->left;
            else {
                AvlNode<T> *temp = replaceLeft(node->left);
                node->data = temp->data;
                delete temp;
            }
        }
        if(node) {
            node->fe = 1 + max(getFe(node->left), getFe(node->right));
            balance(node);
        }
        return true;
    }
    AvlNode<T>* replaceLeft(AvlNode<T> *&node) { //El eliminar reemplaza por la izquierda
        if(node->right)
            return replaceLeft(node->right);
        AvlNode<T> *temp = node;
        node = node->left;
        return temp;
    }
    T* searchRec(AvlNode<T> *node, T data) { //Busqueda pre-order para buscar datos en el arbol
        if(!node)
            return nullptr;
        if(node->data == data)
            return &node->data;
        if(data < node->data)
            return searchRec(node->left, data);
        return searchRec(node->right, data);
    }
    T* searchInOrderRec(AvlNode<T> *node, int numToSearch, int &counter) { //Busqueda in order para buscar datos en un inidice especifico del arbol
        if(!node)
            return nullptr;
        T* leftResult = searchInOrderRec(node->left, numToSearch, counter);
        if(leftResult)
            return leftResult;

        counter++;
        if(counter == numToSearch) {
            return &node->data;
        }
        return searchInOrderRec(node->right, numToSearch, counter);
    }
    void printInOrderRec(AvlNode<T> *node) { //Recorrido in order
        if(!node)
            return;
        printInOrderRec(node->left);
        cout << node->data << endl;
        printInOrderRec(node->right);
    }
public:
    AvlTree() : root(nullptr) , size(0) {
    }
    ~AvlTree() {
        deleteTree();
    }
    void deleteTree() {
        deleteTreeRec(root);
        size = 0;
    }
    bool insert(T data) {
        if(insertRec(root, data)) {
            size++;
            return true;
        }
        return false;
    }
    bool deleteData(T data) {
        if(deleteDataRec(root, data)) {
            size--;
            return true;
        }
        return false;
    }
    T* search(T data) {
        return searchRec(root, data);
    }
    unsigned int getSize() {
        return this->size;
    }
    T* searchInOrder(int numToSearch) {
        int counter(0);
        return(searchInOrderRec(root, numToSearch, counter));
    }
    void printInOrder() {
        printInOrderRec(root);
    }
};