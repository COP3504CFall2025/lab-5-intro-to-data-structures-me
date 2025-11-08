#include "LLDQ.hpp"

// Constructor
template <typename T>
LLDQ<T>::LLDQ() {}

// Core Insertion Operations
template <typename T>
void LLDQ<T>::pushFront(const T& item) {
    list.addHead(item);
}

template <typename T>
void LLDQ<T>::pushBack(const T& item) {
    list.addTail(item);
}

// Core Removal Operations
template <typename T>
T LLDQ<T>::popFront() {
    if (list.getHead() == nullptr) {
        throw std::runtime_error("Empty list");
    }

    T outgoing = *(list.getHead()->datum);
    list.removeHead();

    return outgoing;
}

template <typename T>
T LLDQ<T>::popBack() {
    if (list.getTail() == nullptr) {
        throw std::runtime_error("Empty list");
    }

    T outgoing = *(list.getTail()->datum);
    list.removeTail();

    return outgoing;
}

// Element Accessors
template <typename T>
const T& LLDQ<T>::front() const {
    if (list.getHead() == nullptr) {
        throw std::runtime_error("Empty list");
    }

    return *(list.getHead()->datum);
}

template <typename T>
const T& LLDQ<T>::back() const {
    if (list.getTail() == nullptr) {
        throw std::runtime_error("Empty list");
    }

    return *(list.getTail()->datum);
}

// Getter
template <typename T>
std::size_t LLDQ<T>::getSize() const noexcept {
    return list.getCount();
}