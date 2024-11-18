#pragma once

template <typename T>
class AvlNode {
public:
    int fe;
    T data;
    AvlNode *left;
    AvlNode *right;
    AvlNode(T data) : data(data), left(nullptr), right(nullptr), fe(0) {
    }
};