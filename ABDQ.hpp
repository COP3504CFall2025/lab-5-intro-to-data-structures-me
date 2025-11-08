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

    void addCapacity() {
        if (capacity_ == 0) {
            capacity_ = 1;
        }

        int oldCapacity = capacity_;

        capacity_ *= SCALE_FACTOR;
        T* newArr = new T[capacity_];

        for (size_t i = 0; i < size_; ++i) {
            newArr[i] = data_[(front_ + i) % oldCapacity];
        }

        delete[] data_;
        data_ = newArr;

        front_ = 0;
        back_ = size_ - 1;
    }

public:
    // Big 5
    ABDQ() {
        capacity_ = 4;
        size_ = 0;
        front_ = 0;
        back_ = 0;
        data_ = nullptr;
    }

    explicit ABDQ(std::size_t capacity) {
        capacity_ = capacity;
        size_ = 0;
        front_ = 0;
        back_ = 0;
        data_ = new T[capacity_];
    }

    ABDQ(const ABDQ& other) {
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;

        if (capacity_ > 0) {
            data_ = new T[capacity_];
        }

        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    ABDQ(ABDQ&& other) noexcept {
        if (this == &rhs) {
            return *this;
        }

        capacity_ = rhs.capacity_;
        size_ = rhs.size_;
        front_ = rhs.front_;
        back_ = rhs.back_;

        T* newArr = nullptr;

        if (capacity_ > 0) {
            newArr = new T[capacity_];
        }

        delete[] data_;

        for (size_t i = 0; i < size_; ++i) {
            newArr[i] = rhs.data_[i];
        }

        data_ = newArr;
    }

    ABDQ& operator=(const ABDQ& other) {
        capacity_ = other.capacity_;
        size_ = other.size_;
        data_ = other.data_;
        front_ = other.front_;
        back_ = other.back_;

        other.capacity_ = 0;
        other.size_ = 0;
        other.data_ = nullptr;
        other.front_ = 0;
        other.back_ = 0;
    }

    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this == &rhs) {
            return *this;
        }

        delete[] data_;

        capacity_ = rhs.capacity_;
        size_ = rhs.size_;
        data_ = rhs.data_;
        front_ = rhs.front_;
        back_ = rhs.back_;

        rhs.capacity_ = 0;
        rhs.size_ = 0;
        rhs.data_ = nullptr;
        rhs.front_ = 0;
        rhs.back_ = 0;
    }

    ~ABDQ() {
        delete[] data_;
        capacity_ = 0;
        size_ = 0;
        front_ = 0;
        back_ = 0;
        data_ = nullptr;
    }

    // Insertion
    void pushFront(const T& item) override {
        if (size_ >= capacity_) {
            addCapacity();
        }

        if (front_ == 0) {
            front_ = capacity_ - 1;
        } else {
            front_--;
        }

        data_[front_] = item;
        size_++;
    }

    void pushBack(const T& item) override {
        if (size_ >= capacity_) {
            addCapacity();
        }

        back_++;
        if (back_ >= capacity_) {
            back_ = 0;
        }

        data_[back_] = item;
        size_++;
    }

    // Deletion
    T popFront() override {
        if (size_ == 0) {
            throw std::runtime_error("Empty List");
        }

        T outgoing = data_[front_];

        front_++;
        if (front_ >= capacity_) {
            front_ = 0;
        }

        size_--;
        return outgoing;
    }

    T popBack() override {
        if (size_ == 0) {
            throw std::runtime_error("Empty List");
        }

        T outgoing = data_[back_];

        if (back_ == 0) {
            back_ = capacity_ - 1;
        } else {
            back_--;
        }

        size_--;
        return outgoing;
    }

    // Access
    const T& front() const override {
        if (size_ == 0) {
            throw std::runtime_error("Empty List");
        }

        return data_[front_];
    }

    const T& back() const override {
        if (size_ == 0) {
            throw std::runtime_error("Empty List");
        }

        return data_[back_];
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    }

};
