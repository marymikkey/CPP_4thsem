#pragma once

#include "set.h"
#include <vector>

template <typename T>
struct ArraySet: public Set<T> {

    size_t Size() const override {
        return items_.size();
    }

    bool Contains(const T& item) const override {
        return std::find(items_.begin(), items_.end(), item) != items_.end();
    }

    void Iterate(std::function<void(const T&)> callback) const override {
        std::for_each(items_.cbegin(), items_.cend(), callback);
    }

    void Insert(T item) override {
        if (!Contains(item)) {
            items_.push_back(item);
        }
    }

    void Delete(T item) override {
        auto pos = std::find(items_.begin(), items_.end(), item);
        if(pos != items_.end()) {
            items_.erase(pos);
        }
    }

    void Union(const Set<T>& other) override {
        other.Iterate([this](const T& item) {
            Insert(item);
        });
    }

    void Intersect(const Set<T>& other) override {
        std::vector<T> intersection;
        other.Iterate([this, &intersection](const T& item) {
            if (Contains(item)) {
                intersection.push_back(item);
            }
        });
        items_ = std::move(intersection);
    }

private:

    std::vector<T> items_;
};
