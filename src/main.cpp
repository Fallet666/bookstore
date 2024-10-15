#include "BookStoreUI.h"
#include <string>

int main() {
    const std::string path = "../db/bookstore.db";
    const BookStoreUI ui(path);
    ui.handleUserInput();
}
