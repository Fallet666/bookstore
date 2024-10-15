#include <gtest/gtest.h>
#include <cstdio>
#include "BookStore.h"

TEST(BookStoreTest, AddBookSuccess) {
    std::remove("test.db");
    BookStore store = BookStore("test.db");
    store.addBook(Book("Test Title", "Test Author", 2024, 29.99));
    EXPECT_NO_THROW(store.addBook(Book("Another Book", "Another Author", 2024, 19.99)));
}

TEST(BookStore, FindBookSuccess) {
    std::remove("test.db");
    BookStore store = BookStore("test.db");
    store.addBook(Book("Test Title", "Test Author", 2024, 29.99));
    EXPECT_NO_THROW(store.findBook("Test Title")); // Убедитесь, что книга найдена
}

TEST(BookStoreTest, RemoveBookSuccess) {
    std::remove("test.db");
    BookStore store = BookStore("test.db");
    store.addBook(Book("Test Title", "Test Author", 2024, 29.99));
    EXPECT_NO_THROW(store.removeBook("Test Title")); // Убедитесь, что книга может быть удалена
}

TEST(BookStoreTest, FindBookNotFound) {
    std::remove("test.db");
    BookStore store = BookStore("test.db");
    store.addBook(Book("Test Title", "Test Author", 2024, 29.99));
    EXPECT_THROW(store.findBook("Nonexistent Title"), std::runtime_error);
}
