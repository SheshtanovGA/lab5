#include <stdio.h>
#include <math.h>

const double pi = acos(-1);

double distance(double x1, double y1, double x2, double y2) {
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

double traverseClockwise(const double shape[], const int n) {
    double center[2];
    for (int i = 0; i < n; i+=2 ) {
       center[0] += shape[i];
       center[1] += shape[i+1];
    }
    center[0] /= n/2;
    center[1] /= n/2;
    double len[n/2];
    double arg[n/2];
    int order[n/2];
    for (int i = 0; i < n; i+=2 ) {
        double x = shape[i] - center[0];
        double y = shape[i+1] - center[1];
        len[i/2] = sqrt( x*x + y*y );
        arg[i/2] = acos( x / len[i/2] );
        if (y<0) arg[i/2] = 2*pi - arg[i/2];
        order[i/2] = i/2;
    }
    for (int i = 0; i < n/2; i++ ) {
        for (int j = i+1; j < n/2; j++ ) {
            if (arg[i] > arg[j]) {
                // swap args
                arg[i] = arg[i] + arg[j];
                arg[j] = arg[i] - arg[j];
                arg[i] = arg[i] - arg[j];
                // swap order
                order[i] = order[i] + order[j];
                order[j] = order[i] - order[j];
                order[i] = order[i] - order[j];
            }
        }
    }
    double result = distance(shape[order[0]*2], shape[order[0]*2 + 1], shape[order[n/2-1]*2], shape[order[n/2-1]*2+1]);
    for (int i = 0; i < n/2 - 1; i++ ) {
        result += distance(shape[order[i]*2], shape[order[i]*2 + 1], shape[order[i+1]*2], shape[order[i+1]*2 + 1]);
    }
    return result;
}

int main() {
    double test[] = { 3, 0, 3, 3, 0, 3, -3, 3, -3, 0, -3, -3, 0, -3, 3, -3 };
    const int n0 = sizeof(test)/sizeof(double);
    double rect[] = { 1, 5, 7, 1, 7, 5, 1, 1 };
    const int n1 = sizeof(rect)/sizeof(double);
    double star[] = { 3.97, 0.82, 2.26, 3.69, 5.39, 2.16, 2.03, 2.11, 5.36, 4.06 };
    const int n2 = sizeof(star)/sizeof(double);
    double enneagon[] = { 76, 67.1, -8.3, 18, 55, 93.3, 77, 33, 21.3, 99, -20, 50, -8.3, 82, 55, 6.7, 21.3, 0.76 };
    const int n3 = sizeof(enneagon)/sizeof(double);
    printf("Perimeter of the rectangle is %.2f\n", traverseClockwise(rect, n1));
    printf("Perimeter of the star is %.2f\n", traverseClockwise(star, n2));
    printf("Perimeter of the enneagon is %.2f\n", traverseClockwise(enneagon, n3));
}