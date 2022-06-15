/****************************************************************************
 The purpose of this example is to exercise using data and function pointers.
 It also demonstrates the value of using NULL assignments to identify pointer
 issues.
 
 student version 
 
 
 gcc -O1 -Wall -std=c99 -pedantic -g  lab_b.c -o lab_b
 valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./lab_b
 
 
 09/09/2019 R. Repka    Minor formatting changes
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { 
   int entry;
   char string [40];
} Data;

int fun2x(int num);
int fun3x(int num);

Data ramData;


int main(int argc, char *argv[]) {
   int(*function_p)(int);
   int answer;
   Data stackData;
   static Data staticData;
   Data *heapData_p;


   //Allocate space for heapData_p
   heapData_p = (Data *) malloc ( 1 * sizeof(Data) );
   if ( heapData_p == NULL ){
      printf("Error when trying to allocate memory for 'heapData_p'.. Exiting");
      exit(-99);
   }

   
   // "Program 0x40074d"
   printf("Program %8p\n", main);

   // "Static data 0x6010a0"
   printf("Static data %8p\n", &staticData);
  
   // "Ram data 0x6010e0"
   printf("Ram data %8p\n", &ramData);

   // "Heap data 0xe56010
   printf("Heap data %8p\n", heapData_p);

   // "Stack data 0x7ffff2f43340"
   printf("Stack data %8p\n", &stackData);
           
 
 
   // Using function pointers
   //
   // "Passing the 2X function a 2, I got 4"
   function_p = fun2x;
   answer = function_p(2);
   printf("Passing the 2X function a 2, I got a %d\n", answer);  
  

   // "Passing the 3X function a 2, I got 6"
   function_p = fun3x;
   answer = function_p(2);
   printf("Passing the 3X function a 2, I got a %d\n", answer);  
  
 


   // Initialize the stack data
   //char stackString[40] = "Stack";
   stackData.entry = 1;
   strncpy(stackData.string, "Stack", sizeof(stackData.string));
   //
   // "Stack data values before free: 1 'Stack'"
   printf("Stack data values before free: %d '%s'\n", stackData.entry, stackData.string);

    
   // Initialize the heap data
   //char heapString[40] = "Pointer";
   heapData_p->entry = 2;
   strncpy(heapData_p->string, "Pointer", sizeof(heapData_p->string));
   //
   // "Heap data values before free: 2 'Pointer'"
   printf("Heap data values before free: %d '%s'\n", heapData_p->entry, heapData_p->string);


   // Free the heapData_p but DO NOT SET TO NULL
   free(heapData_p);
   heapData_p = NULL;    
 
   // Re-print the "heapData_p" data as shown above
   // "Heap data values after free: <could be anything>"
   printf("Heap data values after free: %d '%s'\n", heapData_p->entry, heapData_p->string); 



   return 0;
}


int fun2x(int num) {
   return(num*2);
}
int fun3x(int num) {
   return(num*3);
}


