#ifndef LLIST_H
#define LLIST_H

#include "functions.h"

/**************************************************************************************************
 * Structure and type definitions
 *************************************************************************************************/

/*
 * A list node is contains a reference to the data contained within the node and the node that comes
 * immediately after itself. It contains the following fields:
 *
 * data -- A reference to the data that is contained within this node
 * next -- The node that comes immediatley after this node (or NULL if none is present)
 */
typedef struct ListNode {
    void *data;
    struct ListNode *next;
} ListNode;

/*
 * A linked list is a data structure where each node knows that the data that is contains and has
 * a reference to the node that immediately follows it. It contains the following fields:
 *
 * head -- The first node in the list
 * size -- The number of nodes in the list
 * comparisonFunction -- A function which can be used to compare node data
 */
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
