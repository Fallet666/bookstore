#include <gtest/gtest.h>
#include "BookStore.h"

class BookStoreTest : public ::testing::Test {
protected:
    BookStore store;

    // Этот метод будет вызван перед каждым тестом
    void SetUp() override {
        // Добавляем книгу перед тестами
        store.addBook(Book("Test Title", "Test Author", 2024, 29.99));
    }
};

TEST_F(BookStoreTest, AddBookSuccess) {
    EXPECT_NO_THROW(store.addBook(Book("Another Book", "Another Author", 2024, 19.99)));
}

TEST_F(BookStoreTest, FindBookSuccess) {
    EXPECT_NO_THROW(store.findBook("Test Title")); // Убедитесь, что книга найдена
}

TEST_F(BookStoreTest, RemoveBookSuccess) {
    EXPECT_NO_THROW(store.removeBook("Test Title")); // Убедитесь, что книга может быть удалена
}

TEST_F(BookStoreTest, FindBookNotFound) {
    EXPECT_THROW(store.findBook("Nonexistent Title"), std::runtime_error);
}
