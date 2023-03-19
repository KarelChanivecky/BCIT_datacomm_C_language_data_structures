/**
 * @since Oct 15, 2020
 * @author Karel Chanivecky Garcia
 *
 * BCIT Datacomm
 *
 * dlinked_list
 *
 * This header defines a doubly linked list.
 *
 * It will provide dlinked_push/pop/peek to head or tail at constant time.
 * It will also provide size at constant time.
 */

#include "stdlib.h"
#include "dlinked_list.h"
#include "stdio.h"

/**
 * Create a dynamically allocated dlinked_list node.
 * @param content the content to assign to the new node
 * @return the new node. May return NULL
 */
static dlink * create_link( void * content ) {
    dlink * l = ( dlink * ) malloc( sizeof( struct dlink_s ));
    if ( !l ) {
        return NULL;
    }
    l->content = content;
    l->next = NULL;
    l->prev = NULL;
    return l;
}

/**
 * @see create_link
 */
static dlink * create_link_with_next( void * content, dlink * next ) {
    dlink * l = create_link( content );
    if ( !l ) {
        return NULL;
    }
    l->next = next;
    return l;
}

/**
 * @see create_link
 */
static dlink * create_link_with_next_and_prev( void * content, dlink * prev, dlink * next ) {
    dlink * l = create_link_with_next( content, next );
    if ( !l ) {
        return NULL;
    }
    l->prev = prev;
    return l;
}

/**
 * Get the link at a certain index.
 *
 * beware: does not perform error checking
 *
 * @param head the head, not null
 * @param index must be such as 0 <= index < size
 * @return the link specified by index. NULL if out of bounds
 */
static dlink * get_link( dlink * head, size_t index ) {
    while ( head && index-- ) {
        head = head->next;
    }
    return head;
}

static void free_heads( dlink ** h ) {
    if ( !h || !*h ) {
        return;
    }
    dlink * next = ( *h )->next;
    free( *h );
    *h = NULL;
    while ( next ) {
        dlink * this = next;
        next = this->next;
        free( this );
    }
}

void dlinked_free_list( dlinked_list ** list ) {

    if ( !list || !( *list )) {
        return;
    }
    free_heads( &( *list )->head );
    free( *list );
    *list = NULL;
}

dlinked_list * dlinked_create_list() {
    dlinked_list * ll = ( dlinked_list * ) malloc( sizeof( struct dlinked_list_s ));
    if ( !ll ) {
        return NULL;
    }
    ll->size = 0;
    ll->head = NULL;
    ll->tail = NULL;
    return ll;
}

/**
 * Initialize the head.
 * @param list
 * @param content
 * @return SUCCESS or if memory allocation failed, MALLOC_ERR
 */
int initialize_head( dlinked_list * list, void * content ) {
    list->head = create_link( content );
    list->tail = list->head;
    if ( !list->head ) {
        return MALLOC_ERR;
    }
    list->size++;
    return SUCCESS;
}

int dlinked_push( dlinked_list * list, void * content ) {
    if ( !list ) {
        return BAD_ARGS;
    }
    if ( list->size == 0 ) {
        return initialize_head( list, content );
    }

    dlink * l = list->tail;

    l->next = create_link( content );
    if ( !l->next ) {
        return MALLOC_ERR;
    }

    l->next->prev = l;
    list->size++;
    list->tail = l->next;
    return SUCCESS;
}

int dlinked_push_head( dlinked_list * list, void * content ) {
    if ( !list ) {
        return BAD_ARGS;
    }
    dlink * l = create_link_with_next( content, list->head );
    if ( !l ) {
        return MALLOC_ERR;
    }
    list->head = l;
    if ( l->next ) {
        l->next->prev = l;
    } else {
        list->tail = l;
    }
    list->size++;
    return SUCCESS;
}

void * dlinked_pop_head( dlinked_list * list ) {
    if ( !list || !list->head ) {
        return NULL;
    }
    dlink * h = list->head;
    list->head = h->next;
    if ( list->head ) {
        list->head->prev = NULL;
    } else {
        list->tail = NULL;
    }
    void * content = h->content;
    list->size--;
    free( h );
    return content;
}

void * dlinked_pop_tail( dlinked_list * list ) {
    if ( !list || !list->tail ) {
        return NULL;
    }
    dlink * tail = list->tail;

    if ( !tail->prev ) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->tail = tail->prev;
        list->tail->next = NULL;
        tail->next = NULL;
    }
    void * content = tail->content;
    free( tail );
    list->size--;
    return content;
}

void * dlinked_peek_tail( const dlinked_list * const list ) {

    if ( !list || !list->tail ) {
        return NULL;
    }
    return list->tail->content;
}

void * dlinked_get_value( const dlinked_list * const list, size_t index ) {
    if ( !list || list->size <= index ) {
        return NULL;
    }
    dlink * l = get_link( list->head, index );

    if ( l ) {
        return l->content;
    }
    return NULL;
}

void * dlinked_extract_value( dlinked_list * list, size_t index ) {
    if ( !list || list->size <= index ) {
        return NULL;
    }
    dlink * l = get_link( list->head, index );

    if ( !l ) {
        return NULL;
    }
    if ( l->prev ) {
        l->prev->next = l->next;
    }
    if ( l->next ) {
        l->next->prev = l->prev;
    }
    list->size--;
    void * content = l->content;
    free( l );
    return content;
}

int dlinked_insert_value( dlinked_list * list, size_t index, void * content ) {
    if ( !list ) {
        return BAD_ARGS;
    }
    if ( !list->head || index == 0 ) {
        return dlinked_push_head( list, content );
    }
    dlink * to_move = get_link( list->head, index );
    if ( !to_move ) {
        return OUT_OF_BOUND_ERR;
    }
    dlink * to_insert = create_link_with_next_and_prev( content, to_move->prev, to_move );
    if ( !to_insert ) {
        return MALLOC_ERR;
    }
    if ( to_move->prev ) {
        to_move->prev->next = to_insert;
    }
    to_move->prev = to_insert;
    list->size++;
    return SUCCESS;
}

int dlinked_set_value( const dlinked_list * const list, size_t index, void * content ) {
    if ( !list || !list->head ) {
        return BAD_ARGS;
    }
    dlink * l = get_link( list->head, index );

    if ( !l ) {
        return OUT_OF_BOUND_ERR;
    }
    l->content = content;
    return SUCCESS;
}

int dlinked_index_of_value( const dlinked_list * const list,
                            void * key, int(* comparator)( void *, void * ),
                            size_t * result ) {
    if ( !list || !key || !comparator ) {
        return BAD_ARGS;
    }
    size_t index = 0;
    dlink * l = list->head;
    while ( l ) {
        if ( comparator( l->content, key )) {

            *result = index;
            return SUCCESS;
        }
        l = l->next;
        index++;
    }
    return FAILURE;
}

dlinked_list * dlinked_shallow_copy( const dlinked_list * const src ) {
    if ( !src ) {
        return NULL;
    }
    dlinked_list * cp = dlinked_create_list();
    if ( !src->head ) {
        return cp;
    }
    initialize_head( cp, src->head->content );
    dlink * src_link = src->head->next;
    while ( src_link ) {
        dlinked_push( cp, src_link->content );
        src_link = src_link->next;
    }
    return cp;
}

void default_malloc_error_handler() {
    perror( "Memory allocation error: dlinked_quicksort\n" );
    exit( EXIT_FAILURE );
}

dlinked_list * dlinked_quicksort( dlinked_list * list, int comparator( void *, void * )) {
    return dlinked_quicksort_custom_error_handler( dlinked_shallow_copy( list ),
                                                   comparator,
                                                   default_malloc_error_handler,
                                                   NULL);
}

dlinked_list * dlinked_quicksort_custom_error_handler( dlinked_list * list,
                                                       int comparator( void *, void * ),
                                                       void(* malloc_error_handler)( void * ),
                                                       void * err_status ) {
    if ( list->size == 0 ) {
        free(list);
        return dlinked_create_list();
    }
    void * pivot = dlinked_pop_head( list );
    dlinked_list * lower = dlinked_create_list();
    dlinked_list * equal = dlinked_create_list();
    dlinked_list * higher = dlinked_create_list();
    if ( !lower || !equal || !higher ) {
        malloc_error_handler( err_status );
    }
    dlinked_push( equal, pivot );
    while ( 0 < list->size ) {
        void * cur = dlinked_pop_head( list );
        if ( comparator( cur, pivot ) == LHS_SMALLER ) {
            dlinked_push( lower, cur );
        } else if ( comparator( cur, pivot ) == LHS_EQUAL ) {
            dlinked_push( equal, cur );
        } else {
            dlinked_push( higher, cur );
        }
    }
    int status;
    dlinked_list * lower_sorted =
            dlinked_quicksort_custom_error_handler( lower, comparator, malloc_error_handler, &status );
    while ( 0 < lower_sorted->size ) {
        dlinked_push_head( equal, dlinked_pop_tail( lower_sorted ));
    }
    dlinked_list * higher_sorted =
            dlinked_quicksort_custom_error_handler( higher, comparator, malloc_error_handler, &status );
    while ( 0 < higher_sorted->size ) {
        dlinked_push( equal, dlinked_pop_head( higher_sorted ));
    }
    dlinked_free_list( &list);
    dlinked_free_list( &lower_sorted );
    dlinked_free_list( &higher_sorted );
    return equal;
}

void dlinked_map(const dlinked_list * const list, void(* func)(void * )) {
    if ( !list || !func ) {
        return;
    }
    dlink * link = list->head;
    while ( link ) {
        func( link->content );
        link = link->next;
    }
}

int dlinked_to_pointer(dlinked_list * list, void *** pointer) {
    size_t i = 0;
    if ( !list ) {
        return SUCCESS;
    }

    *pointer = malloc(sizeof(void *) * list->size);
    if (!*pointer ) {
        return FAILURE;
    }

    dlink * link = list->head;
    while ( link ) {
        (*pointer)[i] = link->content;
        link = link->next;
        i++;
    }

    return SUCCESS;
}
