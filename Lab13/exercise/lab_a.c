/*---------------------------------------------------------------------------
  Create a single thread and use pthread_exit()  
  student copy
  
  gcc -g -std=c99 lab14a.c -lpthread -o lab14a
---------------------------------------------------------------------------*/
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> //For sleep().  
#include <pthread.h> //For threads
#include <time.h>

void *mySimpleThread(void *name);

// Global variables
int taskRC = -1;

int main(int argc, char *argv[]) { 
   // Thread data structure
   pthread_t thread_id; 
   
   // Pointer to the process return code, used later
   void *rcp;
   
   // Process index id number 
   int num = 1;
   
   int rc;

   printf("Main: Starting thread...\n"); 
   // Student should add the thread create call here
   rc = pthread_create( &thread_id, NULL, mySimpleThread, &num ); 
   if (rc) {
      printf("Thread failed to start rc= %d\n", rc);
      exit(99);
   } // End if rc
   printf("Main: All threads started...\n"); 

   // Student should add wait for the thread to finish
   // when instructed. Always check the join RC as you
   // may get memory leaks otherwise.
   
   
   // Print status in the main routine 
   for (int i = 0; i < 2; i++){
      printf("Main will sleep 1 second. \n"); 
      sleep(1); 
   }
   
   printf("Exiting main thread\n");
   taskRC = 0;
   pthread_exit(&taskRC);
}

/*---------------------------------------------------------------------------
  A thread that prints out it's ID number and sleeps in a loop,
  printing status
---------------------------------------------------------------------------*/
void *mySimpleThread(void *num) { 
   for (int i = 0; i < 6; i++){
      printf("     Thread %d, will sleep 1 second. \n", *(int *)num); 
      sleep(1); 
   }
   taskRC = 0;
   return(&taskRC); 
} 
