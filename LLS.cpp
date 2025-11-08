#include "LLS.hpp"

// Constructor
template <typename T>
LLS<T>::LLS() {}

// Insertion
template <typename T>
void LLS<T>::push(const T& item) {
    list.addTail(item);
}

// Deletion
template <typename T>
T LLS<T>::pop() {
    if (list.getTail() == nullptr) {
        throw std::runtime_error("Empty list");
    }

    T outgoing = *(list.getTail()->datum);
    list.removeTail();

    return outgoing;
}

// Access
template <typename T>
T LLS<T>::peek() const {
    if (list.getTail() == nullptr) {
        throw std::runtime_error("Empty list");
    }

    return *(list.getTail()->datum);
}

//Getters
template <typename T>
std::size_t LLS<T>::getSize() const noexcept {
    return list.getCount();
}