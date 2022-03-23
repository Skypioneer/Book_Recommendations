// Jason Wang
// File: p1.cpp
// Date: 9/22/20
// Purpose: The program demonstrates how to add member and book, view
//          each member's ratings and his/her books of recommendations as many
//          times as the user wants.

#include "BookList.h"
#include "MemberList.h"
#include "RatingList.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void readBookFile(BookList&, const string&);
// Given the references of BookList and string, assign the contents to bookList
// IN: references of BookList and string
// MODIFY: none
// OUT: none

void readRatingFile(MemberList&, RatingList&, const string&);
// Given the references of MemberList and RatingList, assign the contents to
// memberList and ratingList
// IN: references of BookList, RatingList, and string
// MODIFY: none
// OUT: none

int menu();
// The entrance main for operation
// IN: none
// MODIFY: none
// OUT: option from user

void newMember(MemberList&, RatingList&);
// Add a new member into the program
// IN: references of MemberList and RatingList
// MODIFY: none
// OUT: none

void newBook(BookList&, RatingList&);
// Add a new book into the program
// IN: references of BookList and RatingList
// MODIFY: none
// OUT: none

void logIn(BookList&, MemberList&, RatingList&);
// Main operations for login interface
// IN: references of BookList, MemberList, and RatingList
// MODIFY: none
// OUT: none

int logInMenu();
// The login menu for operation
// IN: none
// MODIFY: none
// OUT: option from user

void rateBook(RatingList&, BookList&, int);
// Given rating to ratingList
// IN: references of RatingList and BookList, and member account
// MODIFY: none
// OUT: none

void viewRatings(BookList&, MemberList&, RatingList&, int);
// Printed table of member's ratings
// IN: references of BookList, MemberList, and RatingList, and member account
// MODIFY: none
// OUT: none

void seeRecommendations(BookList&, MemberList&, RatingList&, int);
// Printed table of recommended books for member
// IN: references of BookList, MemberList, and RatingList, and member account
// MODIFY: none
// OUT: none

int main() {
    string bookFile, ratingFile;    // the variables holding files
    const int SIZE = 100;           // set size to 100
    int option;                     // user's choice

    BookList bookList(SIZE);        // declare class BookList
    MemberList memberList(SIZE);    // declare class MemberList
    RatingList ratingList(SIZE);    // declare class RatingList

    cout << "Welcome to the Book Recommendation Program!" << endl
            << "The program can allow the user to add member and books,\n"
            << "view the current ratings, and recommend the books that\n"
            << "the user may like as many times as he/she wants.\n\n";

    cout << "Enter books file: ";
    cin >> bookFile;
    readBookFile(bookList, bookFile);

    cout << "Enter rating file: ";
    cin >> ratingFile;
    readRatingFile(memberList, ratingList, ratingFile);

    cout << "\n# of books: " << bookList.size() << endl;
    cout << "# of memberList: " << memberList.size() << endl;

    // determine which operation that the user wanna execute
    do{
        option = menu();

        if (option == 1)
           newMember(memberList, ratingList);
        else if (option == 2)
            newBook(bookList, ratingList);
        else if (option == 3)
            logIn(bookList, memberList, ratingList);
        else if (option < 1 || option > 4)
           cout << "\nError operation... try again!\n";
        else
           cout << "Thank you for using the Book Recommendation Program!\n";
    }while (option != 4);

    return 0;
}

int menu(){
    int input;      // user's input

    cout << endl;
    cout << "************** MENU **************" << endl;
    cout << "* 1. Add a new member            *" << endl;
    cout << "* 2. Add a new book              *" << endl;
    cout << "* 3. Login                       *" << endl;
    cout << "* 4. Quit                        *" << endl;
    cout << "**********************************" << endl << endl;
    cout << "Enter a menu option: ";
    cin >> input;

    cout << endl;

    return input;
}

void newMember(MemberList& memberList, RatingList& ratingList){
    string name;    // to hold member's name

    cout << "Enter the name of the new member: ";
    cin.ignore();
    getline(cin, name);

    memberList.add(name);
    ratingList.extendRow();

    cout << memberList.to_string();
}

void newBook(BookList& bookList, RatingList& ratingList){
    string aAuthor, aTitle, aYear;
    cout << "Enter the author of the new book: ";
    cin.ignore();
    getline(cin, aAuthor);
    cout << "Enter the title of the new book: ";
    getline(cin, aTitle);
    cout << "Enter the year (or range of years) of the new book: ";
    cin >> aYear;

    bookList.add(aAuthor, aTitle, aYear);
    ratingList.extendCol();

    cout << bookList.to_string();
}

void logIn(BookList& bookList, MemberList& memberList, RatingList& ratingList){
    int account, option;            // to hold member account and user's choice
    cout << "Enter member account: ";
    cin >> account;
    cout << memberList.name(account) << ", you are logged in!\n";

    // Determine which operation that the user wanna execute
    do {
        option = logInMenu();

        if (option == 1)
            newMember(memberList, ratingList);
        else if (option == 2)
            newBook(bookList, ratingList);
        else if (option == 3)
            rateBook(ratingList,bookList, account);
        else if (option == 4)
            viewRatings(bookList, memberList, ratingList, account);
        else if (option == 5)
            seeRecommendations(bookList, memberList, ratingList,
                                                                    account);
        else if (option < 1 || option > 6)
            cout << "Error operation... try again!\n";

    }while (option != 6);

}

int logInMenu(){
    int option;     // user input

    cout << endl;
    cout << "************** MENU **************" << endl;
    cout << "* 1. Add a new member            *" << endl;
    cout << "* 2. Add a new book              *" << endl;
    cout << "* 3. Rate book                   *" << endl;
    cout << "* 4. View ratings                *" << endl;
    cout << "* 5. See recommendations         *" << endl;
    cout << "* 6. Logout                      *" << endl;
    cout << "**********************************" << endl << endl;
    cout << "Enter a menu option: ";
    cin >> option;

    if (option != 6)
        cout << endl;

    return option;
}

void rateBook(RatingList& ratingList, BookList& bookList, int mem){
    int ISBN, rating;   // to hold the user's inputs
    char ans = 'y';     // answer to whether re-rate books

    cout << "Enter the ISBN for the book you'd like to rate: ";
    cin >> ISBN;

    // check if the member has rated the book
    if (ratingList.returnOneRating(mem, ISBN) != 0){
        cout << "Your current rating for " << bookList.bookInfo(ISBN)
        << "=> rating: " << ratingList.returnOneRating(mem, ISBN) << endl;
        cout << "Would you like to re-rate this book (y/n)? ";
        cin >> ans;
    }

    // rate the book
    if (ans == 'y' || ans == 'Y') {
        cout << "Enter your rating: ";
        cin >> rating;

        ratingList.rate(mem, ISBN, rating);

        cout << "Your new rating for " << bookList.bookInfo(ISBN)
        << " => rating: " << ratingList.returnOneRating(mem, ISBN) << endl;
    }
}

void viewRatings(BookList& bookList, MemberList& memberList,
                                            RatingList& ratingList, int mem){
    cout << memberList.name(mem) << "'s ratings...\n";
    for (int i = 0; i < bookList.size(); i++){
        cout << bookList.bookInfo(i + 1) << " => rating: "
        << ratingList.returnOneRating(mem, i + 1) << endl;
    }
}

void seeRecommendations(BookList& bookList, MemberList& memberList,
                                            RatingList& ratingList, int mem){
    int sum, tmpSum, position, tmpPosition;     // to hold sum, temporarily sum,
                                                // position, and temporarily
                                                // position

    // find the position that has the most maximum sum
    for (int i = 0; i < memberList.size(); i++){
        tmpPosition = i;
        tmpSum = 0;
        if (i != mem - 1) {
            for (int k = 0; k < bookList.size(); k++) {
                tmpSum += ratingList.returnOneRating(mem, k + 1) *
                        ratingList.returnOneRating(i + 1, k + 1);
            }
            if (i > 0){
                if (tmpSum > sum){
                    sum = tmpSum;
                    position = tmpPosition;
                }
            }
            else{
                sum = tmpSum;
                position = tmpPosition;
            }
        }
    }

    cout << "You have similar taste in books as "
         << memberList.name(position + 1) << "!\n\n";

    // print out the 5 ratings recommended books
    cout << "Here are the books they really liked:\n";
    for (int i = 0; i < bookList.size(); i++){
        if (ratingList.returnOneRating(mem, i + 1) == 0 &&
                        ratingList.returnOneRating(position + 1, i + 1) == 5){
            cout << bookList.bookInfo(i + 1) << endl;
        }
    }
    cout << "\nAnd here are the books they liked:\n";
    for (int i = 0; i < bookList.size(); i++){
        if (ratingList.returnOneRating(mem, i + 1) == 0 &&
            ratingList.returnOneRating(position + 1, i + 1) == 3){
            cout << bookList.bookInfo(i + 1) << endl;
        }
    }
}

void readBookFile(BookList& bookList, const string& bookFile){
    string fileName, word, aAuthor, aTitle, aYear;  // to hold values from
                                                    // the file
    int count;                                      // loop control variable
    ifstream inFile;                                // file variable

    // open the file
    inFile.open(bookFile);

    // read in the file and classify its contents in terms of author, title, and
    // year
    if (inFile){
        string line, token;
        stringstream iss;
        while (getline(inFile, line)){
            count = 0;
            iss << line;
            while (getline(iss, token, ',')){
                if (count == 0)
                    aAuthor = token;
                else if (count == 1)
                    aTitle = token;
                else
                    aYear = token;
                count++;
            }
            bookList.add(aAuthor, aTitle, aYear);

            // clean iss
            iss.clear();        // 清除錯誤(eof), 因為要重複使用iss。
            iss.str("");     // 清空內存，省空間。
        }
    }
    else
        cout << "Error opening file...\n";

    //close file
    inFile.close();
}

void readRatingFile(MemberList& memberList, RatingList& ratingList,
                                                    const string& ratingFile) {
    string line;                // to hold the values from the file
    int count = 0;              // loop control variable
    ifstream infile;            //variable to read in a file

    //open and read file
    infile.open(ratingFile);

    // determine if the file can be opened
    if (infile) {
        // assign contents into either members array or ratings 2D array
        while (getline(infile, line)) {
            // determine which line it is
            if (count % 2 == 0) {
                memberList.add(line);
            }
            else {
                ratingList.add(line);
            }
            count++;
        }
    }else
        cout << "Error opening file...\n";

    // close file
    infile.close();
}