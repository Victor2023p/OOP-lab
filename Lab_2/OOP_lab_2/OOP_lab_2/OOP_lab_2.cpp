#include "Library.h"
#include <iostream>
#include <string>
#include <sstream> // ��� ������ � stringstream

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
        cout << "����:\n";
        cout << "1. ����� �� ��i������ ������\n";
        cout << "2. ����� �� ������ �����\n";
        cout << "3. ����� �� ������������\n";
        cout << "4. ����� �� ����� �������\n";
        cout << "0. ���i�\n";
        cout << "��� ���i�: ";

        cin >> choiceStr;
        cin.ignore();

        stringstream ss(choiceStr);
        if (ss >> choice) {
            switch (choice) {
            case 1:
                cout << "������ ������� ������: ";
                cin.getline(searchTerm, 256);
                myLibrary.searchByAuthor(searchTerm);
                break;
            case 2:
                cout << "������ ����� �����: ";
                cin.getline(searchTerm, 256);
                myLibrary.searchByTitle(searchTerm);
                break;
            case 3:
                cout << "������ ����������� �����: ";
                cin.getline(searchTerm, 256);
                myLibrary.searchByPublisher(searchTerm);
                break;
            case 4:
                cout << "������ �� ������� �����: ";
                cin >> searchYear;
                myLibrary.searchByYear(searchYear);
                cin.ignore();
                break;
            case 0:
                cout << "�������� ������� ������.\n";
                break;
            default:
                cout << "����������� ����. ��������� �� ���.\n";
            }
        }
        else {
            cout << "����������� ������ ������. ���� �����, ����i�� �����.\n";
            choice = -1; 
        }

    } while (choice != 0);

    return 0;
}