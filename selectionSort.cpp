//
//  main.cpp
//  selectionSort
//
//  Created by user on 2/10/16.
//  Copyright © 2016 Josh. All rights reserved.
//

#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

// getData accepts no parameters and returns a vector after asking for a sequence numbers
//stringstream accepts the string str and breaks it on spaces. We iterate through the string
//and push the numbers found in the string into a vector<int>.

vector<int> getData() {
    vector<int> tempV;
    string str;
    cout << "enter a sequence of numbers seperated by spaces(Anything not a number or space will also be determined as a break): ";
    getline(cin, str);
    stringstream sstr;
    sstr << str;
    while(sstr) {
        int temp;
        sstr >> temp;
        if(sstr.fail()) {
            cout << "breaking on " << temp;
            break;
        }
        else tempV.push_back(temp);
    }
    return tempV;
}
// selectionSort is exactly what it says it is. It is based on the selection sort algorithm
//with a Big O of (n^2). It loops once through each element but each loop contains one nested loop
//where it also loops through the string checking for the lowest element to swap. It accepts a
//vector<int> and sorts the contents.

void selectionSort(vector<int>& sortThis) {
    long len = sortThis.size();
    int swapIt = -1;
    int current;
    for(int i = 0; i < len; i++){
        current = sortThis[i];
        for(int z = i + 1; z < len; z++) {
            if(current > sortThis[z]) {
                swapIt = z;
                current = sortThis[z];
            }
        }
        // Check to see if swapIt changed positions
        if(swapIt != -1) {
            std::swap(sortThis[i],sortThis[swapIt]);
        }
        swapIt = -1;
    }
}
// printVector is a very basic function that accepts a vector and outputs it's contents.

void printVector(vector<int>& sortThis) {
    cout << "The sorted vector: ";
    for(int x: sortThis) {
        cout << x << " ";
    }
}
// Main function, where it calls the other three functions.

int main(int argc, const char * argv[]) {
    vector<int> listOfNumbers = getData();
    selectionSort(listOfNumbers);
    printVector(listOfNumbers);
    return 0;
}
