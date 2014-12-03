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
int *increment(int *x);
int comparisonFunction( int *aPtr, int *bPtr);
void printInt( int *number );

int main( int argc, char *argv[] ) {
    setDebuggingLevel( E_ERROR );
    srand( time(NULL) );
    testNewSet();
    testSetAdd();
    testSetRemove();
    testIsInSet();
    testSetMapping();
    testSetUnion();
    testSetIntersect();
}

void testNewSet() {
    Set *set = newSet( (ComparisonFunction) comparisonFunction);
    setFree(set);
}

void testSetAdd() {
    Set *set = newSet( (ComparisonFunction) comparisonFunction);
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
    Set *set = newSet( (ComparisonFunction) comparisonFunction);
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
    Set *set = newSet( (ComparisonFunction) comparisonFunction);
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
    const int numElements = 40; // Should be even
    Set *firstHalf = newSet( (ComparisonFunction) comparisonFunction );
    Set *secondHalf= newSet( (ComparisonFunction) comparisonFunction );

    //Insert the first half
    for( int i = 0; i < (numElements / 2); i++ ) {
        int *elementToAdd = mallocInt(i);
        setAdd( firstHalf, elementToAdd );
    }

    assertTrue( firstHalf->size == (numElements / 2), "There should be %d in the first half!\n",
            (numElements / 2) );

    // Insert the second half
    for( int i = numElements / 2; i < numElements; i++ ) {
        int *elementToAdd = mallocInt(i);
        setAdd( secondHalf, elementToAdd );
    }

    assertTrue( secondHalf->size == (numElements / 2), "There should be %d in the second half!\n",
            (numElements / 2) );

    // Union the first and second half to create the full set
    Set *unionResult = setUnion( firstHalf, secondHalf, NULL );
    assertTrue( unionResult->size == numElements, "There should %d in the union result!",
            numElements );

    for( int i = 0; i < numElements; i++ ) {
        int *elementToFind = mallocInt(i);
        assertTrue( isInSet(unionResult, elementToFind), "Could not find %d in union result!\n",
                *elementToFind );
        free( elementToFind );
    }

    setFreeStructure( firstHalf );
    setFreeStructure( secondHalf );
    setFree( unionResult );
}

void testSetIntersect() {
    // Testing bounds
    const int firstStart = 0;
    const int firstEnd = 20;
    const int secondStart = 10;
    const int secondEnd = 30;

    Set *first = newSet( (ComparisonFunction) comparisonFunction );
    Set *second = newSet( (ComparisonFunction) comparisonFunction );

    // Add elements to both sets
    for( int i = firstStart; i <= firstEnd; i++ ) {
        setAdd( first, mallocInt(i) );
    }

    for( int i = secondStart; i <= secondEnd; i++ ) {
        setAdd( second, mallocInt(i) );
    }

    Set *intersectionResult = setIntersect( first, second, NULL );

    // Test the intersection
    for( int i = firstEnd; i <= secondStart; i++ ) {
        int *element = mallocInt(i);
        assertTrue( isInSet( intersectionResult, element ), "Couldn't find %d in the intersection!", i );
        free(element);
    }

    setFreeStructure( intersectionResult );
    setFree( first );
    setFree( second );
}

void testSetMapping() {
    Set *set = newSet( (ComparisonFunction) comparisonFunction);
    const int numElements = 50;

    // Insert the elements
    for( int i = 0; i < numElements; i++ ) {
        int *newValue = mallocInt(i);
        setAdd( set, newValue );
    }

    // Map increment over the set
    Set *mapResult = setMap( set, (MapFunction) increment, NULL );
    for( int i = 1; i <= numElements; i++ ) {
        int *elementToFind = mallocInt(i);
        assertTrue( isInSet(mapResult, elementToFind), "%d should be in the map result!" );
        free( elementToFind );
    }

    // Print out the numbers. Should be 1 - numElements, inclusive.
    printf("Printing out set. Should be the numbers from 1 to %d inclusive:\n", numElements);
    setForEach( mapResult, (ElementConsumer)printInt );
    printf("\n");

    setFree( mapResult );
    setFree( set );
}

int *mallocInt( int a ) {
    int *newInt = (int *) malloc( sizeof(int) );
    *newInt = a;

    return newInt;
}

int comparisonFunction( int *aPtr, int *bPtr) {
    int a = *aPtr;
    int b = *bPtr;

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

void printInt( int *number ) {
    printf( "%d ", *number );
}
