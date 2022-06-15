/**************************************************************************
  quadTest.c - for the student
  This program demonstrates C99's complex support.
 
 12/22/2018 - R. Repka  Initial version
 03/27/2019 - R. Repka  b**2 typo
**************************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>
#include </usr/include/complex.h>
#include "ClassErrors.h"
#include "rootfinding.h"
#include "Timers.h"

#define NTERMS (3)


/************************************************************************
   Simple code to test complex support  
************************************************************************/
int main(int argc, char* argv[]){
    /*------------------------------------------------------------------------
      UI variables with sentential values
   ------------------------------------------------------------------------*/
    double numA = NAN;
    double numB = NAN;
    double numC = NAN;

    int AWasSet = 0;
    int BWasSet = 0;
    int CWasSet = 0;

    /*------------------------------------------------------------------------
      These variables are used to control the getopt_long_only command line
      parsing utility.
    ------------------------------------------------------------------------*/
    int rc;
    /* getopt_long stores the option index here. */
    int option_index = 0;

    /* This contains the short command line parameters list */
    char *getoptOptions = "a:b:c:";    /* add lots of stuff here */

    /* This contains the long command line parameter list, it should mostly
      match the short list                                                  */
    struct option long_options[] = {
            //Inputs for quadratic formula
            {"numa",     required_argument,       	0, 'a'},
            {"numb",     required_argument,       	0, 'b'},
            {"numc",     required_argument,       	0, 'c'},
            {0, 0, 0, 0}
    };

    opterr = 1;           /* Enable automatic error reporting */
    while ((rc = getopt_long_only(argc, argv, getoptOptions, long_options,
                                  &option_index)) != -1) {

        /* Detect the end of the options. */
        switch (rc)
        {
            case 'a':                    /* A input */
                numA = atof(optarg);
                AWasSet = 1;
                break;

            case 'b':                    /* B input */
                numB = atof(optarg);
                BWasSet = 1;
                break;

            case 'c':                    /* C input */
                numC = atof(optarg);
                CWasSet = 1;
                break;

            case '?':  /* Handled by the default error handler */
                break;

            default:
                printf ("Internal error: undefined option %0xX\n", rc);
                exit(PGM_INTERNAL_ERROR);
        } // End switch
    } /* end while */

    /*------------------------------------------------------------------------
      Check for command line syntax errors
    ------------------------------------------------------------------------*/
    if ( AWasSet == 0 || BWasSet == 0 || CWasSet == 0 || numA == 0 ){

        if ( AWasSet == 0 || BWasSet == 0 || CWasSet == 0 ) {
            fprintf(stderr, "Error: you must specify -a -b and -c parameters\n");
        }

        else if ( numA == 0 ){
            fprintf(stderr, "Error: -a must be non-zero\n");
            fflush(stderr);
        } /* End if error */

        else { return(PGM_INTERNAL_ERROR); }
        fprintf(stderr, "Program to find real and complex roots of quadratic polynomials\n");
        fprintf(stderr, "    f(x) = ax**2 + bx + c\n");
        fprintf(stderr, "usage: quadTest -a a -b b -c c\n");
        fprintf(stderr, "e.g. ./quadTest -a 1 -b 0 -c 1\n");
        fflush(stderr);
    } /* End if error */

    /*------------------------------------------------------------------------
      Begin doing the dirty work...
      Main program stuff goes here
    ------------------------------------------------------------------------*/

    #ifdef EN_TIME
    DECLARE_TIMER(timer);
    DECLARE_REPEAT_VAR(repeat);
    #endif
    
    /* setup the stuff needed to solve for the 
       roots of the given 3 term polynomial */
    polynomial poly;
    double complex *rootList;
    double complex roots[2];
    rootList = roots;


    initPoly(&poly, NTERMS); // creates polynomial structure with 3 terms for a,b,c
    poly.polyCoef[0] = numA; // assign the given values from the user
    poly.polyCoef[1] = numB;
    poly.polyCoef[2] = numC;

    #ifdef EN_TIME
    START_TIMER(timer);
    BEGIN_REPEAT_TIMING(1500000, repeat);
    #endif
    
    quadraticRoots(&poly, rootList);

    #ifdef EN_TIME
    END_REPEAT_TIMING;
    STOP_TIMER(timer);
    #endif

    //print results from root finding
    printf("\n\nThe roots of: %gx**2 + %gx + %g\n", numA, numB, numC);
    printf("  Root1: %g + %gi\n", creal(rootList[0]), cimag(rootList[0]));
    printf("  Root2: %g + %gi\n", creal(rootList[1]), cimag(rootList[1]));

    
    //print out timing results
    #ifdef EN_TIME
    PRINT_TIMER(timer);
    PRINT_RTIMER(timer, 1500000);
    #endif

    //clean up aka free stuff
    freePoly(&poly);
    
    return( PGM_SUCCESS );
} /* End main */


 /*---------------------------------------------------------------------------
  Returns the two roots from a quadratic polynomial
  
    =  -b +-sqrt(b**2-4ac)
       ----------------------
                 2a
  
  Where: polynomial *p              - Pointer to a 2nd order polynomial
  Returns: double complex* rootList - A pointer to a complex root pair.
  Errors:  prints an error and exits
---------------------------------------------------------------------------*/
void quadraticRoots(volatile polynomial *p, double complex *rootList){
   double numA, numB, numC;
   numA = p -> polyCoef[0];
   numB = p -> polyCoef[1];
   numC = p -> polyCoef[2];
   //use temp variables to simplify the equations for each root

   rootList[0] = (-numB + (csqrt( numB*numB - (4.0*numA*numC) )/(2.0*numA))); // pos sign
   rootList[1] = (-numB - (csqrt( numB*numB - (4.0*numA*numC) )/(2.0*numA))); // neg sign
}


/*---------------------------------------------------------------------------
  This function allocates an array of "nterm" double complex elements and then
  initializes the terms of the polynomial to NAN (not a number).
  We initialize the terms of the polynomial to NAN to prevent the users from
  accidentally using the polynomial before valid values are set.
  
  Where: polynomial *p       - Pointer to polynomial data structure to create
         unsigned int nterms - The number of elements to create
  Returns: nothing
  Errors:  prints an error and exits
---------------------------------------------------------------------------*/
void initPoly(polynomial *p, unsigned int nterms){
   p -> nterms = nterms;
   p -> polyCoef = malloc( NTERMS * sizeof( double complex ) );
   int i;
   for (i = 0; i < nterms; i++ ) {
      p -> polyCoef[i] = NAN;
   }
}


/*---------------------------------------------------------------------------
  Destroys/frees a polynomial
  
  Where: polynomial *p - Pointer to polynomial data structure to destroy
  Returns: nothing
  Errors:  none
---------------------------------------------------------------------------*/
void freePoly(polynomial *p){
   free( p -> polyCoef );
   p -> polyCoef = NULL;
}


