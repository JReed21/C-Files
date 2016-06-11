//
//  main.cpp
//  OReading
//
//  Created by user on 2/23/16.
//  Copyright © 2016 Josh. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
/* This method checks to see whether or not we can access the file in the directory*/
bool checkErrors(vector<int> firstArr) {
    if(firstArr.empty()) {
        cout << "There is no access to specified file, or file does not exist. (Try changing directory or permissions)" << endl;
        return true;
    }
    return false;
}
/*This method simply reads the file and outputs it's contents into a vector which
 it returns to the main function. The fileName string is the name of the file to find
 and the returnString vector is the vector that contains the contents.*/
vector<int> intArray(string fileName) {
    vector<int> returnString;
    int str1;
    ifstream ifs(fileName);
    while(ifs >> str1){
        if(ifs.fail()) {
            ifs.get();
        }
        returnString.push_back(str1);
    }
    return returnString;
}
/*This is based off the merge sort function, but very simplified since we are not
 breaking up the contents. We are just comparing the contents of each file one by one.
 The contents of each file will be written into a new file called mergedFile.txt and will
 be saved into the current directory.*/
void mergeIt(vector<int>& firstVec, vector<int>& secondVec) {
    ofstream w("mergedFile.txt");
    int i = 0;
    int j = 0;
    while(i < firstVec.size() && j < secondVec.size()) {
        if(firstVec[i] < secondVec[j]) {
            w << firstVec[i] << "\n";
            i++;
        }
        else {
            w << secondVec[j] << "\n";
            j++;
        }
    }
    if((i) == firstVec.size()) {
        while(j < secondVec.size()){
            w << secondVec[j] << "\n";
            j++;
        }
    }
    else {
        while(i < firstVec.size()) {
            w << firstVec[i] << "\n";
            i++;
        }
    }
    w.close();
    cout << "The new file is called mergedFile.txt and is located in the current directory" << endl;
}
/* This method checks to see whether or not we can access the file in the directory*/
bool fileExist(string name) {
    ifstream infile(name);
    if(infile.good()) {
        return true;
    }
    else {
        return false;
    }
}
/*This method asks the user to input a file name then checks if the file is
 accessible or exists by calling the fileExist method*/
string getFile() {
    string name;
    cout<< "Enter a file name: ";
    cin >> name;
    if(fileExist(name)) {
        return name;
    }
    else{
        return "";
    }
}
using namespace std;
/*The main fucntion simple calls the other methos and checks for the errors by seeing if the
 array is empty.*/
int main() {
    vector<int> firstArr = intArray(getFile());
    if(checkErrors(firstArr)) {
        return 0;
    }
    vector<int> secondArr = intArray(getFile());
    if(checkErrors(secondArr)) {
        return 0;
    }
    mergeIt(firstArr,secondArr);
    ifstream s("mergedFile.txt");
    string f;
    return 0;
}

