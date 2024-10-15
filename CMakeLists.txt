cmake_minimum_required(VERSION 3.28)
project(bookstore)

set(CMAKE_CXX_STANDARD 17)

add_executable(bookstore main.cpp
        BookStore.h
        BookStore.cpp)