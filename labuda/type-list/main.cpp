#include <iostream>

#include "type_list.h"

int main ()
{
    TypeList<> empty;
    TypeList<int, bool> tl;
    Print(tl);
    std::cout << Size(tl) << std::endl;
    std::cout << ByIndex<1>(tl).name() << " " << std::is_same_v<int, decltype(ByIndex<0>(tl))::Type> << std::endl;
    std::cout << Contains<int>(tl) << " " << Contains<float>(tl) <<std::endl;
    auto tl2 = PushFront<double>(tl);
    Print(tl2);
    auto tl3 = PushBack<double>(tl);
    Print(tl3);
    return 0;
}
