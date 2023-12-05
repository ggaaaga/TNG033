/*************************
 * Class Polynomial       *
 * TNG033: Lab 2          *
 **************************/

#pragma once

#include <iostream>
#include <vector>
#include "expression.h"

class Polynomial : public Expression {

public:
    
    //Constructors
    explicit Polynomial(const std::vector<double>& V);
    Polynomial(double d);

    //Copy constructor
    Polynomial(const Polynomial& P);

    //Assignment Operator
    Polynomial& operator=(const Polynomial& P) = default;

    //Add-and-assign operator
    Polynomial& operator+=(const Polynomial &P); 
    
    //Addition
    friend Polynomial operator+(Polynomial lhs, const Polynomial& rhs) {
        lhs += rhs; //add and assign operator
        return lhs;
    }

    //Subscript operator
    double& operator[](int i);
    const double& operator[](int i) const;

    //Base class 
    virtual Polynomial* clone() const; 
    double operator()(double d) const;

protected:

    void display(std::ostream& os) const;
    std::vector<double> terms;

};
