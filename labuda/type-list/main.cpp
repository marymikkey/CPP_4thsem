#include <iostream>

#include "type_list.h"

int main ()
{
    TypeList<> empty;
    static_assert(Size(empty) == 0);

    TypeList<int, bool> tl;
    std::cout << "tl: ";
    Print(tl);
    std::cout << "\nSize " << Size(tl) << std::endl;
    std::cout << "int idx = " << Find<int>(tl) << std::endl;
    std::cout << "bool idx = " << Find<bool>(tl) << std::endl;

    static_assert(std::is_same_v<int, decltype(ByIndex<0>(tl))::Type>);
    static_assert(Size(tl) == 2);

    std::cout << "ByIndex(1) = " << ByIndex<1>(tl).name() << std::endl;
    std::cout << "Contains(int) = " << Contains<int>(tl) 
        << "\nContains(float) = " << Contains<float>(tl) <<std::endl;


    auto tl2 = PushFront<double>(tl);
    static_assert(std::is_same_v<double, decltype(ByIndex<0>(tl2))::Type>);
    static_assert(Size(tl2) == 3);
    std::cout << "double idx = " << Find<double>(tl2) << std::endl;
    std::cout << "tl2: ";
    Print(tl2);
    std::cout << std::endl;
    auto tl3 = PushBack<double>(tl);
    static_assert(std::is_same_v<double, decltype(ByIndex<2>(tl3))::Type>);
    std::cout << "double idx = " << Find<double>(tl3) << std::endl;
    std::cout << "\ntl3: ";
    Print(tl3);
    return 0;
}
