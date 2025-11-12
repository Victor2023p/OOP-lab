#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> 
#include <iterator>

using namespace std;

int main() {
    setlocale(LC_ALL, "ukr");

    vector<int> arr = { 3, 0, 4, 2, 0, 5, 7, 1, 6 };
    cout << "Початковий масив: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    // 1. Знайти номер максимального елемента
    vector<int>::iterator it_max = max_element(arr.begin(), arr.end());
    int index_max = distance(arr.begin(), it_max);
    cout << "Номер максимального елемента: " << index_max << endl;

    // 2. Добуток елементів між першим і другим нулями
    vector<int>::iterator first_zero = find(arr.begin(), arr.end(), 0);
    int product = 1;
    bool found = false;
    if (first_zero != arr.end()) {
        vector<int>::iterator second_zero = find(next(first_zero), arr.end(), 0);
        if (second_zero != arr.end() && distance(first_zero, second_zero) > 1) {
            product = accumulate(next(first_zero), second_zero, 1, multiplies<int>());
            found = true;
        }
    }

    if (found)
        cout << "Добуток елементів між першим і другим нулями: " << product << endl;
    else
        cout << "У масиві менше двох нульових елементів або між ними немає елементів." << endl;

    // 3. Перетворення масиву (непарні позиції в першу половину)
    vector<int> odd_pos, even_pos;
    for (int i = 0; i < arr.size(); ++i) {
        if ((i + 1) % 2 != 0)
            odd_pos.push_back(arr[i]);
        else
            even_pos.push_back(arr[i]);
    }

    vector<int> transformed;
    transformed.reserve(arr.size());
    transformed.insert(transformed.end(), even_pos.begin(), even_pos.end());
    transformed.insert(transformed.end(), odd_pos.begin(), odd_pos.end());

    cout << "Перетворений масив: ";
    for (int x : transformed) cout << x << " ";
    cout << endl;

    return 0;
}
