#include "../include/BookStoreUI.h"

BookStoreUI::BookStoreUI(BookStore &store) : store(store) {
}

void BookStoreUI::handleUserInput() const {
    int choice;
    do {
        printMenu();
        std::cin >> choice;
        switch (choice) {
            case 1:
                handleAddBook();
                break;
            case 2:
                handleRemoveBook();
                break;
            case 3:
                handleFindBook();
                break;
            case 4:
                handleListBooks();
                break;
            case 5:
                handleFindBooksInPriceRange();
                break;
            case 6:
                std::cout << "Выход из программы." << std::endl;
                break;
            default:
                std::cout << "Некорректный выбор, попробуйте снова." << std::endl;
        }
    } while (choice != 6);
}

void BookStoreUI::handleAddBook() const {
    std::string title, author;
    int year;
    double price;

    std::cout << "Введите название книги: ";
    std::cin.ignore();
    std::getline(std::cin, title);
    std::cout << "Введите автора книги: ";
    std::getline(std::cin, author);
    std::cout << "Введите год издания: ";
    std::cin >> year;
    std::cout << "Введите цену: ";
    std::cin >> price;

    try {
        Book book(title, author, year, price);
        store.addBook(book);
        std::cout << "Книга успешно добавлена!" << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void BookStoreUI::handleFindBook() const {
    std::string title;
    std::cout << "Введите название книги для поиска: ";
    std::cin.ignore();
    std::getline(std::cin, title);

    try {
        const Book *book = store.findBook(title);
        std::cout << "Найдена книга: " << *book << std::endl;
        delete book;
    } catch (const std::exception &e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void BookStoreUI::handleRemoveBook() const {
    std::string title;
    std::cout << "Введите название книги для удаления: ";
    std::cin.ignore();
    std::getline(std::cin, title);

    try {
        store.removeBook(title);
        std::cout << "Книга успешно удалена!" << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void BookStoreUI::handleListBooks() const {
    int sortChoice;
    std::cout << "Выберите тип сортировки: 1 - Название, 2 - Автор, 3 - Год издания: ";
    std::cin >> sortChoice;

    SortType sortType;
    switch (sortChoice) {
        case 1:
            sortType = SortType::Title;
            break;
        case 2:
            sortType = SortType::Author;
            break;
        case 3:
            sortType = SortType::Year;
            break;
        default:
            std::cout << "Некорректный выбор, сортировка по названию." << std::endl;
            sortType = SortType::Title;
    }

    try {
        std::vector<Book> books = store.listBooks(sortType);
        for (const auto &book: books) {
            std::cout << book << std::endl;
        }
    } catch (const std::exception &e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void BookStoreUI::handleFindBooksInPriceRange() const {
    double minPrice, maxPrice;
    std::cout << "Введите минимальную цену: ";
    std::cin >> minPrice;
    std::cout << "Введите максимальную цену: ";
    std::cin >> maxPrice;

    try {
        std::vector<Book> books = store.findBooksInPriceRange(minPrice, maxPrice);
        for (const auto &book: books) {
            std::cout << book << std::endl;
        }
    } catch (const std::exception &e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void BookStoreUI::printMenu() {
    std::cout << "1. Добавить книгу\n"
            << "2. Удалить книгу\n"
            << "3. Найти книгу по названию\n"
            << "4. Показать все книги (сортировка по названию/автору/году издания)\n"
            << "5. Найти книги в ценовом диапазоне\n"
            << "6. Выйти\n"
            << "Выберите опцию: ";
}
