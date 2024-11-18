#pragma once

template <typename T>
class DLinkedNode {
public:
    T data;
    DLinkedNode *next;
    DLinkedNode *prev;
    DLinkedNode(T data) : data(data), next(nullptr) , prev(nullptr) {
    }
};