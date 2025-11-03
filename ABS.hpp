#pragma once

#include <cstddef>
#include <stdexcept>
#include <iostream>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS();
    explicit ABS(const size_t capacity);
    ABS(const ABS& other);
    ABS& operator=(const ABS& rhs);
    ABS(ABS&& other) noexcept;
    ABS& operator=(ABS&& rhs) noexcept;
    ~ABS() noexcept override;

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override;

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept;

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept;

    // Push item onto the stack
    void push(const T& data) override;

    T peek() const override;

    T pop() override;

    void PrintForward() const;
    void PrintReverse() const;

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};

template<typename T>
ABS<T>::ABS() : capacity_(1), curr_size_(0), array_(new T[capacity_]) {}

template<typename T>
ABS<T>::ABS(const size_t capacity) : capacity_(capacity), curr_size_(0), array_(new T[capacity_]) {}

template<typename T>
ABS<T>::ABS(const ABS<T>& other) : capacity_(other.capacity_), curr_size_(other.curr_size_), array_(new T[other.capacity_]) {
    for (int i = 0; i < curr_size_; i++) {
        array_[i] = other.array_[i];
    }
}

template<typename T>
ABS<T>& ABS<T>::operator=(const ABS<T>& rhs) {
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
ABS<T>::ABS(ABS<T>&& other) noexcept : capacity_(other.capacity_), curr_size_(other.curr_size_), array_(other.array_) {
    other.array_ = nullptr;
    other.curr_size_ = 0;
    other.capacity_ = 0;
}

template<typename T>
ABS<T>& ABS<T>::operator=(ABS<T>&& rhs) noexcept {
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
ABS<T>::~ABS() noexcept {
    delete[] array_;
}

template<typename T>
size_t ABS<T>::getSize() const noexcept { 
    return curr_size_; 
}

template<typename T>
size_t ABS<T>::getMaxCapacity() const noexcept { 
    return capacity_; 
}

template<typename T>
T* ABS<T>::getData() const noexcept { 
    return array_; 
}

template<typename T>
void ABS<T>::push(const T& data) {
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
T ABS<T>::peek() const {
    if (curr_size_ == 0) 
        throw std::runtime_error("cannot peek empty stack");
    return array_[curr_size_ - 1];
}

template<typename T>
T ABS<T>::pop() {
    if (curr_size_ == 0) 
        throw std::runtime_error("cannot pop empty stack");
    T item = array_[curr_size_ - 1];
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
void ABS<T>::PrintForward() const {
    for (int i = 0; i < curr_size_; i++) {
        std::cout << array_[i] << " \n"[i == curr_size_ - 1];
    }
}

template<typename T>
void ABS<T>::PrintReverse() const {
    for (int i = curr_size_ - 1; i >= 0; i--) {
        std::cout << array_[i] << " \n"[i == 0];
    }
}
