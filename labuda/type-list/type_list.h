#pragma once

#include <iostream>
#include <string>
#include <typeinfo>
#include <tuple>

template <typename... Types>
struct TypeList {
};

template <typename T>
struct TypeWrapper {
    using Type = T;
    std::string name() { return typeid(T).name(); }
};

template<typename Head, typename... Tail>
void Print(TypeList<Head,Tail...>& t) {
    std::cout << typeid(Head).name() << ' ';
    TypeList<Tail...> remaining;
    Print(remaining);
}

void Print(TypeList<>& t) {
}

template<typename... Types>
constexpr size_t Size(TypeList<Types...> list) {
    return sizeof...(Types);
}

template<size_t idx, typename... Types>
constexpr auto ByIndex(TypeList<Types...> list) {
    return TypeWrapper<std::tuple_element_t<idx, std::tuple<Types...>>>();
}

template<typename T, typename Head, typename... Tail>
constexpr size_t FindReverse(TypeList<Head,Tail...>& t) {
    TypeList<Tail...> remaining;
    return std::is_same_v<T, Head>
               ? sizeof...(Tail)
               : FindReverse<T, Tail...>(remaining);
}

template <typename T>
constexpr size_t FindReverse(TypeList<>& t) {
    return SIZE_MAX;
}

template <typename T, typename... Types>
constexpr int Find(TypeList<Types...> list) {
    constexpr size_t reverseIdx = FindReverse<T>(list);
    return reverseIdx == SIZE_MAX
               ? SIZE_MAX
               : sizeof...(Types) - reverseIdx - 1;
}


template<typename T, typename Head, typename... Tail>
constexpr bool Contains(TypeList<Head,Tail...>& t) {
    TypeList<Tail...> remaining;
    return std::is_same_v<T, Head> ? true : Contains<T, Tail...>(remaining);
}

template <typename T>
constexpr bool Contains(TypeList<>& t) {
    return false;
}

template<typename T, typename... Types>
constexpr TypeList<T, Types...> PushFront(TypeList<Types...> list) {
    return {};
}

template<typename T, typename... Types>
constexpr TypeList<Types..., T> PushBack(TypeList<Types...> list) {
    return {};
}

