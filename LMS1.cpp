/* Library Management System 
Part 1 Purpose: Practice using structures and functions 
Written by: George O Alabi */

#include <iostream>
#include <string>
using namespace std;

struct Date { int month; int day; int year; }; 
struct Book { string title; string author; int id; bool checkedOut; Date dueDate; }; 
struct Member { string name; int cardNumber; };
Book makeBook(); void printBook(Book b); void checkOutBook(Book& b, Member m);

int main() {
    Book myBook = makeBook();
	//Creating one member 
    Member myMember;
    myMember.name = "King Georrge";
    myMember.cardNumber = 12345;

    // Displaying the book before checkout
    cout << "Book Information BEFORE Checkout";
    printBook(myBook);

    // Attempt to check out the book
    checkOutBook(myBook, myMember);

    // Display book after checkout
    cout << "Book Information AFTER Checkout";
    printBook(myBook);

    return 0;  
}

// Create one book using user input
Book makeBook() {
    Book temp;
    cout << "Enter Book title";
        getline(cin, temp.title);

    cout << "Enter book author: ";
    getline(cin, temp.author);

    cout << "Enter book ID: ";
    cin >> temp.id;

        //Book starts as NOT checked out
    temp.checkedOut = false;
        
        //Clear leftover newline 
        cin.ignore();

    return temp;
}

// Displaying the book information
void printBook(Book b) {
    cout << "Title: " << b.title << endl;
    cout << "Author: " << b.author << endl;
    cout << "ID: " << b.id << endl;

    if (b.checkedOut == true) {
        cout << "Status: Checked Out" << endl;
        cout << "Due Date: "
            << b.dueDate.month << "/"
            << b.dueDate.day << "/"
            << b.dueDate.year << endl;
    }
    else {
        cout << "Status: Available" << endl;
    }
}

// Now to check out the book
void checkOutBook(Book& b, Member m) {
    if (b.checkedOut == true)
        cout << "This book i schecked out already, have a nice day";

    else {
        cout << "Checking out book to" << m.name << endl;

        cout << "Enter due Month:";
        cin >> b.dueDate.month;

        cout << "Enter due day:";
        cin >> b.dueDate.year;

        cout << "Enter due year: ";
            cin >> b.dueDate.year;

        b.checkedOut = true;

        cout << "Book successfully checked out";
    }
}