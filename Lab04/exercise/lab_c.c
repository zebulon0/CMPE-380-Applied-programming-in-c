/****************************************************************************
 The purpose of this example is to exercise, using pointers
 
 student version 
 
 gcc -O1 -Wall -std=c99 -pedantic -g  lab_c.c -o lab_c
 valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./lab_c
 
 09/09/2019 R. Repka    Minor formatting changes
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*---------------------------------------------------------------------------
  These data structures are used to simulated a very simple linked list
---------------------------------------------------------------------------*/
typedef struct Node{
    int index;      
    struct Node *next;        
    char string[40];
} Node;

typedef struct {
    int nterms;      
    Node *front;         
} Wrapper;



// Function prototypes
void printList(Wrapper *wrapper_p);

int main(int argc, char *argv[]) {
   Wrapper *wrapper_p = (Wrapper *) malloc( sizeof(Wrapper) );
   Node *node_p = (Node *) malloc ( sizeof(Node) ); //node 1
   Node *temp_p = (Node *) malloc ( sizeof(Node) );; //node 2

   if (!wrapper_p || !node_p || !temp_p) {
      printf("Error trying to maloc... exiting");
      exit(-99);
   }
   
   //initialize nterms to zero
   wrapper_p->nterms = 0;
   wrapper_p->front = NULL;


   //NODE 1:  
   *node_p = (Node){1, NULL, "One"};
   wrapper_p->front = node_p;
   wrapper_p->nterms ++;
   printf("Printing 1 node linked list\n");
   printList(wrapper_p);


   //NODE 2:
   *temp_p = (Node){2, NULL, "Two"};
   node_p->next = temp_p;
   wrapper_p->nterms ++;
   printf("Printing 2 node linked list\n");
   printList(wrapper_p);

 
   // Clean up memory
   //
   printf("Clean up\n");

   free(temp_p);
   temp_p = NULL;

   free(node_p);
   node_p = NULL;

   free(wrapper_p);

   return 0;
}

// Walk the linked list and print the contents 
void printList(Wrapper *wrapper_p) {
   Node *temp;
   temp = wrapper_p->front;

   while ( temp != NULL ) {
      printf("Node %d contains the string '%s'\n", temp->index, temp->string);     
      temp = temp->next;
   }
   printf("\n");
}

