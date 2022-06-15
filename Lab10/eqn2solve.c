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
   /* using honer's method for best performance */
   /* Function = x^3 - 0.0001x^2 - 676.0x + 0.0676 */
   return x*(x*(x-0.0001) - 676.0) + 0.0676;
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
   /* using honer's method again... */
   /* Derivative = 3.0x^2 - 0.0002x - 676.0 */
   return x*(3.0*x - 0.0002) - 676.0;
}
