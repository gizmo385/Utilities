#include <stdlib.h>
#include <time.h>

#include "set.h"
#include "utils.h"

/* Test functions */
void testNewSet();
void testSetAdd();
void testSetRemove();
void testIsInSet();
void testSetUnion();
void testSetIntersect();
void testSetMapping();

/* Functions used in testing */
int *mallocInt( int a );
int comparisonFunction( void *aPtr, void *bPtr);
int *increment(int *x);

int main( int argc, char *argv[] ) {
    setDebuggingLevel( E_ERROR );
    srand( time(NULL) );
    testNewSet();
    testSetAdd();
    testSetRemove();
    testIsInSet();
    testSetMapping();
    /*testSetUnion();*/
    /*testSetIntersect();*/
}

void testNewSet() {
    Set *set = newSet(comparisonFunction);
    setFree(set);
}

void testSetAdd() {
    Set *set = newSet(comparisonFunction);
    const int numElements = 50;

    // Test basic insertion
    for( int i = 0; i < numElements; i++ ) {
        int *newValue = mallocInt(i);
        setAdd( set, newValue );
    }

    assertTrue( numElements == set->size, "Set size should be %d\n", numElements );

    // Test that you can't add duplicates
    for( int i = 0; i < numElements; i++ ) {
        int *newValue = mallocInt(i);
        setAdd( set, newValue );
        free(newValue);
    }

    assertTrue( numElements == set->size, "Set size should be %d\n", numElements );
    setFree(set);
}

void testSetRemove() {
    Set *set = newSet(comparisonFunction);
    const int numElements = 50;
    const int numElementsToRemove = 20;

    // Insert the elements
    for( int i = 0; i < numElements; i++ ) {
        int *newValue = mallocInt(i);
        setAdd( set, newValue );
    }

    // Remove some elements
    for( int i = 0; i < numElementsToRemove; i++ ) {
        int *elementToRemove = mallocInt(i);
        setRemove( set, elementToRemove );

        assertFalse( isInSet(set, elementToRemove), "%d should not be in the set!\n",
                *elementToRemove );
        free( elementToRemove );
    }

    // Ensure that non-removed elements are still present
    for( int i = numElementsToRemove; i < numElements; i++ ) {
        int *elementToFind = mallocInt(i);
        assertTrue( isInSet(set, elementToFind), "Couldn't find %d in the set!\n", *elementToFind );
        free( elementToFind );
    }

    assertTrue( set->size == (numElements - numElementsToRemove), "Size of the set should be %d, was %d\n",
            (numElements - numElementsToRemove), set->size );

    setFree( set );
}

void testIsInSet() {
    Set *set = newSet(comparisonFunction);
    const int numElements = 50;

    // Insert the elements
    for( int i = 0; i < numElements; i++ ) {
        int *newValue = mallocInt(i);
        setAdd( set, newValue );
    }

    // Test that the inserted elements can be found
    for( int i = 0; i < numElements; i++ ) {
        int *intToFind = mallocInt(i);
        assertTrue( isInSet(set, intToFind), "Could not find %d in the set!", *intToFind );
        free( intToFind );
    }

    // Test that non-inserted elements cannot be found
    int *intToFind = mallocInt( numElements );
    assertFalse( isInSet(set, intToFind), "Found %d in the set!", *intToFind );
    free( intToFind );

    setFree( set );
}

void testSetUnion() {
    //TODO
}

void testSetIntersect() {
    //TODO
}

void testSetMapping() {
    Set *set = newSet(comparisonFunction);
    const int numElements = 50;

    // Insert the elements
    for( int i = 0; i < numElements; i++ ) {
        int *newValue = mallocInt(i);
        setAdd( set, newValue );
    }

    Set *mapResult = setMap( set, (MapFunction) increment, NULL );
    for( int i = 1; i <= numElements; i++ ) {
        int *elementToFind = mallocInt(i);
        assertTrue( isInSet(mapResult, elementToFind), "%d should be in the map result!" );
        free( elementToFind );
    }

    setFree( mapResult );
    setFree( set );
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

int *increment(int *x) {
    int *result = malloc( sizeof(int) );
    *result = (*x) + 1;
    return result;
}
