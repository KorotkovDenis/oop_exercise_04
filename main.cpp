#include <algorithm>
#include <iostream>
#include <exception>
#include <type_traits>
#include <tuple>
#include "Vertex.hpp"
#include "Templates.hpp"
#include "Triangle.hpp"
#include "Rectangle.hpp"
#include "Square.hpp"


int main() {
    while(1) {
        char object_type;
        std::cin >> object_type;
        if (object_type == 't') {
            triangle<double> figure(std::cin);
            std::cout << "area:" << area(figure) << '\n';
            std::cout << "center:" << center(figure) << '\n';
            print(std::cout, figure);
        } else if(object_type == 's') {
            square<double> figure(std::cin);
            std::cout << "area:" << area(figure) << '\n';
            std::cout << "center:" << center(figure) << '\n';
            print(std::cout, figure);
        } else if (object_type == 'r') {
            rectangle<double> figure(std::cin);
            std::cout << "area:" << area(figure) << '\n';
            std::cout << "center:" << center(figure) << '\n';
            print(std::cout, figure);
        } else if (object_type == 'u') {
            std::tuple<vertex<double>, vertex<double>, vertex<double> > figure;

            std::cin >> std::get<0>(figure) >> std::get<1>(figure) >> std::get<2>(figure);
            std::cout << "area:" << area(figure) << '\n';
            std::cout << "center:" << center(figure) << '\n';
            print(std::cout, figure);
        } else if (object_type == 'q') {
            return 0;
        }
    }
}




