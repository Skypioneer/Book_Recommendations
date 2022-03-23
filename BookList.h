// Jason Wang
// File: BookList.h
// Date: 9/22/20
// Purpose: Define the class BookList

#ifndef P1_BOOKLIST_H
#define P1_BOOKLIST_H

#include <string>
using namespace std;

class BookList {
public:
    explicit BookList(int);
    // Constructor
    // precondition: accept size of capacity
    // postcondition: declare bookList, assign cap to capacity, and set
    // numElements to 0 and aISBN to 1;

    ~BookList();
    // Destructor
    // precondition: none
    // postcondition: delete bookList

    void add(string, string, string);
    // add element to array
    // precondition: accept three strings: aTitle, aAuthor, and aYear
    // postcondition: assign three strings and aISBN to bookList

    int size() const;
    // number of elements in array
    // precondition: none
    // postcondition: return size of memberList

    string to_string() const;
    // return string representation
    // precondition: none
    // postcondition: return the latest element in array

    string bookInfo(int);
    // return one book information in array
    // precondition: a index to determine witch information
    // postcondition: return one book information in array

private:
    struct Book {                   // struck book that contains int ISBN, and
                                    // string year, author, and title
        int ISBN;                   // index of book information
        string year;                // year of publishment
        string author;              // author of book
        string title;               // title of book
    };
    Book * bookList;                // pointer to the array

    int aISBN;                      // the ISBN
    int capacity;                   // capacity of bookList array
    int numElements;                // Number of elements

    void resize();                  // resize array (when full)
};

#endif //P1_BOOKLIST_H
