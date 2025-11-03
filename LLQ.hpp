#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ();

    // Insertion
    void enqueue(const T& item) override;

    // Deletion
    T dequeue() override;

    // Access
    T peek() const override;

    // Getter
    std::size_t getSize() const noexcept override;

    void PrintForward() const;
    void PrintReverse() const;

};

template <typename T>
LLQ<T>::LLQ() : list() {}

template <typename T>
void LLQ<T>::enqueue(const T& item) { list.addTail(item); }

template <typename T>
T LLQ<T>::dequeue() {
    if (list.getCount() == 0) {
        throw std::runtime_error("LLQ is empty");
    }
    T item = list.getHead()->data;
    list.removeHead();
    return item;
}

template <typename T>
T LLQ<T>::peek() const {
    if (list.getCount() == 0) {
        throw std::runtime_error("LLQ is empty");
    }
    return list.getHead()->data;
}

template <typename T>
std::size_t LLQ<T>::getSize() const noexcept {
    return list.getCount();
}

template <typename T>
void LLQ<T>::PrintForward() const {
    list.printForward();
}

template <typename T>
void LLQ<T>::PrintReverse() const {
    list.printReverse();
}
