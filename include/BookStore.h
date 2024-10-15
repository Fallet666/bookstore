//
// Created by user on 15.10.2024.
//

#ifndef BOOKSTORE_H
#define BOOKSTORE_H
#include <random>
#include <string>
#include <vector>
#include <sqlite3.h>

class Book {
public:
    Book(std::string _title, std::string _author, int _year, double _price)
        : title(std::move(_title)), author(std::move(_author)), year(_year), price(_price) {}

    [[nodiscard]] std::string getTitle() const { return title; }
    [[nodiscard]] std::string getAuthor() const { return author; }
    [[nodiscard]] int getYear() const { return year; }
    [[nodiscard]] double getPrice() const { return price; }

    bool operator<(const Book& other) const {
        return title < other.title;
    }

    bool operator==(const Book& other) const {
        return title == other.title;
    }

private:
    std::string title;
    std::string author;
    int year;
    double price;
};

enum class SortType {
    Title,
    Author,
    Year
};


class BookStore {
private:
    sqlite3* db{};
public:
    explicit BookStore(const std::string& dbPath);
    ~BookStore();
    void createTable() const;
    void addBook(const Book& book) const;
    void removeBook(const std::string& title) const;
    [[nodiscard]] const Book* findBook(const std::string& title) const;
    [[nodiscard]] std::vector<Book> listBooks(SortType sortType) const;
    [[nodiscard]] std::vector<Book> findBooksInPriceRange(double minPrice, double maxPrice) const;
};



#endif //BOOKSTORE_H
