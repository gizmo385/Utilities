#include <stdlib.h>
#include <time.h>

#include "utils.h"
#include "vector.h"

/* Function prototypes */
void testListCreation();
void testListAddition();
void testListRemoval();
void testListResizing();
void testLargeVectors();
int *mallocedInt( int a );

int main( int argc, char *argv[] ) {
    setDebuggingLevel( E_ERROR );
    testListCreation();
    testListAddition();
    testListRemoval();
    testListResizing();
    testLargeVectors();

    return 0;
}

int *mallocedInt( int a ) {
    int *mInt = (int *) malloc( sizeof(int) );

    if( mInt != NULL ) {
        *mInt = a;
        return mInt;
    } else {
        debug( E_ERROR, "malloc returned NULL\n" );
        return mallocedInt( a );
    }
}

void testListCreation() {
    Vector *vector = newVector( 10 );

    assertNotNull( vector, "Vector shouldn't be null!\n" );
    assertNotNull( vector->elements, "Vector elements shouldn't be null!\n" );

    assertTrue( vector->size == 0, "Vector size: expected 0, was %d\n", vector->size );
    assertTrue( vector->capacity == 10, "Vector capacity: expected 10, was %d\n",
            vector->capacity );

    freeVector( vector );
}

void testListAddition() {
    Vector *vector = newVector( 10 );

    // Add 10 element
    for( int i = 0; i < vector->capacity; i++ ) {
        vectorAdd( vector, mallocedInt( i ) );
    }

    assertTrue( vector->size == 10, "Vector size should still be 10!\n" );
    assertTrue( vector->capacity == 10, "Vector capacity should still be 10!\n" );

    // Attempt to add null and then verify that the addition is not successful
    vectorAdd( vector, NULL );
    assertTrue( vector->size == 10, "Vector size should still be 10!\n" );
    assertTrue( vector->capacity == 10, "Vector capacity should still be 10!\n" );

    freeVector( vector );
}

void testListRemoval() {
    Vector *vector = newVector( 10 );

    // Add 10 elements
    for( int i = 0; i < vector->capacity; i++ ) {
        vectorAdd( vector, mallocedInt( i ) );
    }

    // Remove a single element
    void *firstRemoved = vectorRemove( vector, 0 );
    assertNotNull( firstRemoved, "Removed element shouldn't be NULL!\n" );
    free( firstRemoved );
    assertTrue( vector->size == 9, "Vector size should be 9, was %d\n", vector->size);

    // Remove the rest of the elements
    for( int i = 1; i < vector->capacity; i++ ) {
        free( vectorRemove( vector, i ) );
    }

    assertTrue( vector->size == 0, "Vector size should be 0, was %d\n", vector->size);

    freeVector( vector );
}

void testListResizing() {
    Vector *vector = newVector( 10 );
    const int numElements = 20;

    // Add 20 elements
    for( int i = 0; i < numElements; i++ ) {
        vectorAdd( vector, mallocedInt( i ) );
    }

    assertTrue( vector->size == numElements, "Vector size should be == %d after item removal, was %d\n",
            numElements, vector->size);
    assertTrue( vector->capacity >= numElements, "Vector capacity should be > %d after item removal\n",
            numElements );

    // Remove and free all of the elements in the list
    int size = vector->size;
    for( int i = 0; i < size; i++ ) {
        void *removed = vectorRemove( vector, i );
        free( removed );
    }

    assertTrue( vector->size == 0, "Removed all elements. Size was %d, expected 0\n", vector->size );

    freeVector( vector );
}

void testLargeVectors() {
    Vector *vector = newVector( 10 );
    const int numElements = 10000;

    // Silently add 10000 elements to the vector
    for( int i = 0; i < numElements; i++ ) {
        vectorAdd( vector, mallocedInt(i) );
    }

    // Print out the size and capacity
    assertTrue( vector->capacity >= numElements, "Capacity should be >= %d\n", numElements );
    assertTrue( vector->size == numElements, "Capacity should be >= %d\n", numElements );

    //Remove a random 500 elements
    srand( time(NULL) );
    for( int i = 0; i < 100; i++ ) {
        int randomIndex = rand() % vector->size;
        void *removed = vectorRemove( vector, randomIndex );

        free( removed );
    }

    freeVector( vector );
}
