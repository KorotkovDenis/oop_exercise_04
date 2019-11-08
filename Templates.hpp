#ifndef LAB4_TEMPLATES_HPP
#define LAB4_TEMPLATES_HPP

#include <tuple>
#include <type_traits>
#include <exception>
#include "Vertex.hpp"

template<class T>
struct is_vertex : std::false_type {};

template<class T>
struct is_vertex<vertex<T>> : std::true_type {};

template<class T>
struct is_figurelike_tuple : std::false_type {};

template<class Head, class... Tail>
struct is_figurelike_tuple<std::tuple<Head, Tail...> > :
    std::conjunction<is_vertex<Head>, std::is_same<Head, Tail>...> {};

template<class T>
inline constexpr bool is_figurelike_tuple_v = is_figurelike_tuple<T>::value;

template<class T, class = void>
struct has_method_area : std::false_type {};

template<class T>
struct has_method_area<T, std::void_t<decltype(std::declval<const T&>().area())>> :
std::true_type {};

template<class T>
inline constexpr bool has_method_area_v = has_method_area<T>::value;

template<class T>
std::enable_if_t<has_method_area_v<T>, double> area(const T& object) {
    return object.area();
}

template<size_t Id, class T>
double compute_area(const T& tuple) {
    if constexpr (Id >= std::tuple_size_v<T>) {
        return 0;
    } else {
        const auto dx1 = std::get<Id - 0>(tuple).x - std::get<0>(tuple).x;
        const auto dy1 = std::get<Id - 0>(tuple).y - std::get<0>(tuple).y;
        const auto dx2 = std::get<Id - 1>(tuple).x - std::get<0>(tuple).x;
        const auto dy2 = std::get<Id - 1>(tuple).y - std::get<0>(tuple).y;
        const double local_area = std::abs(dx1 * dy2 - dy1 * dx2) * 0.5;
        return local_area + compute_area<Id + 1>(tuple);
    }
}

template<class T>
std::enable_if_t<is_figurelike_tuple_v<T>, double> area(const T& object) {
    if constexpr (std::tuple_size_v<T> < 3) {
        throw std::logic_error("invalid area");
    } else {
        return compute_area<2>(object);
    }
}


template<class T, class = void>
struct has_method_center : std::false_type {};

template<class T>
struct has_method_center<T, std::void_t<decltype(std::declval<const T&>().center())>> :
std::true_type {};

template<class T>
inline constexpr bool has_method_center_v = has_method_center<T>::value;


template<class T, class=void>
struct center_return {};


template<class T>
struct center_return<T, std::void_t <decltype(std::declval<const T&>().center())>> {
    using type=decltype(std::declval<T>().center());
};


template<class Head, class ...Tail>
struct center_return<std::tuple<Head, Tail...> > {
    using type = Head;
};


template<class T>
using center_return_t = typename center_return<T>::type;


template<class T>
auto center(const T& object) -> std::enable_if_t<has_method_center_v<T>, center_return_t<T> >
{
    return object.center();
}

template<size_t Id, class T>
auto compute_center(const T& tuple) {
    if constexpr (Id == std::tuple_size_v<T> - 1) {
        auto ans = std::get<Id>(tuple);
        return ans;
    } else if constexpr (Id == 0){
        auto V = compute_center<Id + 1>(tuple);
        auto ans = std::get<Id>(tuple);
        V = {(V.x + ans.x) / std::tuple_size_v<T>, (V.y + ans.y) / std::tuple_size_v<T>};
        return V;
    } else {
        auto V = compute_center<Id + 1>(tuple);
        auto ans = std::get<Id>(tuple);
        V = {(V.x + ans.x), (V.y + ans.y)};
        return V;
    }
}



template<class T>
auto center(const T& object) -> std::enable_if_t<is_figurelike_tuple_v<T>, center_return_t<T> >
{
    if constexpr (std::tuple_size_v<T> < 3) {
        throw std::logic_error("invalid center");
    } else {
        return compute_center<0>(object);
    }
}


template<class T, class = void>
struct has_method_print : std::false_type {};

template<class T>
struct has_method_print<T, std::void_t<decltype(std::declval<const T&>().print(std::declval<std::ostream&>()))>> :
std::true_type {};

template<class T>
inline constexpr bool has_method_print_v = has_method_print<T>::value;

template<class T>
std::enable_if_t<has_method_print_v<T>, void> print(std::ostream& os, const T& object) {
    return object.print(os);
}


template<size_t Id, class T>
void compute_print(std::ostream& os, const T& tuple) {
    if constexpr (Id == std::tuple_size_v<T> - 1) {
        auto v = std::get<Id>(tuple);
        os << v;
    } else {
        auto v = std::get<Id>(tuple);
        os << v << ' ';
        return compute_print<Id + 1>(os, tuple);
    }
}


template<class T>
std::enable_if_t<is_figurelike_tuple_v<T>, void> print(std::ostream& os, const T& object) {
    if constexpr (std::tuple_size_v<T> < 3) {
        throw std::logic_error("invalid print");
    } else {
        return compute_print<0>(os, object);
    }
}



#endif //LAB4_TEMPLATES_HPP
