#ifndef BOOKSTORE_H
#define BOOKSTORE_H
#include <random>
#include <sqlite3.h>
#include <vector>
#include "Book.h"

enum class SortType { Title, Author, Year };


class BookStore {
private:
    sqlite3 *db{};
    [[nodiscard]] int getBookCount() const;

public:
    explicit BookStore(const std::string &dbPath);

    ~BookStore();

    void createTable() const;

    void addBook(const Book &book) const;

    void removeBook(const std::string &title) const;

    [[nodiscard]] const Book *findBook(const std::string &title) const;

    [[nodiscard]] std::vector<Book> listBooks(SortType sortType) const;

    [[nodiscard]] std::vector<Book> findBooksInPriceRange(double minPrice, double maxPrice) const;
};


#endif // BOOKSTORE_H
