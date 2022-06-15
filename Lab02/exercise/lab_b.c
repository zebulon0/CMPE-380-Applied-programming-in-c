/****************************************************************************
 Lab 2 student file
 10/05/2019 R. Repka    Initial release
****************************************************************************/
#include <stdio.h> 
#include <stdint.h> 
#include <string.h>
   
/*---------------------------------------------------------------------------
  Student data structure
---------------------------------------------------------------------------*/
struct bandMember {
   char f_name[256]; 
   char l_name[256]; 
   int  year; 
};	

union anumber1 {
   float a;
   int b;
} aNumber1;

struct anumber2 {
   float a;
   int b;
} aNumber2;

typedef struct {
   char f_name[256];
   char l_name[256];
   int year;
} band;
   
int main(int argc, char *argv[]) {
   /*------------------------------------------------------------------------
     Add code here
   ------------------------------------------------------------------------*/
   aNumber1.a = 6.0;  // assign value to one variable and print out both 
   //this will show the garbage values for the unused variable in the union
   printf("aNumber1.a = %f\n", aNumber1.a);
   printf("aNumber1.b = %d\n", aNumber1.b);
   printf("sizeof union = %ld\n", sizeof(aNumber1));    

   aNumber1.b = 5;
   printf("\naNumber1.a = %f\n", aNumber1.a);
   printf("aNumber1.b = %d\n", aNumber1.b);
   printf("sizeof union = %ld\n", sizeof(aNumber1));    
   
   aNumber2.a = 6.0; //display that a struct will give an unassigned value 0
   printf("\naNumber2.a = %f\n", aNumber2.a);
   printf("aNumber2.b = %d\n", aNumber2.b);
   printf("sizeof struct = %ld\n", sizeof(aNumber2));    
   
   aNumber2.b = 5;
   printf("\naNumber2.a = %f\n", aNumber2.a);
   printf("aNumber2.b = %d\n", aNumber2.b);
   printf("sizeof struct = %ld\n", sizeof(aNumber2));

   band beatles[4]; // initialize array of typedef band
  
   strncpy(beatles[0].f_name, "John", 4);
   strncpy(beatles[0].l_name, "Lennon", 6);
   beatles[0].year = 1940;
     
   strncpy(beatles[1].f_name, "Paul", 4);
   strncpy(beatles[1].l_name, "McCartney", 9);
   beatles[1].year = 1942;

   strncpy(beatles[2].f_name, "George", 6);
   strncpy(beatles[2].l_name, "Harrison", 8);
   beatles[2].year = 1943;

   strncpy(beatles[3].f_name, "Ringo", 5);
   strncpy(beatles[3].l_name, "Starr", 5);
   beatles[3].year = 1940;
     

   //for loop through array and print out 'John Lennon born 1940'
   int i;
   for( i = 0; i < 4; i++ ) {
      printf("\n%s %s born %d", beatles[i].f_name, beatles[i].l_name, beatles[i].year); 
   }
   printf("\n");
   
   char runOnString[1024];
   for ( i = 0; i < 4; i++ ) {
      strncat(runOnString, beatles[i].f_name, 6);
   }
   printf("\nRun on string of first names: %s\n", runOnString);
   
   char base[5];
   strncpy(base, beatles[3].f_name, 5);//copy Ringo to temp string
   for ( i = 0; i < 4; i++ ) {
      if (strcmp(base, beatles[i].f_name) == 0)//compare w temp string and if matches
         printf("The Ringo index is %d\n", i);//print out the index where Ringo was found
   }

} 

