#pragma once

#include <cstdlib>
#include <functional>
#include <memory>

template <typename T>
struct Set {
    virtual ~Set() {}
    virtual size_t Size() const = 0;
    virtual bool Contains(const T& item) const = 0;

    virtual void Iterate(std::function<void(const T&)> callback) const = 0;

    virtual void Insert(T item) = 0;
    virtual void Delete(T item) = 0;
    virtual void Union(const Set<T>& other) = 0;
    virtual void Intersect(const Set<T>& other) = 0;
};

template <typename T>
struct AdaptiveSet: public Set<T> {
    AdaptiveSet();

    size_t Size() const override {
        return impl_->Size();
    }

    bool Contains(const T& item) const override {
        return impl_->Contains(item);
    }

    void Iterate(std::function<void(const T&)> callback) const override {
        impl_->Iterate(callback);
    }

    void Insert(T item) override {
        ReInitialize();
        impl_->Insert(item);
    }

    void Delete(T item) override {
        ReInitialize();
        impl_->Delete(item);
    }

    void Union(const Set<T>& other) override {
        ReInitialize();
        impl_->Union(other);
    }

    void Intersect(const Set<T>& other) override {
        ReInitialize();
        impl_->Intersect(other);
    }

private:
    void ReInitialize();

    std::unique_ptr<Set<T>> impl_;
};
