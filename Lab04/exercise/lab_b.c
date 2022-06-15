/****************************************************************************
 The purpose of this example is to exercise, creating, using and destroying
 pass by pointer and pass by value data structures
 
 student version 
 
 gcc -O1 -Wall -std=c99 -pedantic -g  lab_a.c -o lab_a
 valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./lab_a
 
 
 09/09/2019 R. Repka    Minor formatting changes
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*---------------------------------------------------------------------------
  The polynomial data structure contains the number of (size) of the
  allocated array of polynomial coefficients 
  e.g     nterms = 4;
          polyCoef = malloc(sizeof(double)*4);    
---------------------------------------------------------------------------*/
typedef struct {
    unsigned int nterms;      /* number of terms */
    double *polyCoef;         /* coefficients         */
} Poly;

// Function prototypes
void createPoly(Poly *p, int n);
Poly *createPoly_p(int n);
void destroyPoly(Poly *p);
void destroyPoly_p(Poly *p);
void printPolyRef(Poly *p);
void printPolyVal(Poly data);

int main(int argc, char *argv[]) {
   Poly stackPoly;         // Stack data structure
   Poly *poly_p;           // Pointer 
   
   // Create and use the data structure ( stackPoly )
   createPoly(&stackPoly, 10);
   // Print using pass by pointer AND value
   //
   // "Print poly by reference: 0 2 4 6 8 10 12 14 16 18"
   printf("Print poly by reference: ");
   printPolyRef(&stackPoly);
   
   // "Print poly by value: 0 2 4 6 8 10 12 14 16 18"
   printf("Print poly by value: ");
   printPolyVal(stackPoly);
   
   destroyPoly(&stackPoly);


   // Create and use the pointer as a data structure ( poly_p )
   poly_p = (Poly *) malloc ( 1 * sizeof(Poly));
   if (!poly_p) {
      printf("Error trying to malloc for poly_p");
      exit(-99);
   }

   createPoly(poly_p, 10);

   // Print using pass by pointer AND value
   //
   //  "Print poly by reference: ..."
   printf("Print poly by reference: ");
   printPolyRef(poly_p);
   //
   //
   //  "Print poly by value: ..."
   printf("Print poly by value: ");
   printPolyVal(*poly_p);


   //destroy the contents of the pointer
   destroyPoly_p(poly_p);



   return 0;
}

/*---------------------------------------------------------------------------
  Create a test polynomial using a pointer to the data structure
  Be sure to initialize the elements aka: polyCoef[i]  2.0*i
---------------------------------------------------------------------------*/
void createPoly(Poly *p, int n){
   //create a 'Poly' object with 'n' number of terms
   //and ??? for the 'polyCoef' double value
   p->nterms = n;
   p->polyCoef = (double *) malloc (p->nterms * sizeof(double));
   if (p->polyCoef == NULL) {
      printf("createPoly(): error trying to malloc ... exiting");
      exit(-99);
   }

  //do some sort of for loop to assign coefficient values
  //increment by 2 for each coefficient
  int i;
  for ( i=0; i<n; i++ ){
     p->polyCoef[i] = 2.0 * i;
  }  

}

/*---------------------------------------------------------------------------
  Create a test polynomial using a pointer to the data structure
---------------------------------------------------------------------------*/
// Destroy data structure based test polynomial 
void destroyPoly(Poly *p){
   free(p->polyCoef);
   p->polyCoef = NULL;  

   
}

/*---------------------------------------------------------------------------
  Create a test polynomial returning a pointer to the data structure
    Be sure to initialize the elements aka: polyCoef[i]  2.0*i
---------------------------------------------------------------------------*/
Poly *createPoly_p(int n){
   Poly *tempPoly; 
   //malloc space for the pointer??
   tempPoly = (Poly *) malloc (1 * sizeof(Poly));
   if (!tempPoly) {
      printf("createPoly_p(): error trying to malloc ... exiting");
      exit(-99);
   }   

   tempPoly->nterms = n;
   tempPoly->polyCoef = (double *) malloc (tempPoly->nterms * sizeof(double));
   
   if (tempPoly->polyCoef == NULL) {
      printf("createPoly_p(): error trying to malloc ... exiting");
      exit(-99);
   }
   
   int i;
   for ( i=0; i<n; i++ ) {
      tempPoly->polyCoef[i] = 2.0 * i;
   }
   return tempPoly;
}

/*---------------------------------------------------------------------------
  Destroy pointer based test polynomial 
---------------------------------------------------------------------------*/
void destroyPoly_p(Poly *p){
   free(p->polyCoef);
   p->polyCoef = NULL;

   free(p);
   p = NULL;
   
}

/*---------------------------------------------------------------------------
  Prints the polynomial data passing by reference use %3.0f
---------------------------------------------------------------------------*/
void printPolyRef(Poly *p){
   int i;
   for ( i=0; i<p->nterms; i++ ) {
      printf("%3.0f ", p->polyCoef[i]);
   } 
   printf("\n");  
}

/*---------------------------------------------------------------------------
  Prints the polynomial data passing by value use %3.0f
---------------------------------------------------------------------------*/
void printPolyVal(Poly data){
   int i;
   for ( i=0; i<data.nterms; i++) {
      printf("%3.0f ", data.polyCoef[i]);
   }   
   printf("\n");
}

