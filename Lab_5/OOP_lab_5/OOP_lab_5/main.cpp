#include <iostream>
#include <string>
using namespace std;

class Mammals {
protected:
    string name;
public:
    Mammals(string n = "Невідомо") : name(n) {}
    virtual void opis() const = 0; 
    virtual ~Mammals() {} 
};

class Animal : public Mammals {
protected:
    int age;
public:
    Animal(string n, int a) : Mammals(n), age(a) {}
    virtual void opis() const override {
        cout << "Це тварина: " << name << ", вік: " << age << " років." << endl;
    }
};

class Person : public Mammals {
private:
    string profession;
public:
    Person(string n, string prof) : Mammals(n), profession(prof) {}
    void opis() const override {
        cout << "Людина: " << name << ", професія: " << profession << "." << endl;
    }
};

class Kin : public Animal {
private:
    string poroda;
public:
    Kin(string n, int a, string p) : Animal(n, a), poroda(p) {}
    void opis() const override {
        cout << "Кінь: " << name << ", порода: " << poroda
            << ", вік: " << age << " років." << endl;
    }
};

class Korova : public Animal {
private:
    double milkPerDay;
public:
    Korova(string n, int a, double milk) : Animal(n, a), milkPerDay(milk) {}
    void opis() const override {
        cout << "Корова: " << name << ", дає " << milkPerDay
            << " л молока на день, вік: " << age << " років." << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Ukr");
    Mammals* s1 = new Person("Олександр", "вчитель");
    Mammals* s2 = new Kin("Блискавка", 5, "арабська");
    Mammals* s3 = new Korova("Мурка", 4, 18.5);

    cout << "=== Опис ссавців ===" << endl;
    s1->opis();
    s2->opis();
    s3->opis();

    delete s1;
    delete s2;
    delete s3;
    return 0;
}