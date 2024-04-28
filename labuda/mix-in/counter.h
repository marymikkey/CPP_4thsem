#pragma once

#include <cstddef>

template <typename T>
struct Counter {
public:
    static size_t count() { return count_; }

protected:
    static size_t count_;

    Counter() { ++count_; }
    ~Counter() { --count_; }
};

template <typename T> size_t Counter<T>::count_ = 0;
