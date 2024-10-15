cmake_minimum_required(VERSION 3.28)
project(bookstore)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)

# Создаем исполняемый файл для вашего проекта
add_executable(bookstore
        src/main.cpp
        src/BookStore.cpp
        src/BookStoreUI.cpp
        src/Book.cpp
)

# Включаем тесты
enable_testing()

# Находим библиотеку GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Добавляем исполняемый файл для тестов
add_executable(tests tests/tests.cpp)
target_link_libraries(tests GTest::GTest GTest::Main)

# Добавляем библиотеку SQLite3
find_package(SQLite3 REQUIRED)
target_link_libraries(bookstore SQLite::SQLite3)
target_link_libraries(tests SQLite::SQLite3)

add_test(NAME BookStoreTests COMMAND tests)
