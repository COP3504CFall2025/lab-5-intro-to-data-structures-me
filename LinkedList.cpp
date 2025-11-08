#include "LinkedList.hpp"
#include <iostream>

template <typename T>
void LinkedList<T>::printForward() const {
    Node<T>* current = head;
    Node<T>* next = nullptr;

    while (current != nullptr) {
        next = current->next;

        if (current->datum == nullptr) {
            std::cout << "nullptr" << std::endl;
        } else {
            std::cout << *(current->datum) << std::endl;
        }

        current = next;
    }
}

template <typename T>
void LinkedList<T>::printReverse() const {
    Node<T>* current = tail;
    Node<T>* previous = nullptr;

    while (current != nullptr) {
        previous = current->previous;

        if (current->datum == nullptr) {
            std::cout << "nullptr" << std::endl;
        } else {
            std::cout << *(current->datum) << std::endl;
        }

        current = previous;
    }
}

// Accessors
template <typename T>
unsigned int LinkedList<T>::getCount() const {
    return count;
}

template<typename T>
LinkedList<T>::Node<T>* LinkedList<T>::getHead() {
    return head;
}

template<typename T>
const typename LinkedList<T>::Node<T>* LinkedList<T>::getHead() const {
    return head;
}

template<typename T>
LinkedList<T>::Node<T>* LinkedList<T>::getTail() {
    return tail;
}

template<typename T>
const typename LinkedList<T>::Node<T>* LinkedList<T>::getTail() const {
    return tail;
}

// Insertion
template <typename T>
void LinkedList<T>::addHead(const T& data) {
    Node<T>* newNode = new Node<T>(data, nullptr, head);

    if (head != nullptr) {
        head->previous = newNode;
    }

    head = newNode;

    if (tail == nullptr) {
        tail = newNode;
    }

    count++;
}

template <typename T>
void LinkedList<T>::addTail(const T& data) {
    Node<T>* newNode = new Node<T>(data, tail, nullptr);

    if (tail != nullptr) {
        tail->next = newNode;
    }

    tail = newNode;

    if (head == nullptr) {
        head = newNode;
    }

    count++;
}

// Removal
template <typename T>
bool LinkedList<T>::removeHead() {
    if (head == nullptr) {
        return false;
    }

    if (head == tail) {
        delete head;
        head = nullptr;
        tail = nullptr;
        count = 0;
        return true;
    }

    if (head->next == nullptr) {
        delete head;
        head = nullptr;
    } else {
        head = head->next;
        delete head->previous;
        head->previous = nullptr;
    }

    count--;
    return true;
}

template <typename T>
bool LinkedList<T>::removeTail() {
    if (tail == nullptr) {
        return false;
    }

    if (head == tail) {
        delete head;
        head = nullptr;
        tail = nullptr;
        count = 0;
        return true;
    }

    if (tail->previous == nullptr) {
        delete tail;
        tail = nullptr;
    } else {
        tail = tail->previous;
        delete tail->next;
        tail->next = nullptr;
    }

    count--;
    return true;
}

template <typename T>
void LinkedList<T>::Clear() {
    if (head == nullptr && tail == nullptr) {
        return;
    }

    if (head == tail) {
        delete head;
        head = nullptr;
        tail = nullptr;
        return;
    }

    Node<T>* current = head;
    Node<T>* next = nullptr;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }

    head = nullptr;
    tail = nullptr;
    count = 0;
}

// Operators
// LinkedList<T>& operator=(const LinkedList<T>& rhs);
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    head = other.head;
    tail = other.tail;
    count = other.count;

    other.head = nullptr;
    other.tail = nullptr;
    other.count = 0;
}

// Construction/Destruction
template <typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    tail = nullptr;
    count = 0;
}

// LinkedList(const LinkedList<T>& list);
template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& other) noexcept {
    head = other.head;
    tail = other.tail;
    count = other.count;

    other.head = nullptr;
    other.tail = nullptr;
    other.count = 0;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    Clear();
}