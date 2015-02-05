#ifndef VECTOR_H
#define VECTOR_H

/**************************************************************************************************
 * Structure and type definitions
 *************************************************************************************************/

/**
 * A vector is defined by three compositional elements:
 *
 * size     -- The number of elements actually present within the vector
 * capacity -- The amount of available space within the vector. This is the number of elements that
 *             can be added without incurring a resize.
 * elements -- The elements within the vector
 */
typedef struct Vector {
    int size;
    int capacity;
    void **elements;
} Vector;

/**************************************************************************************************
 * Constructor Functions
 *************************************************************************************************/

/*
 * Creates a new vector that has a specific amount of specific previously allocated.
 *
 * Arguments:
 * initalCapacity -- The amount of space to initially allocate for the elements.
 *
 * Returns:
 * A pointer to a newly allocated Vector
 */
extern Vector *newVector( int initialCapacity );

/**************************************************************************************************
 * Insertion functions
 *************************************************************************************************/

/*
 * Adds an element to the supplied vector. In the case that the size == capacity, the vector will
 * have to be resized to accomodate for the additional element.
 *
 * Arguments:
 * vector  -- The vector that the element is being added to
 * element -- The element that is being added to the vector
 */
extern void vectorAdd( Vector *vector, void *element );

/*
 * Inserts an element into a specified index in a vector. If this falls outside the bounds of the
 * vector, the function will fail and return a false value. Otherwise it will return true.
 *
 * Arguments:
 * vector  -- The vector that the item is being inserted into.
 * element -- The element that is being inserted into the list.
 * index   -- The index that the element is being inserted into
 *
 * Returns:
 * In the case that the element is successfully inserted, this will return 1. Otherwise, it will
 * return 0.
 */
extern int vectorInsert( Vector *vector, void *element, int index );

/**************************************************************************************************
 * Removal functions
 *************************************************************************************************/

/*
 * Removes the element from the vector at the specified location.
 *
 * Arguments:
 * vector -- The vector to remove from
 * index  -- The index of the element to remove
 */
extern void *vectorRemove( Vector *vector, int index );

/**************************************************************************************************
 * Member access functions
 *************************************************************************************************/

/*
 * Returns whether or not the supplied vector is empty. This will return 1 when the vector is empty
 * and will return 0 when the vector is not empty.
 *
 * Arguments:
 * vector -- The vector to check for emptiness
 *
 * Returns:
 * 1 in the case that the vector is empty, 0 otherwise.
 */
extern int vectorIsEmpty( Vector *vector );

/*
 * Returns the value at the specified index in the vector.
 *
 * Arguments:
 * vector -- The vector the element is being retrieved from
 * index  -- The index to retrieve in the vector
 *
 * Returns:
 * The element in the location
 */
extern void *vectorGet( Vector *vector, int index );

/**************************************************************************************************
 * Free functions
 *************************************************************************************************/

/*
 * Frees up the memory used by the vector.
 *
 * Arguments:
 * vector -- The vector whose memory you would like to free
 */
extern void freeVector( Vector *vector );

/*
 * Frees the memory allocated for the structure of the vector. This should be used when you want to
 * maintain access to the elements that were within the vector.
 *
 * Arguments:
 * vector -- The vector whose structural memory you would like to free
 */
extern void vectorFreeStructure( Vector *vector );

#endif
