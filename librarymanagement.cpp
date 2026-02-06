#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
class User {
private:
    int userId;
    vector<int> borrowedBooks;
public:
    User(int id) : userId(id), borrowedBooks({}) {}

    virtual int getMaxLimit() = 0;

    int booksBorrowed() {
        return borrowedBooks.size();
    }

    void addBook(int bookId) {
        borrowedBooks.push_back(bookId);
    }

    void returnBook(int bookId) {
        borrowedBooks.erase(remove(borrowedBooks.begin(), borrowedBooks.end(), bookId), borrowedBooks.end());
    }

    bool isBookBorrowed(int bookId) {
        return find(borrowedBooks.begin(), borrowedBooks.end(), bookId) != borrowedBooks.end();
    }
};

class Student : public User {
public:
    Student(int id) : User(id) {};

    int getMaxLimit() override {
        return 3;
    }
};

class Teacher : public User {
public:
    Teacher(int id) : User(id) {};

    int getMaxLimit() override {
        return 5;
    }
};

class Book {
private:
    int bookId;
    bool isAvailable;

public:
    Book(int id) : bookId(id), isAvailable(true) {}

    bool isBookAvailable() {
        return isAvailable;
    }

    void setAvailability(bool status) {
        isAvailable = status;
    }

    int getBookId() {
        return bookId;
    }
};

class Library {
private:
    vector<User*> users;
    vector<Book*> books;

public:
    void addUser(User* user) {
        users.push_back(user);
    }

    void addBook(Book* book) {
        books.push_back(book);
    }

    bool borrowBook(User* user, Book* book) {
        if(find(users.begin(), users.end(), user) == users.end() || find(books.begin(), books.end(), book) == books.end()) {
            return false;
        }   

        if(user->booksBorrowed() >= user->getMaxLimit()) {
            return false;
        }

        if(!book->isBookAvailable()) {
            return false;
        }

        book->setAvailability(false);
        user->addBook(book->getBookId());

        return true;
    }

    bool returnBook(User* user, Book* book) {
        if(find(users.begin(), users.end(), user) == users.end() && find(books.begin(), books.end(), book) == books.end()) {
            return false;
        } 
        
        if(!user->isBookBorrowed(book->getBookId())) {
            return false;
        }

        book->setAvailability(true);
        user->returnBook(book->getBookId());

        return true;
    }
};

int main() {
    Library library;

    User* student = new Student(1);
    User* teacher = new Teacher(2);

    Book* book1 = new Book(101);
    Book* book2 = new Book(102);

    library.addUser(student);
    library.addUser(teacher);
    library.addBook(book1);
    library.addBook(book2);

    if(library.borrowBook(student, book1)){
        cout<<"Student borrowed book 101"<<endl;
    } else{
        cout<<"Student failed to borrow book 101"<<endl;
    }

    if(library.borrowBook(student, book2)){
        cout<<"Student borrowed book 102"<<endl;
    } else{
        cout<<"Student failed to borrow book 102"<<endl;
    }

    if(library.borrowBook(teacher, book2)){
        cout<<"Teacher borrowed book 102"<<endl;
    } else{
        cout<<"Teacher failed to borrow book 102"<<endl;
    }

    if(library.returnBook(student, book1)){
        cout<<"Student returned book 101"<<endl;
    } else{
        cout<<"Student failed to return book 101"<<endl;
    }

    if(library.borrowBook(teacher, book1)){
        cout<<"Teacher borrowed book 101"<<endl;
    } else{
        cout<<"Teacher failed to borrow book 101"<<endl;
    }

    if(library.returnBook(student, book2)){
        cout<<"Student returned book 102"<<endl;
    } else{
        cout<<"Student failed to return book 102"<<endl;
    }

    if(library.returnBook(teacher, book2)){
        cout<<"Teacher returned book 102"<<endl;
    } else{
        cout<<"Teacher failed to return book 102"<<endl;
    }

    delete student;
    delete teacher;
    delete book1;
    delete book2;

    return 0;
}