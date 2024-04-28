#include "set.h"
#include "array_set.h"
#include "hash_set.h"
#include <iostream>

template <typename T>
AdaptiveSet<T>::AdaptiveSet()
    : impl_(std::make_unique<ArraySet<T>>())
{}

template <typename T>
void AdaptiveSet<T>::ReInitialize() {
    auto size = Size();
    std::unique_ptr<Set<T>> newSet;
    if (size < 5 && dynamic_cast<ArraySet<T>*>(impl_.get()) == nullptr) {
        std::cout << "convert to array\n";
        newSet = std::make_unique<ArraySet<T>>();
    } else if (size > 10 && dynamic_cast<HashSet<T>*>(impl_.get()) == nullptr) {
        std::cout << "convert to hash\n";
        newSet = std::make_unique<HashSet<T>>();
    }
    if (newSet) {
        Iterate([&newSet](const T& item) { newSet->Insert(item); });
        impl_ = std::move(newSet);
    }
}

template class AdaptiveSet<int>;
