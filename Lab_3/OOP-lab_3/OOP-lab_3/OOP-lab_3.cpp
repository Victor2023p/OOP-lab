#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>   //  numeric_limits
#include <cctype>   //  isalpha

using namespace std;

void safeIntInput(istream& in, const char* prompt, int& val) {
    cout << prompt;
    while (!(in >> val)) {
        cout << "Помилка: невірний формат! Введіть число.\n";
        in.clear();
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << prompt;
    }
}

struct Finally {
    ~Finally() {
        cout << "Блок finally: цей код виконується завжди\n";
    }
};

class Person {
private:
    string surname;
    string name;
    string patronymic;
    string gender;
    int day, month, year;

    // Допоміжна перевірка для текстових полів
    static bool isAlpha(const string& str) {
        for (char c : str) {
            if (!isalpha((unsigned char)c) && c != ' ') return false;
        }
        return true;
    }

    // Допоміжна функція для введення текстового поля
    void inputAlphaField(istream& in, string& field, const char* prompt, const char* error) {
        do {
            cout << prompt;
            in >> field;
            if (!isAlpha(field))
                cerr << "Помилка: " << error << " Спробуйте ще раз.\n";
        } while (!isAlpha(field));
    }

public:
    Person() : day(1), month(1), year(2000) {}

    Person(string s, string n, string p, string g, int d, int m, int y) {
        if (!isAlpha(s) || !isAlpha(n) || !isAlpha(p) || !isAlpha(g))
            throw invalid_argument("Текстові поля не повинні містити цифр або спецсимволів!");
        setDate(d, m, y);
        surname = s; name = n; patronymic = p; gender = g;
    }

    // Метод встановлення дати з валідацією та генерацією винятків
    void setDate(int d, int m, int y) {
        if (d < 1 || d > 31) throw invalid_argument("Невірний день! (очікується 1-31)");
        if (m < 1 || m > 12) throw invalid_argument("Невірний місяць! (очікується 1-12)");
        if (y < 1900 || y > 2025) throw invalid_argument("Невірний рік! (очікується 1900-2025)");
        day = d; month = m; year = y;
    }

    // === Перевантажені методи пошуку ===
    bool search(const string& s) const { return surname == s; }
    bool search(const string& s, const string& n) const { return surname == s && name == n; }
    bool search(int y) const { return year == y; }
    bool search(int d, int m, int y) const { return day == d && month == m && year == y; }

    // === Перевантаження оператора потокового введення (>>) ===
    friend istream& operator>>(istream& in, Person& p) {

        // Введення текстових полів з перевіркою
        p.inputAlphaField(in, p.surname, "Прiзвище: ", "прiзвище повинно мiстити тiльки букви!");
        p.inputAlphaField(in, p.name, "Iм'я: ", "iм'я повинно містити тiльки букви!");
        p.inputAlphaField(in, p.patronymic, "По батькові: ", "по батькові повинно містити тільки букви!");
        p.inputAlphaField(in, p.gender, "Стать (ч/ж): ", "стать повинна містити тільки букви!");

        // Введення дати з перевіркою формату та діапазону
        bool validDate = false;
        while (!validDate) {
            int d = 0, m = 0, y = 0;

            // Використовуємо глобальну функцію для безпечного введення чисел
            safeIntInput(in, "День народження: ", d);
            safeIntInput(in, "Мiсяць народження: ", m);
            safeIntInput(in, "Рiк народження: ", y);

            Finally f;
            // Перевірка логіки дати (діапазон) за допомогою setDate і try-catch
            try {
                p.setDate(d, m, y);
                validDate = true;
            }
            catch (invalid_argument& e) {
                cout << "Помилка дати: " << e.what() << ". Спробуйте ще раз!\n";
            }
        }

        return in;
    }

    // === Перевантаження оператора потокового виведення (<<) ===
    friend ostream& operator<<(ostream& out, const Person& p) {
        out << p.surname << " " << p.name << " " << p.patronymic
            << " (" << p.gender << "), дата: "
            << p.day << "." << p.month << "." << p.year;
        return out;
    }
};

// ==============================================================================================

int main() {
    setlocale(LC_ALL, "Ukrainian");

    const int SIZE = 5;
    Person people[SIZE];
    int n = 0;

    // Безпечне введення для кількості осіб
    safeIntInput(cin, "Скiльки осiб додати (макс 5): ", n);

    if (n < 1 || n > SIZE) {
        if (n < 1) n = 1; // Додати хоча б одну особу
        if (n > SIZE) n = SIZE;
        cout << "Встановлено кiлькiсть осiб: " << n << endl;
    }

    // Введення даних для кожної особи
    for (int i = 0; i < n; i++) {
        cout << "\n=== Введення особи " << i + 1 << " ===\n";
        cin >> people[i];
    }

    int choice;
    do {
        cout << "\n==============================\n";
        cout << "=== МЕНЮ ПОШУКУ ===\n";
        cout << "1 - Пошук за прiзвищем\n";
        cout << "2 - Пошук за прiзвищем та iм'ям\n";
        cout << "3 - Пошук за роком народження\n";
        cout << "4 - Пошук за повною датою\n";
        cout << "5 - Вихiд\n";

        // --- Виправлене безпечне введення для пункту меню ---
        safeIntInput(cin, "Ваш вибiр: ", choice);

        if (choice < 1 || choice > 5) {
            cout << "Невiрний вибiр. Будь ласка, введiть число від 1 до 5.\n";
            continue;
        }
        // ----------------------------------------------------

        bool found = false;

        if (choice == 1) {
            string s;
            cout << "Введiть прiзвище: "; cin >> s;
            for (int i = 0; i < n; i++)
                if (people[i].search(s)) { cout << people[i] << endl; found = true; }
        }
        else if (choice == 2) {
            string s, nn;
            cout << "Введiть прiзвище: "; cin >> s;
            cout << "Введiть iм'я: "; cin >> nn;
            for (int i = 0; i < n; i++)
                if (people[i].search(s, nn)) { cout << people[i] << endl; found = true; }
        }
        else if (choice == 3) {
            int y;
            safeIntInput(cin, "Введiть рiк: ", y);
            for (int i = 0; i < n; i++)
                if (people[i].search(y)) { cout << people[i] << endl; found = true; }
        }
        else if (choice == 4) {
            int d, m, y;
            safeIntInput(cin, "Введiть день: ", d);
            safeIntInput(cin, "Введiть мiсяць: ", m);
            safeIntInput(cin, "Введiть рiк: ", y);


            for (int i = 0; i < n; i++)
                if (people[i].search(d, m, y)) { cout << people[i] << endl; found = true; }
        }

        if (!found && choice >= 1 && choice <= 4)
            cout << "Осiб не знайдено!\n";

    } while (choice != 5);

    return 0;
}