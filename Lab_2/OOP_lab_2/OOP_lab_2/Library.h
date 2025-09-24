#pragma
#include "Book.h"

using namespace std;

class Library {
protected:
    Book* books;
    int bookCount;

public:

    Library(Book* initialBooks, int count);
    ~Library();

    void showAllBooks();

    void searchByAuthor(const char* author);
    void searchByTitle(const char* title);
    void searchByPublisher(const char* publisher);
    void searchByYear(int year);
};