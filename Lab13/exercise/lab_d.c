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
int taskRC[3];
pthread_mutex_t lock;
volatile int processed = 0;

int main(int argc, char *argv[]) { 
   // Thread data structure
   pthread_t thread_id, thread_id2, thread_id3; 
   
   // Pointer to the process return code, used later
   void *rcp;
   
   // Process index id number 
   int num[3] = {1, 2, 3};  
   int rc;

   // start clock
   time_t start = time(NULL);

   // initialize mutex lock
   if (pthread_mutex_init(&lock, NULL) != 0) {
      printf("Mutex init failed.\n");
      return 1;
   }



   printf("Main: Starting thread...\n"); 
   // Student should add the thread create call here
   rc = pthread_create( &thread_id, NULL, mySimpleThread, &num[0] ); 
   if (rc) {
      printf("Thread failed to start rc= %d\n", rc);
      exit(99);
   } // End if rc

   rc = pthread_create( &thread_id2, NULL, mySimpleThread, &num[1] ); 
   if (rc) {
      printf("Thread failed to start rc= %d\n", rc);
      exit(99);
   } // End if rc

   rc = pthread_create( &thread_id3, NULL, mySimpleThread, &num[2] ); 
   if (rc) {
      printf("Thread failed to start rc= %d\n", rc);
      exit(99);
   } // End if rc
   printf("Main: All threads started...\n"); 

 
   // Print status in the main routine 
   for (int i = 0; i < 10; i++){
      printf("Main will sleep 1 second. \n"); 
      printf("processed = %d\n", processed);
      sleep(1); 
   }






   // Student should add wait for the thread to finish
   // when instructed. Always check the join RC as you
   // may get memory leaks otherwise.
   rc = pthread_join(thread_id, &rcp);
   if (rc) {
      printf("Thread failed to start rc= %d\n", rc);
      exit(99);
   } // End if rc
   printf("Value of rcp = %d\n", *(int *)rcp);

   rc = pthread_join(thread_id2, &rcp);
   if (rc) {
      printf("Thread failed to start rc= %d\n", rc);
      exit(99);
   } // End if rc
   printf("Value of rcp = %d\n", *(int *)rcp);

   rc = pthread_join(thread_id3, &rcp);
   if (rc) {
      printf("Thread failed to start rc= %d\n", rc);
      exit(99);
   } // End if rc
   printf("Value of rcp = %d\n", *(int *)rcp);

   






   // stop time
   time_t end = time(NULL);
   
   printf("wall time = %ds\n", end-start);
   printf("Exiting main thread\n");
   taskRC[0] = 0;
   taskRC[1] = 0;
   taskRC[2] = 0;
   pthread_exit(&taskRC);
}

/*---------------------------------------------------------------------------
  A thread that prints out it's ID number and sleeps in a loop,
  printing status
---------------------------------------------------------------------------*/
void *mySimpleThread(void *num) { 
   for (int i = 0; i < 6; i++){
      pthread_mutex_lock(&lock);
      processed++;
      pthread_mutex_unlock(&lock);

      printf("     Thread %d, will sleep 1 second.\n", *(int *)num); 
      sleep(1); 
   }
   taskRC[*(int *)num-1] = *(int *)num;
   return(&taskRC[*(int *)num-1]); 
} 
