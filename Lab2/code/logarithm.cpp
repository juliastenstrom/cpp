/*********************************************************
 * Class Logarithm member functions implementation        *
 * TNG033: Lab 2                                          *
 **********************************************************/

#include "logarithm.h"
#include "polynomial.h"
#include <cmath>
#include <format>

 // ADD implementation of the member functions for class Logarithm


//defaualt constrctor 
Logarithm::Logarithm() {
	c1 = 0;
	c2 = 1;
	b = 2;
	E = new Polynomial(std::vector<double>{0,1});
}

//destructor
Logarithm::~Logarithm() {
	delete E;
}


Logarithm::Logarithm(const Expression& arg1, const double arg2, const double arg3, const int arg4) {
	
	c1 = arg2;
	c2 = arg3;
	b = arg4;
	E = arg1.clone();

}

//copy
Logarithm::Logarithm(const Logarithm& loga){
	c1 = loga.c1;
	c2 = loga.c2;
	b = loga.b;
	E = loga.E->clone();
}


//Logarithm& operator=(const Logarithm&); //assignment 
Logarithm& Logarithm::operator=(Logarithm& loga) {
	c1 = loga.c1;
	c2 = loga.c2;
	b = loga.b;
	delete E;
	E = loga.E->clone();
	return *this;
}

//function set base
Logarithm& Logarithm::set_base(int x) {
	b = x;
	return *this;
}

double Logarithm::operator()(double x) const {
	return c1 + c2 * (std::log10((*E)(x)) / std::log10(b));
}


Logarithm::operator std::string() const {

	std::string EStr = E->operator std::string();

	std::string result = std::format("{:.2f} + {:.2f} * Log_{}( {} )", c1, c2, b, EStr);

	if (c2 < 0) {
		std::string s = std::format("{:.2f} - {:.2f} * Log_{}( {} )", c1, abs(c2), b, EStr);
		return s;
	}

	return result;
}


//virtual Expression* clone() const override;
Expression* Logarithm::clone() const {
	return new Logarithm{ *this };
}

double Logarithm::base(double x, double y) const {
	return std::log(x)/(std::log(y));
}