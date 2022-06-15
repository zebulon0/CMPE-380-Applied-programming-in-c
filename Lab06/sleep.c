/*---------------------------------------------------------------------------
  sleep.c - student file
  01/01/2016    R. Repka    This code is only used to verify your timing macros
  02/202016     R. Repka    Added include file hint
  10/21/2018    R. Repka    Added time.h
---------------------------------------------------------------------------*/
#include <unistd.h>
#include <stdio.h>
#include <time.h>
/* add other include files as necessary */
#include "Timers.h"

int main()
   {
   clock_t end_t;
   int delay;
   printf("Start\n");

   /* Your macro stuff here */
   START_TIMER(FuncTime);
   DECLARE_REPEAT_VAR(repeat);
   BEGIN_REPEAT_TIMING(2, repeat);
  
   /* wait for 60 seconds */
   end_t = clock() + 60 * CLOCKS_PER_SEC;
   while (end_t > clock())
      {
      /* Consume CPU time */
      delay = 1<<19;
      while (delay) 
         {
         delay--;
         }
      }
   
   /* more of your macro stuff */   
   END_REPEAT_TIMING;
   STOP_TIMER(FuncTime);
   PRINT_TIMER(FincTime);
   PRINT_RTIMER(FuncTime, 2);
  
   printf("End\n");
   return 0;
}
