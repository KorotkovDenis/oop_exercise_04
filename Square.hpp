#ifndef LAB4_SQUARE_HPP
#define LAB4_SQUARE_HPP

#include <algorithm>
#include <iostream>
#include <exception>
#include "Vertex.hpp"

template<class T>
struct square {
    vertex<T> vertices[4];
    square(std::istream& is);
    vertex<T> center() const;
    double area() const;
    void print(std::ostream& os) const;
};

template<class T>
square<T>::square(std::istream& is) {
    for(int i = 0; i < 4; ++i){
        is >> vertices[i];
    }
    vertex<T> vec1 {vertices[1].x - vertices[0].x, vertices[1].y - vertices[0].y};
    vertex<T> vec2 {vertices[2].x - vertices[1].x, vertices[2].y - vertices[1].y};
    vertex<T> vec3 {vertices[3].x - vertices[2].x, vertices[3].y - vertices[2].y};
    vertex<T> vec4 {vertices[0].x - vertices[3].x, vertices[0].y - vertices[3].y};
    T l1 = vec1.x * vec1.x + vec1.y * vec1.y;
    T l2 = vec2.x * vec2.x + vec2.y * vec2.y;
    T l3 = vec3.x * vec3.x + vec3.y * vec3.y;
    T l4 = vec4.x * vec4.x + vec4.y * vec4.y;
    if (!(l1 == l2 && l2 == l3 && l3 == l4) || !(vec1.x * vec2.x + vec1.y * vec2.y == 0)) {
        throw std::logic_error("invalid");
    }
}

template<class T>
double square<T>::area() const {
    const T dx1 = vertices[1].x - vertices[0].x;
    const T dy1 = vertices[1].y - vertices[0].y;
    const T dx2 = vertices[2].x - vertices[0].x;
    const T dy2 = vertices[2].y - vertices[0].y;
    return std::abs(dx1 * dy2 - dy1 * dx2);
}


template<class T>
void square<T>::print(std::ostream& os) const {
    for(int i = 0; i < 4; ++i){
        os << '[' << vertices[i] << ']';
        if(i + 1 != 4){
            os << ' ';
        }
    }
}


template<class T>
vertex<T> square<T>::center() const {
    vertex<T> ans = {0, 0};
    for (int i = 0; i < 4; ++i) {
        ans.x += vertices[i].x;
        ans.y += vertices[i].y;
    }
    ans = {ans.x / 4, ans.y / 4};
    return ans;
}


#endif //LAB4_SQUARE_HPP
