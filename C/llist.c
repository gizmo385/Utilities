#include <stdlib.h>

#include "utils.h"
#include "llist.h"

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
Node *newNode( void* data, Node *next ) {
    Node *node = (Node *) malloc( sizeof(Node) );
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
LList *newList() {
    LList *list = (LList *) malloc( sizeof(LList) );
    list->size = 0;
    list->comparisonFunction = NULL;
    list->head = newNode( NULL, NULL );

    return list;
}

/*
 * Creates a list that starts with a NULL node.
 *
 * Arguments:
 * comparisonFunction -- A function pointer that can compare two elements and determine their
 *                       relative ordering.
 *
 * Returns:
 * The newly allocated linked list
 */
LList *newSortedList( int (*comparisonFunction)(void *, void *) ) {
    LList *list = newList();
    list->comparisonFunction = comparisonFunction;

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
    Node *node = listFind( list, data );
    Node *temp = newNode( node->data, node->next );

    node->data = data;
    node->next = temp;

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
    Node *node = listFind( list, data );

    if( (node != NULL) && (node->data != NULL) && (node->next != NULL) ) {
        void *nodeData = node->data;
        Node *temp = node->next;

        node->next = temp->next;
        node->data = temp->data;

        free( temp );
        list->size -= 1;

        return nodeData;
    } else {
        return NULL;
    }

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
Node *listFind( LList *list, void *data ) {
    Node *current = list->head;

    // Iterate over the list looking for our element
    if( list->comparisonFunction == NULL ) {
        while( current->next != NULL && current->data < data ) {
            current = current->next;
        }
    } else {
        int (*comparisonFunction)( void*, void *) = list->comparisonFunction;
        while( current->next != NULL && comparisonFunction(data, current->data) < 0 ) {
            current = current->next;
        }
    }

    return current;
}

/*
 * Frees the list and the nodes in the list
 *
 * Arguments:
 * list -- The list that is being freed
 */
void listFree( LList *list ) {
    Node *current = list->head;

    while( current != NULL ) {
        if( current->data != NULL ) {
            free( current->data );
        }

        Node *next = current->next;
        free( current );
        current = next;
    }

    free( list );
}
