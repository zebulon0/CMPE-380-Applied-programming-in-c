/* Applied Programming Examples: sorting.c
 * student copy
 *
 * Uses qsort() to sort an array of random polar data
 *
 * Use compiler directive -DN=size to change the size of the array
 *
 * Reference: A. Kelley and I Pohl "A book on C" 4th Ed.
 * Revised: 3/31/2015 (JCCK)
 */
 
#include <stdio.h>  
#include <math.h>
#include <float.h>
#include <stdlib.h> /* for qsort()    */

/* The polar data structure */
typedef struct {double mag; double ang;} polar;

/* Add your polar compare function prototype here */
int cmpplr(const void *p1, const void *p2); 
/* 
 Initialize an array of doubles of size N, with random numbers
 between -50 and 50, sort it and print it 
*/
int main(int argc, char *argv[]) {

   polar *array;
   int num;
   int i;
   
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
   }   

   
   // Get the memory
   array = (polar *) malloc( 2 * num * sizeof(double) );
   if ( array == NULL ) {
      printf("Malloc error\n");
      exit(99);
   }

   // Initialize the array with random data, make one magnitude identical
   for(i = 0; i < num-1; ++i) {
      array[i].mag = (rand() % 1001) /10.0 - 50.0;
      array[i].ang = (rand() % 1001) /10.0 - 50.0;
   }
   // Identical 
   array[i].mag = array[i-1].mag;
   array[i].ang = (rand() % 1001) /10.0 - 50.0;


   
   // Sort the data
   qsort(array, num, 2*sizeof(double), cmpplr);
   
   // Print the sorted dat
   for(i = 0; i < num; ++i) {
      printf("%10.1f %10.1f\n", array[i].mag, array[i].ang);
   }
   printf("\n"); 
   free(array);  
return(0);
}  
 
/*---------------------------------------------------------------------------
  The compare function to use.  Cast p1 and p2 to polar in this case
---------------------------------------------------------------------------*/
// add your function and code here
int cmpplr(const void *p1, const void *p2) {
   polar *n1 = (polar *) p1;
   polar *n2 = (polar *) p2;
   polar a = *n1;
   polar b = *n2;  
   if (a.mag - b.mag > 0) { return 1; }
   else if (a.mag - b.mag < 0) { return -1; }
   else{
      if (a.ang - b.ang > 0) { return 1; }
      else if (a.ang - b.ang < 0) { return -1; }
      return 0;
   }
}











