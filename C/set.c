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
 *
 * Returns:
 * A set containing all non-equivalent elements from setA and setB.
 */
Set *setUnion( Set *setA, Set *setB ) {
    // TODO
    return NULL;
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
 *
 * Returns:
 * A set containing all elements present in both sets.
 */
Set *setIntersect( Set *setA, Set *setB ) {
    // TODO
    return NULL;
}

/*
 * Applies the consumer function to every element within the set.
 *
 * Arguments:
 * set      -- The set that will have the function applied
 * consumer -- The function that will be applied to every element within the set.
 */
void setForEach( Set *set, SetConsumer consumer ) {
    // TODO
}

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
Set *setMap( Set *set, MapFunction function, ComparisonFunction comparisonFunction) {
    // TODO
    return NULL;
}
