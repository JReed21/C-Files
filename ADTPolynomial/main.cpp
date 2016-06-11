//
//  main.cpp
//  ADT
//
//  Created by user on 3/28/16.
//  Copyright © 2016 Josh. All rights reserved.
//

#include <iostream>
#include "polynomial.h"
#include <regex>
using namespace std;

//  The main method just tests each method of the polynomial that is accessible
//by the user.

int main(int argc, const char * argv[]) {
    Polynomial poly;
    Polynomial poly2;
    Polynomial poly3;
    poly.readFromUser();
    poly2.readFromUser();
    cout << "poly: ";
    poly.print();
    cout << "poly2: ";
    poly2.print();
    cout << "poly3 = poly2 + poly: ";
    poly3 = poly+poly2;
    poly3.print();
    cout << "poly2 before being multiplied by 3: ";
    poly2.print();
    poly2.multyPoly(3);
    cout << "after ";
    poly2.print();
    poly = -poly;
    cout << "poly being negated: ";
    poly.print();
    cout << "poly3's coefficient for 5th degree: " << poly3.coefficient(5) << endl;
    poly3.changeCoefficient(10, 5);
    cout << "after changing poly3's 5th degree coefficient to 10: " << poly3.coefficient(5) << endl;
    cout << "highest degree of poly2: " << poly2.degree() << endl;
    return 0;
}
