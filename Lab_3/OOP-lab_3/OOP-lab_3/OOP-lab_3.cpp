#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>   //  numeric_limits
#include <cctype>   //  isalpha

using namespace std;

void safeIntInput(istream& in, const char* prompt, int& val) {
    cout << prompt;
    while (!(in >> val)) {
        cout << "�������: ������� ������! ������ �����.\n";
        in.clear();
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << prompt;
    }
}

struct Finally {
    ~Finally() {
        cout << "���� finally: ��� ��� ���������� ������\n";
    }
};

class Person {
private:
    string surname;
    string name;
    string patronymic;
    string gender;
    int day, month, year;

    // �������� �������� ��� ��������� ����
    static bool isAlpha(const string& str) {
        for (char c : str) {
            if (!isalpha((unsigned char)c) && c != ' ') return false;
        }
        return true;
    }

    // �������� ������� ��� �������� ���������� ����
    void inputAlphaField(istream& in, string& field, const char* prompt, const char* error) {
        do {
            cout << prompt;
            in >> field;
            if (!isAlpha(field))
                cerr << "�������: " << error << " ��������� �� ���.\n";
        } while (!isAlpha(field));
    }

public:
    Person() : day(1), month(1), year(2000) {}

    Person(string s, string n, string p, string g, int d, int m, int y) {
        if (!isAlpha(s) || !isAlpha(n) || !isAlpha(p) || !isAlpha(g))
            throw invalid_argument("������� ���� �� ������ ������ ���� ��� �����������!");
        setDate(d, m, y);
        surname = s; name = n; patronymic = p; gender = g;
    }

    // ����� ������������ ���� � ��������� �� ���������� �������
    void setDate(int d, int m, int y) {
        if (d < 1 || d > 31) throw invalid_argument("������� ����! (��������� 1-31)");
        if (m < 1 || m > 12) throw invalid_argument("������� �����! (��������� 1-12)");
        if (y < 1900 || y > 2025) throw invalid_argument("������� ��! (��������� 1900-2025)");
        day = d; month = m; year = y;
    }

    // === ������������ ������ ������ ===
    bool search(const string& s) const { return surname == s; }
    bool search(const string& s, const string& n) const { return surname == s && name == n; }
    bool search(int y) const { return year == y; }
    bool search(int d, int m, int y) const { return day == d && month == m && year == y; }

    // === �������������� ��������� ���������� �������� (>>) ===
    friend istream& operator>>(istream& in, Person& p) {

        // �������� ��������� ���� � ���������
        p.inputAlphaField(in, p.surname, "��i�����: ", "��i����� ������� �i����� �i���� �����!");
        p.inputAlphaField(in, p.name, "I�'�: ", "i�'� ������� ������ �i���� �����!");
        p.inputAlphaField(in, p.patronymic, "�� �������: ", "�� ������� ������� ������ ����� �����!");
        p.inputAlphaField(in, p.gender, "����� (�/�): ", "����� ������� ������ ����� �����!");

        // �������� ���� � ��������� ������� �� ��������
        bool validDate = false;
        while (!validDate) {
            int d = 0, m = 0, y = 0;

            // ������������� ��������� ������� ��� ���������� �������� �����
            safeIntInput(in, "���� ����������: ", d);
            safeIntInput(in, "�i���� ����������: ", m);
            safeIntInput(in, "�i� ����������: ", y);

            Finally f;
            // �������� ����� ���� (�������) �� ��������� setDate � try-catch
            try {
                p.setDate(d, m, y);
                validDate = true;
            }
            catch (invalid_argument& e) {
                cout << "������� ����: " << e.what() << ". ��������� �� ���!\n";
            }
        }

        return in;
    }

    // === �������������� ��������� ���������� ��������� (<<) ===
    friend ostream& operator<<(ostream& out, const Person& p) {
        out << p.surname << " " << p.name << " " << p.patronymic
            << " (" << p.gender << "), ����: "
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

    // �������� �������� ��� ������� ���
    safeIntInput(cin, "��i���� ��i� ������ (���� 5): ", n);

    if (n < 1 || n > SIZE) {
        if (n < 1) n = 1; // ������ ���� � ���� �����
        if (n > SIZE) n = SIZE;
        cout << "����������� �i���i��� ��i�: " << n << endl;
    }

    // �������� ����� ��� ����� �����
    for (int i = 0; i < n; i++) {
        cout << "\n=== �������� ����� " << i + 1 << " ===\n";
        cin >> people[i];
    }

    int choice;
    do {
        cout << "\n==============================\n";
        cout << "=== ���� ������ ===\n";
        cout << "1 - ����� �� ��i������\n";
        cout << "2 - ����� �� ��i������ �� i�'��\n";
        cout << "3 - ����� �� ����� ����������\n";
        cout << "4 - ����� �� ������ �����\n";
        cout << "5 - ���i�\n";

        // --- ���������� �������� �������� ��� ������ ���� ---
        safeIntInput(cin, "��� ���i�: ", choice);

        if (choice < 1 || choice > 5) {
            cout << "���i���� ���i�. ���� �����, ����i�� ����� �� 1 �� 5.\n";
            continue;
        }
        // ----------------------------------------------------

        bool found = false;

        if (choice == 1) {
            string s;
            cout << "����i�� ��i�����: "; cin >> s;
            for (int i = 0; i < n; i++)
                if (people[i].search(s)) { cout << people[i] << endl; found = true; }
        }
        else if (choice == 2) {
            string s, nn;
            cout << "����i�� ��i�����: "; cin >> s;
            cout << "����i�� i�'�: "; cin >> nn;
            for (int i = 0; i < n; i++)
                if (people[i].search(s, nn)) { cout << people[i] << endl; found = true; }
        }
        else if (choice == 3) {
            int y;
            safeIntInput(cin, "����i�� �i�: ", y);
            for (int i = 0; i < n; i++)
                if (people[i].search(y)) { cout << people[i] << endl; found = true; }
        }
        else if (choice == 4) {
            int d, m, y;
            safeIntInput(cin, "����i�� ����: ", d);
            safeIntInput(cin, "����i�� �i����: ", m);
            safeIntInput(cin, "����i�� �i�: ", y);


            for (int i = 0; i < n; i++)
                if (people[i].search(d, m, y)) { cout << people[i] << endl; found = true; }
        }

        if (!found && choice >= 1 && choice <= 4)
            cout << "��i� �� ��������!\n";

    } while (choice != 5);

    return 0;
}