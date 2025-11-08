#include "ABS.hpp"

// Big 5 + Parameterized Constructor
template <typename T>
ABS<T>::ABS() {
    capacity_ = 4;
    curr_size_ = 0;
    array_ = nullptr;
}

template <typename T>
ABS<T>::ABS(const size_t capacity) {
    capacity_ = capacity;
    curr_size_ = 0;
    array_ = new T[capacity];
}

template <typename T>
ABS<T>::ABS(const ABS<T>& other) {
    capacity_ = other.capacity_;
    curr_size_ = other.curr_size_;

    if (capacity_ > 0) {
        array_ = new T[capacity_];
    }

    for (size_t i = 0; i < curr_size_; ++i) {
        array_[i] = other.array_[i];
    }
}

template <typename T>
ABS<T>& ABS<T>::operator=(const ABS<T>& rhs) {
    if (this == &rhs) {
        return *this;
    }

    capacity_ = rhs.capacity_;
    curr_size_ = rhs.curr_size_;

    T* newArr = nullptr;

    if (capacity_ > 0) {
        newArr = new T[capacity_];
    }

    delete[] array_;

    for (size_t i = 0; i < curr_size_; ++i) {
        newArr[i] = rhs.array_[i];
    }

    array_ = newArr;
}

template <typename T>
ABS<T>::ABS(ABS<T>&& other) noexcept {
    capacity_ = other.capacity_;
    curr_size_ = other.curr_size_;
    array_ = other.array_;

    other.capacity_ = 0;
    other.curr_size_ = 0;
    other.array_ = nullptr;
}

template <typename T>
ABS<T>& ABS<T>::operator=(ABS<T>&& rhs) noexcept {
    if (this == &rhs) {
        return *this;
    }

    delete[] array_;

    capacity_ = rhs.capacity_;
    curr_size_ = rhs.curr_size_;
    array_ = rhs.array_;

    rhs.capacity_ = 0;
    rhs.curr_size_ = 0;
    rhs.array_ = nullptr;
}

template <typename T>
ABS<T>::~ABS() noexcept {
    delete[] array_;
    curr_size_ = 0;
    capacity_ = 0;
}

// Get the number of items in the ABS
template <typename T>
[[nodiscard]] size_t ABS<T>::getSize() const noexcept {
    return curr_size_;
}

// Get the max size of the ABS
template <typename T>
[[nodiscard]] size_t ABS<T>::getMaxCapacity() const noexcept {
    return capacity_;
}

// Return underlying data for the stack
template <typename T>
[[nodiscard]] T* ABS<T>::getData() const noexcept {
    return array_;
}

// Push item onto the stack
template <typename T>
void ABS<T>::push(const T& data) {
    if (curr_size_ >= capacity_) {
        addCapacity();
    }

    array_[curr_size_] = data;
    curr_size_++;
}

template <typename T>
T ABS<T>::peek() const {
    if (curr_size_ == 0) {
        throw std::invalid_argument("Empty list");
    }

    return array_[curr_size_ - 1];
}

template <typename T>
T ABS<T>::pop() {
    if (curr_size_ == 0) {
        throw std::invalid_argument("Empty list");
    }

    T outgoing = array_[curr_size_ - 1];
    curr_size_--;

    return outgoing;
}

template <typename T>
void ABS<T>::addCapacity() {
    if (capacity_ == 0) {
        capacity_ = 1;
    }

    capacity_ *= scale_factor_;
    T* newArr = new T[capacity_];

    for (size_t i = 0; i < curr_size_; ++i) {
        newArr[i] = array_[i];
    }

    delete[] array_;
    array_ = newArr;
}