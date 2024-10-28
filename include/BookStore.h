#ifndef BOOKSTORE_H
#define BOOKSTORE_H
#include "Book.h"
#include <sqlite3.h>
#include <vector>

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

  [[nodiscard]] std::vector<std::shared_ptr<Book>>
  listBooks(SortType sortType) const;

  [[nodiscard]] std::vector<std::shared_ptr<Book>>
  findBooksInPriceRange(double minPrice, double maxPrice) const;

  BookStore(const BookStore &) = delete;
  BookStore &operator=(const BookStore &) = delete;
};

#endif // BOOKSTORE_H
