#pragma once

template <typename T>
class StackNode {
public:
    T data;
    StackNode *next;
    StackNode(T data) : data(data), next(nullptr) {
    }
};