#include <stdlib.h>

#include "set.h"

/*
 * Creates a new set that uses a binary search tree as its backing element representation. A set
 * will prevent the addition of duplicate items.
 *
 * Arguments:
 * comparisonFunction -- A function that will compare elements to determine equality and prevent
 *                       duplicates from being added.
 *
 * Returns:
 * An empty set
 */
Set *newSet( ComparisonFunction comparisonFunction ) {
    Set *set = malloc( sizeof(Set) );
    set->elements = newBST(comparisonFunction);
    set->size = 0;

    return set;
}

/*
 * Attempts to add the element to the set. If the element is already present in the set, then it is
 * not added. If the element was added, then the size of the set will be incremented by 1.
 *
 * Arguments:
 * set     -- The set to add the element to
 * element -- The element to add to the set
 */
void setAdd( Set *set, void *element ) {
    if( element ) {
        if( ! bstFind(set->elements, element) ) {
            bstInsert( set->elements, element );
            set->size += 1;
        }
    }
}

/*
 * Attempts to remove the element from the set.
 *
 * Arguments:
 * set     -- The set to remove the element from
 * element -- The element to remove from the set
 */
void setRemove( Set *set, void *element ) {
    void *removed = bstRemove( set->elements, element );
    if( removed ) {
        free( removed );
        set->size -= 1;
    }
}

/*
 * Determines whether or not the provided item is in the set
 *
 * Arguments:
 * set     -- The set to search through
 * element -- The element to check the set for
 *
 * Returns:
 * True if the element is in the set, false otherwise
 */
bool isInSet( Set *set, void *element ) {
    return bstFind( set->elements, element ) != NULL;
}

/*
 * Calculates and returns the set theoretic union of two sets. A union creates a set whose elements
 * are all elements from setA and all elements from setB. For this to work, the two sets should
 * contain the same type of elements and the comparison functions for setA and setB should be
 * functionally equivalent as well.
 *
 * Arguments:
 * setA -- The first set in the pair of sets to union
 * setB -- The second set in the pair of sets to union
 * comparisonfunction -- A function to compare the elements in the union. If this is NULL, the
 *                       comparison function from setA will be used.
 *
 * Returns:
 * A set containing all non-equivalent elements from setA and setB.
 */
Set *setUnion( Set *setA, Set *setB, ComparisonFunction comparisonFunction ) {
    // Ensure that the proper comparison function gets used
    if( ! comparisonFunction ) {
        comparisonFunction = setA->elements->comparisonFunction;
    }

    // Get the elements from A & B, create a new Set
    void **elementsA = bstElements( setA->elements );
    void **elementsB = bstElements( setB->elements );
    Set *unionResult = newSet( comparisonFunction );

    // Insert the elements from A into the set
    for( int i = 0; i < setA->size; i++ ) {
        setAdd( unionResult, elementsA[i] );
    }

    // Insert the elements from B into the set
    for( int i = 0; i < setB->size; i++ ) {
        setAdd( unionResult, elementsB[i] );
    }

    // Free the structure from the element vectors
    free( elementsA );
    free( elementsB );

    return unionResult;
}

/*
 * Calculates the set theoretic intersection of two sets. An intersection creates a set whose
 * elements are present in setA AND present in setB. For this to work, the two sets should
 * contain the same type of elements and the comparison functions for setA and setB should be
 * functionally equivalent as well.
 *
 * Arguments:
 * setA -- The first set in the pair of sets to intersection
 * setB -- The second set in the pair of sets to intersection
 * comparisonfunction -- A function to compare the elements in the union. If this is NULL, the
 *                       comparison function from setA will be used.
 *
 * Returns:
 * A set containing all elements present in both sets.
 */
Set *setIntersect( Set *setA, Set *setB, ComparisonFunction comparisonFunction ) {
    // Ensure that the proper comparison function gets used
    if( ! comparisonFunction ) {
        comparisonFunction = setA->elements->comparisonFunction;
    }

    Set *intersectionResult = newSet( comparisonFunction );

    // Iterate over the smaller set
    if( setA->size <= setB->size ) {
        void **elements = bstElements( setA->elements );

        for( int i = 0; i < setA->size; i++ ) {
            void *element = elements[i];

            // If the element is in both sets, add it
            if( isInSet( setB, element ) ) {
                setAdd( intersectionResult, element );
            }
        }

        free( elements );
    } else {
        void **elements = bstElements( setB->elements );

        for( int i = 0; i < setB->size; i++ ) {
            void *element = elements[i];

            // If the element is in both sets, add it
            if( isInSet( setA, element ) ) {
                setAdd( intersectionResult, element );
            }
        }

        free( elements );
    }

    return intersectionResult;
}

/*
 * Applies the consumer function to every element within the set.
 *
 * Arguments:
 * set      -- The set that will have the function applied
 * consumer -- The function that will be applied to every element within the set.
 */
void setForEach( Set *set, ElementConsumer consumer ) {
    void **elements = bstElements( set->elements );

    for( int i = 0; i < set->size; i++ ) {
        consumer( elements[i] );
    }

    free( elements );
}

/*
 * Creates a new set where the elements in the set derived by applying the map function to every
 * element in the set passed to the function
 *
 * Arguments:
 * set                -- The set whose elements will be mapped over
 * function           -- The function that will be applied to every element in the set. This
 *                       function should allocate new space for the result rather than overwrite the
 *                       space already present.
 * comparisonfunction -- A function that can be used to compare elements in the codomain of the
 *                       mapping function. This can safely be set to NULL if it is known that the
 *                       codomain is the set as the domain of the mapping function. If this is NULL
 *                       and the codomain is different, the behavior is unspecified and could lead
 *                       to errors and crashes depending on the nature of the original set's
 *                       comparison function.
 *
 * Returns:
 * A new set containing every element within the original set after the function has been applied.
 */
Set *setMap( Set *set, MapFunction function, ComparisonFunction comparisonFunction) {
    if( ! comparisonFunction ) {
        comparisonFunction = set->elements->comparisonFunction;
    }

    // Create the new set and get the elements from the old set
    Set *result = newSet( comparisonFunction );
    void **elements = bstElements( set->elements );

    // Apply the function to each element in the old set, then add it to the new set
    for( int i = 0; i < set->size; i++ ) {
        void *element = function( elements[i] );
        setAdd( result, element );
    }

    free( elements );
    return result;
}

/*
 * Frees the memory used by this set.
 *
 * Arguments:
 * set -- The set whose you would like to free
 */
void setFree( Set *set ) {
    bstFree( set->elements );
    free(set);
}

/*
 * Frees the structural memory of the Set without freeing the elements in the set. This should be
 * used when you want to free the set, but maintain the current access that you have to the elements
 * within the vector.
 *
 * Arguments:
 * set -- The set whose structure you would like to free.
 */
void setFreeStructure( Set *set ) {
    bstFreeStructure( set->elements );
    free( set );
}
