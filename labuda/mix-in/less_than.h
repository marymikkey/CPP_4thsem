#pragma once

template <typename T>
struct LessThanComparable {
    
    bool operator>(const T& other) const {
        return other < static_cast<const T&>(*this);
    }

    // better impelement using friend function, see Lection 7 slides 34-35 
    bool operator==(const T& other) const {
        auto& self = static_cast<const T&>(*this);
        return !(self < other || other < self); 
    }

    bool operator<=(const T& other) const {
        return !(other < static_cast<const T&>(*this));
    }

    bool operator>=(const T& other) const {
        return !(static_cast<const T&>(*this) < other);
    }
};
