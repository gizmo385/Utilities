#ifndef LLIST_H
#define LLIST_H

#include "functions.h"

/**************************************************************************************************
 * Structure and type definitions
 *************************************************************************************************/

typedef struct ListNode {
    void *data;
    struct ListNode *next;
} ListNode;

typedef struct LList {
    ListNode *head;
    int size;
    ComparisonFunction comparisonFunction;
} LList;

/**************************************************************************************************
 * Constructor Functions
 *************************************************************************************************/

/*
 * Creates a new linked list node.
 *
 * Arguments:
 * data -- The data contained within the node
 * next -- The node that follows this node in the list
 *
 * Returns:
 * The newly allocated node
 */
extern ListNode *newListNode( void* data, ListNode *next );

/*
 * Creates a list that starts with a NULL node.
 *
 * Returns:
 * The newly allocated linked list
 */
extern LList *newList();

/**************************************************************************************************
 * Insertion functions
 *************************************************************************************************/

/*
 * Inserts the element into the list.
 *
 * Arguments:
 * list -- The to add the element into
 * data -- The data to be added into the list
 */
extern void listInsert( LList *list, void *data );

/**************************************************************************************************
 * Removal functions
 *************************************************************************************************/

/*
 * Removes the specified data element from the list
 *
 * Arguments:
 * list -- The list to remove the elements from
 * data -- The data to remove from the list
 *
 * Returns:
 * The element that was removed from the list
 */
extern void *listRemove( LList *list, void *data );

/**************************************************************************************************
 * Find functions
 *************************************************************************************************/

/*
 * Searchs for and returns the element in the list
 *
 * Arguments:
 * list -- The list to traverse in search for the desired element
 * data -- The data to search for in the list
 *
 * Returns:
 * The ListNode containing the desired data, or NULL if it can't be found
 */
extern ListNode *listFind( LList *list, void *data );

/**************************************************************************************************
 * Free functions
 *************************************************************************************************/

/*
 * Frees the list and the nodes in the list
 *
 * Arguments:
 * list -- The list that is being freed
 */
extern void listFree( LList *list );

#endif
