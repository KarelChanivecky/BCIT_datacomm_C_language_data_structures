/**
 * @since 2020
 * @author Karel Chanivecky Garcia
 * BCIT
 *
 */

#include <stdlib.h>
#include "dc_tree.h"


dc_tree_node * dc_tree_create_node( void * content ) {
    dc_tree_node * new_node = ( dc_tree_node * ) malloc( sizeof( struct dc_tree_node_s ));
    if ( !new_node ) {
        return NULL;
    }
    new_node->content = content;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}


size_t dc_tree_free_branch( dc_tree_node ** node ) {
    if ( !node || !*node ) {
        return 0;
    }
    size_t l_count = dc_tree_free_branch( &( *node )->left );
    size_t r_count = dc_tree_free_branch( &( *node )->right );
    free( *node );
    *node = NULL;
    return l_count + r_count + 1;
}

size_t dc_tree_height( dc_tree_node * tree ) {
    if ( !tree ) {
        return 0;
    }
    size_t left_h = dc_tree_height( tree->left );
    size_t right_h = dc_tree_height( tree->right );
    size_t height = left_h < right_h ? right_h : left_h;
    return height + 1;
}

size_t dc_tree_size( dc_tree_node * tree ) {
    if ( !tree ) {
        return 0;
    }
    return dc_tree_height( tree->left ) + dc_tree_height( tree->right ) + 1;
}

int dc_tree_is_leaf( dc_tree_node * tree ) {
    return !tree->left && !tree->right;
}

void dc_tree_map( dc_tree_node * tree, void func( void *, void * ), void * func_args ) {
    if ( !tree ) {
        return;
    }
    func( tree->content, func_args );
    dc_tree_map( tree->left, func, func_args );
    dc_tree_map( tree->right, func, func_args );
}
