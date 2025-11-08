#include "LLQ.hpp"

template <typename T>
LLQ<T>::LLQ() {}

// Insertion
template <typename T>
void LLQ<T>::enqueue(const T& item) {
    list.addTail(item);
}

// Deletion
template <typename T>
T LLQ<T>::dequeue() {
    if (list.getHead() == nullptr) {
        throw std::runtime_error("Empty list");
    }

    T outgoing = *(list.getHead()->datum);
    list.removeHead();

    return outgoing;
}

// Access
template <typename T>
T LLQ<T>::peek() const {
    if (list.getHead() == nullptr) {
        throw std::runtime_error("Empty list");
    }

    return *(list.getHead()->datum);
}

// Getter
template <typename T>
std::size_t LLQ<T>::getSize() const noexcept {
    return list.getCount();
}