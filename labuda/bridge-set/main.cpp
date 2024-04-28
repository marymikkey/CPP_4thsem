#include "set.h"
#include <iostream>

int main() {
    AdaptiveSet<int> s;
    s.Insert(1);
    s.Insert(1);
    s.Insert(2);
    s.Insert(4);
    s.Delete(3);
    s.Delete(4);
    std::cout << "contains 2 " << s.Contains(2) << std::endl;
    std::cout << "contains 3 " << s.Contains(3) << std::endl;
    std::cout << "size " << s.Size() << std::endl;

    AdaptiveSet<int> s2;
    s2.Insert(2);
    s2.Insert(5);
    s2.Intersect(s);
    std::cout << "s2: ";
    s2.Iterate([](const auto& item) { std::cout << item << " "; });
    std::cout << std::endl;

    for (int i = 10; i < 20; ++i) {
        s.Insert(i);
    }

    std::cout << "s: ";
    s.Iterate([](const auto& item) { std::cout << item << " "; });
    std::cout << std::endl;

    for (int i = 10; i < 20; ++i) {
        s.Delete(i);
    }

    std::cout << "s: ";
    s.Iterate([](const auto& item) { std::cout << item << " "; });
    std::cout << std::endl;
}
