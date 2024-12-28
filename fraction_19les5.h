//
// Created by Lauren Steel on 10/8/22.
// 20218337
// Assignment 2
// Oct 24 2022
//

#pragma once
#include <iostream>
using namespace std;

//Exception is thrown if user attempts to make a fraction with denominator zero
class FractionException {
public:
    FractionException(const string&);
    string& what();
private:
    string message;
};

//Fraction class
class Fraction {
public:

    //makes a fraction with numerator of zero and denominator of one
    Fraction();

    //makes a fraction with numerator of top and denominator of one
    Fraction(int top);

    //makes a fraction with numerator (top) and denominator (bottom) given
    Fraction(int top, int bottom);
    //returns numerator
    int numerator() const;
    //returns denominator
    int denominator() const;

    //updates the fraction - adds another fraction value
    Fraction& operator+=(const Fraction& right);
    //increments by one
    Fraction& operator++();//preincrement
    Fraction operator++(int unused);//postincrement

    /*makes a comparison of one fraction value to the other the result is negative if it's less than
     * right and positive if it's greater than right. If they are equal the result is zero*/
    int comparison(const Fraction& right) const;

private:
    //ensuring fraction is simplified to the lowest common denominator
    void normalize();
    //finding gcd
    int gcd(int n, int m);

    int topVal;//numerator
    int bottomVal;//denominator
};

//non-member overloaded arithmetic operators
Fraction operator+(const Fraction& left, const Fraction& right);
Fraction operator-(const Fraction& left, const Fraction& right);
Fraction operator*(const Fraction& left, const Fraction& right);
Fraction operator/(const Fraction& left, const Fraction& right);
Fraction operator-(const Fraction& value);

//non-member overloaded boolean operators
bool operator<=(const Fraction& left, const Fraction& right);
bool operator>=(const Fraction& left, const Fraction& right);
bool operator!=(const Fraction& left, const Fraction& right);
bool operator==(const Fraction& left, const Fraction& right);
bool operator<(const Fraction& left, const Fraction& right);
bool operator>(const Fraction& left, const Fraction& right);

//non-member stream operators
ostream& operator<<(ostream& out, const Fraction& value);
istream& operator>>(istream& in, Fraction& returnFraction);