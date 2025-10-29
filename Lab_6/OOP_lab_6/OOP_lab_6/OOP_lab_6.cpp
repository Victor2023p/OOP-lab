#include <iostream>
using namespace std;

template <typename T>
T absoluteValue(T number) {
    return (number < 0) ? -number : number;
}

template <typename T>
class SequentialSearch {
private:
    T* arr;   
    int size; 

public:
    SequentialSearch(T* array, int n) {
        arr = array;
        size = n;
    }

    void searchElement(T key) {
        bool found = false;
        for (int i = 0; i < size; i++) {
            if (arr[i] == key) {
                cout << "Елемент знайдено!" << endl;
                cout << "Індекс: " << i << endl;
                cout << "Значення: " << arr[i] << endl;
                found = true;
            }
        }
        if (!found)
            cout << "Елемент не знайдено." << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Ukr");
    cout << "=== Завдання 1: Модуль числа ===" << endl;
    int a = -10;
    double b = -5.67;
    float c = 3.14f;

    cout << "Модуль цілого числа (" << a << ") = " << absoluteValue(a) << endl;
    cout << "Модуль дійсного числа (" << b << ") = " << absoluteValue(b) << endl;
    cout << "Модуль float числа (" << c << ") = " << absoluteValue(c) << endl;

    cout << "\n=== Завдання 2: Пошук елемента в масиві ===" << endl;
    int arr1[] = { 2, 7, 4, 9, 1 };
    double arr2[] = { 1.1, 3.3, 5.5, 7.7, 9.9 };

    SequentialSearch<int> intSearch(arr1, 5);
    SequentialSearch<double> doubleSearch(arr2, 5);

    cout << "\nПошук цілого елемента 9:" << endl;
    intSearch.searchElement(9);

    cout << "\nПошук дійсного елемента 3.3:" << endl;
    doubleSearch.searchElement(3.3);

    cout << "\nПошук елемента, якого немає (10):" << endl;
    intSearch.searchElement(10);

    return 0;
}
