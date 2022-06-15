/******************************************************************************
 An student framework implementation of doubly linked lists that holds 
 elements containing a 256 character string and a sequence number.
 12/24/2017 - R. Repka     Removed AddToFrontOfLinkedList()
 03/12/2018 - R. Repka     Added pseudo code 
 09/17/2019 - R. Repka     fixed minor prototype errors 
 09/26/2019 - R. Repka     Added comments to RemoveFromFrontOfLinkedList()
 10/01/2019 - R. Repka     Changed search function to int
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ClassErrors.h"
#include "LinkedLists.h"


/******************************************************************************
  Use the following pseudo code to help with all the functions in this module
  
  add 1st node
    LinkedList front = points to node 1,  LinkedList back = points to node 1
      Node 1 next     = NULL  (at the end)
      Node 1 previous = NULL (at the start)
          
  add 2nd node
    LinkedList front = points to node 1,  LinkedList back = points to node 2
      Node 1 next points to node 2             Node 2 next   = NULL  (at the end)
      Node 1 previous = NULL (at the start)    Node 2 previous points to node 1

  add 3rd node
  LinkedList front = points to node 1,  LinkedList back = points to node 3
      Node 1 next points to node 2           Node 2 next points to node 3      Node 3 next   = NULL  (at the end)
      Node 1 previous = NULL (at the start)  Node 2 previous points to node 1  Node 3 previous points to node 2
      
   Note: It is possible to implement with only 2 special cases 
      
   Remove from front of 3 node list 
    save the pointer to the data and return it at the end
    LinkedList front = points to node 2,  LinkedList back = points to node 3
      Node 2 next points to node 3           Node 3 next   = NULL  (at the end)
      Node 2 previous = NULL (at the start)  Node 3 previous points to node 2
      free Node but NOT the data
******************************************************************************/

/******************************************************************************
 Initialize the linked list data structure.  Points to nothing, no entries.

 Where: LinkedLists *ListPtr - Pointer to the linked list to create
 Returns: nothing
 Errors: none
******************************************************************************/
void InitLinkedList(LinkedLists *ListPtr)
{ 
   ListPtr->NumElements = 0; //init NumElements
   ListPtr->FrontPtr = NULL; //init FrontPtr
   ListPtr->BackPtr = NULL; //init Back Ptr

} /* InitLinkedList() */


/******************************************************************************
 Adds a node to the back of the list.

 Where: LinkedLists *ListPtr    - Pointer to the linked list to add to
        char *DataPtr - Pointer to the data to add to the list
 Returns: nothing
 Errors: Prints to stderr and exits
******************************************************************************/
void AddToBackOfLinkedList(LinkedLists *ListPtr, char *DataPtr)
{
   LinkedListNodes *NodeToAdd;
   NodeToAdd = (LinkedListNodes*) malloc( sizeof(LinkedListNodes) );
   if ( NodeToAdd == NULL ) {
      printf("Error trying to malloc: NodeToAdd");
      exit(MALLOC_ERROR);
   }
   
   NodeToAdd->Next = NULL; //New node's next is NULL b/c last node on list
   
   /* Previous node for the new node is the 
      current back node of the LL */
   NodeToAdd->Previous = ListPtr->BackPtr;

   strncpy(NodeToAdd->String, DataPtr, MAX_BUFF_LEN);
   ListPtr->BackPtr = NodeToAdd; //have the list point to the new Back node

   // If the linked list is empty...
   // set the front to the node that is being added
   if ( ListPtr->NumElements == 0 ) { ListPtr->FrontPtr = NodeToAdd; }
   
   // If the linked list isn't empty...
   // link the last node's next pointer to the node being
   // added
   else { (NodeToAdd->Previous)->Next = NodeToAdd; }
   
   ListPtr->NumElements ++; //update number of nodes in LL

} /* AddToBackOfLinkedList */

/******************************************************************************
 Removes a node from the front of the list and returns a pointer to the node
 data removed. On empty lists should return a NULL pointer.  
 Note: You will need to malloc a string buffer and copy the data from the
       linked list node before destroying the node.  The calling routine was
       written to free the string so there are no memory leaks

 
   Linked lists contain nodes, which contain data strings
 
 Where: LinkedLists *ListPtr    - Pointer to the linked list to remove from
 Returns: Pointer to the data removed or NULL for none
 Errors: none
******************************************************************************/
char *RemoveFromFrontOfLinkedList(LinkedLists *ListPtr) {
   char *Data = malloc ( sizeof(char) * MAX_BUFF_LEN ); //string from the front node that is removed
   LinkedListNodes *NodeToRemove; //front node that is removed
   if ( Data == NULL ) { //error check
      printf("Error trying to malloc: Data");
      exit(MALLOC_ERROR);
   }
   

   switch( ListPtr->NumElements ) {
      //list is empty -> error -> return null
      case 0:
         free(Data);
         return NULL;
         break;

      //only 1 node in list -> remove and set list to init state
      case 1:
         NodeToRemove = ListPtr->FrontPtr;
         strncpy(Data, NodeToRemove->String, MAX_BUFF_LEN);
         ListPtr->FrontPtr = NULL;
         ListPtr->BackPtr = NULL;
         free(NodeToRemove);
         NodeToRemove = NULL;
         ListPtr->NumElements --;
         return Data;
         break;

      //2+ nodes in list -> remove front node, update pointers, update numElements
      default:
         NodeToRemove = ListPtr->FrontPtr;
         strncpy(Data, NodeToRemove->String, MAX_BUFF_LEN);
         ListPtr->FrontPtr = NodeToRemove->Next;
         (ListPtr->FrontPtr)->Previous = NULL;
         free(NodeToRemove);
         NodeToRemove = NULL;
         ListPtr->NumElements --;
         return Data;
         break;

   }
} /* RemoveFromFrontOfLinkedList() */


/******************************************************************************
 De-allocates the linked list and resets the struct fields (in the header) 
 to indicate that the list is empty.  
 
 If you choose to use the RemoveFromFrontOfLinkedList() function, remember 
 the calling routine must free the returned pointer so there are no memory leaks
       
 Where: LinkedLists *ListPtr    - Pointer to the linked list to destroy
 Returns: nothing
 Errors: none
******************************************************************************/
void DestroyLinkedList(LinkedLists *ListPtr) {
   LinkedListNodes *Node = ListPtr->FrontPtr; //get first node to remove
  
   while ( Node != NULL ) { // while there are still nodes left
      ListPtr->FrontPtr = Node->Next;//set new front
      ListPtr->NumElements --;//decrement number of elements in list
      free(Node);
      Node = ListPtr->FrontPtr;//get the next node to remove
   }
} /* DestroyLinkedList() */


/******************************************************************************
 Searches the linked list for a provided word. If found, returns 1 otherwise 0
 
 Where: LinkedLists *ListPtr - Pointer to the linked list to search
        char *String         - Pointer to the string to search
 Returns: 1 if found, 0 otherwise
 Errors: none
 * ***************************************************************************/
int SearchList(LinkedLists *ListPtr, char *String)
{
/*-----  Don't implement this until instructed in a future lab ----*/
return 0;
} /* SearchList() */




