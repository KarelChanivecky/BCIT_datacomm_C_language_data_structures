/**
 * @since 2020
 * @author Karel Chanivecky Garcia
 * BCIT
 *
 */

#include <stdlib.h>
#include "dc_tree.h"
#include "dc/stdlib.h"



dc_tree_node dc_tree_create_node(void * content) {
    dc_tree_node new_node = (dc_tree_node) dc_malloc(sizeof(struct dc_tree_node_s));
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}


size_t dc_tree_free_branch( dc_tree_node * node ) {
    if (!node || !*node) {
        return 0;
    }
    size_t l_count = dc_tree_free_branch(&(*node)->left);
    size_t r_count = dc_tree_free_branch(&(*node)->right);
    free(*node);
    *node = NULL;
    return l_count + r_count + 1;
}


size_t dc_tree_height( dc_tree_node tree ) {
    if (!tree) {
        return 0;
    }
    return dc_tree_height(tree->left) + dc_tree_height(tree->right) + 1;
}
