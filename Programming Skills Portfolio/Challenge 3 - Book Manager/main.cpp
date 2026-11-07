#include <algorithm>
#include <cctype>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// AI assistance: OpenAI ChatGPT helped plan and draft this solution.
// Prompt: "so do everything that needed and make sure evrything is workinh and uploaded to github, work should be excellent and the best"

std::string toLower(std::string text) {
    std::transform(text.begin(), text.end(), text.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });
    return text;
}

class Book {
public:
    Book(std::string title, std::string author, int pages, std::string id, bool borrowed)
        : title_(title), author_(author), pages_(pages), id_(id), borrowed_(borrowed) {}
    const std::string& getId() const { return id_; }
    bool isBorrowed() const { return borrowed_; }
    bool borrowBook() {
        if (borrowed_) return false;
        borrowed_ = true;
        return true;
    }
    bool returnBook() {
        if (!borrowed_) return false;
        borrowed_ = false;
        return true;
    }
    void displayRow() const {
        std::cout << std::left << std::setw(6) << id_ << std::setw(32) << title_
                  << std::setw(25) << author_ << std::right << std::setw(7) << pages_
                  << "  " << (borrowed_ ? "Borrowed" : "Available") << '\n';
    }
    void displayDetails() const {
        std::cout << "ID: " << id_ << "\nTitle: " << title_ << "\nAuthor: " << author_
                  << "\nPages: " << pages_ << "\nStatus: "
                  << (borrowed_ ? "Borrowed" : "Available") << '\n';
    }
private:
    std::string title_;
    std::string author_;
    int pages_;
    std::string id_;
    bool borrowed_;
};

bool loadBooks(std::vector<Book>& books) {
    std::ifstream file("bookData.txt");
    if (!file) file.open("Programming Skills Portfolio/Challenge 3 - Book Manager/bookData.txt");
    if (!file) return false;
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream row(line);
        std::string title, author, pagesText, id, status;
        if (!std::getline(row, title, ',') || !std::getline(row, author, ',') ||
            !std::getline(row, pagesText, ',') || !std::getline(row, id, ',') ||
            !std::getline(row, status)) continue;
        try {
            books.emplace_back(title, author, std::stoi(pagesText), id, toLower(status) == "true");
        } catch (const std::exception&) { continue; }
    }
    return !books.empty();
}

Book* findBook(std::vector<Book>& books, const std::string& id) {
    for (Book& book : books) if (book.getId() == id) return &book;
    return nullptr;
}

void showAllBooks(const std::vector<Book>& books) {
    std::cout << std::left << std::setw(6) << "ID" << std::setw(32) << "Title"
              << std::setw(25) << "Author" << std::right << std::setw(7) << "Pages"
              << "  Status\n";
    for (const Book& book : books) book.displayRow();
}

int main() {
    std::vector<Book> books;
    if (!loadBooks(books)) {
        std::cout << "Could not load bookData.txt or it contains no valid books.\n";
        return 1;
    }
    std::string choice;
    while (true) {
        std::cout << "\nBook Manager\n1. View all books\n2. View a book by ID\n"
                  << "3. Borrow a book\n4. Return a book\n5. Exit\nChoose an option: ";
        if (!std::getline(std::cin, choice)) break;
        if (choice == "1") showAllBooks(books);
        else if (choice == "2" || choice == "3" || choice == "4") {
            std::string id;
            std::cout << "Enter the book ID: ";
            if (!std::getline(std::cin, id)) break;
            Book* book = findBook(books, id);
            if (book == nullptr) std::cout << "No book has that ID.\n";
            else if (choice == "2") book->displayDetails();
            else if (choice == "3") std::cout << (book->borrowBook() ? "Book borrowed.\n" : "Already borrowed.\n");
            else std::cout << (book->returnBook() ? "Book returned.\n" : "Was not borrowed.\n");
        } else if (choice == "5") {
            std::cout << "Goodbye!\n";
            break;
        } else std::cout << "Choose a number from 1 to 5.\n";
    }
    return 0;
}
