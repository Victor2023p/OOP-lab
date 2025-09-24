#include "Library.h"
#include <iostream>
#include <string>
#include <sstream> // Для роботи з stringstream

using namespace std;

int main() {
    setlocale(LC_ALL, "Ukrainian");

    Book initialBooks[] = {
        Book("Franko", "Berkyt", "Old tiger", 2021, 320),
        Book("Shevchenko", "Kobzar", "Folio", 2021, 450),
        Book("Kostenko", "Berestechko", "NLTY", 2022, 180)
    };

    int bookCount = sizeof(initialBooks) / sizeof(Book);

    Library myLibrary(initialBooks, bookCount);

    myLibrary.showAllBooks();

    char searchTerm[256];
    int searchYear;
    string choiceStr;
    int choice;

    do {
        cout << "\n===========================\n";
        cout << "Меню:\n";
        cout << "1. Пошук за прiзвищем автора\n";
        cout << "2. Пошук за назвою книги\n";
        cout << "3. Пошук за видавництвом\n";
        cout << "4. Пошук за роком видання\n";
        cout << "0. Вихiд\n";
        cout << "Ваш вибiр: ";

        cin >> choiceStr;
        cin.ignore();

        stringstream ss(choiceStr);
        if (ss >> choice) {
            switch (choice) {
            case 1:
                cout << "Введіть прізвище автора: ";
                cin.getline(searchTerm, 256);
                myLibrary.searchByAuthor(searchTerm);
                break;
            case 2:
                cout << "Введіть назву книги: ";
                cin.getline(searchTerm, 256);
                myLibrary.searchByTitle(searchTerm);
                break;
            case 3:
                cout << "Введіть видавництво книги: ";
                cin.getline(searchTerm, 256);
                myLibrary.searchByPublisher(searchTerm);
                break;
            case 4:
                cout << "Введіть рік видання книги: ";
                cin >> searchYear;
                myLibrary.searchByYear(searchYear);
                cin.ignore();
                break;
            case 0:
                cout << "Програма завершує роботу.\n";
                break;
            default:
                cout << "Некоректний вибір. Спробуйте ще раз.\n";
            }
        }
        else {
            cout << "Некоректний формат вибору. Будь ласка, введiть число.\n";
            choice = -1; 
        }

    } while (choice != 0);

    return 0;
}