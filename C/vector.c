#include <stdlib.h>
#include <stdio.h>

#include "vector.h"
#include "utils.h"

/* Function prototypes */
int isInBounds( Vector *vector, int indexToCheck );
void resizeIfNecessary( Vector *vector );


/* Verifies that the supplied index is within the bounds of the vector
 *
 * Arguments:
 * vector -- The vector to bound check
 * index  -- The index that is being tested
 *
 * Returns:
 * 1 if the index is within the bounds of vector. 0 otherwise.
 */
int isInBounds( Vector *vector, int indexToCheck ) {
    return ( indexToCheck < vector->capacity );
}

/*
 * Resizes the vector if the size and the capacity are equal. It will increase the overall capacity
 * of the vector by 25% upon resizing it.
 *
 * Arguments:
 * vector -- The vector that you would like to resize
 */
void resizeIfNecessary( Vector *vector ) {
    if( vector->size == vector->capacity ) {
        int newCapacity = (vector->capacity * 1.25);
        void** newElements  = (void **)realloc( vector->elements, sizeof(void *) * newCapacity );

        if( ! newElements ) {
            free( vector->elements );
        }

        // Prevent unitialized pointers from being passed to free()
        for( int i = vector->capacity; i < newCapacity; i++ ) {
            newElements[i] = NULL;
        }

        vector->elements = newElements;
        vector->capacity = newCapacity;

        debug( E_DEBUG, "Resized vector to have capacity %d @ location %p\n", newCapacity,
                vector->elements);
    }
}

/*
 * Creates a new vector that has a specific amount of specific previously allocated.
 *
 * Arguments:
 * initalCapacity -- The amount of space to initially allocate for the elements.
 *
 * Returns:
 * A pointer to a newly allocated Vector
 */
Vector *newVector( int initialCapacity ) {
    Vector *vector = NULL;

    if( initialCapacity >= 0 ) {
        vector = (Vector *) malloc( sizeof(Vector) );
        vector->capacity = initialCapacity;
        vector->size = 0;
        vector->elements = (void **) calloc( initialCapacity, sizeof(void *) );

        for( int i = 0; i < vector->capacity; i++ ) {
            vector->elements[i] = NULL;
        }
    }

    return vector;
}

/*
 * Adds an element to the supplied vector. In the case that the size == capacity, the vector will
 * have to be resized to accomodate for the additional element.
 *
 * Arguments:
 * vector  -- The vector that the element is being added to
 * element -- The element that is being added to the vector
 */
void vectorAdd( Vector *vector, void *element ) {
    if( element == NULL ) {
        debug( E_WARNING, "Cannot add a NULL element to the vector!\n" );
        return;
    }

    resizeIfNecessary( vector );
    vector->elements[ (vector->size) ] = element;
    vector->size += 1;
}

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
int vectorInsert( Vector *vector, void *element, int index ) {
    if( isInBounds( vector, index ) ) {
        vector->elements[index] = element;
        return 1;
    } else {
        return 0;
    }
}

/*
 * Removes the element from the vector at the specified location.
 *
 * Arguments:
 * vector -- The vector to remove from
 * index  -- The index of the element to remove
 */
void *vectorRemove( Vector *vector, int index ) {
    if( isInBounds( vector, index ) ) {
        void *removedElement = vector->elements[index];
        vector->elements[index] = NULL;
        vector->size -= 1;

        return removedElement;
    }

    return NULL;
}

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
int vectorIsEmpty( Vector *vector ) {
    return (vector->size == 0);
}

/*
 * Returns the value at the specified index in the vector.
 *
 * Arguments:
 * vector -- The vector the element is being retrieved from
 * index  -- The index to retrieve in the vector
 *
 * Returns:
 * The element in the location or NULL if the index is out of bounds
 */
void *vectorGet( Vector *vector, int index ) {
    if( isInBounds( vector, index ) ) {
        return vector->elements[index];
    } else {
        debug( E_WARNING, "WARNING: GET called with index that is out of bounds.\n" );
        return NULL;
    }
}

/*
 * Frees up the memory used by the vector.
 *
 * Arguments:
 * vector -- The vector whose memory you would like to free
 */
void freeVector( Vector *vector ) {
    for( int i = 0; i < vector->capacity; i++ ) {
        void *itemToFree = vectorGet(vector, i);
        if( itemToFree ) {
            free( itemToFree );
        }
    }

    free( vector->elements );
    free( vector );
}

/*
 * Frees up the structural memory used by the vector, but doesn't free the elements inside the
 * vector.
 *
 * Arguments:
 * vector -- The vector whose memory you would like to free
 */
void vectorFreeStructure( Vector *vector ) {
    free( vector->elements );
    free( vector );
}
