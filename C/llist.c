#include <stdio.h>
#include <stdlib.h>

#include "llist.h"
#include "utils.h"

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
ListNode *newListNode( void* data, ListNode *next ) {
    ListNode *node = malloc( sizeof(ListNode) );
    node->data = data;
    node->next = next;

    return node;
}

/*
 * Creates a list that starts with a NULL node.
 *
 * Returns:
 * The newly allocated linked list
 */
LList *newList( ComparisonFunction comparisonFunction ) {
    LList *list = malloc( sizeof(LList) );
    list->size = 0;
    list->head = newListNode(NULL, NULL);

    if( comparisonFunction != NULL ) {
        list->comparisonFunction = comparisonFunction;
    }

    return list;
}

/*
 * Inserts the element into the list.
 *
 * Arguments:
 * list -- The to add the element into
 * data -- The data to be added into the list
 */
void listInsert( LList *list, void *data ) {
    // You cannot insert NULL into the list
    if( data == NULL ) {
        return;
    }

    ListNode *current = list->head;
    ComparisonFunction compare = list->comparisonFunction;

    // Determine where the data will be inserted
    while( current->next != NULL && compare(current->data, data) < 0 ) {
        current = current->next;
    }

    // Insert the element
    ListNode *tempNode = newListNode( current->data, current->next );
    current->data = data;
    current->next = tempNode;
    list->size += 1;
}

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
void *listRemove( LList *list, void *data ) {
    // You cannot remove NULL from the list
    if( data == NULL ) {
        return NULL;
    }

    ListNode *current = list->head;
    ComparisonFunction compare = list->comparisonFunction;

    // Determine where the data will be inserted
    while( current->next != NULL && compare(current->data, data) != 0 ) {
        current = current->next;
    }

    // Remove the element
    void *elementRemoved = current->data;
    ListNode *temp = current->next;
    current->data = temp->data;
    current->next = temp->next;

    free( temp );

    list->size -= 1;
    return elementRemoved;
}

/*
 * Searchs for and returns the element in the list
 *
 * Arguments:
 * list -- The list to traverse in search for the desired element
 * data -- The data to search for in the list
 *
 * Returns:
 * The Node containing the desired data, or NULL if it can't be found
 */
ListNode *listFind( LList *list, void *data ) {
    ListNode *current = list->head;
    ComparisonFunction compare = list->comparisonFunction;

    while( current->next != NULL && compare( current->data, data ) != 0 ) {
        current = current->next;
    }

    // If the data in current isn't equal to the data we're trying to find, return NULL
    if( compare( current->data, data ) != 0 ) {
        return NULL;
    } else {
        return current;
    }
}

/*
 * Frees the list and the nodes in the list
 *
 * Arguments:
 * list -- The list that is being freed
 */
void listFree( LList *list ) {
    ListNode *current = list->head;

    // Free the nodes along the list
    while( current->next != NULL ) {
        ListNode *next = current->next;
        free( current->data );
        free( current );
        current = next;
    }

    // Free the last node and the list
    free( current->data );
    free( current );
    free( list );
}
