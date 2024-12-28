//
// Created by Lauren Steel on 10/8/22.
// 20218337
// Assignment 2
// Oct 24 2022
//

#include <iostream>
#include "fraction_19les5.h"
using namespace std;

//exception is thrown if user attempts to make a fraction with denominator zero
FractionException::FractionException(const string& m) : message(m) {}
string& FractionException::what() {
    return message;
}

//throw exception if denominator is zero
Fraction::Fraction(int top, int bottom) : topVal(top), bottomVal(bottom){
    if (bottomVal == 0)
        throw FractionException("denominator cannot be zero");
    normalize();
}

//fraction top is zero bottom is one
Fraction::Fraction() : topVal(0), bottomVal(1){}
//fraction top is top bottom is one
Fraction::Fraction(int top) : topVal(top), bottomVal(1){}

//fraction top is numerator bottom is denominator
int Fraction::numerator() const{
    return topVal;
}
int Fraction::denominator() const {
    return bottomVal;
}

/*simplify - ensure that the top and bottom don't have common denominators
 * and also move the sign to top if applicable*/
void Fraction::normalize() {
    int fracSign = 1;
    if (topVal < 0){
        fracSign = -1;
        topVal = -topVal;
    }
    if (bottomVal < 0){
        fracSign = -fracSign;
        bottomVal = -bottomVal;
    }
    int cd = 1;
    if (topVal > 0)
        cd = gcd(topVal,bottomVal);
    topVal =fracSign * (topVal / cd);
    bottomVal = bottomVal / cd;
}

//calculate gcd
int Fraction::gcd(int n, int m) {
    if (m <= n && n % m == 0)
        return m;
    else if (n < m)
        return gcd(m,n);
    else
        return gcd(m, n % m);
}

//updates the fraction
Fraction& Fraction::operator+=(const Fraction& right){
    topVal = topVal * right.denominator() + bottomVal * right.numerator();
    bottomVal *= right.denominator();
    normalize();
    return *this;
}

//increments by one (pre)
Fraction& Fraction::operator++(){
    topVal += bottomVal;
    return *this;
}

//increments by one (post)
Fraction Fraction::operator++(int unused){
    Fraction copy(topVal, bottomVal);
    topVal += bottomVal;
    return copy;
}

//comparison of one fraction value to the other determining which is greater
int Fraction::comparison(const Fraction& right) const{
    return topVal*right.denominator() - bottomVal*right.numerator();
}

//arithmetic operators
Fraction operator+(const Fraction& left, const Fraction& right){
    Fraction result(left.numerator()*right.denominator()+right.numerator()*left.denominator(),left.denominator()*right.denominator());
    return result;
}

Fraction operator-(const Fraction& left, const Fraction& right){
    Fraction result(left.numerator()*right.denominator()-right.numerator()*left.denominator(),left.denominator()*right.denominator());
    return result;
}

Fraction operator*(const Fraction& left, const Fraction& right){
    Fraction result(left.numerator()*right.numerator(),right.denominator()*left.denominator());
    return result;
}

Fraction operator/(const Fraction& left, const Fraction& right){
    Fraction result(left.numerator()*right.denominator(), left.denominator()*right.numerator());
    return result;
}

Fraction operator-(const Fraction& value){
    Fraction result(-value.numerator(), value.denominator());
    return result;
}

//bool operators
bool operator<(const Fraction& left, const Fraction& right){
    return left.comparison(right) < 0;
}

bool operator<=(const Fraction& left, const Fraction& right){
    return left.comparison(right) <= 0;
}

bool operator==(const Fraction& left, const Fraction& right){
    return left.comparison(right) == 0;
}

bool operator!=(const Fraction& left, const Fraction& right){
    return left.comparison(right) != 0;
}

bool operator>=(const Fraction& left, const Fraction& right){
    return left.comparison(right) >= 0;
}

bool operator>(const Fraction& left, const Fraction& right){
    return left.comparison(right) > 0;
}

ostream& operator<<(ostream& out, const Fraction& value){
    out << value.numerator() << "/" << value.denominator();
    return out;
}

//stream operators
istream& operator>>(istream& in, Fraction& returnFraction){
    int topVal, bottomVal;
    //reading numerator
    in >> topVal;
    //if not enter read the next number skipping the division sign '/'
    if (in.peek() != 10){
        char next;
        in >> next;
        if (next == '/')
            //reading denominator
            in >> bottomVal;
        else
            bottomVal = 1;
        returnFraction = Fraction(topVal, bottomVal);
    } else
        returnFraction = Fraction(topVal);
    return in;
}