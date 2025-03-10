/*************************
 * Class Logarithm        *
 * TNG033: Lab 2          *
 **************************/

#pragma once

#include <iostream>

#include "expression.h"
#include "polynomial.h"

class Logarithm : public Expression {
public:

	//default constructor 
	Logarithm();


	//Destructor
	~Logarithm();

	//Constructor that makes a specific
	Logarithm(const Expression& arg1, const double arg2, const double arg3, const int arg4);


	//Copy constructor
	Logarithm(const Logarithm& loga); 


	//assignment 
	Logarithm& operator=(Logarithm& loga); 


	//function set base
	Logarithm& set_base(const int x);


	//From Expression vitrual
	double operator()(double x) const override;

	operator std::string() const override;

	Expression* clone() const override;


private:

	double base(double x, double y) const;

	double c1;
	double c2;
	int b;
	Expression* E;

};