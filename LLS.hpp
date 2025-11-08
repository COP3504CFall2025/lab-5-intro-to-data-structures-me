#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() {}

    // Insertion
    void push(const T& item) override {
        list.addTail(item);
    }

    // Deletion
    T pop() override {
        if (list.getTail() == nullptr) {
            throw std::runtime_error("Empty list");
        }

        T outgoing = *(list.getTail()->data);
        list.removeTail();

        return outgoing;
    }

    // Access
    T peek() const override {
        if (list.getTail() == nullptr) {
            throw std::runtime_error("Empty list");
        }

        return *(list.getTail()->data);
    }

    //Getters
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }
};