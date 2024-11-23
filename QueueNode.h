#pragma once

template <typename T>
class QueueNode {
public:
    T data;
    QueueNode *next;
    QueueNode(T data) : data(data), next(nullptr) {
    }
};