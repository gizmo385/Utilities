#ifndef SET_H
#define SET_H

#include <stdbool.h>

#include "bst.h"
#include "functions.h"

/**************************************************************************************************
 * Structure and type definitions
 *************************************************************************************************/

typedef struct Set {
    BST *elements;
    int size;
} Set;

/**************************************************************************************************
 * Constructor Functions
 *************************************************************************************************/

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
extern Set *newSet( ComparisonFunction comparisonFunction );

/**************************************************************************************************
 * Insertion functions
 *************************************************************************************************/

/*
 * Attempts to add the element to the set. If the element is already present in the set, then it is
 * not added. If the element was added, then the size of the set will be incremented by 1.
 *
 * Arguments:
 * set     -- The set to add the element to
 * element -- The element to add to the set
 */
extern void setAdd( Set *set, void *element );

/**************************************************************************************************
 * Removal functions
 *************************************************************************************************/

/*
 * Attempts to remove the element from the set.
 *
 * Arguments:
 * set     -- The set to remove the element from
 * element -- The element to remove from the set
 */
extern void setRemove( Set *set, void *element );

/**************************************************************************************************
 * Fundamental set operations
 *************************************************************************************************/

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
extern bool isInSet( Set *set, void *element );

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
extern Set *setUnion( Set *setA, Set *setB, ComparisonFunction comparisonFunction );

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
extern Set *setIntersect( Set *setA, Set *setB, ComparisonFunction comparisonFunction );

/**************************************************************************************************
 * Iteration functions
 *************************************************************************************************/

/*
 * Applies the consumer function to every element within the set.
 *
 * Arguments:
 * set      -- The set that will have the function applied
 * consumer -- The function that will be applied to every element within the set.
 */
extern void setForEach( Set *set, ElementConsumer consumer );

/*
 * Creates a new set where the elements in the set derived by applying the map function to every
 * element in the set passed to the function
 *
 * Arguments:
 * set                -- The set whose elements will be mapped over
 * function           -- The function that will be applied to every element in the set
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
extern Set *setMap( Set *set, MapFunction function, ComparisonFunction comparisonFunction);

/**************************************************************************************************
 * Free functions
 *************************************************************************************************/

/*
 * Frees the memory used by this set.
 *
 * Arguments:
 * set -- The set whose you would like to free
 */
extern void setFree( Set *set );

/*
 * Frees the structural memory of the Set without freeing the elements in the set. This should be
 * used when you want to free the set, but maintain the current access that you have to the elements
 * that the set contained
 *
 * Arguments:
 * set -- The set whose structure you would like to free.
 */
extern void setFreeStructure( Set *set );

#endif
