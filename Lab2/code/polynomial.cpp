/*********************************************************
 * Class Polynomial member functions implementation       *
 * TNG033: Lab 2                                          *
 **********************************************************/

#include "polynomial.h"
#include <cmath>
#include <string>

 // ADD implementation of the member functions for class Polynomial


Polynomial::Polynomial(){}

 //add only one coefficient 
Polynomial::Polynomial(const double x){
	const std::vector<double> X = { x };
	coef = X;
}

Polynomial::Polynomial(const std::vector<double> somecoef) : coef{ somecoef} {}


Polynomial::Polynomial(const Polynomial& poly) {
	coef = poly.coefs();
}

std::vector<double> Polynomial::coefs() const {
	return coef;
}


Polynomial& Polynomial::operator+=(Polynomial poly) {
	
	if (coef.size() < poly.coefs().size()) {
		coef.resize(poly.coefs().size(), 0);
	}
	
	for (int i = 0; i < poly.coefs().size(); i++) {
		coef[i] = coef[i] + poly.coefs()[i];
	}
	
	return *this;
	//[1, 2, 3] + [1, 2] = [2, 4, 3]
}



//Addition +
Polynomial operator+(const Polynomial& poly1, const Polynomial& poly2) {

	Polynomial result{ poly1 };
	result += poly2;
	return result;
}


double& Polynomial::operator[](const int x) {
	return coef[x];
}

double Polynomial::operator[](const int x) const {
	return coef[x];
}


//    virtual double operator()(double x) const override;

double Polynomial::operator()(double x) const {
	double result = 0;
	for (int i = 0; i < coef.size(); i++) {
		result += coef[i] * (pow(x, i));
	}
	return result;
}


Polynomial::operator std::string() const {
	std::string result;
	result += std::format("{:.2f}", coef[0]);
	for (int i = 1; i < coef.size(); i++) {
		if (coef[i] < 0) {
			result += std::format(" - {:.2f} * X^{}", -coef[i], i);
		}
		else {
			result += std::format(" + {:.2f} * X^{}", coef[i], i);
		}
	}
	return result;
}




//an assignment operator
Polynomial& Polynomial::operator=(Polynomial poly) {
	coef = poly.coefs();
	return *this;
}

//Clone
Expression* Polynomial::clone() const {
	return new Polynomial(*this);
}
