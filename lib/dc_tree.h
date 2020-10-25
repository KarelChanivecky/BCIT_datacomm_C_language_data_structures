/**
 * @since 2020
 * @author Karel Chanivecky Garcia
 * BCIT
 *
 */

#ifndef ASSIGNMENT3_DC_TREE_H
#define ASSIGNMENT3_DC_TREE_H

#include "unistd.h"
#include "stdint.h"
#include <stdbool.h>

struct dc_tree_node_s {
    void * content;
    struct dc_tree_node_s * left;
    struct dc_tree_node_s * right;
};
typedef struct dc_tree_node_s dc_tree_node;

/**
 * Create a node with the given content and null children.
 * @param content
 * @return
 */
dc_tree_node * dc_tree_create_node( void * content );

/**
 * Recursively free all children of the given node.
 *
 * You would use this to delete a branch. For this use-case, it is your responsibility
 * to appropriately decrease the size of the tree.
 *
 * @param node parent node of the branch to free. Will be fred and nullified
 * @return the number of nodes removed
 */
size_t dc_tree_free_branch( dc_tree_node ** node );

/**
 * Add a new node to the left branch.
 * @param content the content of the new node
 */
void dc_tree_add_left( dc_tree_node * tree, void * content );

/**
 * Add a new node to the right branch.
 * @param content the content of the new node
 */
void dc_tree_add_right( dc_tree_node * tree, void * content );

/**
 * Evaluate the height of the tree.
 * @param tree
 * @return the height of the tree
 */
size_t dc_tree_height( dc_tree_node * tree );

/**
 * Get the number of nodes in the tree.
 */
size_t dc_tree_size( dc_tree_node * tree );

/**
 * Tell if a tree node is a leaf.
 * @param tree
 * @return true if both children are null, else false
 */
int dc_tree_is_leaf( dc_tree_node * tree );

/**
 * Apply func to all elements in tree in preorder manner.
 * @param tree
 * @param func a function pointer. The node's content will be passed as the first parameter. func_args as the second
 */
void dc_tree_map( dc_tree_node * tree, void func( void * el, void * args ), void * func_args );

#endif //ASSIGNMENT3_DC_TREE_H
