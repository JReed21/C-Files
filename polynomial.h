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
    //Default constructor, creates an empty polynomial with Highest Degree set to 0
    //
    Polynomial();
    
    //This prompts the user for input, reading one coefficient and its power at a time
    //
    void readFromUser();
    
    //This method simply returns the highest degree
    //
    int degree() const;
    
    //This method returns the coefficient of the power, otherwise returns 0
    //
    int coefficient(int power);
    
    //This method changes the coefficient of the specific power to the given coefficient
    //
    void changeCoefficient(int newC, int power);
    
    //This method multiplies a polynomial by a single constant
    //
    void multyPoly(int num);
    
    //This overloaded operator returns the sum of two given polynomials
    //
    Polynomial operator+(Polynomial& otherPoly) const;
    
    //This method prints the polynomial
    //
    void print() const;
    
    //This overloaded negation method simply negates all the coefficients
    Polynomial operator-() const;
    
    
private:
    //This ADT uses a map to store the polynomials and coefficients, The std::greater
    //makes the map order the keys from greatest to least.
    std::map<int,int,std::greater<int>> poly;
    
    //This is a private method to reduce repeated code
    int getInfoPoly(std::string header);
    
    //This is the highest degree of the polynomial
    int highDeg;
    
};

#endif