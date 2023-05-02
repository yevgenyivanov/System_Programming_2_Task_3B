#include "Fraction.hpp"
#include <iostream>
#include <iomanip>
/////////////////////////////////////////////////////////////////////////////////////////// constructors
Fraction::Fraction()
{
    this->_numerator = 0;
    this->_denominator = 1;
}
Fraction::Fraction(int numerator, int denominator) : _numerator(numerator), _denominator(denominator)
{
    //handle 0 denominator
    if (_denominator == 0)
    {
        throw std::invalid_argument("Denominator cannot be 0!");
    }
    if (_numerator == 0)
    { // legal 0 fraction
        this->_numerator = 0;
        this->_denominator = 1;
        return;
    }
    //both ints are negative
    if(_numerator < 0 && _denominator < 0){
        _numerator *= (-1);
        _denominator *= (-1);
        fractionReduction();
        return;
    }
    if(_denominator<0){
        //move the negative 1 multiplier to the numerator
        _numerator *= (-1);
        _denominator *= (-1);
        fractionReduction();
        return;    
    }
    fractionReduction(); // reduce fraction to minimal value
};
Fraction::Fraction(double decimalVal)
{
    this->_numerator = decimalVal * 1000;
    this->_denominator = 1000;
    fractionReduction();
}
// getters
int Fraction::getNumerator()
{
    return this->_numerator;
}
int Fraction::getDenominator()
{
    return this->_denominator;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////// helper functions

// reduce fraction using euclid's GCD algorithm
int gcd_calc(int &a, int &b)
{
    if (b == 0)
    {
        return a;
    }
    a = a % b;
    return gcd_calc(b, a);
}
void Fraction::fractionReduction()
{
    int tmp_numerator = this->_numerator;
    if (tmp_numerator < 0 ){ tmp_numerator *= (-1);}
    // std::cout << "tmp_numerator: " << tmp_numerator << std::endl;
    // std::cout << "_numerator: " << this->_numerator << std::endl;
    int tmp_denominator = this->_denominator;
    
    int gcd_res = gcd_calc(tmp_numerator, tmp_denominator);
    // std::cout << "gcd of fraction is " << gcd_res << std::endl;
    this->_numerator = this->_numerator / gcd_res;
    this->_denominator = this->_denominator / gcd_res;
}
// convert a fraction to a float
float Fraction::fractionToFloat() const
{
    float float_fraction = (float)this->_numerator / this->_denominator;
    float_fraction = (int)(float_fraction * 1000);
    float_fraction = (float)float_fraction / 1000;
    return float_fraction;
}
Fraction Fraction::decimalToFraction(double decicmalVal)
{
    int tmp = decicmalVal * 1000;
    return Fraction(tmp, 1000);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////// arithmetic operators

Fraction Fraction::operator+(const Fraction &other) const
{
    // same denominator
    if (this->_denominator == other._denominator)
    {
        return Fraction((this->_numerator + other._numerator), this->_denominator);
    }
    int new_numerator_1 = this->_numerator * other._denominator,
        new_numerator_2 = this->_denominator * other._numerator,
        new_denominator = this->_denominator * other._denominator;
    return Fraction((new_numerator_1 + new_numerator_2), new_denominator);
}
Fraction Fraction::operator-(const Fraction &other) const
{
    if (this->_denominator == other._denominator)
    {
        return Fraction((this->_numerator - other._numerator), this->_denominator);
    }
    int new_numerator_1 = this->_numerator * other._denominator, // lvalue
        new_numerator_2 = this->_denominator * other._numerator, // rvalue
        new_denominator = this->_denominator * other._denominator;
    return Fraction((new_numerator_1 - new_numerator_2), new_denominator);
}
Fraction Fraction::operator*(const Fraction &other) const { return Fraction((this->_numerator * other._numerator), (this->_denominator * other._denominator)); }
Fraction Fraction::operator/(const Fraction &other) const { return Fraction((this->_numerator * other._denominator), (this->_denominator * other._numerator)); }

// prefix
Fraction &Fraction::operator++()
{
    this->_numerator += this->_denominator;
    return *this;
}
Fraction &Fraction::operator--()
{
    this->_numerator -= this->_denominator;
    return *this;
}
// postfix (int-s are dummy flags)
Fraction Fraction::operator++(int dummy_flag)
{
    Fraction copy = *this;
    this->_numerator += this->_denominator;
    return copy;
}
Fraction Fraction::operator--(int dummy_flag)
{
    Fraction copy = *this;
    this->_numerator -= this->_denominator;
    return copy;
}

// between Fraction and float
Fraction Fraction::operator+(float decimalNum) const { return *this + Fraction(decimalNum); }
Fraction Fraction::operator-(float decimalNum) const { return *this - Fraction(decimalNum); }
Fraction Fraction::operator*(float decimalNum) const { return *this * Fraction(decimalNum); }
Fraction Fraction::operator/(float decimalNum) const { return *this / Fraction(decimalNum); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// comparison operators between Fractions
bool Fraction::operator==(const Fraction &other) const { return ((this->_numerator == other._numerator) && (this->_denominator == other._denominator)); }
bool Fraction::operator>(const Fraction &other) const
{
    float fraction_1 = this->fractionToFloat(),
          fraction_2 = other.fractionToFloat();
    return (fraction_1 > fraction_2);
}
bool Fraction::operator<(const Fraction &other) const { return (other > *this); }
bool Fraction::operator>=(const Fraction &other) const { return (*this > other || *this == other); }
bool Fraction::operator<=(const Fraction &other) const { return (*this < other || *this == other); }
///////////////////////////////////////////////////////////////////////////////////////////
// comparison operators between a Fraction and float
bool Fraction::operator==(const float decimalNum) const { return *this == Fraction(decimalNum); }
bool Fraction::operator>(const float decimalNum) const { return *this > Fraction(decimalNum); }
bool Fraction::operator<(const float decimalNum) const { return *this < Fraction(decimalNum); }
bool Fraction::operator>=(const float decimalNum) const { return (*this > decimalNum || *this == decimalNum); }
bool Fraction::operator<=(const float decimalNum) const { return (*this < decimalNum || *this == decimalNum); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////// friend funcs
// arithmetics
Fraction operator+(const float decimalNum, const Fraction &_fraction) { return Fraction(decimalNum) + _fraction; }
Fraction operator-(const float decimalNum, const Fraction &_fraction) { return Fraction(decimalNum) - _fraction; }
Fraction operator*(const float decimalNum, const Fraction &_fraction) { return Fraction(decimalNum) * _fraction; }
Fraction operator/(const float decimalNum, const Fraction &_fraction) { return Fraction(decimalNum) / _fraction; }

// comparisons
bool operator==(const float decimalNum, const Fraction &_fraction) { return _fraction == decimalNum; }
bool operator<(const float decimalNum, const Fraction &_fraction) { return _fraction > decimalNum; }
bool operator>(const float decimalNum, const Fraction &_fraction) { return _fraction < decimalNum; }
bool operator>=(const float decimalNum, const Fraction &_fraction) { return _fraction <= decimalNum; }
bool operator<=(const float decimalNum, const Fraction &_fraction) { return _fraction >= decimalNum; }


// friend IO operators for a single fraction
std::ostream &operator<<(std::ostream &output, const Fraction &_fraction)
{
    return (output << _fraction._numerator << '/' << _fraction._denominator);
}

static std::istream &checkInput(std::istream &input, int expectedInteger)
{
    // int receivedInteger;
    return input;
}

std::istream &operator>>(std::istream &input, Fraction &_fraction)
{
    int new_numerator, new_denominator;
    return input;
}