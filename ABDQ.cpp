#include "ABDQ.hpp"

// Big 5
template <typename T>
ABDQ<T>::ABDQ() {
    capacity_ = 4;
    size_ = 0;
    front_ = 0;
    back_ = 0;
    data_ = nullptr;
}

template <typename T>
ABDQ<T>::ABDQ(std::size_t capacity) {
    capacity_ = capacity;
    size_ = 0;
    front_ = 0;
    back_ = 0;
    data_ = new T[capacity_];
}

template <typename T>
ABDQ<T>::ABDQ(const ABDQ<T>& other) {
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

template <typename T>
ABDQ<T>& ABDQ<T>::operator=(const ABDQ<T>& rhs) {
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

template <typename T>
ABDQ<T>::ABDQ(ABDQ<T>&& other) noexcept {
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

template <typename T>
ABDQ<T>& ABDQ<T>::operator=(ABDQ<T>&& rhs) noexcept {
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

template <typename T>
ABDQ<T>::~ABDQ() {
    delete[] data_;
    capacity_ = 0;
    size_ = 0;
    front_ = 0;
    back_ = 0;
    data_ = nullptr;
}

// Insertion
template <typename T>
void ABDQ<T>::pushFront(const T& item) {
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

template <typename T>
void ABDQ<T>::pushBack(const T& item) {
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
template <typename T>
T ABDQ<T>::popFront() {
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

template <typename T>
T ABDQ<T>::popBack() {
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
template <typename T>
const T& ABDQ<T>::front() const {
    if (size_ == 0) {
        throw std::runtime_error("Empty List");
    }

    return data_[front_];
}

template <typename T>
const T& ABDQ<T>::back() const {
    if (size_ == 0) {
        throw std::runtime_error("Empty List");
    }

    return data_[back_];
}

// Getters
template <typename T>
std::size_t ABDQ<T>::getSize() const noexcept {
    return size_;
}

template <typename T>
void ABDQ<T>::addCapacity() {
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