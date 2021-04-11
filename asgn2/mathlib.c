#include <assert.h>
#include <math.h>

#define EPSILON 1e-12

double Abs(double x) {
    return (x < 0) ? -x : x;
}

double Exp(double x) { // code from Piazza
    double term = 1, sum = 1;
    for (int k = 1; Abs(term) > EPSILON; k += 1) {
        term *= x / k;
        sum += term;
    }
    return sum;
}

double Sqrt(double x) { // code from Piazza
    double y = 1.0;
    assert(x >= 0);
    for (double guess = 0.0; Abs(y - guess) > EPSILON; y = (y + x / y) / 2.0) {
        guess = y;
    }
    return y;
}

double arcSin(double x) {
    double m, l = -M_PI / 2, h = M_PI / 2;
    do {
        m = (l + h) / 2.0;
        if (sin(m) < x) {
            l = m;
        } else {
            h = m;
        }
    } while (Abs(l - h) > EPSILON);
    return m;
}

double arcCos(double x) {
    return M_PI / 2 - arcSin(x);
}

double arcTan(double x) {
    return arcSin(x / Sqrt(x * x + 1));
}

double Log(double x) {
    double k = 1.0;
    assert(x > 0);
    for (double guess = 0.0; Abs(k - guess) > EPSILON; k = (k + (x - Exp(k)) / Exp(k))) {
        guess = k;
    }
    return k;
}
