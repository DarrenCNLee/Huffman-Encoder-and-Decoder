// Darren Lee
// CruzID: danalee
// CSE 13S Spring 2021
//
// This program defines the functions for the math library.
// The included functions are Abs, Exp, Sqrt, arcSin, arcCos,
// and Log.

#include "mathlib.h"

#include <assert.h>
#include <math.h>

#define EPSILON 1e-10

// Returns the absolute value of x
// x: double of which to take the absolute value
double Abs(double x) { // code provided by Professor Long on Piazza
    return (x < 0) ? -x : x;
}

// Returns e raised to x
// x: the power to raise x to
double Exp(double x) { // code provided by Professor Long on Piazza
    double term = 1, sum = 1;
    for (int k = 1; Abs(term) > EPSILON; k += 1) {
        term *= x / k;
        sum += term;
    }
    return sum;
}

// Returns the square root of x
// x: the value of which to take the square root
double Sqrt(double x) { // code provided by Professor Long on Piazza
    double y = 1.0;
    assert(x >= 0);
    for (double guess = 0.0; Abs(y - guess) > EPSILON; y = (y + x / y) / 2.0) {
        guess = y;
    }
    return y;
}

// Returns the arcsin of x
// x: the value of which to take the arcsin
double arcSin(double x) {
    double sum = 0.0, i = 1.0, j = 1.0, p = 0.0, term = x;
    if (x > 0.99 || x < -0.99) { // use Newton's method and trig identity if x is close to 1 or -1
        while (Abs(p - j) > EPSILON) {
            p = j;
            j = j - (Sqrt(1 - x * x) - cos(j)) / sin(j); // arcSin=arcCos(Sqrt(1-x^2))
        }
        if (x < -0.99) {
            return j - M_PI; // use guess - pi for values close to -1
        }
        return j;
    }
    do {
        sum += term;
        i += 2;
        term *= (i - 2) * (i - 2) * x * x / (i - 1) / i;
    } while (Abs(term) > EPSILON / 10); // use Taylor series if x is not close to -1 or 1
    return sum;
}

// Returns the arccos of x
// x: value of which to take the arccos
double arcCos(double x) { // arcCos(x)=pi/2-arcSin(x)
    return M_PI_2 - arcSin(x);
}

// Returns the arctan of x
// x: value of which to take the arctan
double arcTan(double x) { // arcTan=arcCos(1/Sqrt(x^2+1))
    return arcCos(1 / Sqrt(x * x + 1));
}

// Returns the log base n of x
// x: value of which to take the natural log
double Log(double x) { // uses Newton's method
    double k = 1.0, p = 0.0; // k is next term, p is previous term
    assert(x > 0);
    while (Abs(p - k) > EPSILON) {
        p = k;
        k = k + (x - Exp(k)) / Exp(k);
    }
    return k;
}
