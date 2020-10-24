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
typedef struct dc_tree_node_s * dc_tree_node;

/**
 * Create a node with the given content and null children.
 * @param content
 * @return
 */
dc_tree_node dc_tree_create_node(void * content);

/**
 * Recursively free all children of the given node.
 *
 * You would use this to delete a branch. For this use-case, it is your responsibility
 * to appropriately decrease the size of the tree.
 *
 * @param node parent node of the branch to free. Will be fred and nullified
 * @return the number of nodes removed
 */
size_t dc_tree_free_branch( dc_tree_node * node);

/**
 * Add a new node to the left branch.
 * @param content the content of the new node
 */
void dc_tree_add_left(dc_tree_node tree, void * content);

/**
 * Add a new node to the right branch.
 * @param content the content of the new node
 */
void dc_tree_add_right(dc_tree_node tree, void * content);

/**
 * Evaluate the height of the tree.
 * @param tree
 * @return the height of the tree
 */
size_t dc_tree_height(dc_tree_node tree);


#endif //ASSIGNMENT3_DC_TREE_H
