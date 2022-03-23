// Jason Wang
// File: RatingList.h
// Date: 9/22/20
// Purpose: Define the class RatingList

#ifndef P1_RATINGLIST_H
#define P1_RATINGLIST_H
#include <string>
using namespace std;

class RatingList {
public:
    explicit RatingList(int);
    // Constructor
    // precondition: none
    // postcondition: row and col are assigned to 0, and declare 2D ratingList
    //                array

    ~RatingList();
    // Destructor
    // precondition: none
    // postcondition: delete 2D ratingList array

    void add(const string&);
    // add element to array
    // precondition: accept a reference
    // postcondition: turn string into int and then separate them to arrayList

    void rate(int, int, int);
    // add rating to array
    // precondition: three integers
    // postcondition: add rating to array

    void extendRow();
    // extend row in ratingList
    // precondition: none
    // postcondition: extend row in ratingList if row >= capacity

    void extendCol();
    // extend col in ratingList
    // precondition: none
    // postcondition: extend col in ratingList if col >= capacity

    int returnOneRating(int, int);
    // return one rating
    // precondition: accept tow integers to pick rating up
    // postcondition: return one rating

private:
    int capacity;                   // capacity of bookList array
    int row, col;                   // scope of array
    void resize();                  // resize array (when full)
    int ** ratingList;              // 2D array


};

#endif //P1_RATINGLIST_H
