#include <iostream>
#include <fstream>
#include <cmath>
#include <stdexcept>  // для std::invalid_argument

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

class Circle {
protected:
    double radius;
public:
    Circle(double r = 1.0) {
        if (r <= 0) {
            throw invalid_argument("Радіус повинен бути додатним числом!");
        }
        radius = r;
    }

    double area() const { return M_PI * radius * radius; } // площа кола
    double circumference() const { return 2 * M_PI * radius; } // довжина кола
    double getRadius() const { return radius; }

    virtual void printInfo(ostream& os) const {
        os << "Коло:\n";
        os << "  Радіус: " << radius << endl;
        os << "  Площа: " << area() << endl;
        os << "  Довжина кола: " << circumference() << endl;
    }
};


class Rectangle {
protected:
    double width;
    double height;
public:
    Rectangle(double w = 1.0, double h = 1.0) {
        if (w <= 0 || h <= 0) {
            throw invalid_argument("Сторони прямокутника повинні бути додатними!");
        }
        width = w;
        height = h;
    }

    double area() const { return width * height; }
    double perimeter() const { return 2 * (width + height); }
    double diagonal() const { return sqrt(width * width + height * height); }

    virtual void printInfo(ostream& os) const {
        os << "Прямокутник:\n";
        os << "  Ширина: " << width << endl;
        os << "  Висота: " << height << endl;
        os << "  Площа: " << area() << endl;
        os << "  Периметр: " << perimeter() << endl;
        os << "  Діагональ: " << diagonal() << endl;
    }
};


class RectangleInCircle : public Circle, public Rectangle {
public:
    RectangleInCircle(double r, double w, double h)
        : Circle(r), Rectangle(w, h) {
        double d = 2 * radius;
        double diag = diagonal();

        if (diag != d) {
            throw invalid_argument("Діагональ прямокутника не дорівнює діаметрі кола! Прямокутник не може бути вписаний у коло.");
        }
    }

    void printInfo(ostream& os) const override {
        os << "=== Прямокутник, вписаний у коло ===\n";
        Circle::printInfo(os);
        Rectangle::printInfo(os);
        os << "--------------------------------------\n";
    }
};


int main() {
    setlocale(LC_ALL, "Ukr");

    ofstream fout("figures_info.txt");
    if (!fout) {
        cerr << "Помилка відкриття файлу!" << endl;
        return 1;
    }

    double R, H, W;

    while (true) {
        cout << "Введіть радіус: ";
        cin >> R;

        cout << "Введіть висоту прямокутника: ";
        cin >> H;

        cout << "Введіть ширину прямокутника: ";
        cin >> W;


        try {
            RectangleInCircle fig1(R, W, H);
            fig1.printInfo(cout);
            fig1.printInfo(fout);
            cout << "\n✅ Дані про фігуру записано у файл 'figures_info.txt'.\n";
            break; // вихід з циклу після успішного введення
        }
        catch (const invalid_argument& e) {
            cerr << "Помилка: " << e.what() << endl;
            cout << "Спробуйте ще раз.\n\n";
        }
    }

    fout.close();
    return 0;
}
