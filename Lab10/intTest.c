/**************************************************************************
  intTest.c - for students
  This program demonstrates the speed advantages of integer versus floating
  point math.
 12/28/2015 - R. Repka  Initial version
 10/12/2016 - R. Repka  Switched to PRINT_RTIMER() macro
 03/25/2018 - R. Repka  Switched to timing macros 
 11/18/2019 - R. Repka  Polynomial comment error 
**************************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ClassErrors.h"
#include "rootfinding.h"
#include "Timers.h"

/****************************************************************************
  Use this to define the number of iterations in your performance measurements
  ----------- You will need to adjust this number  --------
****************************************************************************/
#define ITERATIONS   (2500000)
#define BI_LIMIT     (1000)

/* Optional verbose flag, compile with -DVERBOSE or not */
#ifdef VERBOSE
   #undef VERBOSE 
   #define VERBOSE (1)
#else 
   #define VERBOSE (0)
#endif

/****************************************************************************
  Remember to set the QN value in rootfinding.h
****************************************************************************/

/************************************************************************
   Simple code to test Qn performance vs floating point  
************************************************************************/
int main(int argc, char* argv[])
    {
    double Result;          /* The result from floating point calculation   */
    long  iResult;          /* The result from floating point calculation   */
    
    /* The bisection guesses and tolerance value                        */
    double a = -25.0;
    double b = 25.0;
    double tol= 0.000001;

    /* You many need to modify the timing code for your macro implementation! */
    #ifdef EN_TIME
    DECLARE_TIMER(timer);
    DECLARE_REPEAT_VAR(tloop)
    #endif

    /************************************************************************
     Run the Qn format test 
    ************************************************************************/
    /* You many need to modify the timing code for your macro implementation! */
    long qnumA = FLOAT_TO_FIX(a);
    long qnumB = FLOAT_TO_FIX(b);
    long qTol  = FLOAT_TO_FIX(tol);

    #ifdef EN_TIME
    START_TIMER(timer);
    BEGIN_REPEAT_TIMING(ITERATIONS,tloop)
    #endif
         iResult = ibisection(&iPoly, qnumA, qnumB, qTol, VERBOSE);
    #ifdef EN_TIME
    END_REPEAT_TIMING
    STOP_TIMER(timer);
    #endif

    if(iNAN == iResult)
        {
        fprintf(stderr, "Qn %d bisection couldn't find a root. \n", QN);
        exit(99);
        }
    else
        {
        fprintf(stderr, "Found the root %f using Qn %d integer bisection.\n",
                        FIX_TO_FLOAT(iResult ), QN);
        }
    #ifdef EN_TIME      
    PRINT_TIMER(timer);
    PRINT_RTIMER(timer, ITERATIONS);
    #endif
    printf("\n");

    /************************************************************************
     Run the floating point format test 
    ************************************************************************/
    #ifdef EN_TIME
    RESET_TIMER(timer);
    START_TIMER(timer);
    BEGIN_REPEAT_TIMING(ITERATIONS,tloop)
    #endif
        Result = bisection(&rPoly, a, b, tol, VERBOSE);
    #ifdef EN_TIME
    END_REPEAT_TIMING
    STOP_TIMER(timer);
    #endif

    if(NAN == Result)
        {
        fprintf(stderr, "Float bisection couldn't find a root. \n");
        exit(99);
        }
    else
        {
        fprintf(stderr, "Found the root %f using float bisection.\n",
                        Result);
        }

    #ifdef EN_TIME
    PRINT_TIMER(timer);
    PRINT_RTIMER(timer, ITERATIONS);
    #endif   
 
    /* Display the percentage error */
    float floatiResult = FIX_TO_FLOAT(iResult);
    float deviation = (fabs(Result - floatiResult) / Result) * 100.0;
    fprintf(stderr, "\nQn %d error= %f\n", QN, deviation);
    return 0;
    } /* End main */   
    
    

/******************************************************************************
 Purpose: Finds a root of scalar, non-linear function f using the integer 
 bisection  method. a and b make up the initial bracket to start bisecting from.
 Only implement this after you have the floating point function implemented
 
 Where: ifunc1arg f - INTEGER function whose root is to be determined
                      must take a single argument of type long and return
        long a      - initial Qn root bracket guess
        long b      - initial Qn root bracket guess
        long atol   - absolute Qn error termination tolerance,
        int verb    - verbose flag, 1 = TRUE, 0 = FALSE
        
Returns: long - the root refined to the desired tolerance or NAN
Errors:  prints a message and returns with NAN                 
******************************************************************************/
long ibisection(ifunc1arg f, long a, long b, long atol, int verb)
{
   long c; 	//midpoint
   long fc;	//value at midpoint
   int i = 0;	//loop counter
   long two  = FLOAT_TO_FIX(2.0);

   if (( abs(a-b) < atol ) || SIGN( f(a) ) == SIGN( f(b) )) {
      fprintf(stderr, "A and B do not center a root\n");
      return (iNAN);
   }

   while ( i < BI_LIMIT ) {
      c = Qn_DIVIDE( (a+b), two );
      fc = f(c);


      if ( abs(fc) <= atol ) { return (c); }

      if ( abs(Qn_DIVIDE( (a-b), two )) <= atol ) { return (c); }

      if ( verb ) {
         fprintf(stdout, "iter:%d	a:%f	b:%f	x:%f	err:%f\n",
		i, FIX_TO_FLOAT(a), FIX_TO_FLOAT(b), FIX_TO_FLOAT(c), FIX_TO_FLOAT( abs(b-c) ));
      }

      if ( SIGN( f(a) ) == SIGN( fc ) ) { a = c; }
      else { b = c; }
      
      i++;
   }

   fprintf(stderr, "Bisection could not find a root with %d iterations\n", BI_LIMIT);
   return (iNAN);
}    
    
/*---------------------------------------------------------------------------
  This function implements the real polynomial equation to be solved.  
  
  Where:   double x - the value to evaluate
  Returns: double - the value of the function at the point
  Errors:  none
---------------------------------------------------------------------------*/
double rPoly(double x){
    //x**3-.0001x**2-676X+.0676    
    return(x*(x*(x-.0001)-676.0)+.0676);
}


/*---------------------------------------------------------------------------
  This function implements the integer polynomial equation to be solved.  
  
  Where:    long x - the value to evaluate
  Returns: long - the value of the function at the point
  Errors:  none
---------------------------------------------------------------------------*/
long iPoly(long x){
    //x**3-.0001x**2-676X+.0676    
    //Following the same honer's factorization as above...
    return( MUL_FIX(x, MUL_FIX(x, x-FLOAT_TO_FIX(0.0001)) - FLOAT_TO_FIX(676.0)) + FLOAT_TO_FIX(0.0676) ); 
}
