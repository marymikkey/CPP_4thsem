#pragma once

#include <stddef.h>
#include <tuple>
#include <utility>
#include <iostream>

template <typename... Types>
using TypeMap = std::tuple<Types...>;

template <typename T>
constexpr size_t RevIndexOf() {
    return 0;
}

template <typename T, typename Head, typename... Tail>
constexpr size_t RevIndexOf() {
    return std::is_same_v<T, Head>
        ? (sizeof...(Tail) + 1)
        : RevIndexOf<T, Tail...>();
}

template <typename T, typename... Types>
constexpr size_t IndexOf() {
    return sizeof...(Types) - RevIndexOf<T, Types...>();
}

template <typename T, typename... Types>
constexpr bool Contains(TypeMap<Types...> map) {
    return IndexOf<T, Types...>() < sizeof...(Types);
}

template <typename T, typename... Types>
constexpr std::enable_if_t<IndexOf<T, Types...>() < sizeof...(Types), T>
GetValue(TypeMap<Types...> map) {
    constexpr auto idx = IndexOf<T, Types...>();
    return std::get<idx>(map);
}

template <typename T, typename... Types>
constexpr std::enable_if_t<IndexOf<T, Types...>() == sizeof...(Types), std::nullptr_t>
GetValue(TypeMap<Types...> map) {
    return nullptr;
}

template <typename T, typename... Types>
constexpr std::enable_if_t<IndexOf<T, Types...>() < sizeof...(Types), TypeMap<Types...>>
PutValue(TypeMap<Types...> map, T value) {
    constexpr auto idx = IndexOf<T, Types...>();
    std::get<idx>(map) = value;
    return map;
}

template <typename T, typename... Types>
constexpr std::enable_if_t<IndexOf<T, Types...>() == sizeof...(Types), TypeMap<T, Types...>>
PutValue(TypeMap<Types...> map, T value) {
    return std::tuple_cat(std::make_tuple(value), map);
}

template <size_t... idx>
void SeqPrint(std::index_sequence<idx...> seq) {
    (... , (std::cout << idx << " "));
    std::cout << std::endl;
}

template <typename Map, size_t... idx>
void TypeMapPrintImpl(Map map, std::index_sequence<idx...> seq) {
    (... , (std::cout << typeid(std::tuple_element_t<idx, Map>).name() << "=>" << std::get<idx>(map) << " "));
    std::cout << std::endl;
}

template <typename... Types>
void TypeMapPrint(TypeMap<Types...> map) {
    constexpr auto seq = std::index_sequence_for<Types...>{};
    TypeMapPrintImpl(map, seq);
}

template <size_t... idxLeft, size_t... idxRight>
constexpr auto SeqConcat(
        std::index_sequence<idxLeft...> seqLeft,
        std::index_sequence<idxRight...> seqRight) 
{
    return std::index_sequence<idxLeft..., idxRight...>{};
}

template <size_t offset, size_t... idx>
constexpr auto SeqOffset(std::index_sequence<idx...> seq) {
    return std::index_sequence<(offset + idx)...>{};
}

template <size_t idxToRemove, size_t seqSize>
constexpr auto SeqRemoveIdx() {
    if constexpr (idxToRemove < seqSize) {
        constexpr size_t tail = seqSize - idxToRemove - 1;
        return SeqConcat(
                std::make_index_sequence<idxToRemove>{},
                SeqOffset<idxToRemove + 1>(std::make_index_sequence<tail>{}));
    } else {
        return std::make_index_sequence<seqSize>{};
    }
}

template <typename Map, size_t... indices>
constexpr auto TypeMapSubset(Map map, std::index_sequence<indices...> seq) {
    return std::make_tuple(std::get<indices>(map)...);
}

template <typename T, typename... Types>
constexpr auto RemoveType(TypeMap<Types...> map) {
    constexpr auto idx = IndexOf<T, Types...>();
    if constexpr (idx == sizeof...(Types)) {
        return map;
    }
    return TypeMapSubset(map, SeqRemoveIdx<idx, sizeof...(Types)>());
}
