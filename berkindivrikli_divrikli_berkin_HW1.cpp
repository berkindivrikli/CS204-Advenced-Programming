/*
            CS204 HW1
 Author     : Berkin Divrikli
 SUusername : berkindivrikli
 SU id      : 28004
 Date       : 9.03.2021
 
 The purpose of this homework is reading and working on files. By the given data creating a matrix and placing the word on the matrix with given instructions and rules. Also, displaying an error message in case of failure of implementation.
 */



#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;
//converts char to int.
int ctoi(char a){
    return a - '0';
}
//displays the vector.
void displayVector(vector<vector<char>> & myvector){
    for (int i = 0; i < myvector.size(); i++) {
        for (int t = 0; t < myvector[i].size(); t++) {
            cout << myvector[i][t];
        }
        cout << endl;
    }
}
//struct which contains the information about the line.
struct lineword{
    string orientation;
    int row, column;
    string direction;
};

//functions which implements char to the matrix according to the directions
bool right(vector<vector<char>> & myvector, char ch, int & r, int & c, int & count, string orientation){
    bool flag = false;
    if (orientation == "CW") {
//        right
        if ((c + 1 <= myvector[0].size()-1) && (myvector[r][c + 1] == '-')) {
            myvector[r][c+1] = ch;
            c = c+1;
            flag = true;
        }else if ((r < myvector.size()-1) && (myvector[r+1][c] == '-')) {
            myvector[r+1][c] = ch;
            r++;
            flag = true;
//            down
        }else if ((c != 0) && (myvector[r][c-1] == '-')){
            myvector[r][c-1] = ch;
            c--;
            flag = true;
//            left
        }else if ((r != 0) && (myvector[r-1][c] == '-')){
            myvector[r-1][c] = ch;
            r--;
            flag = true;
//            up
        }
    }else if (orientation == "CCW"){
        if ((c + 1 <= myvector[0].size()-1) && (myvector[r][c + 1] == '-')) {
            myvector[r][c+1] = ch;
            c = c+1;
            flag = true;
        }else if ((r != 0) && (myvector[r-1][c] == '-')){
//            up
            myvector[r-1][c] = ch;
            r--;
            flag = true;
        }else if ((c != 0) && (myvector[r][c-1] == '-')){
//            left
            myvector[r][c-1] = ch;
            c--;
            flag = true;
        }else if ((r < myvector.size()-1) && (myvector[r+1][c] == '-')){
//            down
            myvector[r+1][c] = ch;
            r++;
            flag = true;
        }
    }
    
    return flag;
}
bool left(vector<vector<char>> & myvector, char ch, int & r, int & c, int & count, string orientation){
    bool flag = false;
    if (orientation == "CW") {
        if ((c != 0) && (myvector[r][c-1] == '-')) {
            myvector[r][c-1] = ch;
            c--;
            flag = true;
        }else if ((r != 0) && (myvector[r-1][c] == '-')){
            myvector[r-1][c] = ch;
            r--;
            flag = true;
        }else if ((c + 1 <= myvector[0].size()-1) && (myvector[r][c + 1] == '-')){
            myvector[r][c+1] = ch;
            c = c+1;
            flag = true;
        }else if ((r < myvector.size()-1) && (myvector[r+1][c] == '-')){
            myvector[r+1][c] = ch;
            r++;
            flag = true;
        }
    }else{
        if ((c != 0) && (myvector[r][c-1] == '-')) {
//            left
            myvector[r][c-1] = ch;
            c--;
            flag = true;
        }else if ((r < myvector.size()-1) && (myvector[r+1][c] == '-')){
//            down
            myvector[r+1][c] = ch;
            r++;
            flag = true;
        }else if ((c + 1 <= myvector[0].size()-1) && (myvector[r][c + 1] == '-')){
//            right
            myvector[r][c+1] = ch;
            c = c+1;
            flag = true;
        }else if ((r != 0) && (myvector[r-1][c] == '-')){
//            up
            myvector[r-1][c] = ch;
            r--;
            flag = true;
        }
    }
    return flag;
}
bool up(vector<vector<char>> & myvector, char ch, int & r, int & c, int & count, string orientation){
    bool flag = false;
    if (orientation == "CW") {
        if ((r != 0) && (myvector[r-1][c] == '-')) {
//            up
            myvector[r-1][c] = ch;
            r--;
            flag = true;
        }else if ((c + 1 <= myvector[0].size()-1) && (myvector[r][c + 1] == '-')){
//            right
            myvector[r][c+1] = ch;
            c = c+1;
            flag = true;
        }else if ((r < myvector.size()-1) && (myvector[r+1][c] == '-')){
//            down
            myvector[r+1][c] = ch;
            r++;
            flag = true;
        }else if ((c != 0) && (myvector[r][c-1] == '-')){
//            left
            myvector[r][c-1] = ch;
            c--;
            flag = true;
        }
    }else{
        if ((r != 0) && (myvector[r-1][c] == '-')) {
//            up
            myvector[r-1][c] = ch;
            r--;
            flag = true;
        }else if ((c != 0) && (myvector[r][c-1] == '-')){
//            left
            myvector[r][c-1] = ch;
            c--;
            flag = true;
        }else if ((r < myvector.size()-1) && (myvector[r+1][c] == '-')){
//            down
            myvector[r+1][c] = ch;
            r++;
            flag = true;
        }else if ((c + 1 <= myvector[0].size()-1) && (myvector[r][c + 1] == '-')){
//            right
            myvector[r][c+1] = ch;
            c = c+1;
            flag = true;
        }
    }
    return flag;
}
bool down(vector<vector<char>> & myvector, char ch, int & r, int & c, int & count, string orientation){
    bool flag = false;
    if (orientation == "CW") {
        if ((r < myvector.size()-1) && (myvector[r+1][c] == '-')) {
//            down
            myvector[r+1][c] = ch;
            r++;
            flag = true;
        }else if ((c != 0) && (myvector[r][c-1] == '-')){
//            left
            myvector[r][c-1] = ch;
            c--;
            flag = true;
        }else if ((r != 0) && (myvector[r-1][c] == '-')){
//            up
            myvector[r-1][c] = ch;
            r--;
            flag = true;
        }else if ((c + 1 <= myvector[0].size()-1) && (myvector[r][c + 1] == '-')){
//          right
            myvector[r][c+1] = ch;
            c = c+1;
            flag = true;
        }
    }else{
        if ((r < myvector.size()-1) && (myvector[r+1][c] == '-')) {
//            down
            myvector[r+1][c] = ch;
            r++;
            flag = true;
        }else if ((c + 1 <= myvector[0].size()-1) && (myvector[r][c + 1] == '-')){
//            right
            myvector[r][c+1] = ch;
            c = c+1;
            flag = true;
        }else if ((r != 0) && (myvector[r-1][c] == '-')){
//            up
            myvector[r-1][c] = ch;
            r--;
            flag = true;
        }else if ((c != 0) && (myvector[r][c-1] == '-')){
//            left
            myvector[r][c-1] = ch;
            c--;
            flag = true;
        }
    }
    return flag;
}
int main() {
    string fileName;
    ifstream text;
    cout << "Please enter the name of the file: ";
    cin >> fileName;
    text.open(fileName.c_str());
    while (text.fail()) {
        cout << "File name is incorrect, please enter again: ";
        cin >> fileName;
        text.open(fileName.c_str());
    }
    string line;
    getline(text, line);
    int rowx , colmn;
    rowx = stoi(line.substr(0,line.find(" ")));
    colmn = stoi(line.substr(line.find(" ") + 1));
    
    if ((rowx <= 0) || (colmn <= 0)) {
        cout << "Invalid input for row and/or column!" << endl;
    }else{
        vector<vector<char>> myvector(rowx, vector<char>(colmn, '-'));
//        after I create the matrix I read every line first, create the second matrix. If program implements every letter, I change the real vector with the copied one. For every line I check the direction first then send the character ro the functions that I defined.
        while (getline(text, line)) {
            vector<vector<char>> currentVector = myvector;
            lineword current;
            string word, currentRow, currentCol;
           
            istringstream vv(line);
            int elementCheck = 0;
            string flagOne;
            while (vv >> flagOne) {
                elementCheck++;
            }
             if (elementCheck != 5){
                cout << "Invalid line! Number of values is different than 5." << endl;
             }else{
                 istringstream ss(line);
                 ss >> word >> currentRow >> currentCol >> current.direction >> current.orientation;
                 current.row = stoi(currentRow);
                 current.column = stoi(currentCol);
                 //        -----------------------------------------------------------------------------------
                 if ((current.row < 0) || (current.row > rowx-1) || (current.column < 0) || (current.column > colmn-1)){
                     cout << "Starting point is out of range! Point: " << current.row << "," << current.column << endl;
                 }else if ((current.direction != "r") && (current.direction != "l") && (current.direction != "u") && (current.direction != "d")){
                     cout << "Invalid input for direction! Direction: " << current.direction << endl;
                 }else if ((current.orientation != "CCW") && (current.orientation != "CW")) {
                     cout << "Invalid input for orientation! Orientation: " << current.orientation << endl;
                 }else{
                     int check = word.length();
                     int count = 0;
                     int realRow = current.row;
                     int realColumn = current.column;
                     if (currentVector[current.row][current.column] == '-') {
                         currentVector[current.row][current.column] = word[0];
                         count++;
                         for (int c = 1; c < check; c++) {
                             if (current.direction == "r") {
                                 if (right(currentVector, word[c],current.row, current.column, count, current.orientation) == true) {
                                     count++;
                                 }else{
                                     break;
                                 }
                             }else if (current.direction == "l"){
                                 if (left(currentVector, word[c],current.row, current.column, count, current.orientation) == true) {
                                     count++;
                                 }else{
                                     break;
                                 }
                             }else if (current.direction == "u"){
                                 if (up(currentVector, word[c],current.row, current.column, count, current.orientation) == true) {
                                     count++;
                                 }else{
                                     break;
                                 }
                             }else if (current.direction == "d"){
                                 if (down(currentVector, word[c],current.row, current.column, count, current.orientation) == true) {
                                     count++;
                                 }else{
                                     break;
                                 }
                             }
                         }
                         
                         if (count == check) {
                             myvector = currentVector;
                             cout << "\"" <<  word << "\"" << " was put into the matrix with given starting point: "<< realRow << "," << realColumn << " direction: " << current.direction <<" orientation: " << current.orientation << endl;
                         }else{
                             cout << "\"" <<  word << "\"" << " could not be put into the matrix with given starting point: "<< realRow << "," << realColumn << " direction: " << current.direction <<" orientation: " << current.orientation << endl;
                         }
                     }else{
                         cout << "\"" <<  word << "\"" << " could not be put into the matrix with given starting point: "<< realRow << "," << realColumn << " direction: " << current.direction <<" orientation: " << current.orientation << endl;
                     }
                     

                     displayVector(myvector);
                 }
             }
            
            }
    }
    return 0;
}
