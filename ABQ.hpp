#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ();
    explicit ABQ(const size_t capacity);
    ABQ(const ABQ& other);
    ABQ& operator=(const ABQ& rhs);
    ABQ(ABQ&& other) noexcept;
    ABQ& operator=(ABQ&& rhs) noexcept;
    ~ABQ() noexcept override;

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override;
    [[nodiscard]] size_t getMaxCapacity() const noexcept;
    [[nodiscard]] T* getData() const noexcept;

    // Insertion
    void enqueue(const T& data) override;

    // Access
    T peek() const override;

    // Deletion
    T dequeue() override;

    void PrintForward() const;
    void PrintReverse() const;

};



template<typename T>
ABQ<T>::ABQ() : capacity_(1), curr_size_(0), array_(new T[capacity_]) {}

template<typename T>
ABQ<T>::ABQ(const size_t capacity) : capacity_(capacity), curr_size_(0), array_(new T[capacity_]) {}

template<typename T>
ABQ<T>::ABQ(const ABQ<T>& other) : capacity_(other.capacity_), curr_size_(other.curr_size_), array_(new T[other.capacity_]) {
    for (int i = 0; i < curr_size_; i++) {
        array_[i] = other.array_[i];
    }
}

template<typename T>
ABQ<T>& ABQ<T>::operator=(const ABQ<T>& rhs) {
    if (this != &rhs) {
        delete[] array_;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = new T[capacity_];
        for (int i = 0; i < curr_size_; i++) {
            array_[i] = rhs.array_[i];
        }
    }
    return *this;
}

template<typename T>
ABQ<T>::ABQ(ABQ<T>&& other) noexcept : capacity_(other.capacity_), curr_size_(other.curr_size_), array_(other.array_) {
    other.array_ = nullptr;
    other.curr_size_ = 0;
    other.capacity_ = 0;
}

template<typename T>
ABQ<T>& ABQ<T>::operator=(ABQ<T>&& rhs) noexcept {
    if (this != &rhs) {
        delete[] array_;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = rhs.array_;
        rhs.array_ = nullptr;
        rhs.curr_size_ = 0;
        rhs.capacity_ = 0;
    }
    return *this;
}

template<typename T>
ABQ<T>::~ABQ() noexcept {
    delete[] array_;
}

template<typename T>
size_t ABQ<T>::getSize() const noexcept { 
    return curr_size_; 
}

template<typename T>
size_t ABQ<T>::getMaxCapacity() const noexcept { 
    return capacity_; 
}

template<typename T>
T* ABQ<T>::getData() const noexcept { 
    return array_; 
}

template<typename T>
void ABQ<T>::enqueue(const T& data) {
    // resize if needed
    if (curr_size_ >= capacity_) {
        int new_capacity = capacity_ * scale_factor_;
        if (new_capacity < 1) new_capacity = 1;
        T* new_array = new T[new_capacity];
        for (int i = 0; i < curr_size_; i++) {
            new_array[i] = array_[i];
        }
        delete[] array_;
        array_ = new_array;
        capacity_ = new_capacity;
    }

    array_[curr_size_] = data;
    curr_size_++;
}

template<typename T>
T ABQ<T>::peek() const {
    if (curr_size_ == 0) 
        throw std::runtime_error("cannot peek empty queue");
    return array_[0];
}

template<typename T>
T ABQ<T>::dequeue() {
    if (curr_size_ == 0) 
        throw std::runtime_error("cannot dequeue empty queue");
    T item = array_[0];
    for (int i = 1; i < curr_size_; i++)
        array_[i - 1] = array_[i];
    curr_size_--;

    // sparse case
    if (curr_size_ <= capacity_ / 4) {
        int new_capacity = capacity_ / scale_factor_;
        if (new_capacity < 1) new_capacity = 1;
        T* new_array = new T[new_capacity];
        for (int i = 0; i < curr_size_; i++) new_array[i] = array_[i];
        delete[] array_;
        array_ = new_array;
        capacity_ = new_capacity;
    }

    return item;
}

template<typename T>
void ABQ<T>::PrintForward() const {
    for (int i = 0; i < curr_size_; i++) {
        std::cout << array_[i] << " \n"[i == curr_size_ - 1];
    }
}

template<typename T>
void ABQ<T>::PrintReverse() const {
    for (int i = curr_size_ - 1; i >= 0; i--) {
        std::cout << array_[i] << " \n"[i == 0];
    }
}
