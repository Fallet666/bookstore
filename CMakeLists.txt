cmake_minimum_required(VERSION 3.28)
project(bookstore)

set(CMAKE_CXX_STANDARD 17)

add_executable(bookstore src/main.cpp
        include/BookStore.h
        src/BookStore.cpp)

# Добавляем библиотеку SQLite3
find_package(SQLite3 REQUIRED)
target_link_libraries(bookstore SQLite::SQLite3)