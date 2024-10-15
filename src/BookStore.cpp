#include "BookStore.h"
#include <stdexcept>

BookStore::BookStore(const std::string &dbPath) {
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        throw std::runtime_error("Не удалось открыть базу данных: " + std::string(sqlite3_errmsg(db)));
    }
    createTable();
}

BookStore::~BookStore() {
    sqlite3_close(db);
}

void BookStore::createTable() const {
    const char *sql = "CREATE TABLE IF NOT EXISTS books ("
            "title TEXT PRIMARY KEY,"
            "author TEXT,"
            "year INTEGER,"
            "price REAL"
            ");";

    char *errMsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::string errorMessage = "Ошибка создания таблицы: " + std::string(errMsg);
        sqlite3_free(errMsg);
        throw std::runtime_error(errorMessage);
    }
}

void BookStore::addBook(const Book &book) const {
    const char *sql = "INSERT INTO books (title, author, year, price) VALUES (?, ?, ?, ?);";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Ошибка подготовки запроса: " + std::string(sqlite3_errmsg(db)));
    }

    sqlite3_bind_text(stmt, 1, book.getTitle().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, book.getAuthor().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, book.getYear());
    sqlite3_bind_double(stmt, 4, book.getPrice());

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Ошибка добавления книги: " + std::string(sqlite3_errmsg(db)));
    }
    sqlite3_finalize(stmt);
}

void BookStore::removeBook(const std::string &title) const {
    const char *sql = "DELETE FROM books WHERE title = ?;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Ошибка подготовки запроса: " + std::string(sqlite3_errmsg(db)));
    }

    sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Ошибка удаления книги: " + std::string(sqlite3_errmsg(db)));
    }
    if (sqlite3_changes(db) == 0) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Книга с названием \"" + title + "\" не найдена.");
    }
    sqlite3_finalize(stmt);
}

const Book *BookStore::findBook(const std::string &title) const {
    const char *sql = "SELECT * FROM books WHERE title = ?;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Ошибка подготовки SQL-запроса: " + std::string(sqlite3_errmsg(db)));
    }

    sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string foundTitle = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        std::string author = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        int year = sqlite3_column_int(stmt, 3);
        double price = sqlite3_column_double(stmt, 4);

        sqlite3_finalize(stmt);
        return new Book(foundTitle, author, year, price);
    }

    sqlite3_finalize(stmt);
    throw std::runtime_error("Книга с названием \"" + title + "\" не найдена.");
}

std::vector<Book> BookStore::listBooks(SortType sortType) const {
    std::string orderBy;

    switch (sortType) {
        case SortType::Title:
            orderBy = "title";
            break;
        case SortType::Author:
            orderBy = "author";
            break;
        case SortType::Year:
            orderBy = "year";
            break;
    }

    std::string sql = "SELECT * FROM books ORDER BY " + orderBy + ";";
    sqlite3_stmt *stmt;
    std::vector<Book> books;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Ошибка подготовки SQL-запроса: " + std::string(sqlite3_errmsg(db)));
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string title = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        std::string author = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        int year = sqlite3_column_int(stmt, 3);
        double price = sqlite3_column_double(stmt, 4);
        books.emplace_back(title, author, year, price);
    }

    sqlite3_finalize(stmt);
    return books;
}

std::vector<Book> BookStore::findBooksInPriceRange(double minPrice, double maxPrice) const {
    const char *sql = "SELECT * FROM books WHERE price BETWEEN ? AND ?;";
    sqlite3_stmt *stmt;
    std::vector<Book> books;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Ошибка подготовки SQL-запроса: " + std::string(sqlite3_errmsg(db)));
    }

    sqlite3_bind_double(stmt, 1, minPrice);
    sqlite3_bind_double(stmt, 2, maxPrice);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string title = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        std::string author = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        int year = sqlite3_column_int(stmt, 3);
        double price = sqlite3_column_double(stmt, 4);
        books.emplace_back(title, author, year, price);
    }

    sqlite3_finalize(stmt);
    return books;
}
