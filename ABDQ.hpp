#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ();
    explicit ABDQ(std::size_t capacity);
    ABDQ(const ABDQ& other);
    ABDQ(ABDQ&& other) noexcept;
    ABDQ& operator=(const ABDQ& other);
    ABDQ& operator=(ABDQ&& other) noexcept;
    ~ABDQ() override;

    // Insertion
    void pushFront(const T& item) override;
    void pushBack(const T& item) override;

    // Deletion
    T popFront() override;
    T popBack() override;

    // Access
    const T& front() const override;
    const T& back() const override;

    // Getters
    std::size_t getSize() const noexcept override;

    void PrintForward() const;
    void PrintReverse() const;

};

template<typename T>
ABDQ<T>::ABDQ() : data_(new T[1]), capacity_(1), size_(0), front_(0), back_(0) {}

template<typename T>
ABDQ<T>::ABDQ(const size_t capacity) : data_(new T[capacity]), capacity_(capacity), size_(0), front_(0), back_(0) {}

template<typename T>
ABDQ<T>::ABDQ(const ABDQ<T>& other) : data_(new T[other.capacity_]), capacity_(other.capacity_), size_(other.size_), front_(other.front_), back_(other.back_) {
    for (int i = 0; i < size_; i++) {
        data_[i] = other.data_[i];
    }
}

template<typename T>
ABDQ<T>& ABDQ<T>::operator=(const ABDQ<T>& rhs) {
    if (this != &rhs) {
        delete[] data_;
        capacity_ = rhs.capacity_;
        size_ = rhs.size_;
        data_ = new T[capacity_];
        front_ = rhs.front_;
        back_ = rhs.back_;
        for (int i = 0; i < size_; i++) {
            data_[i] = rhs.data_[i];
        }
    }
    return *this;
}

template<typename T>
ABDQ<T>::ABDQ(ABDQ<T>&& other) noexcept : data_(other.data_), capacity_(other.capacity_), size_(other.size_), front_(other.front_), back_(other.back_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
    other.front_ = 0;
    other.back_ = 0;
}

template<typename T>
ABDQ<T>& ABDQ<T>::operator=(ABDQ<T>&& rhs) noexcept {
    if (this != &rhs) {
        delete[] data_;
        capacity_ = rhs.capacity_;
        size_ = rhs.size_;
        data_ = rhs.data_;
        front_ = rhs.front_;
        back_ = rhs.back_;
        rhs.data_ = nullptr;
        rhs.size_ = 0;
        rhs.capacity_ = 0;
        rhs.front_ = 0;
        rhs.back_ = 0;
    }
    return *this;
}

template<typename T>
ABDQ<T>::~ABDQ() {
    delete[] data_;
}

template<typename T>
size_t ABDQ<T>::getSize() const noexcept { 
    return size_; 
}

template<typename T>
void ABDQ<T>::pushFront(const T& data) {
    // resize if needed
    if (size_ >= capacity_) {
        int new_capacity = capacity_ * SCALE_FACTOR;
        T* new_array = new T[new_capacity];
        for (int i = 0; i < size_; i++) {
            new_array[i] = data_[i];
        }
        delete[] data_;
        data_ = new_array;
        capacity_ = new_capacity;
    }

    for (int i = size_; i > 0; i--) {
        data_[i] = data_[i - 1];
    }
    data_[0] = data;
    size_++;
}

template<typename T>
void ABDQ<T>::pushBack(const T& data) {
    // resize if needed
    if (size_ >= capacity_) {
        int new_capacity = capacity_ * SCALE_FACTOR;
        T* new_array = new T[new_capacity];
        for (int i = 0; i < size_; i++) {
            new_array[i] = data_[i];
        }
        delete[] data_;
        data_ = new_array;
        capacity_ = new_capacity;
    }

    data_[size_] = data;
    size_++;
}


template<typename T>
T ABDQ<T>::popFront() {
    if (size_ == 0) 
        throw std::runtime_error("ABDQ empty");
    T item = data_[0];
    for (int i = 0; i < size_ - 1; i++) {
        data_[i] = data_[i + 1];
    }
    size_--;
    return item;
}

template<typename T>
T ABDQ<T>::popBack() {
    if (size_ == 0) 
        throw std::runtime_error("ABDQ empty");
    T item = data_[size_ - 1];
    size_--;
    return item;
}

template<typename T>
const T& ABDQ<T>::front() const {
    if (size_ == 0) 
        throw std::runtime_error("ABDQ empty");
    return data_[0];
}

template<typename T>
const T& ABDQ<T>::back() const {
    if (size_ == 0) 
        throw std::runtime_error("ABDQ empty");
    return data_[size_ - 1];
}


template<typename T>
void ABDQ<T>::PrintForward() const {
    for (int i = 0; i < size_; i++) {
        std::cout << data_[i] << " \n"[i == size_ - 1];
    }
}

template<typename T>
void ABDQ<T>::PrintReverse() const {
    for (int i = (int) size_ - 1; i >= 0; i--) {
        std::cout << data_[i] << " \n"[i == 0];
    }
}
