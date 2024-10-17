//Chatgpt implementation

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Polynomial {
private:
    vector<double> coeffs;

public:
    Polynomial();
    Polynomial(const vector<double>& coefficients);
    Polynomial(const Polynomial& other);
    ~Polynomial();
    Polynomial& operator=(const Polynomial& other);
    Polynomial operator+(const Polynomial& other) const;
    Polynomial operator-(const Polynomial& other) const;
    Polynomial operator*(const Polynomial& other) const;
    bool operator==(const Polynomial& other) const;
    friend ostream& operator<<(ostream& out, const Polynomial& poly);
    int degree() const;
    double evaluate(double x) const;
    Polynomial compose(const Polynomial& q) const;
    Polynomial derivative() const;
    Polynomial integral() const;
    double integral(double x1, double x2) const;
    double getRoot(double guess = 1, double tolerance = 1e-6, int maxIter = 100);
    void setCoefficients(const vector<double>& coefficients);
    double getCoefficient(int degree) const;

private:
    void trim();
};

// Definitions for each function

Polynomial::Polynomial() {}

Polynomial::Polynomial(const vector<double>& coefficients) : coeffs(coefficients) {
    trim();
}

Polynomial::Polynomial(const Polynomial& other) : coeffs(other.coeffs) {}

Polynomial::~Polynomial() {}

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        coeffs = other.coeffs;
    }
    return *this;
}

Polynomial Polynomial::operator+(const Polynomial& other) const {
    vector<double> resultCoeffs(max(coeffs.size(), other.coeffs.size()), 0.0);

    for (size_t i = 0; i < coeffs.size(); ++i)
        resultCoeffs[i] += coeffs[i];

    for (size_t i = 0; i < other.coeffs.size(); ++i)
        resultCoeffs[i] += other.coeffs[i];

    return Polynomial(resultCoeffs);
}

Polynomial Polynomial::operator-(const Polynomial& other) const {
    vector<double> resultCoeffs(max(coeffs.size(), other.coeffs.size()), 0.0);

    for (size_t i = 0; i < coeffs.size(); ++i)
        resultCoeffs[i] += coeffs[i];

    for (size_t i = 0; i < other.coeffs.size(); ++i)
        resultCoeffs[i] -= other.coeffs[i];

    return Polynomial(resultCoeffs);
}

Polynomial Polynomial::operator*(const Polynomial& other) const {
    vector<double> resultCoeffs(coeffs.size() + other.coeffs.size() - 1, 0.0);

    for (size_t i = 0; i < coeffs.size(); ++i) {
        for (size_t j = 0; j < other.coeffs.size(); ++j) {
            resultCoeffs[i + j] += coeffs[i] * other.coeffs[j];
        }
    }

    return Polynomial(resultCoeffs);
}

bool Polynomial::operator==(const Polynomial& other) const {
    return coeffs == other.coeffs;
}

ostream& operator<<(ostream& out, const Polynomial& poly) {
    for (int i = poly.coeffs.size() - 1; i >= 0; --i) {
        if (poly.coeffs[i] != 0) {
            out << (poly.coeffs[i] > 0 && i < poly.coeffs.size() - 1 ? " + " : "")
                << (poly.coeffs[i] < 0 ? " - " : "")
                << abs(poly.coeffs[i])
                << (i > 0 ? "x" : "")
                << (i > 1 ? "^" + to_string(i) : "");
        }
    }
    return out;
}

int Polynomial::degree() const {
    return coeffs.size() - 1;
}

double Polynomial::evaluate(double x) const {
    double result = 0.0;
    for (int i = coeffs.size() - 1; i >= 0; --i) {
        result = result * x + coeffs[i];
    }
    return result;
}

Polynomial Polynomial::compose(const Polynomial& q) const {
    Polynomial result;
    for (int i = coeffs.size() - 1; i >= 0; --i) {
        result = (result * q) + Polynomial({coeffs[i]});
    }
    return result;
}

Polynomial Polynomial::derivative() const {
    vector<double> resultCoeffs;
    for (size_t i = 1; i < coeffs.size(); ++i) {
        resultCoeffs.push_back(coeffs[i] * i);
    }
    return Polynomial(resultCoeffs);
}

Polynomial Polynomial::integral() const {
    vector<double> resultCoeffs(coeffs.size() + 1, 0.0);
    for (size_t i = 0; i < coeffs.size(); ++i) {
        resultCoeffs[i + 1] = coeffs[i] / (i + 1);
    }
    return Polynomial(resultCoeffs);
}

double Polynomial::integral(double x1, double x2) const {
    Polynomial integralPoly = integral();
    return integralPoly.evaluate(x2) - integralPoly.evaluate(x1);
}

double Polynomial::getRoot(double guess, double tolerance, int maxIter) {
    Polynomial deriv = derivative();
    double x = guess;

    for (int i = 0; i < maxIter; ++i) {
        double fx = evaluate(x);
        double dfx = deriv.evaluate(x);
        if (abs(fx) < tolerance) break;
        if (dfx == 0) throw runtime_error("Zero derivative encountered.");
        x = x - fx / dfx;
    }
    return x;
}

void Polynomial::setCoefficients(const vector<double>& coefficients) {
    coeffs = coefficients;
    trim();
}

double Polynomial::getCoefficient(int degree) const {
    return (degree < coeffs.size()) ? coeffs[degree] : 0.0;
}

void Polynomial::trim() {
    while (!coeffs.empty() && coeffs.back() == 0) {
        coeffs.pop_back();
    }
}

#endif // POLYNOMIAL_H
