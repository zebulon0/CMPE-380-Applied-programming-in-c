/*********************************************************************
* Example: Using the GSL (Gnu Scientific Library) to solve a system 
* of algebraic equations Ax=b via permuted LU factorization.
*
* student version
*
* Compile: gcc -o lu lu_fact.c -lgsl -lgslcblas
*
* 
* 12/03/2016   R. Repka - Fixed ansi warning for DECLARE_TIMER()
* 11/29/2019   R. Repka - Added true dynamic support 
* Reference: Golub and Vanloan Algorithms 3.4.1
*********************************************************************/
#include <stdio.h>
#include <gsl/gsl_linalg.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h> // for isspace()
#include "ClassErrors.h"


#ifndef INITIAL_READ_SIZE 
   #define INITIAL_READ_SIZE  (20)
#endif 
#ifndef READ_GROWTH_SIZE
  #define READ_GROWTH_SIZE   (20)
#endif

// Used to return the size of GSL matrix rows and columns 
#define GSL_MAT_ROWS(x)    (x->size1)
#define GSL_MAT_COLS(x)    (x->size2)

// Function prototypes
gsl_matrix* initMatrix(FILE *file);
int readMatrix(FILE *file, gsl_vector *V, gsl_matrix *M);

/*---------------------------------------------------------------------------
      
---------------------------------------------------------------------------*/
int main (int argc, char* argv[]) {
    int  i, j, errorCode = 0;
    FILE *inHandle;
    
    // Allocate the GSL variables
    gsl_matrix *mat;
    gsl_vector *b, *x;
    gsl_permutation *p;
    int s;
    
   /*------------------------------------------------------------------------
     These variables are used to control the getopt_long_only command line 
     parsing utility.  
   ------------------------------------------------------------------------*/
   int rc;
   char *inFile = NULL;
   int verb     = 0;
   int showData = 0;
   
   // getopt_long stores the option index here. 
   int option_index = 0;
  
   // This contains the short command line parameters list 
   char *getoptOptions = "i:vd";
  
   /* This contains the long command line parameter list, it should mostly 
     match the short list.  Note: get_opt_long is not really needed       */
   struct option long_options[] = {
      /* These options don’t set a flag.
         We distinguish them by their indices. */
      {"data",    no_argument, 0, 'd'},
      {"in",      required_argument, 0, 'i'},
      {"input",   required_argument, 0, 'i'},
      {"verb",    no_argument, 0, 'v'},
      {"verbose", no_argument, 0, 'v'},
      {0, 0, 0, 0}
   };
         
   opterr = 1;           // Enable automatic error reporting 
   while ((rc = getopt_long_only(argc, argv, getoptOptions, long_options, 
                                                    &option_index)) != -1) {
   //  printf("getopt_long_only() returned ='%c' index = '%d'\n",  rc, option_index);   
      /* Detect the end of the options. */
      switch (rc)
        {
        case 'i':  
          inFile = optarg;
          break;

        case 'v':   
          verb = 1;
           break;

        case 'd':   
          showData = 1;
           break;
           
        case '?':  // Handled by the default error handler 
          break;

       default:
          printf ("Internal error: undefined option %0xX\n", rc);
          exit(PGM_INTERNAL_ERROR);
       } // End switch 
   } // end while 

   /*------------------------------------------------------------------------
     Check for command line syntax errors like not all parameters specified
     or the first parameter is zero.
   ------------------------------------------------------------------------*/
   if ((optind < argc) || (NULL == inFile)) {
      fprintf(stderr, "This program using GSL PLU factorization to solve a system \n");
      fprintf(stderr, "of algebraic equations via Ax=b\n");
      fprintf(stderr, "usage: hw12  -i[n[put]] file [-v[erb[ose] [-d[ata]\n");
      fprintf(stderr, "Where: -input file - the matrix file to process.\n");
      fprintf(stderr, "                     first line contains the number\n");
      fprintf(stderr, "                     rows and columns in the subsequent\n");
      fprintf(stderr, "                     data\n");
      fprintf(stderr,"        -data       - Print the input A and b data\n");
      fprintf(stderr, "       -verbose    - Enable optional debugging information\n\n");
      fprintf(stderr, "e.g.   hw12 -i rand.txt \n");
      return(PGM_SYNTAX_ERROR);
   } /* End if error */
    
   // Try to open the matrix 
   inHandle = fopen(inFile, "r");
   if (NULL == inHandle){ 
      fprintf(stdout, "Error: input file '%s' not found\n", inFile);
      return(FILE_NOT_FOUND);
   }

   // The file is there, initialize the matrix from the file 
   mat = initMatrix(inHandle);

   // We must have a good matrix file, allocate the data arrays 
   b = gsl_vector_calloc(GSL_MAT_ROWS(mat));
   x = gsl_vector_calloc(GSL_MAT_ROWS(mat));
   p = gsl_permutation_alloc(GSL_MAT_ROWS(mat));
   
   // Read the data into the GSL matrix.
   errorCode = readMatrix(inHandle, b, mat);
   if (errorCode) {
      // There is something wrong with the matrix file 
      return(errorCode);
   } /* End else */
   
   if (showData) {
      printf("Matrix A:\n");
      for (i = 0; i < GSL_MAT_ROWS(mat); i++) {
          for (j = 0; j < GSL_MAT_COLS(mat); j++)
              printf ("%8.4f ", gsl_matrix_get(mat, i, j));
      putchar('\n');
      } 
   
   // Print entries of vector b 
   printf("Vector b:\n");
   gsl_vector_fprintf (stdout, b,"%8.4f") ;
   }
   
   // Do the LU decomposition 
   errorCode = gsl_linalg_LU_decomp (mat, p, &s);
   
   if (verb) {               
      fprintf(stdout, "\nP = [");
      gsl_permutation_fprintf (stdout, p, " %u");
      fprintf(stdout, " ] \n");
      
      fprintf(stdout, "LU matrix = \n");
      printf("Matrix LU:\n");
      for (i = 0; i < GSL_MAT_ROWS(mat); i++) {
         for (j = 0; j < GSL_MAT_COLS(mat); j++) {
            printf ("%7.2g ", gsl_matrix_get (mat, i, j));
         } 
      putchar('\n');
      } // End for i              
   } // End if verbose 
   
   // Was the LU good? 
   if(0 != errorCode){
      fprintf(stdout, "Error: Matrix does not have a solution. \n");
      return(NO_SOLUTION);
   } /* End if */
   
   // We have a good LU, solve it 
   gsl_linalg_LU_solve (mat, p, b, x);
   
   printf("Solution x:\n");
   gsl_vector_fprintf (stdout, x, "%8.4f");
   
   // Free things 
   gsl_matrix_free(mat);
   gsl_vector_free(b);
   gsl_permutation_free(p);
   gsl_vector_free(x);
 
   fclose(inHandle);
     
   return(PGM_SUCCESS);
} /* main */


/*---------------------------------------------------------------------------
  This function allocates a GSL Matrix array from the first row of data supplied.
  The first line will have two numbers (separated by spaces), specifying the 
  dimensions of the augmented matrix G = [A b].  
  
  This routine supports input data of arbitrary length.
  
  The following lines will have the rows of G, each entry separated by spaces. 
  The example below shows the two first lines of the data file for a system of 
  5 equations with 5 unknowns

  # indicates a comment, must be at the top of the file 
  5            6
  1.1       3.4       5.6       7.8       7.8       1.1 
   
  Where:   FILE *file - Open file handle to a matrix data text file
  Returns: gsl_matrix * - an empty GSL matrix file of the correct size 
  
  Error policy: Prints an error message and exit with a unique error code
---------------------------------------------------------------------------*/
gsl_matrix* initMatrix(FILE *file){
   char *buffer = (char *) malloc( sizeof(char) * (INITIAL_READ_SIZE + 1) );
   //int dimensionFound = 0;
   int bufferSize = INITIAL_READ_SIZE;
   long int position = 0;
   int i, nr, nc, numElements;
   i = 0;
   nr = 0;
   nc = 0;


   while(1) {
      bufferSize = INITIAL_READ_SIZE;
      fgets(buffer, bufferSize, file);
      while(strlen(buffer) >= bufferSize-1) {
         bufferSize += READ_GROWTH_SIZE;
         buffer = (char*)realloc(buffer, sizeof(char)*(bufferSize)); //check for alloc error
         if (buffer == NULL) {
            printf("Realloc error\n");
            exit(REALLOC_ERROR);      
         }
         fseek(file, position, SEEK_SET); 
         fgets(buffer, bufferSize, file);
      }
      position = ftell(file);

      i = strlen(buffer)-1;
      while( (i<=0) && (isspace(buffer[i]))) {
         buffer[i] = 0;
         i--;
      }
 
      if( buffer[0] != '#') {
         //dimensionFound = 1;
         char *p;
         p = strtok(buffer, " \r\t\n");
         numElements = 0;   
         while ( p != NULL ){
            numElements++;
            if ( numElements == 1 ) { nr = atoi(p); }
            if ( numElements == 2 ) { nc = atoi(p); }
            p = strtok(NULL, " \r\t\n");
         }
         printf("Rows: %d Cols: %d\n", nr, nc);
         break;
      }
   }
   if ( nr < 2 ){
      printf("Error: Matrix must have at least 2 rows\n");
      exit(NOTENOUGHROWS);
   }
   if ( numElements < 2 ) {
      printf("Error: Not enough columns of data\n");
      exit(NOTENOUGHCOLS);
   }
   if ( numElements > 2) {
      printf("Error: Too many columns of data\n");
      exit(TOOMANYCOLS);
   }
   if ( nc  <= nr ) {
      printf("Error: Column size not greater than row size\n");
      exit(NOTENOUGHCOLS);
   }

   // You will need this code
   gsl_matrix *M;
   M = gsl_matrix_calloc(nr, nc-1);
   return M;
} // initMatrix


/*---------------------------------------------------------------------------
  This function populates a GSL matrix from a supplied text file of the form
 
  
  The first line will have two numbers (separated by spaces), specifying the 
  dimensions of the augmented matrix G = [A b].  
  
  The following lines will have the rows of G, each entry separated by spaces. 
  The example below shows the two first lines of the data file for a system of 
  5 equations with 5 unknowns
  
  # indicates a comment, must be at the top of the file 
  5            6
  1.1       3.4       5.6       7.8       7.8       1.1 
  
  This routine supports input data of arbitrary length
  
  Where: FILE *file - Open file handle to a matrix text file, with the first line
                      already processed
         gsl_vector *V  - Pointer to a vector to hold the "b" vector 
         gsl_matrix *M  - Pointer to a matrix to hold the "A" matrix
  Errors: none
  Returns: int readMatrix - 0 = success, otherwise
                            4 = too many columns
                            5 = too many rows
---------------------------------------------------------------------------*/
int readMatrix(FILE *file, gsl_vector *V, gsl_matrix *M){
   // You will need to use these functions
   // gsl_vector_set(V, i, num);
   // gsl_matrix_set(M, i, j, num);
   
   char *buffer = (char *) malloc( sizeof(char) * (INITIAL_READ_SIZE + 1) );
   int bufferSize = INITIAL_READ_SIZE;
   char *test;
   long int position, nr, nc;
   position = 0;
   int t, i, j;
   i = 0;
   j = 0;
   t = 0;
   nr = GSL_MAT_ROWS(M);
   nc = GSL_MAT_COLS(M);
   //totalElements = 0;
   //neededElements = (int )nr * (int )nc;


   while(1) {
      printf("Rows %ld Cols %ld\n", nr, nc);
      bufferSize = INITIAL_READ_SIZE;
      fgets(buffer, bufferSize, file);
      while(strlen(buffer) >= bufferSize-1) {
         bufferSize += READ_GROWTH_SIZE;
         buffer = (char*)realloc(buffer, sizeof(char)*(bufferSize)); //check for alloc error
         if (buffer == NULL) {
            printf("Realloc error\n");
            exit(REALLOC_ERROR);      
         }
         fseek(file, position, SEEK_SET); 
         test = fgets(buffer, bufferSize, file);
      }
      if ( test == NULL ) { break; }
      //if (i == nr ) {break;}
      //NEED TO FIND THE RIGHT BREAK CASE
      //
      //For some reason the loop continues until its caught by the too many 
      //rows if statement but 
      position = ftell(file);
      
      t = strlen(buffer)-1;
      while( (t>=0) && (isspace(buffer[t]))) {
         buffer[t] = 0;
         t--;
      }
      
      if (i > nr-1) {
         if (feof(file)) {break;}
         printf("Error: Too many rows\n");
         free(buffer);
         exit(TOOMANYROWS);
      }
      if ( (i < nr-1) && feof(file) ) {
         printf("Error: Not enough rows\n");
         free(buffer);
         exit(NOTENOUGHROWS);

      }

      char *p;
      p = strtok(buffer, " \r\t\n");
      //rowElements = 0;
      j = 0;
      while ( p != NULL ) {
         printf("Row i=%d Col j=%d P=%s\n", i, j, p);
         if (j > nc) {
            printf("Error: Too many columns of data\n");
            free(buffer);
            exit(TOOMANYCOLS);
         }
         if (j == nc ) { gsl_vector_set(V, i, atof(p)); }
         if (j <= nc-1 ) { gsl_matrix_set(M, i, j, atof(p)); } 
         p = strtok(NULL, " \r\t\n");
         j++;
      }
      if ( j <= nc ) {
         free(buffer);
         printf("Error: Not enough columns of data\n");
         exit(NOTENOUGHCOLS);
      }
      i++;
   }

   //if (neededElements != totalElements) {
   //   printf("Number of elements don't match");
   //   exit(TOOMANYCOLS);
   //}


return (0);
} // end readMatrix
