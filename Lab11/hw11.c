/********************************************************************
 * Applied Programming:                                             
 *    Solution of Overdetermined System of Equations Ax=b arising   
 *    in least square problems via QR factorizations using the GSL
 *                                                                  
 * Compilation:  gcc -ansi -g -lgsl -lgslcblas  hw8.c DynamicArrays.c -o  hw8
 *                                                                  
 * Tested in Ubuntu 12.04 LTS                                       
 * Revised: Juan C. Cockburn, April 9, 2015 (juan.cockburn@rit.edu) 
 * 10/10/2015 R. Repka - Minor clean up
 * 10/26/2016 R. Repka - Major re-write, added QR and norm solution modes
 * 11/12/2017 R. Repka - Minor comment change for norm of residuals, removed
 *                       "c" in GE_FindPoint
 * 11/28/2016 R. Repka - Added Pearson function
 * 07/11/2017 R. Repka - Switched to getopt_long_only
 * 04/20/2018 R. Repka - removed QR solution, added better problem
 *                       description
 * 12/11/2018 R. Repka - Minor comment changes
 * 04/10/2019 R. Repka - Don't need evalPoly() anymore
 ********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include "ClassErrors.h"
#include "DynamicArrays.h"

/*****************************************************************************
 Function prototypes 
*****************************************************************************/
void readPoints (FILE *file, DArray *DArrayPtr);
void Norm_FindPoint(int nr, int nc, const DArray *points, gsl_vector *x_ls, 
                                                                 int verbose);


/*****************************************************************************
 This program uses least squares to generate approximate functions
    usage: hw12   -order  num   -points  file  [-verbose] \n");
 
 Returns: 0 for success, non-zero for errors
 *****************************************************************************/
int main(int argc, char *argv[])
{
   DArray points;     
   FILE *pointsFile;
   int i;
   int nr, nc;       /* number of rows and cols  */                                                  
   gsl_vector *x_ls; /* least squares solution   */
 
   /*------------------------------------------------------------------------
     add your UI variables with sentential values and add your get_opt_long 
     code here
   ------------------------------------------------------------------------*/
   int order = 0;
   int verbose = 0;
   char *inName = NULL;
   int rc;
   /* getopt_long stores the option index here. */
   int option_index = 0;

   /* This contains the short command line parameters list */
   char *getoptOptions = "o:p:v";    /* add lots of stuff here */

   /* This contains the long command line parameter list, it should mostly
      match the short list                                                  */
   struct option long_options[] = {
   	{"order",     required_argument,    0, 'o'},
   	{"points",    required_argument,    0, 'p'},
   	{"verb",      no_argument,          0, 'v'},
   	{"verbose",   no_argument,          0, 'v'},
   	{0, 0, 0, 0}
   };

   opterr = 1;           /* Enable automatic error reporting */
   while ((rc = getopt_long_only(argc, argv, getoptOptions, long_options,
                                 &option_index)) != -1) {
      /* Detect the end of the options. */
      switch (rc) {
         case 'o':    	/* Order input */
            order = atoi(optarg);
            break;

          case 'p':    	/* PointsFile input */
             inName = optarg;
             break;

          case 'v':	/* Verbose flag */
             verbose = 1;
             break;

          case '?':  	/* Handled by the default error handler */
             break;

          default:
             printf ("Internal error: undefined option %0xX\n", rc);
             exit(PGM_INTERNAL_ERROR);
      } /* End Switch */
   } /* End While */      

   /*------------------------------------------------------------------------
     Check for command line syntax errors
   ------------------------------------------------------------------------*/
   if ( (order < 1) || (inName == NULL) || (optind < argc) ){
      fprintf(stderr, "This program uses least squares to generate approximate functions for data.\n");
      fprintf(stderr, "usage: hw11   -o[rder] num   -p[oints] file   [-v[erb[ose]]] \n");
      fprintf(stderr, "Where: -order  - required, order of the equation to use.  Must be 1 or more\n"); 
      fprintf(stderr, "       -points - required, list of points to evaluate (2 col data)\n");
      fprintf(stderr, "       -verbose     - optional verbose flag\n");
      fprintf(stderr, " e.g: ./hw12 -order 2   -points  points.txt   - use Norm Gaussian elimination for a 2nd order equation\n");
      fflush (stderr);
      return(PGM_SYNTAX_ERROR);
   } /* End if error */

  /* The real matrix size is one larger than the order */    
   nc = order+1;
   
   /* Create a dynamic array to hold the data points */  
   CreateDArray(&points, GROWTH_AMOUNT);
   
   /* Try to open the data points file */
   pointsFile = fopen (inName, "r");
   if (NULL == pointsFile) {
      fprintf (stderr, "Error: unable to open data points file '%s'\n", inName);
      fflush (stderr);
      DestroyDArray(&points);
      return(PGM_FILE_NOT_FOUND);
   }
  
   /* Read the data in */
   readPoints (pointsFile, &points);
   fclose(pointsFile);
   nr = points.EntriesUsed;

   /* Contains the final solution */   
   x_ls = gsl_vector_alloc(nc);     
   
   /* Execute the right algorithm */
   Norm_FindPoint(nr, nc, &points, x_ls, verbose);
   printf("Least Squares Solution via Norm factorization:\n");

   
   /* Print out the variable coefficients */
   if (verbose) {
      for(i = 0; i < nc; i++) {
         printf(" x_ls[%1d] = %20.16f \n",i, gsl_vector_get(x_ls, i));
      }
   printf("\n");
   }
   
   /* Print out the pretty answers */
   printf("  f(x) = ");
   for(i = 0; i < nc; i++) {
      if (0 == i) {
        printf(" %g +", gsl_vector_get(x_ls,i));
      }
      else if (1 == i) {
        printf(" %gx ", gsl_vector_get(x_ls,i));
        if (i < (nc-1)) { printf("+");}
      }
      else {
        printf(" %gx^%d ", gsl_vector_get(x_ls,i), i);
        if (i < (nc-1)) { printf("+");}
      }
    } /* End for i */
   printf("\n\n");
     

 
   /* Cleanup */
   gsl_vector_free(x_ls);  
   DestroyDArray(&points);
   
  return PGM_SUCCESS; /* main */
 
   /* Clean up */
   gsl_vector_free(x_ls);  
   DestroyDArray(&points);
   
  return PGM_SUCCESS; /* main */
}

/*---------------------------------------------------------------------------
  Find the least squares approximation to data "points" of order "nc" using
  the "Normal equations" approach.
        
                        A'Az = A'b
  
  Where: int nr           - The number of points (rows) of the input file
         int nc           - The number of columns (order) of the solution
         DArray *points   - Pointer to the x,y data
         gsl_vector *x_ls - The solution is returned here
         int verbose      - Verbose flag

  Returns: nothing
  Errors: Assumes the standard GSL error handler
---------------------------------------------------------------------------*/
void Norm_FindPoint(int nr, int nc, const DArray *points, gsl_vector *x_ls, int verbose) {
   double x;
   int i, j;         /* counters                 */
   gsl_matrix *A;    /* coefficient matrix A     */
   gsl_matrix *AT;   /* coefficient matrix A'    */
   gsl_matrix *ATA;  /* coefficient matrix A'A   */
   gsl_vector *b;    /* coefficient vector b     */
   gsl_vector *ATB;  /* coefficient vector A'b   */
   gsl_vector *tau;  /* Householder coefficients */
   gsl_vector *res;  //residual vector

   /* Allocate space for Matrices and vectors */
   ATA  = gsl_matrix_alloc(nc, nc); /* Data matrix */
   AT   = gsl_matrix_alloc(nc, nr); /* Data matrix */
   A    = gsl_matrix_alloc(nr, nc); /* Data matrix */
   b    = gsl_vector_alloc(nr);     /* Data vector */
   ATB  = gsl_vector_alloc(nc);     /* Data vector but rotated so nc not nr */
   tau  = gsl_vector_alloc(nc);     /* required place holder for GSL, nc */
   res  = gsl_vector_alloc(nc); //residual vector
    
  /* Setup and solve to get the solution vector */
  //(A'A)z = A'b ... find z

  /* create A matrix = A */
  for ( i = 0; i < nr; i++ ) { gsl_matrix_set(A, i, 0, 1); } //put 1's in first column
  for ( i = 0; i < nr; i++ ) {
     //get the x value for that row
     x = points -> Payload[i].x;
     for ( j = 1; j < nc; j++ ) {
        gsl_matrix_set(A, i, j, x);
        x = x * points -> Payload[i].x; // increment the x value for the next col
     } /* end for cols */
  } /* end for rows */

 
  /* create b vector = b */
  for( i = 0; i < nr; i++ ) { gsl_vector_set(b, i, points -> Payload[i].y); }


  /* compute A' matrix = AT */
  gsl_matrix_transpose_memcpy(AT, A);


  /* compute A'A matrix = ATA */
  //use gsl matrix-matrix dot product
  gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, AT, A, 0.0, ATA);


  /* compute A'b vector = ATB */
  //using gsl matrix-vector dot product
  gsl_blas_dgemv(CblasNoTrans, 1.0, AT, b, 0.0, ATB);


  /* Solve the dang thing already! */
  gsl_linalg_QR_decomp(ATA, tau);
  gsl_linalg_QR_lssolve(ATA, tau, ATB, x_ls, res); //solution vector in x_ls


  if ( verbose ) {
  /* Need to print out A, b, AT, ATA, and ATB */
     printf("A (%d x %d)\n", nr, nc);
     for ( i = 0; i < nr; i++ ) {
        printf("%3d: ", i);
        for ( j = 0; j < nc; j++ ) {
           printf("%12.5f ", gsl_matrix_get(A, i, j));
        } /* end for */
        printf("\n");
     } /* end for */


     printf("b (%d x 1)\n", nr);
     for ( i = 0; i < nr; i++ ) {
        printf("%3d: ", i);
        printf("%12.5f \n", gsl_vector_get(b, i));
     } /* end for loop */


     printf("AT (%d x %d)\n", nc, nr);
     for ( i = 0; i < nc; i++ ) {
        printf("%3d: ", i);
        for ( j = 0; j < nr; j++ ) {
           printf("%12.5f ", gsl_matrix_get(AT, i, j));
        } /* end for */
        printf("\n");
     } /* end for loop */


     printf("ATA (%d x %d)\n", nc, nc);
     for ( i = 0; i < nc; i++ ) {
        printf("%3d: ", i);
        for ( j = 0; j < nc; j++ ) {
           printf("%12.5f ", gsl_matrix_get(ATA, i, j));
        } /* end for */
        printf("\n");
     } /* end for loop */


     printf("ATB (%d x 1)\n", nc);
     for ( i = 0; i < nc; i++ ) {
        printf("%3d: ", i);
        printf("%12.5f \n", gsl_vector_get(ATB, i));
     } /* end for loop */
     
  } /* end verbose printing */

 
  /* Free memory  */
  gsl_matrix_free(A);
  gsl_matrix_free(AT);
  gsl_matrix_free(ATA);
  gsl_vector_free(b);
  gsl_vector_free(ATB);
  gsl_vector_free(tau);
  gsl_vector_free(res);
 
} /* end Norm_FindPoint() */



/***************************************************************************************
 Reads the points data from file and returns it in a Darray
                       
 
 Where: FILE *file     - open handle to read from
                         of the form:     22.0      6.7
                                          23.4      18.8
        DArray *DArrayPtr - Pointer to a dynamic array to store the data
  Returns: nothing
  Errors:  none
*****************************************************************************************/
void readPoints(FILE *file, DArray *DArrayPtr) {
   char String[256], *pch;
   Data tempData;

   /* Grab the data and put it in a Dynamic Array */
   while (fgets (String, 256, file)) {
      pch = strtok (String, "    ");
      tempData.x = atof(pch);
      pch = strtok (NULL, "  ");
      tempData.y = atof(pch);
      PushToDArray (DArrayPtr, &tempData);
   }
   return;
} /* readPoints */
