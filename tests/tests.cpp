#include <gtest/gtest.h>
#include <cstdio>
#include "BookStore.h"

TEST(BookStoreTest, AddBookSuccess) {
    BookStore store1 = BookStore("test1.db");
    store1.addBook(Book("Test Title", "Test Author", 2024, 29.99));
    EXPECT_NO_THROW(store1.addBook(Book("Another Book", "Another Author", 2024, 19.99)));
}

TEST(BookStore, FindBookSuccess) {
    BookStore store2 = BookStore("test2.db");
    store2.addBook(Book("Test Title", "Test Author", 2024, 29.99));
    EXPECT_NO_THROW(store2.findBook("Test Title")); // Убедитесь, что книга найдена
}

TEST(BookStoreTest, RemoveBookSuccess) {
    BookStore store3 = BookStore("test3.db");
    store3.addBook(Book("Test Title", "Test Author", 2024, 29.99));
    EXPECT_NO_THROW(store3.removeBook("Test Title")); // Убедитесь, что книга может быть удалена
}

TEST(BookStoreTest, FindBookNotFound) {
    std::remove("test4.db");
    BookStore store4 = BookStore("test.db");
    store4.addBook(Book("Test Title", "Test Author", 2024, 29.99));
    EXPECT_THROW(store4.findBook("Nonexistent Title"), std::runtime_error);
}
