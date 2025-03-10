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
    
    Polynomial();

    Polynomial(const double x); //convert a const to a polynomial

    Polynomial(const std::vector<double> somecoef); //vector with doubles for a polynomial

    Polynomial(const Polynomial& poly); //Copy constructor

    //~Polynomial() = default;

    Polynomial& operator=(Polynomial poly); //assignment operator

    //varför har man refrence
    Polynomial& operator+=(Polynomial poly);

    //varför har man friend?
    friend Polynomial operator+(const Polynomial& poly1, const Polynomial& poly2);

    double operator()(double x) const override;

    double operator[](const int x) const;

    double& operator[](const int x);

    operator std::string() const override;

    Expression* clone() const override;

    std::vector<double>coefs() const;

private:
    std::vector<double> coef;

};
