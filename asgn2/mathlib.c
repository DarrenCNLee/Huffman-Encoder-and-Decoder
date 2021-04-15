// Darren Lee
// CruzID: danalee
// CSE 13S Spring 2021
//
// This program defines the functions for the math library.
// The included functions are Abs, Exp, Sqrt, arcSin, arcCos,
// and Log.

#include <assert.h>
#include <math.h>

#define EPSILON 1e-10

// Returns the absolute value of x
// x: double of which to take the absolute value
double Abs(double x) {
    return (x < 0) ? -x : x;
}

// Returns e raised to x
// x: the power to raise x to
double Exp(double x) { // code from Piazza
    double term = 1, sum = 1;
    for (int k = 1; Abs(term) > EPSILON; k += 1) {
        term *= x / k;
        sum += term;
    }
    return sum;
}

// Returns the square root of x
// x: the value of which to take the square root
double Sqrt(double x) { // code from Piazza
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
    double k = 0.0, prev = sin(k);
    if (x > 0.99) { // use inverse method if x is close to 1
        for (double guess = 1.0; Abs(k - guess) > EPSILON; k = (k + (x - sin(k)) / cos(k))) {
            guess = k;
        }
        return k;
    }

    if (x < -0.99) { // use binary search if x is close to -1
        double m, l = -M_PI / 2, h = M_PI / 2;
        do {
            m = (l + h) / 2.0;
            if (sin(m) < x) {
                l = m;
            } else {
                h = m;
            }
        } while (Abs(l - h) > EPSILON / 2);
        return m;
    }

    while (Abs(prev - x) > EPSILON) { // use Newton's method if x is not close to -1 or 1
        k = k + (x - prev) / cos(k);
        prev = sin(k);
    }
    return k;
}

// Returns the arccos of x
// x: value of which to take the arccos
double arcCos(double x) {
    return M_PI / 2 - arcSin(x); // arcCos(x)=pi/2-arcSin(x)
}

// Returns the arctan of x
// x: value of which to take the arctan
double arcTan(double x) {
    return arcSin(x / Sqrt(x * x + 1)); // arcTan=arcSin(x / Sqrt(x^2-1))
}

// Returns the log base n of x
// x: value of which to take the natural log
double Log(double x) { // uses Newton's method
    double k = 1.0;
    assert(x > 0);
    for (double guess = 0.0; Abs(k - guess) > EPSILON; k = (k + (x - Exp(k)) / Exp(k))) {
        guess = k;
    }
    return k;
}
