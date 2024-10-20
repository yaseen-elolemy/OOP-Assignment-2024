#include "Polynomial.h"

// Default constructor
Polynomial::Polynomial() : coeffs(1, 0.0) {}

// Constructor with coefficients
Polynomial::Polynomial(const vector<double>& coefficients) : coeffs(coefficients) {}

// Copy constructor
Polynomial::Polynomial(const Polynomial& other) : coeffs(other.coeffs) {}

// Destructor
Polynomial::~Polynomial() {}

// Assignment operator
Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        coeffs = other.coeffs;
    }
    return *this;
}

// Addition operator
Polynomial Polynomial::operator+(const Polynomial& other) const {
    vector<double> result(max(coeffs.size(), other.coeffs.size()), 0.0);

    for (size_t i = 0; i < coeffs.size(); i++) {
        result[i] += coeffs[i];
    }
    for (size_t i = 0; i < other.coeffs.size(); i++) {
        result[i] += other.coeffs[i];
    }

    return Polynomial(result);
}

// Subtraction operator
Polynomial Polynomial::operator-(const Polynomial& other) const {
    vector<double> result(max(coeffs.size(), other.coeffs.size()), 0.0);

    for (size_t i = 0; i < coeffs.size(); i++) {
        result[i] += coeffs[i];
    }
    for (size_t i = 0; i < other.coeffs.size(); i++) {
        result[i] -= other.coeffs[i];
    }

    return Polynomial(result);
}

// Multiplication operator
Polynomial Polynomial::operator*(const Polynomial& other) const {
    vector<double> result(coeffs.size() + other.coeffs.size() - 1, 0.0);

    for (size_t i = 0; i < coeffs.size(); i++) {
        for (size_t j = 0; j < other.coeffs.size(); j++) {
            result[i + j] += coeffs[i] * other.coeffs[j];
        }
    }

    return Polynomial(result);
}

// Equality operator
bool Polynomial::operator==(const Polynomial& other) const {
    return coeffs == other.coeffs;
}

// Output operator
ostream& operator<<(ostream& out, const Polynomial& poly) {
    for (int i = poly.coeffs.size() - 1; i >= 0; i--) {
        if (poly.coeffs[i] != 0) {
            if (i != poly.coeffs.size() - 1) {
                out << (poly.coeffs[i] > 0 ? " + " : " - ");
            }
            out << abs(poly.coeffs[i]);
            if (i > 0) out << "x";
            if (i > 1) out << "^" << i;
        }
    }
    return out;
}

// Return the degree of the polynomial
int Polynomial::degree() const {
    return coeffs.size() - 1;
}

// Evaluate the polynomial at x
double Polynomial::evaluate(double x) const {
    double result = 0;
    for (int i = coeffs.size() - 1; i >= 0; i--) {
        result = result * x + coeffs[i];
    }
    return result;
}

// Polynomial composition
Polynomial Polynomial::compose(const Polynomial& q) const {
    Polynomial result;
    for (int i = degree(); i >= 0; i--) {
        result = result * q + Polynomial(vector<double>{coeffs[i]});
    }
    return result;
}

// Derivative of the polynomial
Polynomial Polynomial::derivative() const {
    if (coeffs.size() <= 1) return Polynomial(); // The derivative of a constant is 0
    vector<double> result(coeffs.size() - 1);
    for (size_t i = 1; i < coeffs.size(); i++) {
        result[i - 1] = coeffs[i] * i;
    }
    return Polynomial(result);
}

// Integration of the polynomial
Polynomial Polynomial::integral() const {
    vector<double> result(coeffs.size() + 1, 0.0);
    for (size_t i = 0; i < coeffs.size(); i++) {
        result[i + 1] = coeffs[i] / (i + 1);
    }
    return Polynomial(result);
}

// Definite integral from x1 to x2
double Polynomial::integral(double x1, double x2) const {
    Polynomial integralPoly = integral();
    return integralPoly.evaluate(x2) - integralPoly.evaluate(x1);
}

// Find the root of the polynomial using Newton's method
double Polynomial::getRoot(double guess, double tolerance, int maxIter) {
    Polynomial deriv = derivative();
    for (int i = 0; i < maxIter; i++) {
        double f_val = evaluate(guess);
        double f_prime_val = deriv.evaluate(guess);
        if (fabs(f_prime_val) < tolerance) break;
        double nextGuess = guess - f_val / f_prime_val;
        if (fabs(nextGuess - guess) < tolerance) return nextGuess;
        guess = nextGuess;
    }
    return guess;
}

// Set coefficients
void Polynomial::setCoefficients(const vector<double>& coefficients) {
    coeffs = coefficients;
}

// Get coefficient of a specific degree
double Polynomial::getCoefficient(int degree) const {
    if (degree < 0 || degree >= coeffs.size()) return 0.0;
    return coeffs[degree];
}
