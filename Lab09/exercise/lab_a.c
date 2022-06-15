/*-----------------------------------------------------------------------
  Simple program to dump IEEE single precision floating point numbers
  student copy
-----------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIGN_MASK         (0x80000000)
#define SIGN_SHIFT        (31)
#define EXPONENT_MASK     (0x7f800000)
#define EXPONENT_SHIFT    (23)
#define EXPONENT_BIAS     (127)
#define SIGNIFICAND_MASK  (0x007fffff)

void ieeePrint(float fnum);

int main(int argc, char * argv[]) {
   
      // Must have a number
   if (2 == argc) {
      ieeePrint(atof(argv[1]));
   }
   else {
      printf("This decodes IEEE single precision numbers\n");
      printf("Error: Syntax is: %s number\n", argv[0]);
   }

   return(0);
}


void ieeePrint(float fnum) {
   int sign, exponent, significand;
   
   // We require a union because C won't let us mask floating point
   union Data {
      int i;
      float fnum;
   } ieee;
   
   ieee.fnum = fnum;

   significand = (ieee.i & SIGNIFICAND_MASK) << 1;
   
   sign = (ieee.i & SIGN_MASK) >> SIGN_SHIFT;

   exponent = (ieee.i & EXPONENT_MASK) >> EXPONENT_SHIFT;
   exponent -= EXPONENT_BIAS;

   
   // Break the floating point item into the proper parts

   
   printf("Number %f => Bin sign:%d Dec exponent:%d  Hex significand .%x\n", ieee.fnum, sign, exponent, significand);
   return;
}

