#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double calculate_a(double x, double y, double z, double b) {
    if (x * x - b < 0) {
        cout << "Помилка: Квадратний корінь з від'ємного числа в a[x,y,z,b]." << endl;
        return NAN;
    }

    if (z + 4 * y * y == 0) {
        cout << "Помилка: Ділення на нуль в a[x,y,z,b]." << endl;
        return NAN;
    }

    double numerator = y - sqrt(x * x - b);
    double term1 = abs(numerator);

    double term2_num = y - x * x;
    double term2_den = z + 4 * y * y;
    double term2 = pow(abs(term2_num / term2_den), 2.0 / 3.0);


    if (term1 * term2 <= 0) {
        cout << "Помилка: Логарифм з непозитивного числа в a[x,y,z,b]." << endl;
        return NAN;
    }

    return log(term1 * term2);
}


double calculate_b(double x, double y, double z) {

    if (z == 0 || z + y == 0) {
        cout << "Помилка: Ділення на нуль в b[x,y,z]." << endl;
        return NAN;
    }

    double term1 = x + y + y * y / tgamma(4);
    double term2 = y * y * y / tgamma(6);
    double term3_num = exp(x - y);
    double term3_den = z + y;


    if (abs(z) <= 0) {
        cout << "Помилка: Негативна або нульова основа для pow() в b[x,y,z]." << endl;
        return NAN;
    }

    double result = 1.0 - (term1 / pow(abs(z), 0.34)) + term2 + term3_num / term3_den;
    return result;
}

int main() {
    setlocale(LC_ALL, "Ukr");
    int variant_number;

    cout << "Введiть номер варiанта (No): ";
    cin >> variant_number;

    double x = 0.48 * variant_number;
    double y = 0.47 * variant_number;
    double z = -1.32 * variant_number;

    double b_result = calculate_b(x, y, z);
    double a_result = calculate_a(x, y, z, b_result);

    cout << fixed << setprecision(6);
    cout << "\nОбчисленi значення:" << endl;
    cout << "a[x, y, z, b] = " << a_result << endl;
    cout << "b[x, y, z]    = " << b_result << endl;

    cout << "\nТабулювання функцiй a та b:" << endl;
    cout << "------------------------------------------" << endl;
    cout << "x\ta(x)\t\tb(x)" << endl;
    cout << "------------------------------------------" << endl;
    cout << fixed << setprecision(6);

    const double x_start = -1.0;
    const double x_end = 1.0;
    const double x_step = 0.2;

    for (double x = x_start; x <= x_end; x += x_step) {
        double b_result = calculate_b(x, y, z);
        double a_result = calculate_a(x, y, z, b_result);

        cout << setw(10) << x << setw(20) << a_result << setw(20) << b_result << endl;
    }
    cout << "------------------------------------------" << endl;

    return 0;
}