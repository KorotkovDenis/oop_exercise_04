#ifndef LAB4_TRIANGLE_HPP
#define LAB4_TRIANGLE_HPP

#include <algorithm>
#include <iostream>
#include <exception>
#include "Vertex.hpp"

template<class T>
struct triangle {
    vertex<T> vertices[3];

    triangle(std::istream& is);

    vertex<T> center() const;
    double area() const;
    void print(std::ostream& os) const;
};

template<class T>
triangle<T>::triangle(std::istream& is) {
    for(int i = 0; i < 3; ++i){
        is >> vertices[i];
    }
    if (area() == 0) {
        throw std::logic_error("invalid");
    }
}

template<class T>
double triangle<T>::area() const {
    const T dx1 = vertices[1].x - vertices[0].x;
    const T dy1 = vertices[1].y - vertices[0].y;
    const T dx2 = vertices[2].x - vertices[0].x;
    const T dy2 = vertices[2].y - vertices[0].y;
    return std::abs(dx1 * dy2 - dy1 * dx2) * 0.5;
}


template<class T>
void triangle<T>::print(std::ostream& os) const {
    for(int i = 0; i < 3; ++i){
        os << '[' << vertices[i] << ']';
        if(i + 1 != 3){
            os << ' ';
        }
    }
}


template<class T>
vertex<T> triangle<T>::center() const {
    vertex<T> ans = {0, 0};
    for (int i = 0; i < 3; ++i) {
        ans.x += vertices[i].x;
        ans.y += vertices[i].y;
    }
    ans = {ans.x / 3, ans.y / 3};
    return ans;
}

#endif //LAB4_TRIANGLE_HPP
