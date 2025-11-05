#include <iostream>
#include <stack>
#include <string>
using namespace std;

struct Student {
    string surname;
    int id;
    double rating;
};

void printStack(stack<Student> st) {
    cout << "\nВміст стеку зараз:\n";
    if (st.empty()) {
        cout << "[Стек порожній]\n";
        return;
    }

    while (!st.empty()) {
        Student s = st.top();
        cout << s.surname << " | ID: " << s.id << " | Рейтинг: " << s.rating << endl;
        st.pop();
    }
}

int main() {
    setlocale(LC_ALL, "Ukr");
    stack<Student> st;

    st.push({ "Shevchenko", 101, 91.5 });
    st.push({ "Petrenko", 102, 85.0 });
    st.push({ "Koval", 103, 78.3 });
    st.push({ "Bondarenko", 104, 95.2 });
    st.push({ "Melnyk", 105, 88.6 });

    string targetSurname;
    cout << "Введіть прізвище студента для пошуку: ";
    cin >> targetSurname;

    stack<Student> temp;
    bool found = false;

    while (!st.empty()) {
        Student top = st.top();
        st.pop();

        if (top.surname == targetSurname) {
            cout << "\nСтудента знайдено:\n";
            cout << "Прізвище: " << top.surname << endl;
            cout << "ID: " << top.id << endl;
            cout << "Рейтинг: " << top.rating << endl;
            found = true;
            temp.push(top);
            break;
        }

        temp.push(top);
    }

    while (!temp.empty()) {
        st.push(temp.top());
        temp.pop();
    }

    if (!found) {
        cout << "\nСтудента не знайдено.\n";
    }

    string delSurname;
    cout << "\nВведіть прізвище до якого очистити стек: ";
    cin >> delSurname;

    while (!st.empty() && st.top().surname != delSurname) {
        /*if (st.top().surname == delSurname) {
            st.pop();
            break;
        }*/
        st.pop();
    }

    cout << "\n✅ Стек очищено до " << delSurname << endl;

    printStack(st);

    return 0;
}
