/*
Library Management System - Part 2
Purpose: Manage a collection of books using arrays and functions
Written by: George Alabi
*/

#include <iostream>
#include <string>
using namespace std;

struct Date
{
    int month;
    int day;
    int year;
};

struct Book
{
    string title;
    string author;
    int id;
    bool checkedOut;
    Date dueDate;
};

struct Member
{
    string name;
    int cardNumber;
};

/* ---------- FUNCTION PROTOTYPES ---------- */

// From Part 1
Book makeBook();
void printBook(Book b);
void checkOutBook(Book& b, Member m);

// New for Part 2
void addBook(Book books[], int& count, Book b);
void printAllBooks(Book books[], int count);
int findBookByID(Book books[], int count, int searchID);


int main()
{
    const int MAX_BOOKS = 50;
    Book library[MAX_BOOKS];   // array of books
    int bookCount = 0;         // number of books in catalog

    // Hard-coded library member
    Member member;
    member.name = "John Doe";
    member.cardNumber = 12345;

    // Add 3 books to the catalog
    cout << "Enter information for Book";
    addBook(library, bookCount, makeBook());

    cout << "Enter information for Book";
    addBook(library, bookCount, makeBook());

    cout << "Enter information for Book";
    addBook(library, bookCount, makeBook());

    // Display all books
    cout << "Library Catalog";
    printAllBooks(library, bookCount);

    // Ask user for book ID to check out
    int searchID;
    cout << "Enter the ID of the book to check out: ";
    cin >> searchID;

    int index = findBookByID(library, bookCount, searchID);

    if (index == -1)
    {
        cout << "Error: Book not found in the catalog";
    }
    else
    {
        checkOutBook(library[index], member);
    }

    // Display updated catalog
    cout << "Updated Library Catalog";
    printAllBooks(library, bookCount);

    return 0;
}

/* FUNCTION DEFINITIONS  */

// Creates a book using user input
Book makeBook()
{
    Book temp;

    cin.ignore();
    cout << "Enter book title: ";
    getline(cin, temp.title);

    cout << "Enter book author: ";
    getline(cin, temp.author);

    cout << "Enter book ID: ";
    cin >> temp.id;

    temp.checkedOut = false;

    return temp;
}

// Displays a single book
void printBook(Book b)
{
    cout << "Title: " << b.title << endl;
    cout << "Author: " << b.author << endl;
    cout << "ID: " << b.id << endl;

    if (b.checkedOut)
    {
        cout << "Status: Checked Out";
        cout << "Due Date: "
            << b.dueDate.month << "/"
            << b.dueDate.day << "/"
            << b.dueDate.year << endl;
    }
    else
    {
        cout << "Status: Available";
    }
}

// Adds a book to the catalog
void addBook(Book books[], int& count, Book b)
{
    books[count] = b;
    count++;
}

// Displays all books in the catalog
void printAllBooks(Book books[], int count)
{
    for (int i = 0; i < count; i++)
    {
        printBook(books[i]);
    }
}

// Searches for a book by ID
int findBookByID(Book books[], int count, int searchID)
{
    for (int i = 0; i < count; i++)
    {
        if (books[i].id == searchID)
        {
            return i;
        }
    }
    return -1;
}

// Checks out a book
void checkOutBook(Book& b, Member m)
{
    if (b.checkedOut)
    {
        cout << "This book is already checked out";
    }
    else
    {
        cout << "Checking out book to " << m.name << endl;

        cout << "Enter due month: ";
        cin >> b.dueDate.month;

        cout << "Enter due day: ";
        cin >> b.dueDate.day;

        cout << "Enter due year: ";
        cin >> b.dueDate.year;

        b.checkedOut = true;
        cout << "Book checked out";
    }
}
