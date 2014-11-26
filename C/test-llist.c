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
    setDebuggingLevel( E_ERROR );
    testListCreation();
    testInserts();
    testListFind();
    testRemoval();

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
    // Create the list
    LList *list = newList( comparisonFunction );

    // Test the initial conditions of the list
    assertNotNull( list, "List should not be null!\n" );
    assertNotNull( list->head, "List head not be null!\n" );
    assertNotNull( list->comparisonFunction, "List comparisonFunction not be null!\n" );
    assertTrue( list->size == 0, "List size should be zero!\n" );

    // Free the list
    listFree( list );
}

void testInserts() {
    // Create the list
    LList *list = newList( comparisonFunction );
    const int numElements = 100;
    int prevSize = list->size;

    // Insert a bunch of elements into the list
    for( int i = 1; i <= numElements; i++ ) {
        listInsert( list, mallocInt(i) );
        assertTrue( (prevSize + 1) == list->size, "List size should have increased by 1\n" );
        prevSize++;
    }

    // Assert that the right number of elements are present in the list
    assertTrue( numElements == list->size, "List should now have %d elements, has %d\n",
            numElements, list->size );

    // Check that the ordering invariant holds
    Node *current = list->head;
    ComparisonFunction compare = list->comparisonFunction;
    int numElementsCompared = 0;
    while( current->next != NULL ) {
        void *nodeData = current->data;
        void *nextNodeData = current->next->data;

        // Segfault prevention check
        if( nodeData != NULL && nextNodeData != NULL ) {
            int comparisonResult = compare(nodeData, nextNodeData);
            assertTrue( comparisonResult < 0, "Assert comparisonResult < 0 failed! (Was %d)\n",
                    comparisonResult );

            numElementsCompared++;
        }

        current = current->next;
    }

    // Ensure that we made some value comparisons throughout the the loop
    assertTrue( numElementsCompared != 0, "Should haven't compared more than 0 elements!\n" );

    // Test insert at beginning
    listInsert( list, mallocInt( -1 ) );

    // Test insert at end
    listInsert( list, mallocInt( 1000 ) );

    // Free the list
    listFree( list );
}

void testListFind() {
    LList *list = newList( comparisonFunction );
    const int numElements = 1000;

    // Insert the elements
    for( int i = 0; i < numElements; i++ ) {
        listInsert( list, mallocInt(i) );
    }

    // Find the elements
    for( int i = 0; i < numElements; i++ ) {
        int *intToFind = mallocInt(i);

        // Ensure that the find didn't return null
        Node *findResult = listFind( list, intToFind );
        assertNotNull( findResult, "find(i) should not be NULL!\n" );

        // Ensure that the elements are equal
        int comparisonResult = list->comparisonFunction( intToFind, findResult->data );
        assertTrue( comparisonResult == 0, "find(%d)->data != %d\n", i, i );

        free( intToFind );
    }

    // Free the list
    listFree( list );
}

void testRemoval() {
    LList *list = newList( comparisonFunction );
    const int numElements = 1000;

    // Insert elements
    for( int i = 0; i < numElements; i++ ) {
        listInsert( list, mallocInt(i) );
    }

    // Remove the elements and ensure that the right elements were removed
    for( int i = 0; i < numElements; i++ ) {
        int *elementToRemove = mallocInt(i);
        int *removedElement = listRemove( list, elementToRemove );

        assertNotNull( removedElement, "removedElement is null!\n" );

        int comparisonResult = list->comparisonFunction( elementToRemove, removedElement );
        assertTrue( comparisonResult == 0, "compare(%d, %d) != 0\n", *elementToRemove,
                *removedElement );

        free( elementToRemove );
        free( removedElement );
    }

    // Free the list
    listFree( list );
}
