/*
Library Management System - Part 3
Purpose: Add member accounts with login, checkout and checkin
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
    int memberID;
    string name;

    int borrowedIDs[10];   // store book IDs only
    int borrowedCount;     // how many books borrowed
};

/* FUNCTION PROTOTYPES */

Book makeBook();
void printBook(Book b);
int findBookByID(Book books[], int count, int searchID);

bool validateMemberID(Member members[], int count, int id);
void registerMember(Member members[], int& count);
Member* login(Member members[], int count);

void viewMemberInfo(Member* m, Book books[], int bookCount);

void checkOutBook(Book books[], int bookCount, Member* m);
void checkInBook(Book books[], int bookCount, Member* m);

void printAllBooks(Book books[], int count);

int main()
{
    const int MAX_BOOKS = 50;
    const int MAX_MEMBERS = 50;

    Book library[MAX_BOOKS];
    int bookCount = 0;

    Member members[MAX_MEMBERS];
    int memberCount = 0;

    // Start with 3 books
    cout << "Enter Book 1\n";
    library[bookCount] = makeBook();
    bookCount++;

    cout << "Enter Book 2\n";
    library[bookCount] = makeBook();
    bookCount++;

    cout << "Enter Book 3\n";
    library[bookCount] = makeBook();
    bookCount++;

    Member* currentUser = nullptr;

    int choice;

    cout << "1. Create Account\n";
    cout << "2. Login\n";
    cin >> choice;

    if (choice == 1)
    {
        registerMember(members, memberCount);
        currentUser = &members[memberCount - 1];
    }
    else if (choice == 2)
    {
        currentUser = login(members, memberCount);
    }

    if (currentUser == nullptr)
    {
        cout << "Login failed\n";
        return 0;
    }

    viewMemberInfo(currentUser, library, bookCount);

    int menu = 0;

    while (menu != 4)
    {
        cout << "\n1. Check Out Book\n";
        cout << "2. Check In Book\n";
        cout << "3. View Borrowed Books\n";
        cout << "4. Logout\n";
        cin >> menu;

        if (menu == 1)
        {
            checkOutBook(library, bookCount, currentUser);
        }
        else if (menu == 2)
        {
            checkInBook(library, bookCount, currentUser);
        }
        else if (menu == 3)
        {
            viewMemberInfo(currentUser, library, bookCount);
        }
    }

    cout << "Session Ended\n";

    return 0;
}

/* FUNCTION DEFINITIONS */

Book makeBook()
{
    Book temp;

    cin.ignore();
    cout << "Enter title: ";
    getline(cin, temp.title);

    cout << "Enter author: ";
    getline(cin, temp.author);

    cout << "Enter ID: ";
    cin >> temp.id;

    temp.checkedOut = false;

    return temp;
}

void printBook(Book b)
{
    cout << "Title: " << b.title << endl;
    cout << "Author: " << b.author << endl;
    cout << "ID: " << b.id << endl;

    if (b.checkedOut)
    {
        cout << "Checked Out\n";
        cout << "Due: "
            << b.dueDate.month << "/"
            << b.dueDate.day << "/"
            << b.dueDate.year << endl;
    }
    else
    {
        cout << "Available\n";
    }
}

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

bool validateMemberID(Member members[], int count, int id)
{
    for (int i = 0; i < count; i++)
    {
        if (members[i].memberID == id)
        {
            return true;
        }
    }
    return false;
}

void registerMember(Member members[], int& count)
{
    Member temp;

    cout << "Enter new member ID: ";
    cin >> temp.memberID;

    if (validateMemberID(members, count, temp.memberID))
    {
        cout << "ID already exists\n";
        return;
    }

    cin.ignore();
    cout << "Enter name: ";
    getline(cin, temp.name);

    temp.borrowedCount = 0;

    members[count] = temp;
    count++;

    cout << "Account Created\n";
}

Member* login(Member members[], int count)
{
    int id;
    cout << "Enter member ID: ";
    cin >> id;

    for (int i = 0; i < count; i++)
    {
        if (members[i].memberID == id)
        {
            cout << "Login Successful\n";
            return &members[i];
        }
    }

    cout << "Invalid ID\n";
    return nullptr;
}

void viewMemberInfo(Member* m, Book books[], int bookCount)
{
    if (m == nullptr)
        return;

    cout << "\nMember Info\n";
    cout << "ID: " << m->memberID << endl;
    cout << "Name: " << m->name << endl;

    if (m->borrowedCount == 0)
    {
        cout << "No books borrowed\n";
        return;
    }

    for (int i = 0; i < m->borrowedCount; i++)
    {
        int index = findBookByID(books, bookCount, m->borrowedIDs[i]);
        if (index != -1)
        {
            printBook(books[index]);
        }
    }
}

void checkOutBook(Book books[], int bookCount, Member* m)
{
    int id;
    cout << "Enter book ID: ";
    cin >> id;

    int index = findBookByID(books, bookCount, id);

    if (index == -1)
    {
        cout << "Book not found\n";
        return;
    }

    if (books[index].checkedOut)
    {
        cout << "Book already checked out\n";
        return;
    }

    cout << "Enter due month: ";
    cin >> books[index].dueDate.month;

    cout << "Enter due day: ";
    cin >> books[index].dueDate.day;

    cout << "Enter due year: ";
    cin >> books[index].dueDate.year;

    books[index].checkedOut = true;

    m->borrowedIDs[m->borrowedCount] = id;
    m->borrowedCount++;

    cout << "Book checked out\n";
}

void checkInBook(Book books[], int bookCount, Member* m)
{
    int id;
    cout << "Enter book ID: ";
    cin >> id;

    int index = findBookByID(books, bookCount, id);

    if (index == -1)
    {
        cout << "Book not found\n";
        return;
    }

    if (!books[index].checkedOut)
    {
        cout << "Book is not checked out\n";
        return;
    }

    bool found = false;
    int position = -1;

    for (int i = 0; i < m->borrowedCount; i++)
    {
        if (m->borrowedIDs[i] == id)
        {
            found = true;
            position = i;
        }
    }

    if (!found)
    {
        cout << "You did not borrow this book\n";
        return;
    }

    for (int i = position; i < m->borrowedCount - 1; i++)
    {
        m->borrowedIDs[i] = m->borrowedIDs[i + 1];
    }

    m->borrowedCount--;

    books[index].checkedOut = false;

    cout << "Book checked in\n";
}

void printAllBooks(Book books[], int count)
{
    for (int i = 0; i < count; i++)
    {
        printBook(books[i]);
    }
}
