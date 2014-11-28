#include <stdio.h>
#include <stdlib.h>

#include "bst.h"
#include "utils.h"

/* Implementation specific helper functions */
void preOrderHelper(BSTNode *node, BSTNodeConsumer consumer );
void postOrderHelper(BSTNode *node, BSTNodeConsumer consumer );
void inOrderHelper(BSTNode *node, BSTNodeConsumer consumer );
void freeNode( BSTNode *node );
void replaceNodeInParent( BST *bst, BSTNode *node, BSTNode *replacement );
void *removeHelper( BST *bst, BSTNode *node );

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
BSTNode *newNode( void *data, BSTNode *parent, BSTNode *left, BSTNode *right ) {
    BSTNode *node = malloc( sizeof(BSTNode) );
    node->parent = parent;
    node->data = data;
    node->left = left;
    node->right = right;

    return node;
}

/*
 * Creates a new binary search tree whose elements are ordered with the the supplied comparison
 * function. The root of this new tree will be NULL.
 *
 * Arguments:
 * comparisonFunction -- A function that will be used to order the inserted elements.
 *
 * Returns:
 * A binary search tree ordered with the supplied function whose root is NULL. If the comparison
 * function is NULL, then this function will return NULL.
 */
BST *newBST( ComparisonFunction comparisonFunction ) {
    if( comparisonFunction != NULL ) {
        BST *bst = malloc( sizeof(BST) );
        bst->root = NULL;
        bst->comparisonFunction = comparisonFunction;

        return bst;
    } else {
        return NULL;
    }
}

/*
 * Inserts an element into the tree. This element will be placed in its correct ordinal position as
 * determined by the tree's comparison function. If the element or the treeis NULL, then the element
 * will not be inserted.
 *
 * Arguments:
 * bst             -- The tree to insert the element into.
 * elementToInsert -- The element that you would like to insert into the tree.
 */
void bstInsert( BST *bst, void *elementToInsert ) {
    BSTNode *current = bst->root;
    BSTNode *parent = NULL;
    ComparisonFunction compare = bst->comparisonFunction;

    // Find where we should insert this new node
    while( current != NULL ) {
        int comparisonResult = compare( elementToInsert, current->data );

        if( comparisonResult == 0 ) {
            // Can't insert the same item multiple times
            return;
        } else if( comparisonResult < 0 ) {
            parent = current;
            current = current->left;
        } else {
            parent = current;
            current = current->right;
        }
    }

    current = newNode( elementToInsert, parent, NULL, NULL );

    if( parent != NULL ) {
        // At this point, current is NULL and parent is our soon-to-be parent
        int parentComparison = compare( elementToInsert, parent->data );

        // Determine which side of the parent we should be placed on
        if( parentComparison > 0 ) {
            parent->right = current;
        } else {
            parent->left = current;
        }
    } else {
        bst->root = current;
    }
}

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
void *bstRemove( BST *bst, void *elementToRemove ) {
    BSTNode *current = bst->root;
    ComparisonFunction compare = bst->comparisonFunction;

    while( current != NULL ) {
        int comparisonResult = compare( elementToRemove, current->data );

        if( comparisonResult == 0 ) {
            return removeHelper( bst, current );
        } else if( comparisonResult < 0 ) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return NULL;
}

/*
 * Helper function for node deletion in the binary search tree
 *
 * Arguments:
 * node -- The node that is being removed from the tree
 *
 * Returns:
 * The element that was removed
 */
void *removeHelper( BST *bst, BSTNode *node ) {
    void *removedElement = (node != NULL) ? node->data : NULL;

    if( node != NULL ) {
        BSTNode *left = node->left;
        BSTNode *right = node->right;

        if( left != NULL && right != NULL ) {
            replaceNodeInParent( bst, node, successor(node) );
        } else if( left != NULL ) {
            replaceNodeInParent( bst, node, left );
        } else if( right != NULL ) {
            replaceNodeInParent( bst, node, right );
        } else {
            replaceNodeInParent( bst, node, NULL );
        }
    }

    free( node );
    return removedElement;
}

/*
 * Replaces a node inside its parent with a replacement
 *
 * Arguments:
 * node        -- The node that is being replaced
 * replacement -- The node to replace it with
 */
void replaceNodeInParent( BST *bst, BSTNode *node, BSTNode *replacement ) {
    if( node != NULL ) {
        BSTNode *parent = node->parent;

        if( parent != NULL ) {
            BSTNode *parentLeft = parent->left;
            BSTNode *parentRight = parent->right;

            // Determine which side of the parent node that the node is on
            if( node == parentLeft ) {
                if( replacement != NULL ) {
                    replacement->parent = parent;
                    replacement->left = node->left;
                    replacement->right = node->right;
                }

                parent->left = replacement;
                node->parent = NULL;
            } else if( node == parentRight ) {
                if( replacement != NULL ) {
                    replacement->parent = parent;
                    replacement->left = node->left;
                    replacement->right = node->right;
                }

                parent->right = replacement;
                node->parent = NULL;
            }
        } else if( node == bst->root ) {
            if( replacement != NULL ) {
                replacement->parent = NULL;
                replacement->left = bst->root->left;
                replacement->right = bst->root->right;
            }

            bst->root = replacement;
        }
    }
}

/*
 * Finds the ordinal successor for a tree node.
 *
 * Arguments:
 * node -- The node whose successor is being found.
 *
 * Returns:
 * The node that is the ordinal successor for the provided node
 */
BSTNode *successor( BSTNode *node ) {
    if( node->right != NULL ) {
        BSTNode *current = node->right;

        while( current->left != NULL ) {
            current = current->left;
        }

        return current;
    } else {
        BSTNode *current = node;
        BSTNode *parent = current->parent;

        while( parent != NULL && current == parent->right ) {
            current = parent;
            parent = parent->parent;
        }

        return parent;
    }
}

/*
 * Finds the ordinal predecessor for a tree node.
 *
 * Arguments:
 * node -- The node whose predecessor is being found.
 *
 * Returns:
 * The node that is the ordinal predecessor for the provided node
 */
BSTNode *predecessor( BSTNode *node ) {
    if( node->left != NULL ) {
        BSTNode *current = node->left;

        while( current->right != NULL ) {
            current = current->right;
        }

        return current;
    } else {
        BSTNode *current = node;
        BSTNode *parent = current->parent;

        while( parent != NULL && current == parent->left ) {
            current = parent;
            parent = parent->parent;
        }

        return parent;
    }
}

/*
 * Attempts to the find the node in the binary search tree that contains the desired element. If the
 * element can't be found, return NULL.
 *
 * Arguments:
 * bst     -- The binary search tree to search through
 * element -- The element that is being searched for
 *
 * Returns:
 * The element that you were searching for. If the item couldn't be found, this
 * will return NULL.
 */
void *bstFind( BST *bst, void *element ) {
    BSTNode *current = bst->root;
    ComparisonFunction compare = bst->comparisonFunction;

    while( current != NULL ) {
        int comparisonResult = compare( element, current->data );

        if( comparisonResult == 0 ) {
            return current->data;
        } else if( comparisonResult < 0 ) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return NULL;
}

/*
 * Performs a pre-order traversal and executes the consumer function on each node in the traversal.
 * In a pre-order traversal, at each node, the node will be supplied to the consumer, then the
 * traversal will be recursively called on the left child and then the right child.
 *
 * Arguments:
 * bst      -- The binary search tree that the pre-order traversal is being performed on
 * consumer -- The function that is applied to every node along the traversal
 */
void bstPreOrder( BST *bst, BSTNodeConsumer consumer ) {
    preOrderHelper( bst->root, consumer );
}

/*
 * Helper function for pre-order binary search tree traversals
 *
 * Arguments:
 * node     -- The node currently being traversed
 * consumer -- The function to apply to each node along the traversal
 */
void preOrderHelper(BSTNode *node, BSTNodeConsumer consumer ) {
    if( node != NULL ) {
        consumer( node );
        preOrderHelper( node->left, consumer );
        preOrderHelper( node->right, consumer );
    }
}

/*
 * Performs an in-order traversal and executes the consumer function on each node in the traversal.
 * In an in-order traversal, at each node, we will recurse on the left child, then we will apply
 * the consumer function to the current node, and then we will recurse on the right child.
 *
 * Arguments:
 * bst      -- The binary search tree that the in-order traversal is being performed on
 * consumer -- The function that is applied to every node along the traversal
 */
void bstInOrder( BST *bst, BSTNodeConsumer consumer ) {
    inOrderHelper( bst->root, consumer );
}

/*
 * Helper function for in-order binary search tree traversals
 *
 * Arguments:
 * node     -- The node currently being traversed
 * consumer -- The function to apply to each node along the traversal
 */
void inOrderHelper(BSTNode *node, BSTNodeConsumer consumer ) {
    if( node != NULL ) {
        inOrderHelper( node->left, consumer );
        consumer(node);
        inOrderHelper( node->left, consumer );
    }
}

/*
 * Performs a post-order traversal and executes the consumer function on each node in the traversal.
 * In a post-order traversal, at each node, the node will be supplied to the consumer, then the
 * traversal will be recursively called on the right child and then the left child.
 *
 * Arguments:
 * bst      -- The binary search tree that the post-order traversal is being performed on
 * consumer -- The function that is applied to every node along the traversal
 */
void bstPostOrder( BST *bst, BSTNodeConsumer consumer ) {
    postOrderHelper( bst->root, consumer );
}

/*
 * Helper function for post-order binary search tree traversals
 *
 * Arguments:
 * node     -- The node currently being traversed
 * consumer -- The function to apply to each node along the traversal
 */
void postOrderHelper(BSTNode *node, BSTNodeConsumer consumer ) {
    if( node != NULL ) {
        postOrderHelper( node->left, consumer );
        postOrderHelper( node->right, consumer );
        consumer( node );
    }
}

/*
 * Frees the binary search tree and all nodes within it. This is expressed as a post order traversal
 * on the provided tree where the consumer function frees the node.
 *
 * Arguments:
 * bst -- The tree that is being freed
 */
void bstFree( BST *bst ) {
    bstPostOrder( bst, freeNode );
    free( bst );
}

/*
 * Frees a binary search tree node
 *
 * Arguments:
 * node -- The node to free
 */
void freeNode( BSTNode *node ) {
    free( node->data );
    free( node );
}
