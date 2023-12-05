/*********************************************************
 * Class Polynomial member functions implementation       *
 * TNG033: Lab 2                                          *
 **********************************************************/

#include "polynomial.h"
#include <cmath>
#include <iomanip>

 //Constructors
Polynomial::Polynomial(const std::vector<double>& V) : terms{ V } {
}

//Conversion constructor
Polynomial::Polynomial(double d) {

	std::vector<double> V;
	V.push_back(d);
	terms = V;
}

//Copy Constructors
Polynomial::Polynomial(const Polynomial& P) : terms{ P.terms } {
}

//Add-and-assign operator
Polynomial& Polynomial::operator+=(const Polynomial& P) { //Ska man göra om den

	for (size_t i = 0; i < P.terms.size(); i++)
	{
		if (i >= terms.size())
		{
			terms.push_back(P.terms[i]);
		}

		else
		{
			terms[i] += P.terms[i];
		}
	}

	return *this;
}

//Subscript operators
double& Polynomial::operator[](int i) {

	return terms[i];
}


const double& Polynomial::operator[](int i) const {

	return terms[i];
}


/**** Base class functions *****/
//Display function
void Polynomial::display(std::ostream& os) const {

	for (int i = 0; i < terms.size(); i++) {

		if (i == 0)
		{
			os << std::fixed << std::setprecision(2) << terms[i];
		}

		else if (this->terms[i] < 0)
		{
			os << " - " << std::fixed << std::setprecision(2) << abs(terms[i]) << " * X^" << i;
		}

		else
		{
			os << " + " << std::fixed << std::setprecision(2) << abs(terms[i]) << " * X^" << i;
		}
	}
}

//Clone function
Polynomial* Polynomial::clone() const {

	return new Polynomial{ *this };
}

//Evaluate expression E for value d
double Polynomial::operator()(double d) const {

	double ans = 0;
	double value = 0;

	for (int i = 0; i < terms.size(); i++)
	{
		value = terms[i] * pow(d, i);
		ans += value;
	}

	return ans;
}