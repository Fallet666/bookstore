#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>


class Book {
public:
    Book(std::string _title, std::string _author, int _year, double _price);

    [[nodiscard]] std::string getTitle() const;

    [[nodiscard]] std::string getAuthor() const;

    [[nodiscard]] int getYear() const;

    [[nodiscard]] double getPrice() const;

    bool operator<(const Book &other) const;

    bool operator==(const Book &other) const;

    friend std::ostream &operator<<(std::ostream &os, const Book &book);

private:
    std::string title;
    std::string author;
    int year;
    double price;
};


#endif // BOOK_H
