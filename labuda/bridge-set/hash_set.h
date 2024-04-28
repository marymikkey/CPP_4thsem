#pragma once

#include "set.h"
#include <unordered_set>

template <typename T>
struct HashSet: public Set<T> {
    size_t Size() const override {
        return set_.size();
    }

    bool Contains(const T& item) const override {
        return set_.find(item) != set_.end();
    }

    void Iterate(std::function<void(const T&)> callback) const override {
        std::for_each(set_.cbegin(), set_.cend(), callback);
    }

    void Insert(T item) override {
        set_.insert(item);
    }

    void Delete(T item) override {
        set_.erase(item);
    }

    void Union(const Set<T>& other) override {
        other.Iterate([this](const T& item) {
            Insert(item);
        });
    }

    void Intersect(const Set<T>& other) override {
        std::unordered_set<T> intersection;
        other.Iterate([this, &intersection](const T& item) {
            if (Contains(item)) {
                intersection.insert(item);
            }
        });
        set_ = std::move(intersection);
    }

private:

    std::unordered_set<T> set_;
};
