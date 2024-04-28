#include "type_map.h"
#include <iostream>

int main() {
    auto m = TypeMap<int, bool>(2, true);
    std::cout << Contains<int>(m) << " " << Contains<double>(m) << std::endl;
    std::cout << IndexOf<bool, int, bool>() << std::endl;
    std::cout << IndexOf<double, int, bool>() << std::endl;
    std::cout << GetValue<int>(m) << std::endl;
    std::cout << GetValue<double>(m) << std::endl;
    static_assert(std::is_same_v<std::nullptr_t, decltype(GetValue<double>(m))>);
    PutValue(m, 3);
    auto m2 = PutValue(m, std::string("a"));
    std::cout << GetValue<int>(m) << std::endl;
    std::cout << GetValue<std::string>(m2) << std::endl;
    std::cout << GetValue<bool>(m2) << std::endl;

    auto seq = std::index_sequence<1,2,3,4>{};
    SeqPrint(seq);
    auto seq2 = std::make_index_sequence<3>{};
    SeqPrint(SeqConcat(seq, seq2));
    SeqPrint(SeqOffset<2>(seq));

    SeqPrint(SeqRemoveIdx<1, 3>());
    SeqPrint(SeqRemoveIdx<3, 3>());

    auto m3 = RemoveType<float>(m);
    static_assert(std::is_same_v<decltype(m), decltype(m3)>);

    auto m4 = RemoveType<int>(m);
    std::cout << "m4(int) => " << Contains<int>(m4) << std::endl;
    std::cout << "m4(bool) => " << GetValue<bool>(m4) << std::endl;

    TypeMapPrint(m);
    TypeMapPrint(m4);
}
