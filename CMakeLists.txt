cmake_minimum_required(VERSION 3.2)

project(lab4)

add_executable(lab4
        main.cpp
        Triangle.hpp
        Rectangle.hpp
        Square.hpp
        Vertex.hpp
        Templates.hpp
        )

set_property(TARGET lab4 PROPERTY CXX_STANDARD 17)