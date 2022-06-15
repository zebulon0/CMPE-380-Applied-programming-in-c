/******************************************************************
 * Program to correct the data for the sensor
 * Note: Each student gets unique data, so this exact equation will
 * differ for each students solution
 * Be sure to use Honer's factorization  
 * ***************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define FROUND(x) (x>=0?(int)(x+0.5):(int)(x-0.5))

/* Runs the data through the fitting line */
int main(int argc, char *argv[])
{
    int res, real, ideal, x;
    double a, b, c, d, e;
    a = -1.24448e-11;
    b = 4.22694e-08;
    c = -6.53866e-05;
    d = 0.340801;
    e = 16.3399;

    while(scanf("%d %d", &ideal, &real) != EOF)
    {
     x = (double) real;
     /* Insert your polynomial here, be sure to round properly */
     //order 2
     res = (x*(x*(x*(a*x + b) + c) + d) + e);


     res = real - (int) FROUND(res);
     printf("%d %d\n", ideal, res);

    }
    return 0;
}
