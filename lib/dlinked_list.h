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

#ifndef DC_DLINKED_LIST_H
#define DC_DLINKED_LIST_H

#include <stddef.h>

#define SUCCESS 0
#define FAILURE -1
#define MALLOC_ERR -2
#define OUT_OF_BOUND_ERR -3
#define BAD_ARGS -4
#define LHS_SMALLER -1
#define LHS_EQUAL 1
#define LHS_LARGER 2


/**
 * Represent a linked list node.
 */
struct dlink_s {
    struct dlink_s * next;
    struct dlink_s * prev;
    void * content;
};
typedef struct dlink_s dlink;

/**
 * Represent a doubly linked list.
 */
struct dlinked_list_s {
    dlink * head;
    dlink * tail;
    size_t size;
};
typedef struct dlinked_list_s dlinked_list;

/**
 * Initialize a dynamically allocated doubly linked list.
 * @return a dynamically allocated linked list. Will return NULL if memory allocation fails
 */
dlinked_list * dlinked_create_list();

/**
 * Free a dynamically allocated linked list.
 * @param list a dlinked_list * *. Will be dlinked_set_value to NULL
 */
void dlinked_free_list( dlinked_list ** list );

/**
 * Add an element at the end.
 * @param list the list to add the element to
 * @param content the content of the new element
 * @return SUCCESS for success, else one of the defined error codes
 */
int dlinked_push( dlinked_list * list, void * content );

/**
 * Add an element at the start.
 * @param list the list to add the element to
 * @param content the content of the new element
 * @return SUCCESS for success, else one of the defined error codes
 */
int dlinked_push_head( dlinked_list * list, void * content );

/**
 * Remove the first element of the list and return its content.
 * @param list a dlinked_list * with at least one element
 * @return the content of the first element. If list was empty, will return NULL
 */
void * dlinked_pop_head( dlinked_list * list );

/**
 * Remove the last element of the list and return its content.
 * @param list a dlinked_list * with at least one element
 * @return the content of the first element. If list was empty, will return NULL
 */
void * dlinked_pop_tail( dlinked_list * list );

/**
 * Get the value in the tail.
 * @param list the list to peek into
 * @return the value in the tail
 */
void * dlinked_peek_tail( const dlinked_list * const list );

/**
 * Get the element at the given index.
 * @param list the list to dlinked_get_value from
 * @param index must be such as 0 <= index < size
 * @return the element at the index or NULL if out of bounds
 */
void * dlinked_get_value( const dlinked_list * const list, size_t index );

/**
 * Remove element at given index and return its content.
 * @param the list to remove from
 * @param index must be such as 0 <= index < size
 * @return the element at the index or NULL if out of bounds
 */
void * dlinked_extract_value( dlinked_list * list, size_t index );

/**
 * Insert an element at the given index.
 *
 * Will displace the next elements by 1 index.
 *
 * @param index the exact index to do the insertion. index must be such as 0 <= index < size
 * @param content the content to dlinked_insert_value
 * @return SUCCESS or one of the defined error codes
 */
int dlinked_insert_value( dlinked_list * list, size_t index, void * content );

/**
 * Set the given content at the given index.
 * @param index must be such as 0 <= index < size
 * @return SUCCESS or one of the defined errors
 */
int dlinked_set_value( const dlinked_list * const list, size_t index, void * content );

/**
 * Get the result of a given element.
 * @param list the list to search in
 * @param key the element to seek
 * @param comparator a predicate function, must return stdbool.h true or false
 * <p>the key will be passed to the rhs argument</p>
 * @param result if key is contained, the result, else ignore
 * @return if key is found, success<br/>
 * if not found, FAILURE<br/>
 * if error occurred, one of the defined error codes
 */
int dlinked_index_of_value( const dlinked_list * const list,
                            void * key, int(* comparator)( void *, void * ),
                            size_t * result );

/**
 * Create a shallow copy.
 */
dlinked_list * dlinked_shallow_copy( const dlinked_list * const src );

/**
 * Sort a list using quicksort.
 * <p>
 * Will print error message and exit if a memory allocation error happens.
 * </p>
 * <p>
 * Comparator must use the given macros:
 * LHS_SMALLER
 * LHS_EQUAL
 * LHS_LARGER
 * </p
 *
 * @param list
 * @param comparator must return -1 if lhs < rhs, 0 if lhs = rhs, 1 if lhs > rhs
 * @return a shallow copy of list, sorted in ascending manner
 */
dlinked_list * dlinked_quicksort( dlinked_list * list, int comparator( void *, void * ));

/**
 * Quicksort the given list.
 * <p>
 * Will consume the passed list. If you intend to keep the unsorted list you must pass a copy.
 * </p>
 * @see dlinked_quicksort
 * @param will be consumed
 * @param malloc_error_handler a handler for memory allocation error
 * @param err_status a variable to pass into the error handler
 * @return a new list with the contents of list
 */
dlinked_list * dlinked_quicksort_custom_error_handler( dlinked_list * list,
                                                       int comparator( void *, void * ),
                                                       void(* malloc_error_handler)( void * ),
                                                       void * err_status );

/**
 * Apply func to every element in list.
 */
void dlinked_map( const dlinked_list * const list, void(* func)(void * ));

/**
 * Convert linked list to pointer to void *
 * @param list The list to convert
 * @param pointer Will contain the list items. Must be freed.
 * @return Success, or failure if failed to allocate memory.
 */
int dlinked_to_pointer(dlinked_list * list, void *** pointer);


#endif // DC_DLINKED_LIST_H
