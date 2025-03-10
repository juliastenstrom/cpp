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

    //Conversion to std::string
    //virtual so that derived classes can override the function 
    virtual operator std::string() const = 0;

    //Overloaded function call operator 
    virtual double operator()(double x) const = 0;

    //Test whether a given value x is a root of function f
    bool isRoot(double x) const;

    //friend can access private data members and is not a member of the class 
    //Expression& reference to avoid copy
    friend std::ostream& operator<<(std::ostream& os, const Expression& E);

    //Clone
    //Expression* since derived class can override and returning a ponter ensures the actual type is preserved
    virtual Expression* clone() const = 0;


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

    // total number of existing expressions -- only to help to detect bugs in the code
    static std::size_t count_expressions;
    // Your code cannot manipulate this variable
};