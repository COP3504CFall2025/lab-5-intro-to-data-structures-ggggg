#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T>* prev;
    Node<T>* next;
};

template <typename T>
class LinkedList {
public:
	// Behaviors
	void PrintForward() const;
    void printForward() const; // scuffed but this is fine :)
	void PrintReverse() const;

	// Accessors
	[[nodiscard]] unsigned int getCount() const;
	Node<T>* getHead();
	const Node<T>* getHead() const;
	Node<T>* getTail();
	const Node<T>* getTail() const;

	// Insertion
    void AddHead(const T& data);
	void AddTail(const T& data);

	// Removal
	bool RemoveHead();
	bool RemoveTail();
	void Clear();

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;
	LinkedList<T>& operator=(const LinkedList<T>& rhs);

	// Construction/Destruction
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	LinkedList(LinkedList<T>&& other) noexcept;
	~LinkedList();

private:
	// Stores pointers to first and last nodes and count
	Node<T>* head;
	Node<T>* tail;
	unsigned int count;

};

// Implementation
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), count(0) {}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) : head(nullptr), tail(nullptr), count(0) {
    Node<T>* curr = list.head;
    while (curr != nullptr) {
        AddTail(curr->data);
        curr = curr->next;
    }
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& other) noexcept : head(other.head), tail(other.tail), count(other.count) {
    other.head = nullptr;
    other.tail = nullptr;
    other.count = 0;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    Clear();
}

// Operators
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
    if (this != &rhs) {
        Clear();
        Node<T>* curr = rhs.head;
        while (curr != nullptr) {
            AddTail(curr->data);
            curr = curr->next;
        }
    }
    return *this;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) noexcept {
    if (this != &other) {
        Clear();
        head = other.head;
        tail = other.tail;
        count = other.count;
        other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;
    }
    return *this;
}

// Behaviors
template <typename T>
void LinkedList<T>::PrintForward() const {
    Node<T>* curr = head;
    while (curr != nullptr) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << '\n';
}

template <typename T>
void LinkedList<T>::printForward() const {
    Node<T>* curr = head;
    while (curr != nullptr) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << '\n';
}


template <typename T>
void LinkedList<T>::PrintReverse() const {
    Node<T>* curr = tail;
    while (curr != nullptr) {
        cout << curr->data << " ";
        curr = curr->prev;
    }
    cout << '\n';
}

// Accessors
template <typename T>
unsigned int LinkedList<T>::getCount() const { return count; }

template <typename T>
Node<T>* LinkedList<T>::getHead() { return head; }

template <typename T>
const Node<T>* LinkedList<T>::getHead() const { return head; }

template <typename T>
Node<T>* LinkedList<T>::getTail() { return tail; }

template <typename T>
const Node<T>* LinkedList<T>::getTail() const { return tail; }

// Insertion
template <typename T>
void LinkedList<T>::AddHead(const T& data) {
    Node<T>* newNode = new Node<T>{data, nullptr, head};
    if (head != nullptr) head->prev = newNode;
    head = newNode;
    count++;

    if (tail == nullptr) tail = newNode;
}

template <typename T>
void LinkedList<T>::AddTail(const T& data) {
    Node<T>* newNode = new Node<T>{data, tail, nullptr};
    if (tail != nullptr) tail->next = newNode;
    tail = newNode;
    count++;

    if (head == nullptr) head = newNode;
}

// Removal
template <typename T>
bool LinkedList<T>::RemoveHead() {
    if (head == nullptr) return false;
    
    Node<T>* tmp = head;
    head = head->next;
    if (head != nullptr) head->prev = nullptr;
    else tail = nullptr;
    
    --count;
    delete tmp;
    
    return true;
}

template <typename T>
bool LinkedList<T>::RemoveTail() {
    if (tail == nullptr) return false;
    
    Node<T>* tmp = tail;
    tail = tail->prev;
    if (tail != nullptr) tail->next = nullptr;
    else head = nullptr;
    
    --count;
    delete tmp;
    
    return true;
}

template <typename T>
void LinkedList<T>::Clear() {
    while (head != nullptr) {
        RemoveHead();
    }
}


