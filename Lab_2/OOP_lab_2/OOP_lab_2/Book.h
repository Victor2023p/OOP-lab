#pragma
#include <iostream>

using namespace std;

class Book {
protected:
    char* authorLastName;
    char* title;
    char* publisher;
    int year;
    int pages;

public:
    Book();
    // ����� ����������� ��� ������ �����������
    Book(const char* author, const char* bookTitle, const char* pub, int y, int p);
    ~Book();

    void show();

    // ������ set()
    void setAuthorLastName(const char* value);
    void setTitle(const char* value);
    void setPublisher(const char* value);
    void setYear(int value);
    void setPages(int value);

    // ������ get()
    char* getAuthorLastName();
    char* getTitle();
    char* getPublisher();
    int getYear();
    int getPages();
};