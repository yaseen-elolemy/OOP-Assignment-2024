#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Polynomial {
private:
    vector<double> coeffs; // Store coefficients of the polynomial

public:
    // Constructors
    Polynomial() : coeffs(vector<double>(1, 0)) {} // Default constructor
    Polynomial(const vector<double>& coefficients) : coeffs(coefficients) {
        // Remove leading zeros
        while (!coeffs.empty() && coeffs.back() == 0) {
            coeffs.pop_back();
        }
    }
    Polynomial(const Polynomial& other) : coeffs(other.coeffs) {}

    // Destructor
    ~Polynomial() {}

    // Assignment operator
    Polynomial& operator=(const Polynomial& other) {
        coeffs = other.coeffs;
        return *this;
    }

    // Arithmetic operators
    Polynomial operator+(const Polynomial& other) const {
        int maxDegree = max(degree(), other.degree());
        Polynomial result(maxDegree + 1);
        for (int i = 0; i <= maxDegree; ++i) {
            result.coeffs[i] = coeffs[i] + other.coeffs[i];
        }
        return result;
    }

    Polynomial operator-(const Polynomial& other) const {
        int maxDegree = max(degree(), other.degree());
        Polynomial result(maxDegree + 1);
        for (int i = 0; i <= maxDegree; ++i) {
            result.coeffs[i] = coeffs[i] - other.coeffs[i];
        }
        return result;
    }

    Polynomial operator*(const Polynomial& other) const {
        int resultDegree = degree() + other.degree();
        Polynomial result(resultDegree + 1);
        for (int i = 0; i <= degree(); ++i) {
            for (int j = 0; j <= other.degree(); ++j) {
                result.coeffs[i + j] += coeffs[i] * other.coeffs[j];
            }
        }
        return result;
    }

    // Equality operator
    bool operator==(const Polynomial& other) const {
        return coeffs == other.coeffs;
    }

    // Output operator
    friend ostream& operator<<(ostream& out, const Polynomial& poly) {
        bool isFirstTerm = true;
        for (int i = poly.degree(); i >= 0; --i) {
            if (poly.coeffs[i] != 0) {
                if (!isFirstTerm) {
                    if (poly.coeffs[i] > 0) {
                        out << " + ";
                    } else {
                        out << " - ";
                    }
                }
                if (abs(poly.coeffs[i]) != 1 || i == 0) {
                    out << abs(poly.coeffs[i]);
                }
                if (i > 1) {
                    out << "x^" << i;
                } else if (i == 1) {
                    out << "x";
                }
                isFirstTerm = false;
            }
        }
        if (isFirstTerm) {
            out << "0";
        }
        return out;
    }

    // Utility functions
    int degree() const {
        return coeffs.size() - 1;
    }

    double evaluate(double x) const {
        double result = 0.0;
        for (int i = degree(); i >= 0; --i) {
            result = result * x + coeffs[i];
        }
        return result;
    }

    Polynomial compose(const Polynomial& q) const {
        // Implement Horner's method for efficient composition
        Polynomial result(degree() * q.degree() + 1);
        for (int i = degree(); i >= 0; --i) {
            for (int j = q.degree(); j >= 0; --j) {
                result.coeffs[i + j] += coeffs[i] * q.coeffs[j];
            }
        }
        return result;
    }

    Polynomial derivative() const {
        if (degree() == 0) {
            return Polynomial();
        }
        Polynomial result(degree() - 1);
        for (int i = 1; i <= degree(); ++i) {
            result.coeffs[i - 1] = coeffs[i] * i;
        }
        return result;
    }

    Polynomial integral() const {
        Polynomial result(degree() + 2);
        result.coeffs[degree() + 1] = 1.0 / (degree() + 1);
        for (int i = degree(); i >= 1; --i) {
            result.coeffs[i] = coeffs[i - 1] / i;
        }
        return result;
    }

    double integral(double x1, double x2) const {
        return integral().evaluate(x2) - integral().evaluate(x1);
    }

    double getRoot(double guess = 1, double tolerance = 1e-6, int maxIter = 100) {
        // Implement Newton-Raphson method for root finding
        for (int i = 0; i < maxIter; ++i) {
            double f = evaluate(guess);
            double df = derivative().evaluate(guess);
            if (abs(df) < tolerance) {
                return guess;
            }
            guess -= f / df;
        }
        return guess; // If not converged, return the last guess
    }

    void setCoefficients(const vector<double>& coefficients) {
        coeffs = coefficients;
    }

    double getCoefficient(int degree) const {
        if (degree >= coeffs.size()) {
            return 0;
        }
        return coeffs[degree];
    }
};

#endif // POLYNOMIAL_H