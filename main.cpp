#include <iostream>
#include <gtest/gtest.h>
#include "Polynomial.h"

// Test Case 1 (Sum)

TEST(Sum, Test1) {
    Polynomial p1;
    Polynomial p2;
    p1.setCoefficients({11, 5, 6, 14, 6, -4, 11, 5, 3});
    p2.setCoefficients({-9, -1, 2, 6, 6, 0, -13, -8, -3});
    Polynomial sum = p1 + p2;
    Polynomial expected_sum;
    expected_sum.setCoefficients({2, 4, 8, 20, 12, -4, -2, -3, 0});
    EXPECT_EQ(expected_sum, sum);
}
// Test Case 2 (Sum)
TEST(Sum, Test2) {
    Polynomial p1;
    Polynomial p2;
    p1.setCoefficients({1, -13, -8, 2, -8});
    p2.setCoefficients({2, -9, 1, -1, -13});
    Polynomial sum = p1 + p2;
    Polynomial expected_sum;
    expected_sum.setCoefficients({3, -22, -7, 1, -21});
    EXPECT_EQ(expected_sum, sum);
}

// Test Case 3 (Sum)
TEST(Sum, Test3) {
    Polynomial p1;
    Polynomial p2;
    p1.setCoefficients({14, -2, 7});
    p2.setCoefficients({-14, 7, -12});
    Polynomial sum = p1 + p2;
    Polynomial expected_sum;
    expected_sum.setCoefficients({0, 5, -5});
    EXPECT_EQ(expected_sum, sum);
}

// Test Case 4 (Sum)
TEST(Sum, Test4) {
    Polynomial p1;
    Polynomial p2;
    p1.setCoefficients({13, 5, 6});
    p2.setCoefficients({3, -12, 11});
    Polynomial sum = p1 + p2;
    Polynomial expected_sum;
    expected_sum.setCoefficients({16, -7, 17});
    EXPECT_EQ(expected_sum, sum);
}

// Test Case 5 (Sum)
TEST(Sum, Test5) {
    Polynomial p1;
    Polynomial p2;
    p1.setCoefficients({-1, -2, 8, 15, -2, -6, 14, 12, 12, 1});
    p2.setCoefficients({15, 0, -7, 11, -2, 14, 8, 7, -13, -3});
    Polynomial sum = p1 + p2;
    Polynomial expected_sum;
    expected_sum.setCoefficients({14, -2, 1, 26, -4, 8, 22, 19, -1, -2});
    EXPECT_EQ(expected_sum, sum);
}

// Test Case 6 (Sum)
TEST(Sum, Test6) {
    Polynomial p1;
    Polynomial p2;
    p1.setCoefficients({-4, 14, -13, -11, 12, 9, -7, -11, -13, -6, 0, 5});
    p2.setCoefficients({-8, -12, -12, 0, -10, -13, -1, 1, 4, 3, -1, 4});
    Polynomial sum = p1 + p2;
    Polynomial expected_sum;
    expected_sum.setCoefficients({-12, 2, -25, -11, 2, -4, -8, -10, -9, -3, -1, 9});
    EXPECT_EQ(expected_sum, sum);
}

// Test Case 7 (Sum)
TEST(Sum, Test7) {
    Polynomial p1;
    Polynomial p2;
    p1.setCoefficients({-14, 9, 3});
    p2.setCoefficients({5, -3, 13});
    Polynomial sum = p1 + p2;
    Polynomial expected_sum;
    expected_sum.setCoefficients({-9, 6, 16});
    EXPECT_EQ(expected_sum, sum);
}

// Test Case 8 (Sum)
TEST(Sum, Test8) {
    Polynomial p1;
    Polynomial p2;
    p1.setCoefficients({-4, 13, -9, 0, 5, 5, -1, 11, 4, 2, -2, 1});
    p2.setCoefficients({9, 12, 9, -10, 3, -11, -14, -13, -9, 5, -14, 0});
    Polynomial sum = p1 + p2;
    Polynomial expected_sum;
    expected_sum.setCoefficients({5, 25, 0, -10, 8, -6, -15, -2, -5, 7, -16, 1});
    EXPECT_EQ(expected_sum, sum);
}

// Test Case 9 (Sum)
TEST(Sum, Test9) {
    Polynomial p1;
    Polynomial p2;
    p1.setCoefficients({-4});
    p2.setCoefficients({-5});
    Polynomial sum = p1 + p2;
    Polynomial expected_sum;
    expected_sum.setCoefficients({-9});
    EXPECT_EQ(expected_sum, sum);
}

// Test Case 10 (Sum)
TEST(Sum, Test10) {
    Polynomial p1;
    Polynomial p2;
    p1.setCoefficients({-3, 4, -5, -4, 8, 6});
    p2.setCoefficients({-13, -2, -11, -2, -8, 7, -7});
    Polynomial sum = p1 + p2;
    Polynomial expected_sum;
    expected_sum.setCoefficients({-16, 2, -16, -6, 0, 13, -7});
    EXPECT_EQ(expected_sum, sum);
}
TEST(PolynomialOperations, Addition10) {
    Polynomial p1({3, 0, 7, 5});
    Polynomial p2({-3, 2, -5, 1});
    Polynomial sum = p1 + p2;
    Polynomial expected_sum({0, 2, 2, 6});
    EXPECT_EQ(expected_sum, sum);
}

// Test Case 11 (Addition)
TEST(PolynomialOperations, Addition11) {
    Polynomial p1({4, -3, 2});
    Polynomial p2({2, 5, -1});
    Polynomial sum = p1 + p2;
    Polynomial expected_sum({6, 2, 1});
    EXPECT_EQ(expected_sum, sum);
}

// Test Case 12 (Addition)
TEST(PolynomialOperations, Addition12) {
    Polynomial p1({7, 3, -4});
    Polynomial p2({-7, 1, 4});
    Polynomial sum = p1 + p2;
    Polynomial expected_sum({0, 4, 0});
    EXPECT_EQ(expected_sum, sum);
}

// Test Case 13 (Addition)
TEST(PolynomialOperations, Addition13) {
    Polynomial p1({5, 8, 1});
    Polynomial p2({-5, -8, -1});
    Polynomial sum = p1 + p2;
    Polynomial expected_sum({0, 0, 0});
    EXPECT_EQ(expected_sum, sum);
}

// Test Case 14 (Addition)
TEST(PolynomialOperations, Addition14) {
    Polynomial p1({1, 4, 7});
    Polynomial p2({-1, -4, -7});
    Polynomial sum = p1 + p2;
    Polynomial expected_sum({0, 0, 0});
    EXPECT_EQ(expected_sum, sum);
}

// Test Case 15 (Addition)
TEST(PolynomialOperations, Addition15) {
    Polynomial p1({9, -3, 5});
    Polynomial p2({-9, 3, -5});
    Polynomial sum = p1 + p2;
    Polynomial expected_sum({0, 0, 0});
    EXPECT_EQ(expected_sum, sum);
}

// Test Case 16 (Addition)
TEST(PolynomialOperations, Addition16) {
    Polynomial p1({3, 7, 1});
    Polynomial p2({4, 2, -1});
    Polynomial sum = p1 + p2;
    Polynomial expected_sum({7, 9, 0});
    EXPECT_EQ(expected_sum, sum);
}

// Test Case 17 (Addition)
TEST(PolynomialOperations, Addition17) {
    Polynomial p1({0, 3, -4, 5});
    Polynomial p2({0, -3, 4, -5});
    Polynomial sum = p1 + p2;
    Polynomial expected_sum({0, 0, 0, 0});
    EXPECT_EQ(expected_sum, sum);
}

// Test Case 18 (Addition)
TEST(PolynomialOperations, Addition18) {
    Polynomial p1({5, -2, 3});
    Polynomial p2({-5, 2, -3});
    Polynomial sum = p1 + p2;
    Polynomial expected_sum({0, 0, 0});
    EXPECT_EQ(expected_sum, sum);
}

// Test Case 19 (Addition)
TEST(PolynomialOperations, Addition19) {
    Polynomial p1({2, 4, 6, 8});
    Polynomial p2({-2, -4, -6, -8});
    Polynomial sum = p1 + p2;
    Polynomial expected_sum({0, 0, 0, 0});
    EXPECT_EQ(expected_sum, sum);
}

// Test Case 20 (Addition)
TEST(PolynomialOperations, Addition20) {
    Polynomial p1({10, -5, 8});
    Polynomial p2({-10, 5, -8});
    Polynomial sum = p1 + p2;
    Polynomial expected_sum({0, 0, 0});
    EXPECT_EQ(expected_sum, sum);
}

// Test Case 21 (Addition)
TEST(PolynomialOperations, Addition21) {
    Polynomial p1({1, -1, 1});
    Polynomial p2({-1, 1, -1});
    Polynomial sum = p1 + p2;
    Polynomial expected_sum({0, 0, 0});
    EXPECT_EQ(expected_sum, sum);
}

// Test Case 22 (Addition)
TEST(PolynomialOperations, Addition22) {
    Polynomial p1({3, 6, 9});
    Polynomial p2({-3, -6, -9});
    Polynomial sum = p1 + p2;
    Polynomial expected_sum({0, 0, 0});
    EXPECT_EQ(expected_sum, sum);
}

// ... [Other provided test cases up to Test24]

TEST(Sum, Test24) {
    Polynomial p1;
    Polynomial p2;
    p1.setCoefficients({12, 2, 8, 4, 2, 2, -2, 3, -6, -11, 14, 13});
    p2.setCoefficients({-12, -14, 11, -13, 11, -8, 1, -12, -5, 10, -2, 1});
    Polynomial sum = p1 + p2;
    Polynomial expected_sum;
    expected_sum.setCoefficients({0, -12, 19, -9, 13, -6, -1, -9, -11, -1, 12, 14});
    EXPECT_EQ(expected_sum, sum);
}

// Additional test cases for other operations

// Test Addition
TEST(PolynomialOperations, Addition) {
    Polynomial p1({1, -2, 3}); // Represents 1 - 2x + 3x^2
    Polynomial p2({-1, 4}); // Represents -1 + 4x
    Polynomial sum = p1 + p2;
    Polynomial expected_sum({0, 2, 3});
    EXPECT_EQ(expected_sum, sum);
}

// Test Subtraction
TEST(PolynomialOperations, Subtraction) {
    Polynomial p1({1, -2, 3}); // Represents 1 - 2x + 3x^2
    Polynomial p2({-1, 4}); // Represents -1 + 4x
    Polynomial difference = p1 - p2;
    Polynomial expected_difference({2, -6, 3});
    EXPECT_EQ(expected_difference, difference);
}
TEST(PolynomialOperations, Subtraction6) {
    Polynomial p1({5, -3, 7, -2, 8, 9, -4});
    Polynomial p2({-2, 4, -6, 3, -5, 10, -7});
    Polynomial difference = p1 - p2;
    Polynomial expected_difference({7, -7, 13, -5, 13, -1, 3});
    EXPECT_EQ(expected_difference, difference);
}

TEST(PolynomialOperations, Subtraction7) {
    Polynomial p1({11, -5, 6, -4, 15, -7, 2, 3});
    Polynomial p2({1, 3, -2, 8, 5, -9, 7, -6});
    Polynomial difference = p1 - p2;
    Polynomial expected_difference({10, -8, 8, -12, 10, 2, -5, 9});
    EXPECT_EQ(expected_difference, difference);
}

TEST(PolynomialOperations, Subtraction8) {
    Polynomial p1({-3, 5, -8, 4, -11, 2, -6, 9, -7});
    Polynomial p2({4, -9, 3, -5, 8, -2, 7, -10, 6});
    Polynomial difference = p1 - p2;
    Polynomial expected_difference({-7, 14, -11, 9, -19, 4, -13, 19, -13});
    EXPECT_EQ(expected_difference, difference);
}

TEST(PolynomialOperations, Subtraction9) {
    Polynomial p1({8, -6, 5, -3, 2, -1, 7, -5, 3});
    Polynomial p2({-7, 3, -2, 5, -4, 6, -8, 4, -1});
    Polynomial difference = p1 - p2;
    Polynomial expected_difference({15, -9, 7, -8, 6, -7, 15, -9, 4});
    EXPECT_EQ(expected_difference, difference);
}

TEST(PolynomialOperations, Subtraction10) {
    Polynomial p1({-5, 7, -3, 6, -8, 4, -1, 9});
    Polynomial p2({9, -8, 7, -4, 5, -6, 3, -7});
    Polynomial difference = p1 - p2;
    Polynomial expected_difference({-14, 15, -10, 10, -13, 10, -4, 16});
    EXPECT_EQ(expected_difference, difference);
}

// Test Multiplication
TEST(PolynomialOperations, Multiplication) {
    Polynomial p1({1, -2, 3}); // Represents 1 - 2x + 3x^2
    Polynomial p2({-1, 4}); // Represents -1 + 4x
    Polynomial product = p1 * p2;
    Polynomial expected_product({-1, 6, -5, 12});
    EXPECT_EQ(expected_product, product);
}
TEST(PolynomialOperations, Multiplication1) {
    Polynomial p1({1, -2, 3}); // Represents 1 - 2x + 3x^2
    Polynomial p2({-1, 4}); // Represents -1 + 4x
    Polynomial product = p1 * p2;
    Polynomial expected_product({-1, 6, -5, 12});
    EXPECT_EQ(expected_product, product);
}

TEST(PolynomialOperations, Multiplication2) {
    Polynomial p1({2, 0, 1}); // Represents 2 + x^2
    Polynomial p2({1, 3, -2}); // Represents 1 + 3x - 2x^2
    Polynomial product = p1 * p2;
    Polynomial expected_product({2, 6, 1, 3, -2});
    EXPECT_EQ(expected_product, product);
}

TEST(PolynomialOperations, Multiplication3) {
    Polynomial p1({-1, 2, -3}); // Represents -1 + 2x - 3x^2
    Polynomial p2({3, -1}); // Represents 3 - x
    Polynomial product = p1 * p2;
    Polynomial expected_product({-3, 5, -7, 3});
    EXPECT_EQ(expected_product, product);
}

TEST(PolynomialOperations, Multiplication4) {
    Polynomial p1({0, 1, 2, 3}); // Represents x + 2x^2 + 3x^3
    Polynomial p2({-3, 0, 1}); // Represents -3 + x^2
    Polynomial product = p1 * p2;
    Polynomial expected_product({0, -3, -6, -8, 2, 3, 3});
    EXPECT_EQ(expected_product, product);
}

TEST(PolynomialOperations, Multiplication5) {
    Polynomial p1({2, -1, 1}); // Represents 2 - x + x^2
    Polynomial p2({1, -1, 1}); // Represents 1 - x + x^2
    Polynomial product = p1 * p2;
    Polynomial expected_product({2, -3, 4, -1, 1});
    EXPECT_EQ(expected_product, product);
}

TEST(PolynomialOperations, Multiplication6) {
    Polynomial p1({1, 2, 3, 4}); // Represents 1 + 2x + 3x^2 + 4x^3
    Polynomial p2({4, -1, -2}); // Represents 4 - x - 2x^2
    Polynomial product = p1 * p2;
    Polynomial expected_product({4, 7, 6, -5, -2, -8, -8});
    EXPECT_EQ(expected_product, product);
}

TEST(PolynomialOperations, Multiplication7) {
    Polynomial p1({-2, 5}); // Represents -2 + 5x
    Polynomial p2({3, 4, 1}); // Represents 3 + 4x + x^2
    Polynomial product = p1 * p2;
    Polynomial expected_product({-6, 7, 18, 5});
    EXPECT_EQ(expected_product, product);
}

TEST(PolynomialOperations, Multiplication8) {
    Polynomial p1({1, 1, 1}); // Represents 1 + x + x^2
    Polynomial p2({1, -1, 1, -1}); // Represents 1 - x + x^2 - x^3
    Polynomial product = p1 * p2;
    Polynomial expected_product({1, 0, 1, -1, 0, -1});
    EXPECT_EQ(expected_product, product);
}

TEST(PolynomialOperations, Multiplication9) {
    Polynomial p1({0, 2}); // Represents 2x
    Polynomial p2({3, 0, 1}); // Represents 3 + x^2
    Polynomial product = p1 * p2;
    Polynomial expected_product({0, 6, 0, 2});
    EXPECT_EQ(expected_product, product);
}

TEST(PolynomialOperations, Multiplication10) {
    Polynomial p1({2, -3, 1}); // Represents 2 - 3x + x^2
    Polynomial p2({1, 2, 1}); // Represents 1 + 2x + x^2
    Polynomial product = p1 * p2;
    Polynomial expected_product({2, 1, -4, -1, 1});
    EXPECT_EQ(expected_product, product);
}

// Test Evaluation
TEST(PolynomialOperations, Evaluation) {
    Polynomial p1({1, -2, 3}); // Represents 1 - 2x + 3x^2
    double x = 2.5;
    double evaluation_result = p1.evaluate(x);
    double expected_result = 1 - 2*2.5 + 3*2.5*2.5;
    EXPECT_DOUBLE_EQ(expected_result, evaluation_result);
}
TEST(PolynomialOperations, Evaluation1) {
    Polynomial p1({1, -2, 3}); // Represents 1 - 2x + 3x^2
    double x = 2.5;
    double evaluation_result = p1.evaluate(x);
    double expected_result = 1 - 2*2.5 + 3*2.5*2.5;
    EXPECT_DOUBLE_EQ(expected_result, evaluation_result);
}

TEST(PolynomialOperations, Evaluation2) {
    Polynomial p1({0, 4, -1, 2}); // Represents 4x - x^2 + 2x^3
    double x = -1.0;
    double evaluation_result = p1.evaluate(x);
    double expected_result = 0*pow(-1, 0) + 4*pow(-1, 1) + -1*pow(-1, 2) + 2*pow(-1, 3);
    EXPECT_DOUBLE_EQ(expected_result, evaluation_result);
}

TEST(PolynomialOperations, Evaluation3) {
    Polynomial p1({-3, 2, 1}); // Represents -3 + 2x + x^2
    double x = 0.5;
    double evaluation_result = p1.evaluate(x);
    double expected_result = -3 + 2*0.5 + 1*0.5*0.5;
    EXPECT_DOUBLE_EQ(expected_result, evaluation_result);
}

TEST(PolynomialOperations, Evaluation4) {
    Polynomial p1({1, 1, 1, 1}); // Represents 1 + x + x^2 + x^3
    double x = 1.0;
    double evaluation_result = p1.evaluate(x);
    double expected_result = 1 + 1*1 + 1*1*1 + 1*1*1*1;
    EXPECT_DOUBLE_EQ(expected_result, evaluation_result);
}

TEST(PolynomialOperations, Evaluation5) {
    Polynomial p1({2, 0, -3}); // Represents 2 - 3x^2
    double x = -2.0;
    double evaluation_result = p1.evaluate(x);
    double expected_result = 2 - 3*(-2)*(-2);
    EXPECT_DOUBLE_EQ(expected_result, evaluation_result);
}

TEST(PolynomialOperations, Evaluation6) {
    Polynomial p1({3, -2, -1}); // Represents 3 - 2x - x^2
    double x = 3.0;
    double evaluation_result = p1.evaluate(x);
    double expected_result = 3 - 2*3 - 1*3*3;
    EXPECT_DOUBLE_EQ(expected_result, evaluation_result);
}

TEST(PolynomialOperations, Evaluation7) {
    Polynomial p1({-1, 0, 0, 4}); // Represents -1 + 4x^3
    double x = 1.5;
    double evaluation_result = p1.evaluate(x);
    double expected_result = -1 + 4*pow(1.5, 3);
    EXPECT_DOUBLE_EQ(expected_result, evaluation_result);
}

TEST(PolynomialOperations, Evaluation8) {
    Polynomial p1({5, 0, -6}); // Represents 5 - 6x^2
    double x = 2.0;
    double evaluation_result = p1.evaluate(x);
    double expected_result = 5 - 6*2*2;
    EXPECT_DOUBLE_EQ(expected_result, evaluation_result);
}

// Test Derivative
TEST(PolynomialOperations, Derivative) {
    Polynomial p1({1, -2, 3}); // Represents 1 - 2x + 3x^2
    Polynomial derivative = p1.derivative();
    Polynomial expected_derivative({-2, 6});
    EXPECT_EQ(expected_derivative, derivative);
}
TEST(PolynomialOperations, Derivative1) {
    Polynomial p1({1, -2, 3}); // Represents 1 - 2x + 3x^2
    Polynomial derivative = p1.derivative();
    Polynomial expected_derivative({-2, 6});
    EXPECT_EQ(expected_derivative, derivative);
}

TEST(PolynomialOperations, Derivative2) {
    Polynomial p1({4, 0, -3, 7}); // Represents 4 - 3x^2 + 7x^3
    Polynomial derivative = p1.derivative();
    Polynomial expected_derivative({0, -6, 21});
    EXPECT_EQ(expected_derivative, derivative);
}

TEST(PolynomialOperations, Derivative3) {
    Polynomial p1({0, 5, -6, 0, 4}); // Represents 5x - 6x^2 + 4x^4
    Polynomial derivative = p1.derivative();
    Polynomial expected_derivative({5, -12, 0, 16});
    EXPECT_EQ(expected_derivative, derivative);
}

TEST(PolynomialOperations, Derivative4) {
    Polynomial p1({2, -3, 0, 0, 5, -1}); // Represents 2 - 3x + 5x^4 - x^5
    Polynomial derivative = p1.derivative();
    Polynomial expected_derivative({-3, 0, 0, 20, -5});
    EXPECT_EQ(expected_derivative, derivative);
}

TEST(PolynomialOperations, Derivative5) {
    Polynomial p1({-1, 4, -5}); // Represents -1 + 4x - 5x^2
    Polynomial derivative = p1.derivative();
    Polynomial expected_derivative({4, -10});
    EXPECT_EQ(expected_derivative, derivative);
}

TEST(PolynomialOperations, Derivative6) {
    Polynomial p1({6, 0, -2, 3}); // Represents 6 - 2x^2 + 3x^3
    Polynomial derivative = p1.derivative();
    Polynomial expected_derivative({0, -4, 9});
    EXPECT_EQ(expected_derivative, derivative);
}

TEST(PolynomialOperations, Derivative7) {
    Polynomial p1({0, 0, 1, -1, 0, 3}); // Represents x^2 - x^3 + 3x^5
    Polynomial derivative = p1.derivative();
    Polynomial expected_derivative({0, 2, -3, 0, 15});
    EXPECT_EQ(expected_derivative, derivative);
}

TEST(PolynomialOperations, Derivative8) {
    Polynomial p1({7, -2, 0, 4}); // Represents 7 - 2x + 4x^3
    Polynomial derivative = p1.derivative();
    Polynomial expected_derivative({-2, 0, 12});
    EXPECT_EQ(expected_derivative, derivative);
}

TEST(PolynomialOperations, Derivative9) {
    Polynomial p1({5, -3, 2, 0, 0, 6}); // Represents 5 - 3x + 2x^2 + 6x^5
    Polynomial derivative = p1.derivative();
    Polynomial expected_derivative({-3, 4, 0, 0, 30});
    EXPECT_EQ(expected_derivative, derivative);
}

TEST(PolynomialOperations, Derivative10) {
    Polynomial p1({0, 2, 0, 0, 1}); // Represents 2x + x^4
    Polynomial derivative = p1.derivative();
    Polynomial expected_derivative({2, 0, 0, 4});
    EXPECT_EQ(expected_derivative, derivative);
}

// Test Integral
TEST(PolynomialOperations, Integral) {
    Polynomial p1({1, -2, 3}); // Represents 1 - 2x + 3x^2
    Polynomial integral = p1.integral();
    Polynomial expected_integral({0, 1, -1, 1});
    EXPECT_EQ(expected_integral, integral);
}

// Test Definite Integral
TEST(PolynomialOperations, DefiniteIntegral) {
    Polynomial p1({1, -2, 3}); // Represents 1 - 2x + 3x^2
    double x1 = 1.0, x2 = 3.0;
    double definite_integral = p1.integral(x1, x2);
    double expected_integral = (1.0/3.0) * (pow(3, 3) - pow(1, 3)) - (1.0) * (pow(3, 2) - pow(1, 2)) + 1 * (3 - 1);
    EXPECT_DOUBLE_EQ(expected_integral, definite_integral);
}
TEST(PolynomialOperations, Integral1) {
    Polynomial p1({1, -2, 3}); // Represents 1 - 2x + 3x^2
    Polynomial integral = p1.integral();
    Polynomial expected_integral({0, 1, -1, 1});
    EXPECT_EQ(expected_integral, integral);
}

TEST(PolynomialOperations, Integral2) {
    Polynomial p1({4, 0, -3, 7}); // Represents 4 - 3x^2 + 7x^3
    Polynomial integral = p1.integral();
    Polynomial expected_integral({0, 4, 0, -1, 1.75});
    EXPECT_EQ(expected_integral, integral);
}

TEST(PolynomialOperations, Integral3) {
    Polynomial p1({0, 5, -6, 0, 4}); // Represents 5x - 6x^2 + 4x^4
    Polynomial integral = p1.integral();
    Polynomial expected_integral({0, 0, 5, -2, 0, 0.8});
    EXPECT_EQ(expected_integral, integral);
}

TEST(PolynomialOperations, Integral4) {
    Polynomial p1({2, -3, 0, 0, 5, -1}); // Represents 2 - 3x + 5x^4 - x^5
    Polynomial integral = p1.integral();
    Polynomial expected_integral({0, 2, -1.5, 0, 0, 1, -0.1667});
    EXPECT_EQ(expected_integral, integral);
}

TEST(PolynomialOperations, Integral5) {
    Polynomial p1({-1, 4, -5}); // Represents -1 + 4x - 5x^2
    Polynomial integral = p1.integral();
    Polynomial expected_integral({0, -1, 2, -1.6667});
    EXPECT_EQ(expected_integral, integral);
}

TEST(PolynomialOperations, Integral6) {
    Polynomial p1({6, 0, -2, 3}); // Represents 6 - 2x^2 + 3x^3
    Polynomial integral = p1.integral();
    Polynomial expected_integral({0, 6, 0, -0.6667, 0.75});
    EXPECT_EQ(expected_integral, integral);
}

TEST(PolynomialOperations, Integral7) {
    Polynomial p1({0, 0, 1, -1, 0, 3}); // Represents x^2 - x^3 + 3x^5
    Polynomial integral = p1.integral();
    Polynomial expected_integral({0, 0, 0, 0.3333, -0.25, 0, 0.5});
    EXPECT_EQ(expected_integral, integral);
}

TEST(PolynomialOperations, Integral8) {
    Polynomial p1({7, -2, 0, 4}); // Represents 7 - 2x + 4x^3
    Polynomial integral = p1.integral();
    Polynomial expected_integral({0, 7, -1, 0, 1});
    EXPECT_EQ(expected_integral, integral);
}

TEST(PolynomialOperations, Integral9) {
    Polynomial p1({5, -3, 2, 0, 0, 6}); // Represents 5 - 3x + 2x^2 + 6x^5
    Polynomial integral = p1.integral();
    Polynomial expected_integral({0, 5, -1.5, 0.6667, 0, 0, 1});
    EXPECT_EQ(expected_integral, integral);
}

TEST(PolynomialOperations, Integral10) {
    Polynomial p1({0, 2, 0, 0, 1}); // Represents 2x + x^4
    Polynomial integral = p1.integral();
    Polynomial expected_integral({0, 0, 1, 0, 0, 0.2});
    EXPECT_EQ(expected_integral, integral);
}


// Test Composition
TEST(PolynomialOperations, Composition) {
    Polynomial p1({1, -2, 3}); // Represents 1 - 2x + 3x^2
    Polynomial p2({-1, 4}); // Represents -1 + 4x
    Polynomial composition = p1.compose(p2);
    Polynomial expected_composition({1, -6, 17, -24, 48});
    EXPECT_EQ(expected_composition, composition);
}

TEST(PolynomialOperations, Composition1) {
    Polynomial p1({1, -2, 3}); // Represents 1 - 2x + 3x^2
    Polynomial p2({-1, 4}); // Represents -1 + 4x
    Polynomial composition = p1.compose(p2);
    Polynomial expected_composition({1, -6, 17, -24, 48});
    EXPECT_EQ(expected_composition, composition);
}

TEST(PolynomialOperations, Composition2) {
    Polynomial p1({2, 0, 1}); // Represents 2 + x^2
    Polynomial p2({3, -2}); // Represents 3 - 2x
    Polynomial composition = p1.compose(p2);
    Polynomial expected_composition({2, 0, 1});
    EXPECT_EQ(expected_composition, composition);
}

TEST(PolynomialOperations, Composition3) {
    Polynomial p1({-1, 4, -5}); // Represents -1 + 4x - 5x^2
    Polynomial p2({2, 1}); // Represents 2 + x
    Polynomial composition = p1.compose(p2);
    Polynomial expected_composition({-1, 12, -15});
    EXPECT_EQ(expected_composition, composition);
}

TEST(PolynomialOperations, Composition4) {
    Polynomial p1({3, -2, 0, 1}); // Represents 3 - 2x + x^3
    Polynomial p2({1, 1}); // Represents 1 + x
    Polynomial composition = p1.compose(p2);
    Polynomial expected_composition({3, -2, 0, 1});
    EXPECT_EQ(expected_composition, composition);
}

TEST(PolynomialOperations, Composition5) {
    Polynomial p1({1, 1, 1}); // Represents 1 + x + x^2
    Polynomial p2({-1, -1}); // Represents -1 - x
    Polynomial composition = p1.compose(p2);
    Polynomial expected_composition({1, -2, 2});
    EXPECT_EQ(expected_composition, composition);
}

TEST(PolynomialOperations, Composition6) {
    Polynomial p1({0, -1, 2}); // Represents -x + 2x^2
    Polynomial p2({2, -1}); // Represents 2 - x
    Polynomial composition = p1.compose(p2);
    Polynomial expected_composition({0, -2, 5});
    EXPECT_EQ(expected_composition, composition);
}

TEST(PolynomialOperations, Composition7) {
    Polynomial p1({4, 0, 3}); // Represents 4 + 3x^2
    Polynomial p2({0, 2}); // Represents 2x
    Polynomial composition = p1.compose(p2);
    Polynomial expected_composition({4, 0, 12});
    EXPECT_EQ(expected_composition, composition);
}

TEST(PolynomialOperations, Composition8) {
    Polynomial p1({5, -3, 2}); // Represents 5 - 3x + 2x^2
    Polynomial p2({1, 1}); // Represents 1 + x
    Polynomial composition = p1.compose(p2);
    Polynomial expected_composition({5, -1, 4});
    EXPECT_EQ(expected_composition, composition);
}

TEST(PolynomialOperations, Composition9) {
    Polynomial p1({2, 3, 4}); // Represents 2 + 3x + 4x^2
    Polynomial p2({3, 2}); // Represents 3 + 2x
    Polynomial composition = p1.compose(p2);
    Polynomial expected_composition({2, 15, 16});
    EXPECT_EQ(expected_composition, composition);
}

TEST(PolynomialOperations, Composition10) {
    Polynomial p1({-1, 0, 1}); // Represents -1 + x^2
    Polynomial p2({1, 2}); // Represents 1 + 2x
    Polynomial composition = p1.compose(p2);
    Polynomial expected_composition({-1, 0, 1});
    EXPECT_EQ(expected_composition, composition);
}

// Test Newton's Method for Root Finding
TEST(PolynomialOperations, RootFinding) {
    Polynomial p1({-6, 11, -6, 1}); // Represents x^3 - 6x^2 + 11x - 6 (roots at x=1,2,3)
    double initialGuess = 0.0;
    double root = p1.getRoot(initialGuess);
    EXPECT_NEAR(1.0, root, 1e-6);
}
TEST(PolynomialOperations, RootFinding1) {
    Polynomial p1({-6, 11, -6, 1}); // Represents x^3 - 6x^2 + 11x - 6 (roots at x=1,2,3)
    double initialGuess = 0.0;
    double root = p1.getRoot(initialGuess);
    EXPECT_NEAR(1.0, root, 1e-6);
}

TEST(PolynomialOperations, RootFinding2) {
    Polynomial p1({2, -4, -3, 1}); // Represents x^3 - 3x^2 - 4x + 2 (roots at x=-1, 1, 2)
    double initialGuess = 2.5;
    double root = p1.getRoot(initialGuess);
    EXPECT_NEAR(2.0, root, 1e-6);
}

TEST(PolynomialOperations, RootFinding3) {
    Polynomial p1({1, -2, 1}); // Represents x^2 - 2x + 1 (root at x=1)
    double initialGuess = 0.0;
    double root = p1.getRoot(initialGuess);
    EXPECT_NEAR(1.0, root, 1e-6);
}

TEST(PolynomialOperations, RootFinding4) {
    Polynomial p1({-3, 6, -3, 1}); // Represents x^3 - 3x^2 + 6x - 3 (root at x=1)
    double initialGuess = 2.0;
    double root = p1.getRoot(initialGuess);
    EXPECT_NEAR(1.0, root, 1e-6);
}

TEST(PolynomialOperations, RootFinding5) {
    Polynomial p1({6, -5, -4, 1}); // Represents x^3 - 4x^2 - 5x + 6 (roots at x=-2, 1, 3)
    double initialGuess = 3.0;
    double root = p1.getRoot(initialGuess);
    EXPECT_NEAR(3.0, root, 1e-6);
}

TEST(PolynomialOperations, RootFinding6) {
    Polynomial p1({2, -3, 1}); // Represents x^2 - 3x + 2 (roots at x=1, 2)
    double initialGuess = 1.5;
    double root = p1.getRoot(initialGuess);
    EXPECT_NEAR(2.0, root, 1e-6);
}

TEST(PolynomialOperations, RootFinding7) {
    Polynomial p1({1, -3, 2}); // Represents x^2 - 3x + 2 (roots at x=1, 2)
    double initialGuess = 1.0;
    double root = p1.getRoot(initialGuess);
    EXPECT_NEAR(1.0, root, 1e-6);
}

TEST(PolynomialOperations, RootFinding8) {
    Polynomial p1({8, -6, 1}); // Represents x^2 - 6x + 8 (roots at x=2, 4)
    double initialGuess = 4.5;
    double root = p1.getRoot(initialGuess);
    EXPECT_NEAR(4.0, root, 1e-6);
}

TEST(PolynomialOperations, RootFinding9) {
    Polynomial p1({5, -10, 1}); // Represents x^2 - 10x + 5 (roots at x=1, 5)
    double initialGuess = 0.5;
    double root = p1.getRoot(initialGuess);
    EXPECT_NEAR(1.0, root, 1e-6);
}

TEST(PolynomialOperations, RootFinding10) {
    Polynomial p1({3, -12, 1}); // Represents x^2 - 12x + 3 (roots at x=3, 9)
    double initialGuess = 3.5;
    double root = p1.getRoot(initialGuess);
    EXPECT_NEAR(3.0, root, 1e-6);
}
TEST(PolynomialOperations, RootFinding14) {
    Polynomial p1({-10, 25, -20, 5}); // Represents 5x^3 - 20x^2 + 25x - 10 (roots at x=1,2)
    double initialGuess = 1.5;
    double root = p1.getRoot(initialGuess);
    EXPECT_NEAR(1.0, root, 1e-6);
}

TEST(PolynomialOperations, RootFinding11) {
    Polynomial p1({0, -1, 3, -2, 1}); // Represents x^4 - 2x^3 + 3x^2 - x (roots at x=0,1,1,-3)
    double initialGuess = -1.0;
    double root = p1.getRoot(initialGuess);
    EXPECT_NEAR(0.0, root, 1e-6);
}

TEST(PolynomialOperations, RootFinding12) {
    Polynomial p1({6, -7, 3, 2}); // Represents 2x^3 + 3x^2 - 7x + 6 (roots at x=2,-1)
    double initialGuess = 2.5;
    double root = p1.getRoot(initialGuess);
    EXPECT_NEAR(2.0, root, 1e-6);
}

TEST(PolynomialOperations, RootFinding13) {
    Polynomial p1({-4, 0, 1}); // Represents x^2 - 4 (roots at x=2,-2)
    double initialGuess = 3.0;
    double root = p1.getRoot(initialGuess);
    EXPECT_NEAR(2.0, root, 1e-6);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
