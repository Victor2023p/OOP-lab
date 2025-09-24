#include "Library.h"
#include <iostream>
#include <cstring>

using namespace std;

Library::Library(Book* initialBooks, int count) {
    setlocale(LC_ALL, "Ukrainian");
    bookCount = count;
    books = new Book[bookCount];
    for (int i = 0; i < bookCount; i++) {
        books[i].setAuthorLastName(initialBooks[i].getAuthorLastName());
        books[i].setTitle(initialBooks[i].getTitle());
        books[i].setPublisher(initialBooks[i].getPublisher());
        books[i].setYear(initialBooks[i].getYear());
        books[i].setPages(initialBooks[i].getPages());
    }
}

Library::~Library() {
    delete[] books;
}

void Library::showAllBooks() {
    setlocale(LC_ALL, "Ukrainian");
    cout << "--- ������ ��i� ���� � �i��i����i ---" << endl;
    for (int i = 0; i < bookCount; i++) {
        cout << "����� #" << i + 1 << ":" << endl;
        books[i].show();
    }
}

void Library::searchByAuthor(const char* author) {
    setlocale(LC_ALL, "Ukrainian");
    cout << "--- ����� ���� �� �������: " << author << " ---" << endl;
    bool found = false;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].getAuthorLastName() && strcmp(books[i].getAuthorLastName(), author) == 0) {
            books[i].show();
            found = true;
        }
    }
    if (!found) {
        cout << "���� ����� ������ �� ��������." << endl;
    }
}

void Library::searchByTitle(const char* title) {
    setlocale(LC_ALL, "Ukrainian");
    cout << "--- ����� ���� �� ������: " << title << " ---" << endl;
    bool found = false;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].getTitle() && strcmp(books[i].getTitle(), title) == 0) {
            books[i].show();
            found = true;
        }
    }
    if (!found) {
        cout << "���� � ����� ������ �� ��������." << endl;
    }
}

void Library::searchByPublisher(const char* publisher) {
    setlocale(LC_ALL, "Ukrainian");
    cout << "--- ����� ���� �� ������������: " << publisher << " ---" << endl;
    bool found = false;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].getPublisher() && strcmp(books[i].getPublisher(), publisher) == 0) {
            books[i].show();
            found = true;
        }
    }
    if (!found) {
        cout << "���� ����� ����������� �� ��������." << endl;
    }
}

void Library::searchByYear(int year) {
    setlocale(LC_ALL, "Ukrainian");
    cout << "--- ����� ���� �� ����� �������: " << year << " ---" << endl;
    bool found = false;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].getYear() == year) {
            books[i].show();
            found = true;
        }
    }
    if (!found) {
        cout << "����, ������� � " << year << " ���i, �� ��������." << endl;
    }
}