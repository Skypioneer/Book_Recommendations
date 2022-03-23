// Jason Wang
// File: BookList.cpp
// Date: 9/22/20
// Purpose: Implement of the book lists

#include "BookList.h"
#include <sstream>
#include <iostream>
using namespace std;

BookList::BookList(int cap) {
    bookList = new Book[cap];
    capacity = cap;
    numElements = 0;
    aISBN = 1;
}

BookList::~BookList() {
    delete [] bookList;
}

void BookList::add(string aAuthor, string aTitle, string aYear) {
    if (numElements >= capacity)
        resize();

    bookList[numElements].ISBN = aISBN;
    bookList[numElements].author = aAuthor;
    bookList[numElements].title = aTitle;
    bookList[numElements].year = aYear;

    aISBN++;
    numElements++;
}

int BookList::size() const {
    return numElements;
}

string BookList::to_string() const {
    stringstream ss;

    ss << bookList[numElements - 1].ISBN << ", "
    << bookList[numElements - 1].author << ", "
    << bookList[numElements - 1].title << ", "
    << bookList[numElements - 1].year << " was created.\n";

    return ss.str();
}

string BookList::bookInfo(int index) {
    stringstream ss;

    ss << bookList[index - 1].ISBN << ", "
       << bookList[index - 1].author << ", "
       << bookList[index - 1].title << ", "
       << bookList[index - 1].year;

    return ss.str();
}

void BookList::resize() {
    // update capacity
    capacity *= 2;

    // create new array based on updated capacity
    Book * tempArr = new Book[capacity];

    // copy old array values to new array
    for (int i = 0; i < numElements; i++)
        tempArr[i] = bookList[i];

    // delete old array
    delete [] bookList;

    // reassign old array to new array
    bookList = tempArr;
}