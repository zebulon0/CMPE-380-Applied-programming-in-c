//  This fills ram with +3 sequential integers
//  student file
//
//   gcc -g -O0 -std=c99 hw13.c -lpthread -o hw13 -Wall -pedantic
//  valgrind --tool=memcheck --leak-check=yes ./hw13 -f -s
// 02/14/2021  R. Repka    Minor changes
                                                            

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <getopt.h>
#include <pthread.h>
#define EN_TIME
#include "Timers.h"
#include "ClassErrors.h"

/*--------------------------------------------------------------------------
  Local data structures and defines 
--------------------------------------------------------------------------*/
// Use the larger data size of the Linux cluster, smaller for
// a typical PC. 
// guarantees divisible by 2/3/4/5/7/8  Note: this number is VERY large
// and MAY cause overflow issues so order of operations will be 
// important.  aka    a*b/c  needs to be written as a*(b/c)  because
// it results in a smaller intermediate value 
#define DATA_SIZE           (136*3*5*7*146*512)
#define VALGRIND_DATA_SIZE  (30*3*5*7*8*1024)


// Maximum number of threads 
#define MAX_THREADS     (8)

// The number of iterations to slow down thread execution
#define DELAY_LOOPS_EXP        (5)     

// The percentage rate to update thread progress
#define STATUS_UPDATE_RATE (10)

// The number to divide by to get segSize in KB
#define KB (1024)

// Thread information control structure 
  struct ThreadData_s {
     int threadID;      // Contains the thread ID number 0..n
     int segSize;       // The amount of total work for this thread
                        // threadID*segSize is the starting index of
                        // the data to initialize
     unsigned *dataPtr; // Pointer to the one contagious array buffer
                        // that each thread will work on
     int trackStatus;   // Flag to identify if status updates should be reported
     int verbose;       // Flag to indicate if the task should run in verbose mode
  };

  
/* Function prototypes */
void *do_process(void *data);

/* Used to control access to the progress counter */
int taskRC[MAX_THREADS]; 	// return codes for each thread
pthread_mutex_t lock;	 	// mutex lock
volatile int progress = 0;	// global variable


int main(int argc, char *argv[]) {
   /*------------------------------------------------------------------------
     General purpose variables 
   ------------------------------------------------------------------------*/
   DECLARE_TIMER(timer); 
   time_t  wallTime;    // Used to report wall execution time.
   int *inData;		// 1D Array of ints
   int i;		// iterator for for loops
   
   /*------------------------------------------------------------------------
     Thread process information
   ------------------------------------------------------------------------*/
   void *rcp; 	// used for thread return code checking and printing
   pthread_t threadProcess[MAX_THREADS];	// array of all threads
   struct ThreadData_s data[MAX_THREADS];	// used for thread communication

   
   /*------------------------------------------------------------------------
      UI variables with sentential values
   ------------------------------------------------------------------------*/
   //DECLARE INPUT VARS HERE
   int verbose = 0;
   int status = 0;
   int threads = 0;
   int dataSize = DATA_SIZE; // Initialize to large size unless 
			     // specified otherwise
   int option_index = 0;
   int rc;
   char *getoptOptions = "t:sfv";

   /*------------------------------------------------------------------------
     These variables are used to control the getopt_long_only command line 
     parsing utility.  
   ------------------------------------------------------------------------*/
   struct option long_options[] = {
      {"threads", required_argument, 0, 't'},
      {"status",  no_argument,       0, 's'},
      {"stat",    no_argument,       0, 's'},
      {"fast",    no_argument,       0, 'f'},
      {"verbose", no_argument,       0, 'v'},
      {"verb",    no_argument,       0, 'v'},
      {0, 0, 0, 0}
   };

   opterr = 1;
   while ((rc = getopt_long_only(argc, argv, getoptOptions, long_options,
                                 &option_index)) != -1) {
      switch (rc) {
         case 't':
            threads = atoi(optarg);
            break;

         case 's':
            status = 1;
            break;

         case 'f':
            dataSize = VALGRIND_DATA_SIZE;
            break;

         case 'v':
            verbose = 1;
            break;

         default:
            printf("internal error: undefined option %0xX\n", rc);
            exit(PGM_INTERNAL_ERROR);
      }/* end switch */
   }/* end while */

   /*------------------------------------------------------------------------
     Check for command line syntax errors
   ------------------------------------------------------------------------*/
   if ((optind < argc) || (threads < 1) || (threads > MAX_THREADS)){
      fprintf(stderr, "This program demonstrates threading performance.\n");
      fprintf(stderr, "usage: hw13 -t[hreads] num [-s[tatus]] [-f[ast]] [-v[erbose]] \n");
      fprintf(stderr, "Where: -t[hreads] num - number of threads 1 to %d,required\n", MAX_THREADS);
      fprintf(stderr, "       -s[tatus]      - display thread progress, optional\n"); 
      fprintf(stderr, "       -v[erbose]     - verbose flag, optional\n");
      fprintf(stderr, "       -f[ast]        - shorter run for Valgrind, optional\n");
      fprintf(stderr, "eg: hw13 -t 3 -status\n");
      fflush(stderr);
      return(PGM_SYNTAX_ERROR);
   } /* End if error */

   /* Get space for the data */
   inData = malloc( dataSize * sizeof(int) );
   if ( inData == NULL ) {
      printf("Error: While trying to malloc for data\n");
      exit( MALLOC_ERROR );
   }

   //setup mutex 
   if ( pthread_mutex_init(&lock, NULL) != 0 ) {
      printf("Mutex init failed.\n");
      return 1;
   }/* End if */   

   // Print message before starting the timer
   printf("\nStarting %d threads generating %d numbers\n\n", threads, dataSize);   

   /* On your mark, get set... Go! */
   START_TIMER(timer);
   wallTime = time(NULL);
 
   
   // Spin up N threads
   for(i = 0; i < threads; i++) {
      // Build the thread specific information
      data[i].threadID = i;
      data[i].segSize	= dataSize/threads;
      data[i].dataPtr 	= (unsigned *)&inData[ i * (dataSize/threads) ];
      data[i].trackStatus = status;
      data[i].verbose 	= verbose;
              
      // Start the thread
      rc = pthread_create(&threadProcess[i], NULL, do_process, &data[i]);
      if ( rc ) {
         printf("Thread failed to start rc= %d\n", rc);
         exit(99);
      }/* End if */
 
      if ( verbose ) {
         fprintf(stdout, "Thread:%d  ID:%ld started\n", i, (unsigned long int)threadProcess[i]);}
   } // End threads  
 
   /* Print out the progress status */
   while( (status) && (progress < dataSize) ) {
      sleep(2);
      pthread_mutex_lock(&lock);
      fprintf(stdout, "Processed:%10d lines %3.0f%% complete\n", 
              progress, 100.0 * ((float)progress/(float)dataSize));
      fflush(stdout);
      pthread_mutex_unlock(&lock);
   }/* End While */


   /* Wait for all processes to end */
   for(i = 0; i< threads; i++) {
      rc = pthread_join(threadProcess[i], &rcp);

      if ( verbose ) {
         fprintf(stdout, "Task %d join %d, task rc %d\n", i, rc, *(int *)rcp);
         fflush(stdout);
      }/* End if */
   } // End threads  
   
   /* Take care of the timer stuff */
   STOP_TIMER(timer);
   wallTime = time(NULL) - wallTime;

   /* Print out timer stuff */
   PRINT_TIMER(timer);
   fprintf(stderr, "Total wall time = %d sec\n", (int)wallTime);
      

   printf("Verifying results...  ");
   for (unsigned i = 0; i < dataSize; i++) {
       if (inData [i] != 3*i) {
         printf("Error inData[%d]= %d != %d\n", i, inData[i], 3*i); 
          exit(PGM_INTERNAL_ERROR);}
   } // End verification
   printf("success\n\n");

   
   // Clean up
   free(inData);
   pthread_exit(&taskRC);
   return(0);
} // End main

   
/****************************************************************************
  This threading process will initialize parts of a very large array by 3's
  It contains code to SLOW execution down so that status updates can be easily
  seen.  The function prototype is defined by pthread so we MUST use it.
  
  void *do_process(void *data)
  Where: void *data - pointer to some user defined data structure
                      We will use struct ThreadData_s
  Returns: void *   - pointer to some user defined return code structure
                      We will use an integer array
  Errors: none
 
****************************************************************************/
void *do_process(void *data) {

   /* Thread variables */
   struct ThreadData_s *thread = data;
   int verbose = thread->verbose;
   int status = thread->trackStatus;
   int segSize = thread->segSize;
   unsigned *dataPtr = thread->dataPtr;
   int taskID = thread->threadID;
   //Extra variables
   int i, start, dataCounted, tenth;
   tenth = STATUS_UPDATE_RATE * (segSize/100); //10% of the data per thread
   dataCounted = 0;		//counter for number of items counted in the array
   start = taskID * segSize; 	//base index for the thread to start at

   // Print out the thread status
   if (verbose) {
      fprintf(stdout, "Thread:%d  track status:%d  seg size:%dKB  data ptr:%p\n", 
              taskID, status, segSize/KB, (void*)dataPtr );
      fflush(stdout);
   } // End verbose
   
   // Process all the data in the portion of the array
   for (i = start; i < start+segSize; i++) {
      dataPtr [i-start] = 3*i;
     
      // Slow the CPU
      int delay = 1<<DELAY_LOOPS_EXP;
      while (delay) {
         delay--;
      }/* End While */
     
      // Track status if required
      if ( (status) && (dataCounted >= tenth) ) {
         pthread_mutex_lock(&lock);
         progress += dataCounted;
         pthread_mutex_unlock(&lock);
         dataCounted = 0; // prevent double counting
        
         // Print out the thread status if tracking status
         // Only print verbose when updating progress.
         if (verbose) {
            fprintf(stdout, "%d ", taskID);
            fflush(stdout);
         } // End verbose if
      }  // End if
      dataCounted ++;
   } // End for
  
   // There might be some status left to update
   if ( status ) {
      pthread_mutex_lock(&lock);
      progress += dataCounted;
      pthread_mutex_unlock(&lock);
   }/* End if */

   // Return the task ID number + 10
   taskRC[taskID] = taskID + 10;

   //might be return( &taskRC[*(int *)taskID] );
   return( &taskRC[taskID] );
} // End do_process

