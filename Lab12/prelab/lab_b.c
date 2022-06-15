/*---------------------------------------------------------------------------
  This prints out argv and env variables 
  student copy
---------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[], char *env[]) {
   //your code here 
   printf("argc: %d\n", argc);

   for (int i = 1; i < argc; i++) {
      printf("argv[%d]: %s\n", i, argv[i]);
   } 
   
   int j = 0;
   while(env[j] != NULL) {
      printf("env[%d]: %s\n", j, env[j]);
      j++;
   }
   return 0;
}
