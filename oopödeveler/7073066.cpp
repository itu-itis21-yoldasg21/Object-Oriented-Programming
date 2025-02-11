//Gülce Su Yoldaş 820210331

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <iomanip>
#include <algorithm>

class Book {
public:
    int book_id;
    int publication_year;
    int author_ID;
    int publisher_ID;
    std::string book_title;

    Book() {}

    Book(int bookid, int publy, int authid, int publid, std::string title)
        : book_id(bookid), publication_year(publy), author_ID(authid), publisher_ID(publid), book_title(title) {}

    void print() const {
        std::cout << std::setw(10) << book_id
                  << std::setw(20) << publication_year
                  << std::setw(25) << author_ID
                  << std::setw(15) << publisher_ID
                  << std::setw(14) << book_title << std::endl;
    }
};

std::map<int, std::string> publishers;
std::map<int, std::string> authors;
std::map<int, Book> books;

void seePublishers() {
    std::ifstream file("PUBLISHERS.TXT");
    if (!file.is_open()) {
        std::cerr << "Error opening PUBLISHERS.TXT" << std::endl;
        return;
    }
    int id;
    std::string name;
    while (file >> id) {
        file.ignore();
        std::getline(file, name);
        // Convert publisher name to uppercase
        std::transform(name.begin(), name.end(), name.begin(), ::toupper);
        publishers[id] = name;
    }
    file.close();
}

void seeAuthors() {
    std::ifstream file("AUTHORS.TXT");
    if (!file.is_open()) {
        std::cerr << "Error opening AUTHORS.TXT" << std::endl;
        return;
    }
    int id;
    std::string name;
    while (file >> id) {
        file.ignore();
        std::getline(file, name);
        authors[id] = name;
    }
    file.close();
}

void seeBooks() {
    std::ifstream file("BOOKS.TXT");
    if (!file.is_open()) {
        std::cerr << "Error opening BOOKS.TXT" << std::endl;
        return;
    }
    int book_id, publication_year, author_ID, publisher_ID;
    std::string book_title;
    while (file >> book_id >> publication_year >> author_ID >> publisher_ID) {
        file.ignore();
        std::getline(file, book_title);
        books[book_id] = Book(book_id, publication_year, author_ID, publisher_ID, book_title);
    }
    file.close();
}

void printBooks() {
    std::cout << "LISTS OF ALL BOOKS GROUPED BY PUBLISHERS" << std::endl;
    std::cout << "========================================" << std::endl;

    int total_books = 0;

    for (const auto& pub : publishers) {
        int pub_id = pub.first;
        std::string pub_name = pub.second;

        std::vector<Book> pub_books;
        for (const auto& book : books) {
            if (book.second.publisher_ID == pub_id) {
                pub_books.push_back(book.second);
            }
        }

        if (!pub_books.empty()) {
            std::cout << "PUBLISHER ID    : " << std::setfill('0') << std::setw(3) << pub_id << std::setfill(' ') << std::endl;
            std::cout << "PUBLISHER NAME  : " << pub_name << std::endl;
            std::cout << "NUMBER OF BOOKS : " << pub_books.size() << std::endl;

            std::cout << std::setw(10) << "BOOK_ID"
                      << std::setw(20) << "PUBLICATION_YEAR"
                      << std::setw(25) << "AUTHOR_FULLNAME"
                      << std::setw(14) << "BOOK_TITLE" << std::endl;

            for (const auto& book : pub_books) {
                std::cout << std::setw(10) << book.book_id
                          << std::setw(20) << book.publication_year
                          << std::setw(25) << authors[book.author_ID]
                          << " " << book.book_title << std::endl;
            }

            std::cout << "--------------------------------------------------------------------------------------------------" << std::endl;
            total_books += pub_books.size();
        }
    }

    std::cout << "TOTAL NUMBER OF ALL BOOKS : " << total_books << std::endl;
    std::cout << std::endl << "Program finished." << std::endl;
}

int main() {
    seePublishers();
    seeAuthors();
    seeBooks();
    printBooks();

    return 0;
}
