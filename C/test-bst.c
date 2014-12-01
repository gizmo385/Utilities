#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"
#include "bst.h"

/* Test functions prototypes */
void testTreeCreation();
void testTreeInsertion();
void testTreeFind();
void testTraversals();
void testTreeRemoval();

/* Functions used in testing */
void printNode( BSTNode *node );
int comparisonFunction( void *aPtr, void *bPtr );
int *mallocInt( int a );

int main( int argc, char *argv[] ) {
    setDebuggingLevel( E_ERROR );
    srand( time(NULL) );

    testTreeCreation();
    testTreeInsertion();
    testTreeFind();
    testTraversals();
    testTreeRemoval();
}

void testTreeCreation() {
    BST *bst = newBST( comparisonFunction );

    assertNotNull( bst, "The new BST shouldn't be null!\n" );
    assertNull( bst->root, "The root of the new tree should be null!\n" );
    assertTrue( comparisonFunction == bst->comparisonFunction,
            "The comparison function should be the same!\n" );

    bstFree( bst );
}

void testTreeInsertion() {
    BST *bst = newBST( comparisonFunction );
    const int numElements = 1000;

    for( int i = 0; i < numElements; i++ ) {
        bstInsert( bst, mallocInt( rand() ) );
    }

    bstFree( bst );
}

void testTreeFind() {
    BST *bst = newBST( comparisonFunction );
    const int numElements = 1000;

    // Insert random elements into the tree (keep track of them in a vector)
    int *insertedElements[ numElements ];
    for( int i = 0; i < numElements; i++ ) {
        int *elementToInsert = mallocInt( rand() );
        bstInsert( bst, elementToInsert );
        insertedElements[i] = elementToInsert;
    }

    // Ensure that finding them works
    for( int i = 0; i < numElements; i++ ) {
        int *intToFind = insertedElements[i];
        int *foundElement = bstFind( bst, intToFind );
        assertNotNull( foundElement, "Could not find %d in the list!\n", *intToFind );

        // Check that the right element was found
        int comparisonResult = comparisonFunction(intToFind, foundElement);
        assertTrue( comparisonResult == 0, "Elements should be equal!\n" );
    }

    // Free up BST memory
    bstFree( bst );
}

void testTraversals() {
    BST *bst = newBST( comparisonFunction );

    // Insert the elements
    bstInsert( bst, mallocInt(100) );
    bstInsert( bst, mallocInt(50) );
    bstInsert( bst, mallocInt(150) );

    // Test bstVector
    setDebuggingLevel( E_ALL );
    debug(E_DEBUG, "Vector Traversal (Should be 50 100 150):\n");
    debug(E_DEBUG, "-------------------------------------------\n" );
    Vector *vector = bstVector(bst);
    for( int i = 0; i < vector->size; i++ ) {
        void *element = vectorGet(vector, i);
        printf( "%d ", *(int *)element );
    }
    freeVectorStructure(vector);
    debug( E_DEBUG, "\n" );
    debug(E_DEBUG, "-------------------------------------------\n\n" );

    // Test pre-order traversal
    debug(E_DEBUG, "Pre-Order Traversal (Should be 100 50 150):\n");
    debug(E_DEBUG, "-------------------------------------------\n" );
    bstPreOrder( bst, printNode );
    debug( E_DEBUG, "\n" );
    debug(E_DEBUG, "-------------------------------------------\n\n" );

    // Test post-order traversal
    debug(E_DEBUG, "Post-Order Traversal (Should be 50 150 100):\n");
    debug(E_DEBUG, "-------------------------------------------\n" );
    bstPostOrder( bst, printNode );
    debug( E_DEBUG, "\n" );
    debug(E_DEBUG, "-------------------------------------------\n\n" );

    // Test in-order traversal
    debug(E_DEBUG, "In-Order Traversal (Should be 50 100 150):\n");
    debug(E_DEBUG, "-------------------------------------------\n" );
    bstInOrder( bst, printNode );
    debug( E_DEBUG, "\n" );
    debug(E_DEBUG, "-------------------------------------------\n" );
    setDebuggingLevel( E_ERROR );

    bstFree( bst );

}

void testTreeRemoval() {
    BST *bst = newBST( comparisonFunction );
    const int numElements = 50;

    // Insert random elements into the tree (keep track of them in a vector)
    int *insertedElements[ numElements ];
    for( int i = 0; i < numElements; i++ ) {
        int *elementToInsert = mallocInt( rand() );
        bstInsert( bst, elementToInsert );
        insertedElements[i] = elementToInsert;
    }

    // Remove the elements
    for( int i = 0; i < numElements; i++ ) {
        // Find the element before we remove it
        int *intToFind = insertedElements[i];
        int *foundElement = bstFind( bst, intToFind );
        assertNotNull( foundElement, "Could not find %d in the list!\n", *intToFind );

        // Check that the right element was found
        int comparisonResult = comparisonFunction(intToFind, foundElement);
        assertTrue( comparisonResult == 0, "Elements should be equal!\n" );

        void *removed = bstRemove( bst, intToFind );

        assertNull( bstFind( bst, intToFind ), "Could still find %d after removal!\n", *intToFind );
        free( removed );

    }

    // Free up BST memory
    bstFree( bst );
}

/* Functions for use in testing */
void printNode( BSTNode *node ) {
    debug( E_DEBUG, "%d ", *(int *)(node->data) );
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
