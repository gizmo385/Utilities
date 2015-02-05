#ifndef BST_H
#define BST_H

#include "functions.h"

/**************************************************************************************************
 * Structure and type definitions
 *************************************************************************************************/

/*
 * A binary search tree node holds an individual item that is to be kept in a search tree. It
 * consists of 4 fields:
 *
 * data   -- This is actual data that is contained with a node and can be of any type
 * parent -- The node that has this node as a child
 * left   -- This node's left child
 * right  -- This node's right child
 */
typedef struct BSTNode {
    void *data;
    struct BSTNode *parent;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

/*
 * A binary search tree is a search tree where each node has at most 2 children. For all nodes in
 * this binary search tree, they follow the same behavior. Children who are ordinally smaller than
 * a node are left children and children who are ordinally larger than a node are right children.
 *
 * This tree consists of 3 fields:
 *
 * root -- The first node in the tree. This is the only node in the tree that does not have
 *         a parent.
 * comparisonFunction -- A function which can be used to compare elements within the tree
 * size -- The number of elements in this tree. Maintained on insertions and deletions
 */
typedef struct BST {
    BSTNode *root;
    ComparisonFunction comparisonFunction;
    int size;
} BST;

/*
 * A BST Node Consumer function takes a BST node and performs some operation on it.
 */
typedef void (*BSTNodeConsumer)(BSTNode *);

/**************************************************************************************************
 * Constructor Functions
 *************************************************************************************************/

/*
 * Creates a new binary search tree node. This node has some data, and references to its left and
 * right children.
 *
 * Arguments:
 * data  -- The data that is being inserted into the tree
 * left  -- The node that should be placed on this new node's left
 * right -- The node that should be placed on this new node's right
 *
 * Returns:
 * A binary search tree node that contains the desired data and has its left and right child
 * pointers pointing at the specified nodes.
 */
extern BSTNode *newNode( void *data, BSTNode *parent, BSTNode *left, BSTNode *right );

/*
 * Creates a new binary search tree whose elements are ordered with the the supplied comparison
 * function.
 *
 * Arguments:
 * comparisonFunction -- A function that will be used to order the inserted elements.
 *
 * Returns:
 * A binary search tree ordered with the supplied function whose root is NULL.
 */
extern BST *newBST( ComparisonFunction comparisonFunction );

/**************************************************************************************************
 * Insertion functions
 *************************************************************************************************/

/*
 * Inserts an element into the tree. This element will be placed in its correct ordinal position as
 * determined by the tree's comparison function. If the element or the treeis NULL, then the element
 * will not be inserted.
 *
 * Arguments:
 * bst             -- The tree to insert the element into.
 * elementToInsert -- The element that you would like to insert into the tree.
 */
extern void bstInsert( BST *bst, void *elementToInsert );

/**************************************************************************************************
 * Removal functions
 *************************************************************************************************/

/*
 * Attempts to find the desired element from the tree. If the element cannot be found, then this
 * function will return NULL, otherwise it will return the removed element.
 *
 * Arguments:
 * bst             -- The tree to remove the element from.
 * elementToInsert -- The element that you would like to remove from the tree.
 *
 * Returns:
 * The element that was removed, or NULL if the element could not be found.
 */
extern void *bstRemove( BST *bst, void *elementToRemove );

/**************************************************************************************************
 * Find functions
 *************************************************************************************************/

/*
 * Attempts to the find the node in the binary search tree that contains the desired element. If the
 * element can't be found, return NULL.
 *
 * Arguments:
 * bst     -- The binary search tree to search through
 * element -- The element that is being searched for
 *
 * Returns:
 * The node containing the element that you were searching for. If the item couldn't be found, this
 * will return NULL.
 */
extern void *bstFind( BST *bst, void *element );

/**************************************************************************************************
 * Tree traversal functions
 *************************************************************************************************/

/*
 * Finds the ordinal successor for a tree node.
 *
 * Arguments:
 * node -- The node whose successor is being found.
 *
 * Returns:
 * The node that is the ordinal successor for the provided node
 */
extern BSTNode *successor( BSTNode *node );

/*
 * Finds the ordinal predecessor for a tree node.
 *
 * Arguments:
 * node -- The node whose predecessor is being found.
 *
 * Returns:
 * The node that is the ordinal predecessor for the provided node
 */
extern BSTNode *predecessor( BSTNode *node );

/*
 * Performs a pre-order traversal and executes the consumer function on each node in the traversal.
 * In a pre-order traversal, at each node, the node will be supplied to the consumer, then the
 * traversal will be recursively called on the left child and then the right child.
 *
 * Arguments:
 * bst      -- The binary search tree that the pre-order traversal is being performed on
 * consumer -- The function that is applied to every node along the traversal
 */
extern void bstPreOrder( BST *bst, BSTNodeConsumer consumer );

/*
 * Performs an in-order traversal and executes the consumer function on each node in the traversal.
 * In an in-order traversal, at each node, we will recurse on the left child, then we will apply
 * the consumer function to the current node, and then we will recurse on the right child.
 *
 * Arguments:
 * bst      -- The binary search tree that the in-order traversal is being performed on
 * consumer -- The function that is applied to every node along the traversal
 */
extern void bstInOrder( BST *bst, BSTNodeConsumer consumer );

/*
 * Performs a post-order traversal and executes the consumer function on each node in the traversal.
 * In a post-order traversal, at each node, the node will be supplied to the consumer, then the
 * traversal will be recursively called on the right child and then the left child.
 *
 * Arguments:
 * bst      -- The binary search tree that the post-order traversal is being performed on
 * consumer -- The function that is applied to every node along the traversal
 */
extern void bstPostOrder( BST *bst, BSTNodeConsumer consumer );

/*
 * Creates and returns an array of the elements within this binary search tree. The items inside the
 * array will be in-order.
 *
 * Arguments:
 * bst -- The binary search tree whose elements are being copied into an array.
 *
 * Returns:
 * An array containing data from the binary search tree.
 */
extern void **bstElements( BST *bst );

/**************************************************************************************************
 * Free functions
 *************************************************************************************************/

/*
 * Frees the binary search tree and all nodes within it. This is expressed as a post order traversal
 * on the provided tree where the consumer function frees the node.
 *
 * Arguments:
 * bst -- The tree that is being freed
 */
extern void bstFree( BST *bst );

/*
 * Frees the memory allocated for the structure of the BST. This should be used when you want to
 * maintain access to the elements that were within the tree.
 *
 * Arguments:
 * bst -- The binary search tree whose structural memory you would like to free
 */
extern void bstFreeStructure( BST *bst );

#endif
