/*---------------------------------------------------------------------------
  This program demonstrates Honer's factorization code vs. alternatives.

  Polynomial: f=4.4x^4 - 3.3x^3 + 2.2x^2 - 1.1x + 6.0
---------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Timers.h"

double mult_func (double x);
double pow_func (double x);
double honer_func (double x);

#define REPEAT_NUM (100000000)

int main(int argc, char *argv[]) {   
   double result;
   
   #ifdef EN_TIME
   DECLARE_TIMER(timer);
   DECLARE_REPEAT_VAR(repeat);
   START_TIMER(timer);
   BEGIN_REPEAT_TIMING(REPEAT_NUM, repeat);
   #endif

   result = honer_func(5.0);   

   #ifdef EN_TIME
   END_REPEAT_TIMING;
   STOP_TIMER(timer);
   printf("Honer's performance, ans %f\n", result);  
   PRINT_TIMER(timer);
   PRINT_RTIMER(timer, REPEAT_NUM);
   printf("\n");
   #endif

   #ifdef EN_TIME
   RESET_TIMER(timer);
   START_TIMER(timer);
   BEGIN_REPEAT_TIMING(REPEAT_NUM, repeat);
   #endif

   result = mult_func(5.0);   

   #ifdef EN_TIME
   END_REPEAT_TIMING;
   STOP_TIMER(timer);
   printf("Mult performance, ans %f\n", result);  
   PRINT_TIMER(timer);
   PRINT_RTIMER(timer, REPEAT_NUM);
   printf("\n");
   #endif

   #ifdef EN_TIME
   RESET_TIMER(timer);
   START_TIMER(timer);
   BEGIN_REPEAT_TIMING(REPEAT_NUM, repeat);
   #endif

   result = pow_func(5.0);   

   #ifdef EN_TIME
   END_REPEAT_TIMING;
   STOP_TIMER(timer);
   printf("Pow performance, ans %f\n", result);  
   PRINT_TIMER(timer);
   PRINT_RTIMER(timer, REPEAT_NUM);
   #endif


  return 0;
}

/*----------------------------------------------------------------------------
 * This function implements traditional multiplications for a representation
 * of a polynomial
 *
 * -------------------------------------------------------------------------*/
double mult_func (double x) {
   return 4.4*x*x*x*x-3.3*x*x*x+2.2*x*x-1.1*x+6.0;
}


/*----------------------------------------------------------------------------
 * This function implements the power function for a representation
 * of a polynomial
 *
 * -------------------------------------------------------------------------*/
double pow_func (double x) {
   return 4.4*pow(x,4)-3.3*pow(x,3)+2.2*pow(x,2)-1.1*x+6.0;
}


/*----------------------------------------------------------------------------
 * This function implements honer's factorization for a representation
 * of a polynomial
 *
 * -------------------------------------------------------------------------*/
double honer_func (double x) {
   return (((4.4*x-3.3)*x+2.2)*x-1.1)*x+6.0;
}
