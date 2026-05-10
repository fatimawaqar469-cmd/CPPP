#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

class Book {
public:
    int id;
    char name[50];
    char category[20];
    int copies;
    int issued;
    int studentID;
    int dueDays;

    void input() {
        cout << "Enter Book ID: ";
        cin >> id;
        cout << "Enter Book Name: ";
        cin >> name;
        cout << "Enter Category: ";
        cin >> category;
        cout << "Enter Copies: ";
        cin >> copies;

        issued = 0;
        studentID = 0;
        dueDays = 0;
    }

    void display() {
        cout << "\nID: " << id;
        cout << "\nName: " << name;
        cout << "\nCategory: " << category;
        cout << "\nCopies: " << copies;
        cout << "\nStatus: " << (issued ? "Issued" : "Available") << endl;
    }
};

void addBook() {
    Book b;
    ofstream file("library.txt", ios::app);
    b.input();
    file << b.id << " " << b.name << " " << b.category << " "
         << b.copies << " " << b.issued << " "
         << b.studentID << " " << b.dueDays << endl;
    file.close();
}

void displayBooks() {
    Book b;
    ifstream file("library.txt");

    while (file >> b.id >> b.name >> b.category >> b.copies
           >> b.issued >> b.studentID >> b.dueDays) {
        b.display();
    }
    file.close();
}

void issueBook() {
    int id, sid, days;
    Book b;
    ifstream file("library.txt");
    ofstream temp("temp.txt");

    cout << "Enter Book ID: ";
    cin >> id;
    cout << "Enter Student ID: ";
    cin >> sid;
    cout << "Enter Due Days: ";
    cin >> days;

    while (file >> b.id >> b.name >> b.category >> b.copies
           >> b.issued >> b.studentID >> b.dueDays) {

        if (b.id == id && b.copies > 0 && b.issued == 0) {
            b.issued = 1;
            b.studentID = sid;
            b.dueDays = days;
            b.copies--;
            cout << "Book Issued!\n";
        }

        temp << b.id << " " << b.name << " " << b.category << " "
             << b.copies << " " << b.issued << " "
             << b.studentID << " " << b.dueDays << endl;
    }

    file.close();
    temp.close();
    remove("library.txt");
    rename("temp.txt", "library.txt");
}

void returnBook() {
    int id, lateDays;
    Book b;
    ifstream file("library.txt");
    ofstream temp("temp.txt");

    cout << "Enter Book ID: ";
    cin >> id;
    cout << "Enter Late Days: ";
    cin >> lateDays;

    while (file >> b.id >> b.name >> b.category >> b.copies
           >> b.issued >> b.studentID >> b.dueDays) {

        if (b.id == id && b.issued == 1) {
            b.issued = 0;
            b.studentID = 0;
            b.copies++;

            int fine = lateDays * 10;
            cout << "Book Returned! Fine: " << fine << endl;
        }

        temp << b.id << " " << b.name << " " << b.category << " "
             << b.copies << " " << b.issued << " "
             << b.studentID << " " << b.dueDays << endl;
    }

    file.close();
    temp.close();
    remove("library.txt");
    rename("temp.txt", "library.txt");
}

void searchBook() {
    int id;
    Book b;
    ifstream file("library.txt");

    cout << "Enter Book ID: ";
    cin >> id;

    while (file >> b.id >> b.name >> b.category >> b.copies
           >> b.issued >> b.studentID >> b.dueDays) {
        if (b.id == id) {
            b.display();
        }
    }

    file.close();
}

int main() {
    int ch;

    do {
        cout << "\n--- Library System ---\n";
        cout << "1. Add Book\n2. Display\n3. Search\n4. Issue\n5. Return\n6. Exit\n";
        cin >> ch;

        switch (ch) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: issueBook(); break;
            case 5: returnBook(); break;
        }

    } while (ch != 6);

    return 0;
}
