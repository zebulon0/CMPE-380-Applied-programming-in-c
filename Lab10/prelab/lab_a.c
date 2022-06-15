/*---------------------------------------------------------------------------
  QN code testing and verification
  student copy
---------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include <math.h>

#define LOOP_DELAY (1<<27)

// QN math functions which pass the number of bits "n" 
#define Qn_MULTIPLY(A,B,n) ((A>>(n/2))*(B >>(n-(n/2))))
#define Qn_DIVIDE(A,B,n) ((int) (((long int)(A)<<n)/(B) ))

// QN math and printing functions
void  printBinary(unsigned num, short N);
int  floatToFixed(double x, int n);
float fixedToFloat(int x, int n); 

/*---------------------------------------------------------------------------
  QN testing framework 
---------------------------------------------------------------------------*/
int main(int argc, char *argv[]) {
   // QN testing variables, add more as necessary
   double fnum1, fnum2;
   int  qnum1, qnval;
   
   //------------------------------------------------------------------------
   // Print data on sizes  
   //------------------------------------------------------------------------
   printf("Integers are %ld bits long\n", 8*sizeof(int));

   //------------------------------------------------------------------------
   // Prove floating point has limits 
   //------------------------------------------------------------------------
   //fnum1 = 10.0;
   //printf("Floating point number: '%e'\n", fnum1);
   //printf("Proving floating point has limits by adding Epsilon\n");
   
   //fnum2 = fnum1 + DBL_EPSILON;
   //if (fnum2 == fnum1) { printf("Epsilon value '%e' didn't add\n", DBL_EPSILON); }
   //else { printf("The addition worked and the sum is '%e'\n", fnum2); }
   
   
   //------------------------------------------------------------------------
   // Examine the conversion utilities
   //------------------------------------------------------------------------
   printf("\nConversion test\n");

   //convert a floating point to decimal
   fnum1 = 0.0;
   qnum1 = 0;
   qnval = floatToFixed(fnum1, qnum1);
   //convert decimal to floating point
   fnum2 = fixedToFloat(qnval, qnum1);
   printf("\n\nStarted with '%f' converted to qn%d = '%d' decimal and then back to '%f'\n", fnum1, qnum1, qnval, fnum2);
   //print out decimal value in binary
   printf("QN '%d' decimal in binary is ", qnval);
   printBinary(qnval, 16);

   //convert a floating point to decimal
   fnum1 = 12.25;
   qnum1 = 3;
   qnval = floatToFixed(fnum1, qnum1);
   //convert decimal to floating point
   fnum2 = fixedToFloat(qnval, qnum1);
   printf("\n\nStarted with '%f' converted to qn%d = '%d' decimal and then back to '%f'\n", fnum1, qnum1, qnval, fnum2);
   //print out decimal value in binary
   printf("QN '%d' decimal in binary is ", qnval);
   printBinary(qnval, 16);

   //convert a floating point to decimal
   fnum1 = 12.0625;
   qnum1 = 3;
   qnval = floatToFixed(fnum1, qnum1);
   //convert decimal to floating point
   fnum2 = fixedToFloat(qnval, qnum1);
   printf("\n\nStarted with '%f' converted to qn%d = '%d' decimal and then back to '%f'\n", fnum1, qnum1, qnval, fnum2);
   //print out decimal value in binary
   printf("QN '%d' decimal in binary is ", qnval);
   printBinary(qnval, 16);

   //convert a floating point to decimal
   fnum1 = 12.0625;
   qnum1 = 4;
   qnval = floatToFixed(fnum1, qnum1);
   //convert decimal to floating point
   fnum2 = fixedToFloat(qnval, qnum1);
   printf("\n\nStarted with '%f' converted to qn%d = '%d' decimal and then back to '%f'\n", fnum1, qnum1, qnval, fnum2);
   //print out decimal value in binary
   printf("QN '%d' decimal in binary is ", qnval);
   printBinary(qnval, 16);







   return(0);
}


/*---------------------------------------------------------------------------
  This prints a number in character binary bracketed by [..]
  
  Where: unsigned num - number to print
         short N      - number of bits to print
         
  Returns: nothing
  Error handling: none
----------------------------------------------------------------------------*/
void printBinary(unsigned num, short N) { 
   unsigned i; 
   printf("\t[");
   
   for (i = 1 << (N-1); i > 0; i = i >> 1) {
      (num & i)? printf("1"): printf("0");
    }        
   printf("]\n");
   return;
} 


/*---------------------------------------------------------------------------
  This convert from Float to FP(Qn) 
  
  Where: double x  - number to convert
         int qnval - number of bits to use
         
  Returns: int    - QN encoded number
  Error handling: none
----------------------------------------------------------------------------*/
int floatToFixed(double x, int qnval) { 
   return( x * (double)(1 << qnval) );            
} 

/*---------------------------------------------------------------------------
  This converts from FP(Qn) to Float
  
  Where: int x     - number to convert
         int qnval - number of bits to use
         
  Returns: float   - converted number
  Error handling: none
----------------------------------------------------------------------------*/
float fixedToFloat(int x, int qnval) { 
   return((double)x / (double) (1 << qnval));
}

