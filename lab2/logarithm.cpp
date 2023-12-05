/*********************************************************
 * Class Logarithm member functions implementation        *
 * TNG033: Lab 2                                          *
 **********************************************************/

#include "logarithm.h"
#include "polynomial.h"
#include <iomanip>

//Constructors
Logarithm::Logarithm() {
	c1 = 0; c2 = 1; b = 2; 
	std::vector<double> V{ 0,1 };
	E = new Polynomial{ V };
}

Logarithm::Logarithm(const Expression& exp, double a, double z, int bas) {

	c1 = a; c2 = z; b = bas; E = exp.clone();
}

//Destructor 
Logarithm::~Logarithm() {
	c1 = 0; c2 = 0; b = 0;
	delete E;
	E = nullptr;
}

//Copy constructors
Logarithm::Logarithm(const Logarithm& L) : c1{ L.c1 }, c2{ L.c2 }, b{ L.b }, E{ L.E->clone()} {
}

//Assignment Operator
Logarithm& Logarithm::operator=(const Logarithm& rhs) {
	c1 = rhs.c1; c2 = rhs.c2; b = rhs.b;
	delete E;
	E = rhs.E->clone();

	return *this;
}

//setbase
Logarithm Logarithm::set_base(int base) {
	b = base;
	return *this;
}

 /**** Base class functions *****/
 //Display function
void Logarithm::display(std::ostream& os) const {

	//l1 = 0.00 + 1.00 * Log_2( 0.00 + 1.00 * X^1 )

	if (c2 < 0 )
	{
		os << std::fixed << std::setprecision(2) << c1 << " - " <<  abs(c2) << " * Log_" << b << "( " << *E << " )";
	}

	else
	{
		os << std::fixed << std::setprecision(2) <<  c1 << " + " << abs(c2) << " * Log_" << b << "( " << *E << " )";
	}
}

//Clone function
Logarithm* Logarithm::clone() const {

	return new Logarithm{ *this };
}

//Function to calculate logarithm of x with base b
double Logarithm::operator()(double d) const {

	return c1 + (c2 * (log(E->operator()(d)) / log(b)));

}
