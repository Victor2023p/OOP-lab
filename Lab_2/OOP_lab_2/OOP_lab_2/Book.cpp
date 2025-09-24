#include "Book.h"
#include <cstring>

using namespace std;

Book::Book() {
    authorLastName = nullptr;
    title = nullptr;
    publisher = nullptr;
    year = 0;
    pages = 0;
}

Book::Book(const char* author, const char* bookTitle, const char* pub, int y, int p) {
    authorLastName = new char[strlen(author) + 1];
    strcpy_s(authorLastName, strlen(author) + 1, author);

    title = new char[strlen(bookTitle) + 1];
    strcpy_s(title, strlen(bookTitle) + 1, bookTitle);

    publisher = new char[strlen(pub) + 1];
    strcpy_s(publisher, strlen(pub) + 1, pub);

    year = y;
    pages = p;
}

Book::~Book() {
    delete[] authorLastName;
    delete[] title;
    delete[] publisher;
}

void Book::show() {
    setlocale(LC_ALL, "Ukrainian");
    cout << "  - Автор: " << (authorLastName ? authorLastName : "Невiдомо") << endl;
    cout << "  - Назва: " << (title ? title : "Невiдомо") << endl;
    cout << "  - Видавництво: " << (publisher ? publisher : "Невiдомо") << endl;
    cout << "  - Рiк видання: " << year << endl;
    cout << "  - Кiлькiсть сторiнок: " << pages << endl;
    cout << endl;
}


void Book::setAuthorLastName(const char* value) {
    delete[] authorLastName;
    if (value) {
        authorLastName = new char[strlen(value) + 1];
        strcpy_s(authorLastName, strlen(value) + 1, value);
    }
    else {
        authorLastName = nullptr;
    }
}

void Book::setTitle(const char* value) {
    delete[] title;
    if (value) {
        title = new char[strlen(value) + 1];
        strcpy_s(title, strlen(value) + 1, value);
    }
    else {
        title = nullptr;
    }
}

void Book::setPublisher(const char* value) {
    delete[] publisher;
    if (value) {
        publisher = new char[strlen(value) + 1];
        strcpy_s(publisher, strlen(value) + 1, value);
    }
    else {
        publisher = nullptr;
    }
}

void Book::setYear(int value) {
    year = value;
}

void Book::setPages(int value) {
    pages = value;
}

char* Book::getAuthorLastName() { return authorLastName; }
char* Book::getTitle() { return title; }
char* Book::getPublisher() { return publisher; }
int Book::getYear() { return year; }
int Book::getPages() { return pages; }