/**************************************************************************
  Student frame work.   Add and remove as you see fit.
  
  07/14/2017    R. Repka    Initial release
 * ***********************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "ClassErrors.h"
#include "rootfinding.h"
#include "Timers.h"

/************************************************************************
  Tests three types of root finding, secant, newton, and bisection,
  based on user input and prints out the timing results.
************************************************************************/
int main(int argc, char* argv[])
{
   /*------------------------------------------------------------------------
      UI variables with sentential values
   ------------------------------------------------------------------------*/
   int verbose = 0;
   enum modes {UNDEF, BISECT, SECANT, NEWTON} mode = UNDEF;
   double tol = 0.0;
   double guess1 = INFINITY;   
   double guess2 = INFINITY;

   /*------------------------------------------------------------------------
     These variables are used to control the getopt_long_only command line 
     parsing utility.  
   ------------------------------------------------------------------------*/
   int rc;
   /* getopt_long stores the option index here. */
   int option_index = 0;
  
   /* This contains the short command line parameters list */
   char *getoptOptions = "vbsnt:g:u:";    /* add lots of stuff here */
  
   /* This contains the long command line parameter list, it should mostly 
     match the short list                                                  */
   struct option long_options[] = {
      /* These options don’t set a flag.
         We distinguish them by their indices. */
      {"verbose",   	no_argument,       	0, 'v'},
      {"verb",      	no_argument,       	0, 'v'},

      //method to find roots
      {"bisection",     no_argument,       	0, 'b'},
      {"secant",      	no_argument,       	0, 's'},
      {"newton",      	no_argument,	   	0, 'n'},

      //tolerance for the root finding
      {"tolerance",     required_argument,      0, 't'},
      {"tol",      	required_argument,     	0, 't'},

      //upper and lower bounds / or guess 1 and guess 1
      {"guessa",      	required_argument,     	0, 'g'},
      {"ga",     	required_argument,     	0, 'g'},
      {"bracket_a",     required_argument,     	0, 'g'},
      {"ba",      	required_argument,     	0, 'g'},

      {"guessb",      	required_argument,     	0, 'u'},
      {"gb",      	required_argument,     	0, 'u'},
      {"bracket_b",     required_argument,     	0, 'u'},
      {"bb",      	required_argument,     	0, 'u'},

    /* add lots of stuff here */
      {0, 0, 0, 0}
   };
  
   opterr = 1;           /* Enable automatic error reporting */
   while ((rc = getopt_long_only(argc, argv, getoptOptions, long_options, 
                                                    &option_index)) != -1) {
      
 //     printf("getopt_long_only() returned ='%c' index = '%d'\n",  rc, option_index);   
      /* Detect the end of the options. */
      switch (rc)
        {
        case 'v':                    /* Verbose */
          verbose = 1;
          break;
        
	case 'b':                    /* Bisection */
          mode = BISECT;
	  break;
        
	case 's':                    /* Secant */
 	  mode = SECANT;
          break;
        
	case 'n':                    /* Newton */
          mode = NEWTON;
          break;
        
	case 't':                    /* Tolerance */
          tol = atof(optarg);
	  break;
        
	case 'g':                    /* GuessA, BracketA */
          guess1 = atof(optarg);
	  break;
        
	case 'u':                    /* GuessB, BracketB */
          guess2 = atof(optarg);
	  break;

        /* add lots of stuff here */

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
   if ((optind < argc) || 
      (mode == BISECT && ((argc != 9) && (argc != 8 ))) ||
      (mode == SECANT && ((argc != 9) && (argc != 8 ))) ||
      (mode == NEWTON && ((argc != 6) && (argc != 7 ))) ){
      fprintf(stderr, "Tests root finding methods\n");
      fprintf(stderr, "usage: hw7 -b[isection] | -s[ecant] | -n[ewton]   -t[ol[erance} number\n");
      fprintf(stderr, "          -g[uess1] number   <-g[u]ess2 number   <-verb[ose]> \n");
      fprintf(stderr, " e.g:   hw7 -bisection -tol 1E-6 -g1 -2 -g2 3 -verb\n"); 
      fflush(stderr);
      return(PGM_INTERNAL_ERROR);
   } /* End if error */
 

   double result;
   int nmax;
 

   #ifdef EN_TIME
   DECLARE_TIMER(timer);
   DECLARE_REPEAT_VAR(repeat);
   START_TIMER(timer);
   BEGIN_REPEAT_TIMING(50000, repeat);
   #endif

  
   /* Performs the root finding with bisection */
   if(mode == BISECT) {
      printf("Bracket1: %f  Bracket2: %f\n\n", guess1, guess2);
      result = bisection(func1, guess1, guess2, tol, verbose);
      if (result) { printf("Root found at: %f\n\n", result); }
      else { printf("No root was found\n\n"); }

   }  // End if bisection
   
   /* Performs the root finding using the secant method */
   else if(mode == SECANT) {
      nmax = 1000;
      printf("Guess1: %f  Guess2: %f\n\n", guess1, guess2);
      result = secant(func1, guess1, guess2, nmax, tol, verbose);
      if (result) { printf("Root found at: %f\n\n", result); }
      else { printf("No root was found\n\n"); }

   } // End secant
   
   /* Performs the root finding using newtons method */
   else /* must be newton */
   {
      nmax = 10000;
      printf("Guess1: %f\n\n", guess1);
      result = newton(func1, func1Deriv, guess1, nmax, tol, verbose);
      if (result) { printf("Root found at: %f\n\n", result); }
      else { printf("No root was found\n\n"); }

   } // End newton 
 
   #ifdef EN_TIME
   END_REPEAT_TIMING;
   STOP_TIMER(timer);
   PRINT_TIMER(timer);
   PRINT_RTIMER(timer, 50000);
   #endif  
        
    return PGM_SUCCESS;
}
