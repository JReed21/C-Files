//
//  main.cpp
//  RandomAccess
//
//  Created by user on 2/25/16.
//  Copyright © 2016 Josh. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
/* This method simply reads a string array and inserts those strings into
 the file from position 6001 forward, overwriting all lines at those places.
 It uses a temporary vector<string> to store values of the file that we do not
 want to lose and writes back to the text file after inserting the new lines.*/
void insertNum(string x[]) {
    vector<string> temp;
    string str;
    fstream strs("file1.txt");
    long pos = 0;
    while(strs >> str) {
        temp.push_back(str);
        pos = (strs.tellp()/5);
        if(pos > 6000) {
            break;
        }
    }
    for(int i =0;i<=x->size();++i) {
        temp.push_back(x[i]);
    }
    for(string x:temp) {
    }
    int count = 0;
    strs.clear();
    strs.seekg(6006*5);
    while(strs >> str) {
        temp.push_back(str);
        count++;
    }
    strs.close();
    ofstream w("file1.txt");
    for(string x: temp) {
        w << x << "\n";
    }
    
}
/*the main function just calls insertNum with the str parameter then exits*/
int main() {
    string str;
    string n[] = {"7777","7778","7779","7780","7781"};
    insertNum(n);
    return 0;
}
