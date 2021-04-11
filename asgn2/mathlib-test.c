#include "mathlib.c"

#include <stdio.h>
#include <unistd.h>

#define OPTIONS "asctl"

int main(int argc, char **argv) {
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            for (double i = -1.0; i <= 1.0; i += 0.1) {
                printf(
                    "%7.4lf%16.8lf%16.8lf%16.10lf\n", i, arcSin(i), asin(i), arcSin(i) - asin(i));
            }
            for (double i = -1.0; i <= 1.0; i += 0.1) {
                printf(
                    "%7.4lf%16.8lf%16.8lf%16.10lf\n", i, arcCos(i), acos(i), arcCos(i) - acos(i));
            }
            for (double i = -1.0; i <= 1.0; i += 0.1) {
                printf(
                    "%7.4lf%16.8lf%16.8lf%16.10lf\n", i, arcTan(i), atan(i), arcTan(i) - atan(i));
            }
            for (double i = -1.0; i <= 1.0; i += 0.1) {
                printf("%7.4lf%16.8lf%16.8lf%16.10lf\n", i, Log(i), log(i), Log(i) - log(i));
            }
            break;
        case 's':
            for (double i = -1.0; i <= 1.0; i += 0.1) {
                printf(
                    "%7.4lf%16.8lf%16.8lf%16.10lf\n", i, arcSin(i), asin(i), arcSin(i) - asin(i));
            }
            break;
        case 'c':
            for (double i = -1.0; i <= 1.0; i += 0.1) {
                printf(
                    "%7.4lf%16.8lf%16.8lf%16.10lf\n", i, arcCos(i), acos(i), arcCos(i) - acos(i));
            }
            break;
        case 't':
            for (double i = -1.0; i <= 1.0; i += 0.1) {
                printf(
                    "%7.4lf%16.8lf%16.8lf%16.10lf\n", i, arcTan(i), atan(i), arcTan(i) - atan(i));
            }
            break;
        case 'l':
            for (double i = -1.0; i <= 1.0; i += 0.1) {
                printf("%7.4lf%16.8lf%16.8lf%16.10lf\n", i, Log(i), log(i), Log(i) - log(i));
            }
            break;
        }
    }
    return 0;
}
