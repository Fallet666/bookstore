#include <gtest/gtest.h>
#include <cstdio>
#include "BookStore.h"


// Простой тест добавления книги
TEST(BookStoreTest, AddBookSuccess) {
    std::remove("test.db");
    BookStore store("test.db");
    Book book("Test Title", "Test Author", 2023, 199.99);
    EXPECT_NO_THROW(store.addBook(book));
}

// Тест поиска книги
TEST(BookStoreTest, FindBookSuccess) {
    std::remove("test.db");
    BookStore store("test.db");
    Book book("Test Title", "Test Author", 2023, 199.99);
    store.addBook(book);

    const Book* foundBook = store.findBook("Test Title");
    ASSERT_NE(foundBook, nullptr);
    EXPECT_EQ(foundBook->getTitle(), "Test Title");
    EXPECT_EQ(foundBook->getAuthor(), "Test Author");
    EXPECT_EQ(foundBook->getYear(), 2023);
    EXPECT_EQ(foundBook->getPrice(), 199.99);
    delete foundBook;
}

// Тест удаления книги
TEST(BookStoreTest, RemoveBookSuccess) {
    std::remove("test.db");
    BookStore store("test.db");
    Book book("Test Title", "Test Author", 2023, 199.99);
    store.addBook(book);
    EXPECT_NO_THROW(store.removeBook("Test Title"));
    EXPECT_THROW(store.findBook("Test Title"), std::runtime_error);
}

// Тест поиска несуществующей книги
TEST(BookStoreTest, FindBookNotFound) {
    std::remove("test.db");
    BookStore store("test.db");
    EXPECT_THROW(store.findBook("Nonexistent Title"), std::runtime_error);
}

