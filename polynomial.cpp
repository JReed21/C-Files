//
//  Polynomial.cpp
//  Polynomial
//
//  Created by user on 3/27/16.
//  Copyright © 2016 Josh. All rights reserved.
//

#include "Polynomial.h"
#include <iostream>
#include <sstream>

using namespace std;

Polynomial::Polynomial() : highDeg(0) {}

void Polynomial::readFromUser() {
    bool end = true;
    while(end) {
        int deg = -1;
        int coeF = 0;
        cout << "Enter a number for the coefficient: ";
        while(!(cin>>coeF) || (coeF < 1)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  //Ignore anything other than integers
            cout << "Enter a valid number for the coefficient: ";
        }
        cin.clear();
        cout << "Enter a number for the coefficient's power: ";
        while(!(cin>>deg) || (deg < 0)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  //Ignore anything other than integers
            cout << "Enter a valid number for the power: ";
        }
        cin.clear();
        if(highDeg < deg) {
            highDeg = deg;
        }
        poly[deg] = coeF;
        cout << "Continue? [Y/N]: ";
        string temp;
        cin >> temp;
        if(temp != "Y") {
            end = false;
        }
    }
}
int Polynomial::degree() const { return highDeg;}

int Polynomial::coefficient(int power) {return poly[power];}

void Polynomial::changeCoefficient(int newC,int power) {
    if(poly.count(power) != 0) {
        poly[power] = newC;
    }
    else {
        cout <<  "Power does not exist." << endl;
    }
}

void Polynomial::multyPoly(int num) {
    for(auto& keyV : poly) {
        int temp = keyV.second;
        temp *= num;
        keyV.second = temp;
    }
}

Polynomial Polynomial::operator+(const Polynomial& otherPoly) const {
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
void Polynomial::print() const {
    string polyS;
    for(auto& keyV : poly) {
        polyS += to_string(keyV.second);
        polyS += "x^";
        polyS += to_string(keyV.first);
        polyS += " + ";
    }
    polyS.pop_back();
    polyS.pop_back();
    cout << polyS;
    cout << endl;
}
Polynomial Polynomial::operator-() const{
    Polynomial newPoly;
    newPoly.highDeg = poly.begin()->first;
    for(auto& keyV : poly) {
        int temp = -keyV.second;
        newPoly.poly[keyV.first] = temp;
    }
    return newPoly;
}








