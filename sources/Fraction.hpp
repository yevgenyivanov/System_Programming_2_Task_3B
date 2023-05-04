#include <iostream>

class Fraction
{
private:
    int _numerator;
    int _denominator;

public:
    Fraction(); // empty constructor will declare 0
    Fraction(int, int);
    Fraction(float);
    // getters
    int getNumerator();
    int getDenominator();

    ///////////////////////////////////////////////////////////////////////////////////////////
    // helper functions
    // fraction reduction func
    void fractionReduction();
    // fraction converters
    float fractionToFloat() const;
    Fraction decimalToFraction(double);

    /////////////////////////////////////////////////////////////////////////////////////////// arithmetics
    // arithmetic operators between Fraction objects
    Fraction operator+(const Fraction &) const;
    Fraction operator-(const Fraction &) const;
    Fraction operator*(const Fraction &) const;
    Fraction operator/(const Fraction &) const;
    // prefix
    Fraction &operator++();
    Fraction &operator--();
    // postfix (int-s are dummy flags)
    Fraction operator++(int);
    Fraction operator--(int);

    ///////////////////////////////////////////////////////////////////////////////////////////
    // arithmetic operators between Fraction and float
    Fraction operator+(float) const;
    Fraction operator-(float) const;
    Fraction operator*(float) const;
    Fraction operator/(float) const;

    /////////////////////////////////////////////////////////////////////////////////////////// comparisons
    // comparison operators between Fractions
    bool operator==(const Fraction &) const;
    bool operator>(const Fraction &) const;
    bool operator<(const Fraction &) const;
    // will use a combination of the two above fractions
    bool operator>=(const Fraction &) const;
    bool operator<=(const Fraction &) const;

    ///////////////////////////////////////////////////////////////////////////////////////////
    // comparison operators between a Fraction and float
    bool operator==(float) const;
    bool operator>(float) const;
    bool operator<(float) const;
    bool operator>=(float) const;
    bool operator<=(float) const;

    /////////////////////////////////////////////////////////////////////////////////////////// friend funcs
    // arithmetics
    friend Fraction operator+(float, const Fraction &);
    friend Fraction operator-(float, const Fraction &);
    friend Fraction operator*(float, const Fraction &);
    friend Fraction operator/(float, const Fraction &);

    // comparisons
    friend bool operator==(float, const Fraction &);
    friend bool operator>=(float, const Fraction &);
    friend bool operator<=(float, const Fraction &);
    friend bool operator<(float, const Fraction &);
    friend bool operator>(float, const Fraction &);

    /////////////////////////////////////////////////////////////////////////////////////////// IO
    // friend IO operators for a single fraction
    friend std::ostream &operator<<(std::ostream &, const Fraction &);
    friend std::istream &operator>>(std::istream &, Fraction &);
};
namespace ariel
{
};
