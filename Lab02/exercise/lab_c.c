/****************************************************************************
Lab 2 student file
 
 To enable gdb logging
   gdb <binary>
   set logging file <file>
   set logging overwrite on
   set logging on
   
         gcc -std=c99  -g -O0 lab_d.c -o lab_d
         
 10/05/2019 R. Repka    Initial release
****************************************************************************/
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>


int main(int argc, char *argv[]) {
   char *text_p;        // do not change
      
   /*------------------------------------------------------------------------
     Add code here
   ------------------------------------------------------------------------*/
   text_p = (char*) malloc(12 * sizeof(char));  //allocate 12 bytes of memory
   if (text_p != NULL) {
      printf("memory allocation was successful.\n"); 
   }
   else {
      printf("Memory allocation failed! text_p == NULL\n");
      return -1;
   }
 
   strncpy(text_p, "CMPE380 lab malloc try 1.", 12);
   printf("'%s'\n", text_p); 

   text_p = (char*) realloc(text_p, 20 * sizeof(char));  //resize to 20 bytes of memory
   if (text_p != NULL) {
      printf("memory resize to 20 bytes was successful.\n"); 
   }
   else {
      printf("Memory resize to 20 bytes failed! text_p == NULL\n");
      return -1;
   }

   char concat[10];
   strncpy(concat, "-- Realloc", 10);//create new safe string
   strncat(text_p, concat, 20 - strlen(text_p));
   printf("'%s'\n", text_p);

   free(text_p);
   text_p = NULL;
   printf("Freed memory. text_p = '%s'\n", text_p);
 
}
