#include "less_than.h"
#include "counter.h"
#include <cassert>
#include <iostream>


class Number: public LessThanComparable<Number>, public Counter<Number> {
public:
    Number(int value): m_value{value} {}

    int value() const { return m_value; }

    bool operator<(const Number& other) const {
        return m_value < other.m_value;
    }

private:
    int m_value;
};

struct Foo: public Counter<Foo> {
};

int main() {
    Foo f1;
    Number one{1};
    Number two{2};
    Number three{3};
    Number four{4};
    Foo f2;

    assert(one >= one);
    assert(three <= four);
    assert(two == two);
    assert(three > two);
    assert(one < two);

    std::cout << "Count<Number>: " << Counter<Number>::count() << std::endl;
    std::cout << "Count<Foo>: " << Counter<Foo>::count() << std::endl;
    return 0;
}
