#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
#include <memory>

class Book {
public:
  explicit Book(std::string _title, std::string _author, int _year,
                double _price);

  [[nodiscard]] std::string getTitle() const;

  [[nodiscard]] std::string getAuthor() const;

  [[nodiscard]] int getYear() const;

  [[nodiscard]] double getPrice() const;

  bool operator<(const Book &other) const;

  bool operator==(const Book &other) const;

  friend std::ostream &operator<<(std::ostream &os, const Book &book);

  Book(const Book &) = delete;
  Book &operator=(const Book &) = delete;

private:
  std::string title;
  std::string author;
  int year;
  double price;
};

#endif // BOOK_H
