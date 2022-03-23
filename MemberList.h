// Jason Wang
// File: MemberList.h
// Date: 9/22/20
// Purpose: Define the class MemberList

#ifndef P1_MEMBERLIST_H
#define P1_MEMBERLIST_H
#include <string>
using namespace std;

class MemberList {
public:
    explicit MemberList(int);
    // Constructor
    // precondition: accept size of capacity
    // postcondition: declare memberList, assign cap to capacity, numElements
    //                is 0, and aAccount is 1;

    ~MemberList();
    // Destructor
    // precondition: none
    // postcondition: delete memberList

    void add(string);
    // add element to array
    // precondition: accept a name
    // postcondition: assign aName to name and the an aAccount to account

    int size() const;
    // number of elements in array
    // precondition: none
    // postcondition: return size of memberList

    string name(int);
    // return a name in array
    // precondition: accept an integer
    // postcondition: return a name in array

    string to_string() const;
    // returns string representation
    // precondition: none
    // postcondition: return the latest element in array

private:
    struct Member {
        int account;                // index of memberList array
        string name;                // name of member
    };
    Member * memberList;            // 1D array

    int aAccount;                   // index of memberList array
    int capacity;                   // capacity of memeberList array
    int numElements;                // Number of elements

    void resize();                  // resize array (when full)
};

#endif //P1_MEMBERLIST_H
