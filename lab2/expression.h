/*************************
 * Class Expression       *
 * TNG033: Lab 2          *
 **************************/

#pragma once

#include <iostream>

constexpr double Epsilon = 1.0e-5;

class Expression {
public:
    // Destructor
    virtual ~Expression() {
        --count_expressions;
    }

    // ADD OTHER MEMBER FUNCTIONS

    bool isRoot(double d) const;

    virtual double operator()(double d) const = 0; //Kolla funktionsvärdet i d

    virtual Expression* clone() const = 0;
    
    friend std::ostream& operator<<(std::ostream& os, const Expression& E); 

    // Return number of existing instances of class Expression
    // Used only for debug purposes
    static std::size_t get_count_expressions();

protected:
    // Default constructor
    Expression() {
        ++count_expressions;
    }

    // Copy constructor
    Expression(const Expression&) {
        ++count_expressions;
    }

    virtual void display(std::ostream& os) const = 0;

    // Total number of existing expressions -- to help to detect bugs in the code
    static std::size_t count_expressions;

    //Default assignment operator
    Expression& operator=(const Expression& E) = default;
};
