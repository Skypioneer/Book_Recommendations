// Jason Wang
// File: RatingList.cpp
// Date: 9/22/20
// Purpose: Implement of the rating lists

#include "RatingList.h"
#include <sstream>
using namespace std;

RatingList::RatingList(int cap) {
    ratingList = new int * [cap];
    for (int k = 0; k < cap; k++)
        ratingList[k] = new int[cap];
    capacity = cap;
    row = 0;
    col = 0;
}

RatingList::~RatingList() {
    for (int i = 0; i < capacity; i++)
        delete [] ratingList[i];
    delete [] ratingList;
}

void RatingList::add(const string& rating) {
    int num;
    string word;
    istringstream ss(rating);
    col = 0;
    while (ss >> word) {
        num = stoi(word);
        ratingList[row][col] = num;
        col++;
    }
    row++;
}

void RatingList::rate(int mem, int book, int rating) {
    ratingList[mem - 1][book - 1] = rating;
}

void RatingList::extendRow() {
    if (row >= capacity)
        resize();

    row++;
}

void RatingList::extendCol() {
    if (col >= capacity)
        resize();

    col++;
}

int RatingList::returnOneRating(int mem, int book) {
    return ratingList[mem - 1][book - 1];
}

void RatingList::resize() {
    // update capacity
    capacity *= 2;

    // create new array based on updated capacity
    int ** tempArr = new int * [capacity];
    for (int k = 0; k < capacity; k++)
        tempArr[k] = new int[capacity];

    // copy old array values to new array
    for (int i = 0; i < row; i++){
        for (int f = 0; f < col; f++)
        tempArr[i][f] = ratingList[i][f];
    }

    // delete old array
    for (int i = 0; i < row; i++)
        delete [] ratingList[i];
    delete [] ratingList;

    // reassign old array to new array
    ratingList = tempArr;
}