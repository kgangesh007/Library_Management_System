#include <iostream>
#include <mysql.h>
#include <sstream>
#include <string>
#include <limits>

#define HOST "127.0.0.1"
#define USER "root"
#define PASS "" // Define your MySQL password here
#define DATABASE ""
#define PORT 3306

using namespace std;

MYSQL *conn;
MYSQL_RES *res_set;
MYSQL_ROW row;
stringstream stmt;
string query;

class books
{
    int id;
    string name;
    string auth;
    int price;
    int qty;

public:
    void add();
    void Delete();
    void search();
    void update();
    void display();
};

void books::add()
{
    cout << "Enter the name of the book : ";
    getline(cin, name);
    cout << "Enter the name of the author : ";
    getline(cin, auth);
    cout << "Enter the Price : ";
    cin >> price;
    cout << "Enter the Qty Received : ";
    cin >> qty;

    stmt.str("");
    stmt << "INSERT INTO books(name, auth, price, qty) VALUES('" << name << "','" << auth << "'," << price << "," << qty << ")";
    query = stmt.str();

    if (mysql_query(conn, query.c_str()) == 0)
        cout << endl << "Book Record Inserted Successfully" << endl << endl;
    else
        cout << endl << "Entry ERROR!" << endl << "Contact Technical Team" << endl << endl;

    // Clear input buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void books::Delete()
{
    char choice;
    cout << "Enter the id of the book for Delete : ";
    cin >> id;
    stmt.str("");
    stmt << "SELECT * FROM books WHERE id = " << id;
    query = stmt.str();

    if (mysql_query(conn, query.c_str()) == 0)
    {
        res_set = mysql_store_result(conn);
        if (res_set)
        {
            row = mysql_fetch_row(res_set);
            if (row != NULL)
            {
                cout << "The Name of the book is : " << row[1] << endl;
                cout << "The Author of the book is : " << row[2] << endl;
                cout << "The Price of the book is : " << row[3] << endl;
                cout << "The Qty of the book is : " << row[4] << endl;
                cout << "Do you Want to Delete the Book [y/n] : ";
                cin >> choice;
                if (choice == 'y' || choice == 'Y')
                {
                    cin.ignore(); // Clear newline character from the input buffer
                    stmt.str("");
                    stmt << "DELETE FROM books WHERE id = " << id;
                    query = stmt.str();
                    if (mysql_query(conn, query.c_str()) == 0)
                        cout << endl << "Book Deleted Successfully" << endl << endl;
                    else
                        cout << endl << "Entry ERROR!" << endl << "Contact Technical Team" << endl << endl;
                }
                else
                {
                    cout << "No changes Made!!";
                }
            }
            else
            {
                cout << "No Book found!!!";
            }
            mysql_free_result(res_set);
        }
    }
}

void books::search()
{
    string book_name;
    cout << "Enter the Name of the book to be Searched : ";
    getline(cin, book_name);
    stmt.str("");
    stmt << "SELECT * FROM books WHERE name = '" << book_name << "'";
    query = stmt.str();

    if (mysql_query(conn, query.c_str()) == 0)
    {
        res_set = mysql_store_result(conn);
        if (res_set)
        {
            while ((row = mysql_fetch_row(res_set)) != NULL)
            {
                cout << "Book ID : " << row[0] << endl;
                cout << "Book Name : " << row[1] << endl;
                cout << "Author Name : " << row[2] << endl;
                cout << "Price : " << row[3] << endl;
                cout << "Qty : " << row[4] << endl << endl;
            }
            mysql_free_result(res_set);
        }
    }

    // Clear input buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void books::update()
{
    char choice;
    cout << "Enter the id of the book for update : ";
    cin >> id;
    stmt.str("");
    stmt << "SELECT * FROM books WHERE id = " << id;
    query = stmt.str();

    if (mysql_query(conn, query.c_str()) == 0)
    {
        res_set = mysql_store_result(conn);
        if (res_set)
        {
            row = mysql_fetch_row(res_set);
            if (row != NULL)
            {
                cout << "The Name of the book is : " << row[1] << endl;
                cout << "The Author of the book is : " << row[2] << endl;
                cout << "The Price of the book is : " << row[3] << endl;
                cout << "The Qty of the book is : " << row[4] << endl;
                cout << "Do you Want to Update the Book [y/n] : ";
                cin >> choice;
                if (choice == 'y' || choice == 'Y')
                {
                    cin.ignore(); // Clear newline character from the input buffer
                    cout << "Enter the new Name : ";
                    getline(cin, name);
                    cout << "Enter the new Author : ";
                    getline(cin, auth);
                    cout << "Enter the new Price : ";
                    cin >> price;
                    cout << "Enter the new Qty : ";
                    cin >> qty;
                    stmt.str("");
                    stmt << "UPDATE books SET name = '" << name << "', auth = '" << auth << "', price = " << price << ", qty = " << qty << " WHERE id = " << id;
                    query = stmt.str();
                    if (mysql_query(conn, query.c_str()) == 0)
                        cout << endl << "Book Updated Successfully" << endl << endl;
                    else
                        cout << endl << "Entry ERROR!" << endl << "Contact Technical Team" << endl << endl;
                }
                else
                {
                    cout << "No changes Made!!";
                }
            }
            else
            {
                cout << "No Book found!!!";
            }
            mysql_free_result(res_set);
        }
    }

    // Clear input buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void books::display()
{
    stmt.str("");
    stmt << "SELECT * FROM books";
    query = stmt.str();

    if (mysql_query(conn, query.c_str()) == 0)
    {
        res_set = mysql_store_result(conn);
        if (res_set)
        {
            while ((row = mysql_fetch_row(res_set)) != NULL)
            {
                cout << "Book ID : " << row[0] << endl;
                cout << "Book Name : " << row[1] << endl;
                cout << "Author Name : " << row[2] << endl;
                cout << "Price : " << row[3] << endl;
                cout << "Qty : " << row[4] << endl << endl;
            }
            mysql_free_result(res_set);
        }
    }

    // Clear input buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main()
{
    conn = mysql_init(NULL);
    if (conn == NULL)
    {
        cout << "MySQL Initialization Failed" << endl;
        return 1;
    }
    conn = mysql_real_connect(conn, HOST, USER, PASS, DATABASE, PORT, NULL, 0);
    if (conn == NULL)
    {
        cout << "MySQL Connection Failed" << endl;
        return 1;
    }
    cout << "Connection Successful" << endl << endl;

    books b;
    int choice;
    do
    {
        cout << "1. Add a book" << endl;
        cout << "2. Delete book" << endl;
        cout << "3. Search for a book" << endl;
        cout << "4. Update a book" << endl;
        cout << "5. Display all books" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice : ";
        cin >> choice;

        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            b.add();
            break;
        case 2:
            b.Delete();
            break;
        case 3:
            b.search();
            break;
        case 4:
            b.update();
            break;
        case 5:
            b.display();
            break;
        case 6:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
        }
    } while (choice != 6);

    mysql_close(conn);
    return 0;
}
