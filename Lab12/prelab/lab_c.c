/* Applied Programming Examples: sorting.c
 * student copy
 *
 * Uses qsort() to sort an array of random doubles
 *
 */
 
#include <stdio.h>  
#include <stdlib.h> /* for qsort()    */

/* Function prototypes */
int cmpdbl(const void *p1,const void *p2); /* for qsort() */
 
/* 
 Initialize an array of doubles of size N, with random numbers
 between -50 and 50, sort it and print it 
*/
int main(int argc, char *argv[]) {
   double *array;
   int num;
   
   // Check the command line entry
   if (argc == 1) {
      printf("Error: No input found\n");
      return -1;
   }
   else if ( argc > 2 ) { 
      printf("Error: Too many arguments\n");
      return -1;
   }
   else {
      if ( argv[1] != NULL ) { num = atoi(argv[1]); }
      if ( num < 2 && num > 0 ) {
         printf("Error: An array of size 1 cannot be sorted\n");
         return -1;
      }  
      if ( num < 0 ) {
         printf("Error: Please specify a positive number\n");
         return -1;
      }
 
   // Get the memory
   array = (double *) malloc( num * sizeof(double) );
   if (array == NULL) {
      printf("Malloc error\n");
      exit(99);
   } 
  
   // Initialize the array with random data
   for(int i = 0; i < num; ++i) {
      array[i] = (rand() % 1001) /10.0 - 50.0;
   }
   
   // Sort the data
   qsort(array, num, sizeof(double), cmpdbl);
   
   // Print the sorted dat
   for(int i = 0; i < num; ++i) {
      printf("% 10.1f\n", array[i]);
   }
   printf("\n");   
   free(array);
   }
return(0);
}  
 
/*---------------------------------------------------------------------------
  The compare function to use.  Cast p1 and p2 to doubles in this case
---------------------------------------------------------------------------*/
int cmpdbl(const void *p1, const void *p2) {
   double* n1 = (double *) p1;
   double* n2 = (double *) p2;
   double a = *n1;
   double b = *n2;
   if ( a - b > 0 ) { return 1; }
   else if ( a - b < 0 ) { return -1; }
   return 0;


}


