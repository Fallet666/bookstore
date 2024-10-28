#ifndef BOOKSTOREUI_H
#define BOOKSTOREUI_H

#include "BookStore.h"
#include <iostream>

class BookStoreUI {
private:
  BookStore store;

  void handleAddBook() const;

  void handleRemoveBook() const;

  void handleFindBook() const;

  void handleListBooks() const;

  void handleFindBooksInPriceRange() const;

  static void printMenu();

public:
  explicit BookStoreUI(const std::string &dbPath);

  void handleUserInput() const;
};

#endif
