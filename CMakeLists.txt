cmake_minimum_required(VERSION 3.28)
project(bookstore)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)
add_executable(bookstore src/main.cpp
        include/BookStore.h
        src/BookStore.cpp
        src/BookStoreUI.cpp
        include/BookStoreUI.h
        src/Book.cpp
        include/Book.h
        tests/tests.cpp)

enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests tests/tests.cpp src/BookStore.cpp src/Book.cpp)


# Добавляем библиотеку SQLite3
find_package(SQLite3 REQUIRED)
target_link_libraries(bookstore SQLite::SQLite3)
target_link_libraries(tests GTest::GTest GTest::Main SQLite::SQLite3)

add_test(NAME BookStoreTests COMMAND tests)
