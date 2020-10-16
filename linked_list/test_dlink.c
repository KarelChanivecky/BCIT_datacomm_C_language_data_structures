/**
 * 10/15/2020
 * Created by Karel Chanivecky Garcia.
 * A01052674
 *
 * BCIT CST
 * Set O Datacomm
 *
 * data_structures
 */

#include <stdio.h>
#include "dlinked_list.h"

static void test_create_linked_list() {
    dlinked_list l = create_linked_list();
    if ( l && l->size == 0 && !l->head && !l->tail ) {
        fprintf(stderr, "test_create_linked_list: Success\n" );
    } else {
        fprintf(stderr, "test_create_linked_list: failure\n" );
    }
    free_list(&l);
}

static void test_result_of_passing_null_list_returns_void_ptr( void * (* func)( void *, void *, void * )) {
    void * result = func(NULL, NULL, NULL );
    if ( result == NULL) {
        fprintf(stderr, "test_result_of_passing_null_list_returns_void_ptr: Success\n" );
    } else {
        fprintf(stderr, "test_result_of_passing_null_list_returns_void_ptr: failure\n" );
    }
}

static void test_result_of_passing_null_head_returns_void_ptr( void * (* func)( void *, void *, void * )) {
    dlinked_list l = create_linked_list();
    void * result = func( l, NULL, NULL );
    if ( result == NULL) {
        fprintf(stderr, "test_result_of_passing_null_head_returns_void_ptr: Success\n" );
    } else {
        fprintf(stderr, "test_result_of_passing_null_head_returns_void_ptr: failure\n" );
    }
    free_list(&l);
}

static void test_result_of_passing_out_of_bounds_returns_void_ptr(void * (* func)( void *, void *, void * )) {
    dlinked_list l = create_linked_list();
    push( l, NULL );
    push( l, NULL );
    push( l, NULL );
    void * result_under_bound = func( l, -1, NULL );
    if ( result_under_bound == NULL) {
        fprintf(stderr, "test_result_of_passing_out_of_bounds_returns_void_ptr: Underbound success\n" );
    } else {
        fprintf(stderr, "test_result_of_passing_out_of_bounds_returns_void_ptr: Underbound failure\n" );
    }
    void * result_over_bound = func( l, 10, NULL );
    if ( result_over_bound == NULL) {
        fprintf(stderr, "test_result_of_passing_out_of_bounds_returns_void_ptr: overbound success\n" );
    } else {
        fprintf(stderr, "test_result_of_passing_out_of_bounds_returns_void_ptr: overbound failure\n" );
    }
    free_list( &l );
}

static void test_result_of_passing_null_list_returns_numeric( void * (* func)( void *, void *, void * )) {

    int result = func(NULL, NULL, NULL );
    if ( result == BAD_ARGS) {
        fprintf(stderr, "test_result_of_passing_null_list_returns_numeric:  success\n" );
    } else {
        fprintf(stderr, "test_result_of_passing_null_list_returns_numeric:  failure\n" );
    }
}

static void test_result_of_passing_null_head_returns_numeric( void * (* func)( void *, void *, void * )) {
    dlinked_list l = create_linked_list();
    int result = func( l, NULL, NULL );
    if ( result == BAD_ARGS) {
        fprintf(stderr, "test_result_of_passing_null_head_returns_numeric:  success\n" );
    } else {
        fprintf(stderr, "test_result_of_passing_null_head_returns_numeric:  failure\n" );
    }
    free_list( &l );
}

static void test_result_of_passing_out_of_bounds_returns_numeric( void * (* func)( void *, void *, void * )) {
    dlinked_list l = create_linked_list();
    push( l, NULL );
    push( l, NULL );
    push( l, NULL );
    int result_under_bound =  func( l, -1, NULL );
    if ( result_under_bound == OUT_OF_BOUND_ERR) {
        fprintf(stderr, "test_result_of_passing_out_of_bounds_returns_numeric: Underbound success\n" );
    } else {
        fprintf(stderr, "test_result_of_passing_out_of_bounds_returns_numeric: Underbound failure\n" );
    }
    int result_over_bound =  func( l, 10, NULL );
    if ( result_over_bound == OUT_OF_BOUND_ERR) {
        fprintf(stderr, "test_result_of_passing_out_of_bounds_returns_numeric: overbound success\n" );
    } else {
        fprintf(stderr, "test_result_of_passing_out_of_bounds_returns_numeric: overbound failure\n" );
    }
    free_list( &l );
}

static void test_free_list() {
    dlinked_list l = create_linked_list();
    push(l, NULL);
    free_list(&l);
    if ( l == NULL) {
        fprintf(stderr, "test_free_list: success\n" );
    } else {
        fprintf(stderr, "test_free_list: failure\n" );
    }
}

static void test_push( ) {
    test_result_of_passing_null_list_returns_numeric(( void * ( * )( void *, void *, void * )) push );
    dlinked_list l = create_linked_list();
    push(l, NULL);
    if (l->size == 1 && l->head && l->tail && l->head == l->tail) {
        fprintf(stderr, "test_push: success\n" );
    } else {
        fprintf(stderr, "test_push: failure\n" );
    }
    free_list(&l);
}

// pass null, pass null head, pass not null head
static void test_push_head( ) {
    test_result_of_passing_null_list_returns_numeric(( void * ( * )( void *, void *, void * )) push_head );
    dlinked_list l = create_linked_list();
    push_head(l, NULL);
    if ( ! (l->size == 1 && l->head && l->tail && l->head == l->tail)) {
        fprintf(stderr, "test_push_head 1: failure\n" );
    }
    push_head(l, 1);
    if (l->head != l->tail && l->size == 2 && l->head->content == 1) {
        fprintf(stderr, "test_push_head: success\n" );
    } else {
        fprintf(stderr, "test_push_head 2: failure\n" );
    }
    free_list(&l);
}

// pass null, pass null head, pass size 1, pass size 2
static void test_pop_head( ) {
    test_result_of_passing_null_list_returns_void_ptr(( void * ( * )( void *, void *, void * )) pop_head );
    test_result_of_passing_null_head_returns_void_ptr(( void * ( * )( void *, void *, void * )) pop_head );
    dlinked_list l = create_linked_list();
    push_head(l, NULL);
    pop_head(l);
    if ( ! (l->size == 0 && !l->head && !l->tail )) {
        fprintf(stderr, "test_pop_head 1: failure\n" );
    }
    push_head(l, 1);
    push_head(l, 2);
    pop_head(l);
    if (l->size == 1 && l->head && l->tail && l->head == l->tail && l->head->content == 1) {
        fprintf(stderr, "test_pop_head: success\n" );
    } else {
        fprintf(stderr, "test_pop_head 2: failure\n" );
    }
    free_list(&l);
}

void test_pop_tail() {
    test_result_of_passing_null_list_returns_void_ptr(( void * ( * )( void *, void *, void * )) pop_tail );
    test_result_of_passing_null_head_returns_void_ptr(( void * ( * )( void *, void *, void * )) pop_tail );
    dlinked_list l = create_linked_list();
    push_head(l, NULL);
    pop_tail(l);
    if ( ! (l->size == 0 && !l->head && !l->tail )) {
        fprintf(stderr, "test_pop_tail 1: failure\n" );
    }
    push_head(l, 2);
    push_head(l, 1);
    pop_tail(l);
    if (l->size == 1 && l->head && l->tail && l->head == l->tail && l->head->content == 1) {
        fprintf(stderr, "test_pop_tail: success\n" );
    } else {
        fprintf(stderr, "test_pop_tail 2: failure\n" );
    }
    free_list(&l);
}

// pass null, pass null head, pass size 1
void test_peek_tail( ) {
    test_result_of_passing_null_list_returns_void_ptr(( void * ( * )( void *, void *, void * )) peek_tail );
    test_result_of_passing_null_head_returns_void_ptr(( void * ( * )( void *, void *, void * )) peek_tail );
    dlinked_list l = create_linked_list();
    push_head(l, 2);
    if (peek_tail(l) == 2) {
        fprintf(stderr, "test_peek_tail 1: success\n" );
    } else {
        fprintf(stderr, "test_peek_tail 1: failure\n" );
    }
    push(l, NULL);
    push(l, 1);
    if (peek_tail(l) == 1) {
        fprintf(stderr, "test_peek_tail 2: success\n" );
    } else {
        fprintf(stderr, "test_peek_tail 2: failure\n" );
    }
    free_list(&l);
}

// pass null, pass null head, pass size 1, pass size 10, get first, center, last, out of bounds
void test_get( ) {
    test_result_of_passing_null_list_returns_void_ptr(( void * ( * )( void *, void *, void * )) get );
    test_result_of_passing_null_head_returns_void_ptr(( void * ( * )( void *, void *, void * )) get );
    test_result_of_passing_out_of_bounds_returns_void_ptr(( void * ( * )( void *, void *, void * )) get );
    dlinked_list l = create_linked_list();
    push_head(l, 2);
    if (get(l, 0) == 2) {
        fprintf(stderr, "test_get 1: success\n" );
    } else {
        fprintf(stderr, "test_get 1: failure\n" );
    }
    push(l, NULL);
    push(l, 1);
    if (get(l, 2) == 1 && get(l, 1) == NULL) {
        fprintf(stderr, "test_get 2: success\n" );
    } else {
        fprintf(stderr, "test_get 2: failure\n" );
    }
    free_list(&l);
}

// pass null, pass null head, pass size 1, pass size 10, remove first, center, last, out of bounds
void test_extract( ) {
    test_result_of_passing_null_list_returns_void_ptr(( void * ( * )( void *, void *, void * )) extract );
    test_result_of_passing_null_head_returns_void_ptr(( void * ( * )( void *, void *, void * )) extract );
    test_result_of_passing_out_of_bounds_returns_void_ptr(( void * ( * )( void *, void *, void * )) extract );
    dlinked_list l = create_linked_list();
    push_head(l, 2);
    if (extract(l, 0) == 2) {
        fprintf(stderr, "test_extract 1: success\n" );
    } else {
        fprintf(stderr, "test_extract 1: failure\n" );
    }
    push(l, NULL);
    push(l, 1);
    push(l, 2);
    push(l, 3);
    push(l, 4);
    int res1 = extract(l, 2);
    int res2 = extract(l, 3);
    if ( res1 == 2 && res2 == 4) {
        fprintf(stderr, "test_extract 2: success\n" );
    } else {
        fprintf(stderr, "test_extract 2: failure\n" );
    }
    free_list(&l);
}

// pass null, pass null head, pass size 1, pass size 10, remove first, center, last, out of bounds
void test_insert( ) {
    test_result_of_passing_null_list_returns_numeric(( void * ( * )( void *, void *, void * )) insert );
    test_result_of_passing_out_of_bounds_returns_numeric(( void * ( * )( void *, void *, void * )) insert );
    dlinked_list l = create_linked_list();
    if (insert(l, 0, 1) == SUCCESS && l->head->prev == NULL) {
        fprintf(stderr, "test_insert 1: success\n" );
    } else {
        fprintf(stderr, "test_insert 1: failure\n" );
    }
    if (insert(l, 0, NULL) == SUCCESS
    && insert(l, 1, 2) == SUCCESS
    && insert(l, 1, 3) == SUCCESS) {
        fprintf(stderr, "test_insert 2: success\n" );
    } else {
        fprintf(stderr, "test_insert 2: failure\n" );

    }
    if (get(l, 0) == NULL
    && get(l, 3) == 1
    && get(l, 1) == 3
    && l->tail->next == NULL
    && l->size == 4) {
        fprintf(stderr, "test_insert 3: success\n" );
    } else {
        fprintf(stderr, "test_insert 3: failure\n" );
    }
    free_list(&l);
}


void test_set( ) {
    test_result_of_passing_null_list_returns_numeric(( void * ( * )( void *, void *, void * )) set );
    test_result_of_passing_null_head_returns_numeric(( void * ( * )( void *, void *, void * )) set );
    test_result_of_passing_out_of_bounds_returns_numeric(( void * ( * )( void *, void *, void * )) set );
    dlinked_list l = create_linked_list();
    push_head(l, 2);
    if (set(l, 0, 2) == SUCCESS && l->head->prev == NULL) {
        fprintf(stderr, "test_set 1: success\n" );
    } else {
        fprintf(stderr, "test_set 1: failure\n" );
    }
    push(l, NULL);
    push(l, 1);
    push(l, 2);
    push(l, 3);
    push(l, 4);
    int res1 = set(l, 2, 5);
    int res2 = set(l, 5, 6);
    if ( res1 == SUCCESS
    && res2 == SUCCESS
    && get(l, 2) == 5
    && get(l, 5) == 6
    && l->size == 6
    && l->tail->next == NULL) {
        fprintf(stderr, "test_set 2: success\n" );
    } else {
        fprintf(stderr, "test_set 2: failure\n" );
    }
    free_list(&l);
}

int comparator(void * lhs, void * rhs) {
    return lhs == rhs;
}

void test_index_of( ) {
    int status1;
    if (index_of(NULL, NULL, NULL, &status1) == 0 &&
    status1 == BAD_ARGS) {
        fprintf(stderr, "test_index_of 1: success\n" );
    } else {
        fprintf(stderr, "test_index_of 1: failure\n" );
    }
    int status2;
    dlinked_list l = create_linked_list();
    if (index_of(NULL, 1, comparator, &status2) == 0 &&
        status2 == BAD_ARGS) {
        fprintf(stderr, "test_index_of 2: success\n" );
    } else {
        fprintf(stderr, "test_index_of 2: failure\n" );
    }
    push(l, 1);
    push(l, 2);
    int status3;
    if (index_of(l, 2, comparator, &status3) == 1
    && status3 == SUCCESS) {
        fprintf(stderr, "test_index_of 3: success\n" );
    } else {
        fprintf(stderr, "test_index_of 3: failure\n" );
    }
    free_list(&l);
}


int main() {
    test_free_list();
    test_push();
    test_push_head();
    test_pop_head();
    test_pop_tail();
    test_peek_tail();
    test_get();
    test_extract();
    test_insert();
    test_set();
    test_index_of();
    return 0;
}