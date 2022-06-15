/*---------------------------------------------------------------------------
  05/08/2017    R. Repka    Make derivative clearer
---------------------------------------------------------------------------*/
#include <math.h>

/*---------------------------------------------------------------------------
  Student framework equations to be solved to help with the root finder 
---------------------------------------------------------------------------*/
#include "rootfinding.h"

/*---------------------------------------------------------------------------
  This function implements the equation to be solved.  
  
  Where: double x - the value to evaluate
  Returns: double - the value of the function at the point
  Errors:  none
---------------------------------------------------------------------------*/
double func1(double x){
   return 0.76*x*sin((30.0/52.0)*x)*tan((10.0/47.0)*x) + 2.9*cos(x+2.5)*sin(0.39*(1.5+x));
}


/*---------------------------------------------------------------------------
  This function implements the first derivative equation, which is calculated
  via any off-line process you wish (e.g  Wolfram Alpha)
  There is NO requirement to programmatically generate the derivative.
  
  Where: double x - the value to evaluate
  Returns: double - the value of the function at the point
  Errors:  none
---------------------------------------------------------------------------*/
double func1Deriv(double x){
   double a = 10.0/47.0;
   double b = 15.0/26.0;


   return -2.9*sin(x+2.5)*sin(0.39*(1.5+x)) + 1.131*cos(x+2.5) *\
cos(0.39*(1.5+x)) + 0.76*sin(b*x)*sin(a*x)\
+ 0.438462*x*cos(b*x)*tan(a*x) + 0.161702*x*(1/(cos(a*x)*cos(a*x)));
}
