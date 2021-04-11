// Darren Lee
// CruzID: danalee
// CSE 13S Spring 2021
//
// This program contains the code for the test harness
// for the math library mathlib.c. It contains
// tests for arcSin, arcCos, arcTan, and Log.

#include "mathlib.c"

#include <stdio.h>
#include <unistd.h>

#define OPTIONS "asctl"

int main(int argc, char **argv) {
    int opt = 0;
    int sin_test = 0, cos_test = 0, tan_test = 0,
        log_test = 0; // test state is 1 if the test has been run; otherwise, test state is 0
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a': // run all tests that have not been run yet if user types -a on command line
            if (!sin_test) {
                printf(" x           arcSin          Library       Difference\n");
                for (double i = -1.0; i <= 1.0; i += 0.1) {
                    printf("%7.4lf%16.8lf%16.8lf%16.10lf\n", i, arcSin(i), asin(i),
                        arcSin(i) - asin(i));
                }
                sin_test = 1; // arcSin test has been run
            }
            if (!cos_test) {
                printf(" x           arcCos          Library       Difference\n");
                for (double i = -1.0; i <= 1.0; i += 0.1) {
                    printf("%7.4lf%16.8lf%16.8lf%16.10lf\n", i, arcCos(i), acos(i),
                        arcCos(i) - acos(i));
                }
                cos_test = 1; // arcCos test has been run
            }
            if (!tan_test) {
                printf(" x           arcTan          Library       Difference\n");
                for (double i = -1.0; i <= 1.0; i += 0.1) {
                    printf("%7.4lf%16.8lf%16.8lf%16.10lf\n", i, arcTan(i), atan(i),
                        arcTan(i) - atan(i));
                }
                tan_test = 1; // arcTan test has been run
            }
            if (!log_test) {
                printf(" x           Log             Library       Difference\n");
                for (double i = 1.0; i <= 10.0; i += 0.5) {
                    printf("%7.4lf%16.8lf%16.8lf%16.10lf\n", i, Log(i), log(i), Log(i) - log(i));
                }
                log_test = 1; // Log test has been run
            }
            break;
        case 's': // run arcSin test if it has not been run yet if user types -s on command line
            if (!sin_test) {
                printf(" x           arcSin          Library       Difference\n");
                for (double i = -1.0; i <= 1.0; i += 0.1) {
                    printf("%7.4lf%16.8lf%16.8lf%16.10lf\n", i, arcSin(i), asin(i),
                        arcSin(i) - asin(i));
                }
                sin_test = 1; // arcSin test has been run
            }
            break;
        case 'c': // run arcCos test if it has not been run yet if user types -c on command line
            if (!cos_test) {
                printf(" x           arcCos          Library       Difference\n");
                for (double i = -1.0; i <= 1.0; i += 0.1) {
                    printf("%7.4lf%16.8lf%16.8lf%16.10lf\n", i, arcCos(i), acos(i),
                        arcCos(i) - acos(i));
                }
                cos_test = 1; // arcCos test has been run
            }
            break;
        case 't': // run arcTan test if it has not been run yet if user types -t on command line
            if (!tan_test) {
                printf(" x           arcTan          Library       Difference\n");
                for (double i = -1.0; i <= 1.0; i += 0.1) {
                    printf("%7.4lf%16.8lf%16.8lf%16.10lf\n", i, arcTan(i), atan(i),
                        arcTan(i) - atan(i));
                }
                tan_test = 1; // arcTan test has been run
            }
            break;
        case 'l': // run Log test if it has not been run yet if user types -l on the command line
            if (!log_test) {
                printf(" x           Log             Library       Difference\n");
                for (double i = 1.0; i <= 10.0; i += 0.5) {
                    printf("%7.4lf%16.8lf%16.8lf%16.10lf\n", i, Log(i), log(i), Log(i) - log(i));
                }
                log_test = 1; // Log test has been run
            }
            break;
        }
    }
    return 0;
}
