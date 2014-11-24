#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "utils.h"
#include "llist.h"

/* Function prototypes */
void testListCreation();
void testInserts();
void testListFind();
void testRemoval();

int main( int argc, char *argv[] ) {
    setDebugReporting( E_ALL );
    testListCreation();
    testInserts();
    testListFind();
    /*testRemoval();*/

    return 0;
}

int *mallocInt( int a ) {
    int *newInt = (int *) malloc( sizeof(int) );
    *newInt = a;

    return newInt;
}

int comparisonFunction( void *aPtr, void *bPtr) {
    int a = *((int *) aPtr);
    int b = *((int *) bPtr);

    if( a < b ) {
        return -1;
    } else if( a == b ) {
        return 0;
    } else {
        return 1;
    }
}

void testListCreation() {
    LList *list = newList();
    LList *sortedList = newSortedList( comparisonFunction );

    assertNotNull( list, "List should not be null!\n" );
    assertNull( list->comparisonFunction, "The unsorted list does not have a comparison function!\n" );

    assertNotNull( sortedList, "List should not be null!\n" );
    assertNotNull( sortedList->comparisonFunction, "The unsorted list has a comparison function!\n" );

    listFree( list );
    listFree( sortedList );
}

void testInserts() {
    const int numElements = 10;

    // Test unsorted list additions
    LList *list = newList();

    srand( time(NULL) );
    for( int i = 0; i < numElements; i++ ) {
        listInsert( list, mallocInt( rand() ) );
    }

    assertTrue( list->size == numElements, "The list should have %d elements!\n", 20 );
    Node *current = list->head;

    // Traverse the list and ensure that none of the nodes are NULL
    int elementsHit = 0;
    while( current->next != NULL ) {
        assertNotNull( current, "The element @ %p should not be NULL!\n", current );
        current = current->next;
        elementsHit++;
    }

    // Ensure that we traversed the correct number of elements
    assertTrue( elementsHit == numElements, "Only hit %d elements!\n", elementsHit );
    listFree( list );
}

void testListFind() {
    const int numElements = 20;
    LList *list = newList();

    for( int i = 0; i < numElements; i++ ) {
        listInsert( list, mallocInt(i) );
    }


    // Search for the elements
    for( int i = 0; i < numElements; i++ ) {
        int *temp = mallocInt( i );
        Node *result = listFind( list, temp );

        debug( E_DEBUG, "listFind(%d) result = %d\n", i, *((int *) result->data) );
    }

    listFree( list );
}

void testRemoval() {

}
