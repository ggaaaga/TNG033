/*************************
 * Class Logarithm        *
 * TNG033: Lab 2          *
 **************************/

#pragma once

#include <iostream>
#include "expression.h"



class Logarithm : public Expression {

public: 

    //Constructors
    Logarithm();
    Logarithm(const Expression& exp, double a, double z, int bas);
    ~Logarithm();

    //Copy constructor
    Logarithm(const Logarithm& L);

    //Assignment Operator
    Logarithm& operator=(const Logarithm& rhs);

    //Setbase
    Logarithm set_base(int base);

    //Base class
    virtual Logarithm* clone() const override;
    double operator()(double d) const override;

protected:

    void display(std::ostream& os) const;

    double c1;
    double c2; 
    int b;
    Expression* E;
};
