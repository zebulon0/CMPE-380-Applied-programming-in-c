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
   double fnum1, fnum2, fnum3;
   int  qnum1, qnum2, qnum3, qnval;
   clock_t  time1, time2;
   unsigned i;
   
   
   //------------------------------------------------------------------------
   // Examine the division utilities
   //------------------------------------------------------------------------   
   printf("\nDivision test");
   printf("\nfnum       qnum1(dec) qnum2(dec) qnum1(float) qnum2(float)\n");
   qnval = 18;
   fnum1 = -.0625;
   qnum1 = floatToFixed(fnum1, qnval); //unique value 1
   qnum2 = floatToFixed(fnum1, qnval); //unique value 2

   while ( qnum1 != 0 || qnum2 != 0 ) {
      qnum1 /= 2; //divide one using integer division
      qnum2 = Qn_DIVIDE(qnum2, 2, 0); //divide the other using the macro
      fnum1 /= 2;
      fnum2 = fixedToFloat(qnum1, qnval); //qnum1 float
      fnum3 = fixedToFloat(qnum2, qnval); //qnum2 float
      printf("%f    %d     %d     %f     %f\n", fnum1, qnum1, qnum2, fnum2, fnum3);
   }


   printf("\n\nDivision test: Absolute Values");
   printf("\nfnum     qnum1(dec) qnum2(dec) qnum1(float) qnum2(float)\n");
   qnval = 18;
   fnum1 = -.0625;
   qnum1 = floatToFixed(fnum1, qnval); //unique value 1
   qnum2 = floatToFixed(fnum1, qnval); //unique value 2

   while ( qnum1 != 0 || qnum2 != 0 ) {
      qnum1 /= 2; //divide one using integer division
      qnum2 = Qn_DIVIDE(qnum2, 2, 0); //divide the other using the macro
      fnum1 /= 2;
      fnum2 = fixedToFloat(qnum1, qnval); //qnum1 float
      fnum3 = fixedToFloat(qnum2, qnval); //qnum2 float
      printf("%f  %d     %d     %f     %f\n", fabs(fnum1), abs(qnum1), abs(qnum2), fabs(fnum2), fabs(fnum3));
   }

  
   //------------------------------------------------------------------------
   // Examine the multiplication utilities
   //------------------------------------------------------------------------   
   printf("\n\nMultiplication test\n");
 
   qnval = 18;
   fnum1 = 64.125;
   fnum2 = .755;
   
   qnum1 = floatToFixed(fnum1, qnval);
   qnum2 = floatToFixed(fnum2, qnval);
   qnum3 = Qn_MULTIPLY(qnum1, qnum2, qnval);
   fnum3 = fnum1 * fnum2;
   fnum1 = fixedToFloat(qnum3, qnval);

   printf("Product = %f float, qn18 product = %d dec, converted back %f float\n", fnum3, qnum3, fnum1);
   

   //------------------------------------------------------------------------
   // Implement floating point scientific equations two different ways
   // using normal fractions and using decimal fractions
   //------------------------------------------------------------------------
   printf("\n\nComplex calculations test\n");

   //implement the equation f(x) = x^x - .0001x^2 - 676x + .0676
   fnum1 = 1.0*1.0*1.0 - .0001*1.0*1.0 - 676.0*1.0 + .0676;   
   fnum2 = 1.0*1.0*1.0 - ((1.0*1.0)/10000.0) - 676.0*1.0 + (169.0/2500.0); 

   printf("Floating point decimal equation: %f:\n", fnum1);
   printf("Floating point fractional equation: %f\n", fnum2);

   qnval = 18;
   fnum3 = 1.0;
   qnum1 = floatToFixed(fnum3, qnval);
   qnum2 = Qn_MULTIPLY(Qn_MULTIPLY(qnum1, qnum1, qnval), qnum1, qnval) - .0001*Qn_MULTIPLY(qnum1, qnum1, qnval) - 676*qnum1 + .0676;
   fnum3 = fixedToFloat(qnum2, qnval);
   printf("Floating point Qn equation evaluation: %f\n\n", fnum3);

   
   //---------------------------------------------------------------------
   // Implement QN scientific equations: x**3-.0001x**2-676X+.0676
   //------------------------------------------------------------------------   
  
   // print all 3 answers

   
   //------------------------------------------------------------------------
   // Examine the performance 
   //------------------------------------------------------------------------
   qnval = 18;
   fnum1 = 3.1415;
   fnum2 = -674.9325;
   floatToFixed(fnum2, qnval);
   floatToFixed(fnum1, qnval);



   printf("\nPerformance test\n");

   // Floating point addition
   time1 = clock();
   for(i = 0; i < LOOP_DELAY; i++) {
      // Insert your addition here
      fnum3 = fnum2 + fnum1;
   }
   time1 = clock()-time1;
   
   // QN addition
   time2 = clock();
   for(i = 0; i < LOOP_DELAY; i++) {
      // Insert your addition here
      qnum3 = qnum2 + qnum1;
   }
   time2 = clock()-time2;
   
   // Print out the clicks and who was faster
   printf("Addition\n");
   printf("Clock ticks for float addition: %d\n", time1); 
   printf("Clock ticks for qn addition: %d\n", time2);
   if (time1 > time2) { printf("Faster operation: 'qn addition'\n\n"); }
   else { printf("Faster operation: 'float addition'\n\n"); }
   
   // Floating multiplication
   time1 = clock();
   for(i = 0; i < LOOP_DELAY; i++) {
      // Insert your addition here
      fnum3 = fnum2 * fnum1;
   }
   time1 = clock()-time1;
   
   // QN multiplication
   time2 = clock();
   for(i = 0; i < LOOP_DELAY; i++) {
      // Insert your addition here
      qnum3 = Qn_MULTIPLY(qnum1, qnum2, qnval);
   }
   time2 = clock()-time2;
   
   // Print out the clicks and who was faster
   printf("Multiplication\n");
   printf("Clock ticks for float multiplication: %d\n", time1);
   printf("Clock ticks for qn multiplication: %d\n", time2);
   if (time1 > time2) { printf("Faster operation: 'qn multiplication'\n\n"); }
   else { printf("Faster operation: 'float multiplication'\n\n"); }





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

