/*********************************************************
 * Class Expression member functions implementation       *
 * TNG033: Lab 2                                          *
 **********************************************************/

#include "expression.h"
#include <cmath>

 // Initialize the counter of the total number of existing Expressions
std::size_t Expression::count_expressions = 0;

// Used only for debug purposes
// Return number of existing Expressions
std::size_t Expression::get_count_expressions() {
    return Expression::count_expressions;
}


std::ostream& operator<<(std::ostream& os, const Expression& E) {
    os << std::string(E);
    return os;
}


bool Expression::isRoot(double x) const {
    if ((*this)(x) <= abs(Epsilon)) {
        return true;
    }
    return false;
}

/* ************************* */