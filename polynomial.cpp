//
//  Polynomial.cpp
//  Polynomial
//
//  Created by user on 3/27/16.
//  Copyright © 2016 Josh. All rights reserved.
//

#include "polynomial.h"
#include <iostream>
#include <sstream>
#include <regex>

using namespace std;

Polynomial::Polynomial() : highDeg(0) {}

//  This private method was created simply to remove repeated lines of code. It prompts the user to enter
//a number for the given header, which is either coefficient or power. It repeatedly asks the user for
//input until given a correct string of input. I import regex and use a simple search that checks the
//string for a 0 or 1 '-' using ? then matches 1 or more numbers from 0 to 9, the anchor forces the match to
//begin at the beginning of the string, and the dollar sign forcesthe match to occur at the end of the string. If
//all of these requirements are not met then the searchreturns false. The second if statement is only for powers
//since they cannot be negative numbers according to the assignment rules.

int Polynomial::getInfoPoly(string header){
    cout << "Enter a number for the " << header << ": ";
    bool check = true;
    string str;
    int number = 0;
    regex re("^-?[0-9]+$");
    while(check) {
        getline(cin, str);
        if(!regex_search(str,re)) {
            cin.clear();
            cout << "Enter a valid number for the " << header << ": ";
        }
        else if(header == "power") {
            if(stoi(str) < 0) {
                cin.clear();
                cout << "Enter a valid number for the " << header << ": ";
            }
            else {
                number = stoi(str);
                check = false;
            }
        }
        else {
            number = stoi(str);
            check = false;
        }
    }
    return number;
}

//  This public method prompts the user to enter a number for the coefficient and power then maps them
//to a map data structure. If the polynomial degree already exists it just adds the current coefficient
//to the old one. Then asks to continue.

void Polynomial::readFromUser() {
    bool end = true;
    while(end) {
        int coeff = getInfoPoly("coefficient");
        int deg = getInfoPoly("power");
        if(highDeg < deg) {
            highDeg = deg;
        }
        if(poly.count(deg) != 0) {
            poly[deg] += coeff;
        }
        else {
            poly[deg] = coeff;
        }
        cout << "Continue? [Y/N]: ";
        string temp;
        cin >> temp;
        if(temp != "Y") {
            end = false;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
//This method returns the highest degree of the polynomial

int Polynomial::degree() const { return highDeg;}

//This method return the coefficient of the specified power, and 0 otherwise
int Polynomial::coefficient(int power) {
    if(poly.count(power) == 0) {
        return 0;
    }
    else {
        return poly[power];
    }
}

//  This method checks to see if the power exists, if it does it returns the
//corresponding coefficient. Otherwise it returns that the string doesn't
//exist

void Polynomial::changeCoefficient(int newC,int power) {
    if (poly.count(power) == 0) {
        cout << "The power doesn't exist" << endl;
    }
    else {
        poly[power] = newC;
    }
}
//  This method multiplies the entire polynomial by a specified constant by simply iterating
//over the map
void Polynomial::multyPoly(int num) {
    for(auto& keyV : poly) {
        int temp = keyV.second;
        temp *= num;
        keyV.second = temp;
    }
}

//  This overloaded operator takes two polynomials and adds each powers coefficient with the other.
//This is done by checking if the first value of the key equals the second, and if so then add the
//coefficients of each. If the power of the first polynomial is greater then map that polynomial
//increase its iterator and repeat until one iterator is at the end. Once one iterator is at its end
//then the other iterator fills the remaining elements into the map
Polynomial Polynomial::operator+(Polynomial& otherPoly) const {
    Polynomial newPoly;
    auto iter1 = poly.begin();
    auto iter2 = otherPoly.poly.begin();
    while(iter1 != poly.end() && iter2 != otherPoly.poly.end()) {
        if(iter1->first == iter2->first) {
            int temp = (iter1->second + iter2->second);
            newPoly.poly[iter1->first] = temp;
            iter1++;
            iter2++;
        }
        else if((iter1->first) > (iter2->first)) {
            newPoly.poly[iter1->first] = iter1->second;
            iter1++;
        }
        else {
            newPoly.poly[iter2->first] = iter2->second;
            iter2++;
        }
    }
    if(iter1 == poly.end()) {
        while(iter2 != otherPoly.poly.end()) {
            newPoly.poly[iter2->first] = iter2->second;
            iter2++;
        }
    }
    else {
        while(iter1 != poly.end()) {
            newPoly.poly[iter1->first] = iter1->second;
            iter1++;
        }
    }
    newPoly.highDeg = newPoly.poly.begin()->first;
    return newPoly;
}

//  This method prints out the polynomial with correct formatting

void Polynomial::print() const {
    string polyS;
    for(auto& keyV : poly) {
        if(keyV.first == 0) {
            polyS += to_string(keyV.second);
        }
        else {
            polyS += to_string(keyV.second);
            polyS += "x^";
            polyS += to_string(keyV.first);
            polyS += " + ";
        }
    }
    size_t ePos = polyS.find_last_not_of(" \t");
    if( string::npos != ePos )
    {
        polyS = polyS.substr(0, ePos+1);
    }
    if(polyS.back() == '+') {
        polyS.back() = ' ';
    }
    cout << polyS;
    cout << endl;
}
//This overloaded operator simply negates every coefficient in the polynomial
Polynomial Polynomial::operator-() const{
    Polynomial newPoly;
    newPoly.highDeg = poly.begin()->first;
    for(auto& keyV : poly) {
        int temp = -keyV.second;
        newPoly.poly[keyV.first] = temp;
    }
    return newPoly;
}








