#include "../include/Book.h"

Book::Book(std::string _title, std::string _author, int _year, double _price)
    : title(std::move(_title)), author(std::move(_author)), year(_year), price(_price) {
}

std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
int Book::getYear() const { return year; }
double Book::getPrice() const { return price; }

bool Book::operator<(const Book &other) const {
    return title < other.title;
}

bool Book::operator==(const Book &other) const {
    return title == other.title;
}

std::ostream &operator<<(std::ostream &os, const Book &book) {
    os << "Title: " << book.title << ", Author: " << book.author << ", Price: " << book.price;
    return os;
}
