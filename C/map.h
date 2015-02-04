#ifndef MAP_H
#define MAP_H

#include "functions.h"
#include "vector.h"
#include "bst.h"
#include "utils.h"

/**************************************************************************************************
 * Structure and type definitions
 *************************************************************************************************/

typedef struct HMapEntry {
    // The result of running the key through the hash function in the HashMap
    int hash_value;

    // The key/value pair make up the contents of the map entry
    void *key;
    void *value;
} HMapEntry;

typedef struct HashMap {
    // This function is used to hash key value pairs that are inserted into the map
    HashFunction hash;

    // The buckets in the map is the vector of map entries
    Vector *entries;
} HashMap;

typedef struct TMapEntry {
    // The key/value pair make up the contents of the map entry
    void *key;
    void *value;
} TMapEntry;

typedef struct TreeMap {
    // A function which will compare the keys of two TMapEntries
    ComparisonFunction keyCompare;

    // The tree which contains the map entries
    BST *map;
} TreeMap;


/**************************************************************************************************
 * Constructor Functions
 *************************************************************************************************/

/*
 * Creates a new tree map. This provides more consistent performance because it does not incur the
 * cost of resizing the hash map and rehashing everything.
 *
 * Arguments:
 * comparisonFunction -- Compares the keys inserted into the map
 */
extern TreeMap *newTreeMap(ComparisonFunction comparisonFunction);

/*
 * Creates a new hash map. This provides amortized constant time performance on inserts, deletes,
 * and lookups, but incurs the the cost of resizing the hash map and rehashing everything.
 *
 * If the hash function supplied is NULL, then the hash function used by the implementation will use
 * the address of the key being inserted as the hash value.
 *
 * Arguments:
 * hashFunction -- A function which can generate a hash value for the keys inserted.
 */
extern HashMap *newHashMap(HashFunction hashFunction);

/**************************************************************************************************
 * Insertion functions
 *************************************************************************************************/

/*
 * Inserts a (key, value) pair into the hash map. The key will be hashed according to the hash
 * function associated with the hash map.
 *
 * Arguments:
 * map   -- The hash map that a value is being inserted into.
 * key   -- The key, which determines the hash value of the map entry.
 * value -- The value, which is associated with the key, in this map.
 */
extern void hmapInsert(HashMap *map, void *key, void *value);

/*
 * Inserts a (key, value) pair into the tree map. The pair will be ordered based upon the comparison
 * function as applied to the key in relation to other elements.
 *
 * Arguments:
 * map   -- The tree map that a value is being inserted into.
 * key   -- The key, which determines the ordinal position in the tree.
 * value -- The value, which is associated with the key, in this map.
 */
extern void tmapInsert(TreeMap *map, void *key, void *value);

/**************************************************************************************************
 * Removal functions
 *************************************************************************************************/

/*
 * Removes the (key, value) pair associated with the supplied key in the hash map.
 *
 * Arguments:
 * map   -- The hash map that a value is being inserted into.
 * key   -- The key, which determines the hash value of the map entry.
 *
 * Returns:
 * The value that was associated with the key that was removed
 */
extern void *hmapRemove(HashMap *map, void *key);

/*
 * Removes the (key, value) pair associated with the supplied key in the tree map.
 *
 * Arguments:
 * map   -- The tree map that a value is being inserted into.
 * key   -- The key, which determines the ordinal position in the tree.
 *
 * Returns:
 * The value that was associated with the key that was removed
 */
extern void *tmapRemove(TreeMap *map, void *key);

/**************************************************************************************************
 * Find functions
 *************************************************************************************************/

/*
 * Attempts to locate the value associated with the supplied key in map
 *
 * Arguments:
 * map   -- The hash map that a value is being inserted into.
 * key   -- The key, which determines the hash value of the map entry.
 *
 * Returns:
 * The value that was associated with the key if it was found or NULL if it was not
 */
extern void *hmapFind(HashMap *map, void *key);

/*
 * Attempts to locate the value associated with the supplied key in map
 *
 * Arguments:
 * map   -- The tree map that a value is being inserted into.
 * key   -- The key, which determines the ordinal position in the tree.
 *
 * Returns:
 * The value that was associated with the key if it was found or NULL if it was not
 */
extern void *tmapFind(TreeMap *map, void *key);

/**************************************************************************************************
 * Free functions
 *************************************************************************************************/

/*
 * Frees the memory that is currently being occupied by a hash map.
 *
 * Arguments:
 * map -- The hash map whose memory will be freed
 */
extern void hmapFree(HashMap *map);

/*
 * Frees the memory that is currently being occupied by a tree map.
 *
 * Arguments:
 * map -- The tree map whose memory will be freed
 */
extern void tmapFree(TreeMap *map);

#endif
