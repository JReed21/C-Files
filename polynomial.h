//
//  Polynomial.h
//  Polynomial
//
//  Created by user on 3/27/16.
//  Copyright © 2016 Josh. All rights reserved.
//

#ifndef _POLYNOMIAL_H
#define _POLYNOMIAL_H

#include <exception>
#include <map>

class Polynomial {
    
public:
    
    Polynomial();
    
    void readFromUser();
    
    int degree() const;

    int coefficient(int power);
    
    void changeCoefficient(int newC, int power);
    
    void multyPoly(int num);
    
    Polynomial operator+(const Polynomial& otherPoly) const;
    
    void print() const;
    
    Polynomial operator-() const;
    
private:
    std::map<int,int,std::greater<int>> poly;
    
    int highDeg;
    
};

#endif