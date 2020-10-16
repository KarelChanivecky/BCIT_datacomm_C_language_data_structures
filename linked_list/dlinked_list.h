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
 * It will provide push/pop/peek to head or tail at constant time.
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

/**
 * Represent a linked list node.
 */
struct list_dlink_s {
    struct list_dlink_s * next;
    struct list_dlink_s * prev;
    void * content;
};
typedef struct list_dlink_s * dlink;

/**
 * Represent a doubly linked list.
 */
struct dlinked_list_s {
    dlink head;
    dlink tail;
    size_t size;
};
typedef struct dlinked_list_s * dlinked_list;

/**
 * Initialize a dynamically allocated doubly linked list.
 * @return a dynamically allocated linked list. Will return NULL if memory allocation fails
 */
dlinked_list create_linked_list();

/**
 * Free a dynamically allocated linked list.
 * @param list a dlinked_list *. Will be set to NULL
 */
void free_list( dlinked_list * list );

/**
 * Add an element at the end.
 * @param list the list to add the element to
 * @param content the content of the new element
 * @return SUCCESS for success, else one of the defined error codes
 */
int push( dlinked_list list, void * content );

/**
 * Add an element at the start.
 * @param list the list to add the element to
 * @param content the content of the new element
 * @return SUCCESS for success, else one of the defined error codes
 */
int push_head( dlinked_list list, void * content );

/**
 * Remove the first element of the list and return its content.
 * @param list a dlinked_list with at least one element
 * @return the content of the first element. If list was empty, will return NULL
 */
void * pop_head( dlinked_list list );

/**
 * Remove the last element of the list and return its content.
 * @param list a dlinked_list with at least one element
 * @return the content of the first element. If list was empty, will return NULL
 */
void * pop_tail( dlinked_list list );

/**
 * Get the value in the tail.
 * @param list the list to peek into
 * @return the value in the tail
 */
void * peek_tail( dlinked_list list );

/**
 * Get the element at the given index.
 * @param list the list to get from
 * @param index must be such as 0 <= index < size
 * @return the element at the index or NULL if out of bounds
 */
void * get( dlinked_list list, size_t index );

/**
 * Remove element at given index and return its content.
 * @param the list to remove from
 * @param index must be such as 0 <= index < size
 * @return the element at the index or NULL if out of bounds
 */
void * extract( dlinked_list list, size_t index );

/**
 * Insert an element at the given index.
 *
 * Will displace the next elements by 1 index.
 *
 * @param index the exact index to do the insertion. index must be such as 0 <= index < size
 * @param content the content to insert
 * @return SUCCESS or one of the defined error codes
 */
int insert( dlinked_list list, size_t index, void * content);

/**
 * Set the given content at the given index.
 * @param index must be such as 0 <= index < size
 * @return SUCCESS or one of the defined errors
 */
int set( dlinked_list list, size_t index, void * content );

/**
 * Get the index of a given element.
 * @param list the list to search in
 * @param key the element to seek
 * @param comparator a predicate function
 * @param result_code will be assigned: <br/>
 * if key is found, success<br/>
 * if not found, FAILURE<br/>
 * if error occurred, one of the defined error codes
 * @return if key is contained, the index, if not found or error 0.
 */
size_t index_of( dlinked_list list, void * key, int(*comparator)(void *, void *), int * result_code);



#endif // DC_DLINKED_LIST_H
