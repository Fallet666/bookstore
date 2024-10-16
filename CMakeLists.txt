cmake_minimum_required(VERSION 3.28)
project(bookstore)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)

# Создаем библиотеку
add_library(bookstore_lib
        src/BookStore.cpp
        src/BookStoreUI.cpp
        src/Book.cpp
)

# Создаем исполняемый файл для вашего проекта
add_executable(bookstore
        src/main.cpp
)

target_compile_options(bookstore_lib PRIVATE -finput-charset=UTF-8 -fexec-charset=UTF-8)
target_compile_options(bookstore PRIVATE -finput-charset=UTF-8 -fexec-charset=UTF-8)


# Связываем исполняемый файл с библиотекой
target_link_libraries(bookstore bookstore_lib)

# Включаем тесты
enable_testing()

# Находим библиотеку GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Добавляем исполняемый файл для тестов
add_executable(tests tests/tests.cpp)

# Связываем тесты с библиотеками
target_link_libraries(tests GTest::GTest GTest::Main bookstore_lib)

# Добавляем библиотеку SQLite3
find_package(SQLite3 REQUIRED)
target_link_libraries(bookstore_lib SQLite::SQLite3)
target_link_libraries(tests SQLite::SQLite3)

add_test(NAME BookStoreTests COMMAND tests)
