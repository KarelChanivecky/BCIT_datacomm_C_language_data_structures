/**
 * 10/15/2020
 * Created by Karel Chanivecky Garcia.
 * A01052674
 *
 * BCIT CST
 * dlinked_set_value O Datacomm
 *
 * data_structures
 */

#include <stdio.h>
#include <stdlib.h>
#include "../lib/dlinked_list.h"

static void test_dlinked_create_list() {
    dlinked_list * l = dlinked_create_list();
    if ( l && l->size == 0 && !l->head && !l->tail ) {
        fprintf(stderr, "test_dlinked_create_list: Success\n" );
    } else {
        fprintf(stderr, "test_dlinked_create_list: failure\n" );
    }
    dlinked_free_list( &l );
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
    dlinked_list * l = dlinked_create_list();
    void * result = func( l, NULL, NULL );
    if ( result == NULL) {
        fprintf(stderr, "test_result_of_passing_null_head_returns_void_ptr: Success\n" );
    } else {
        fprintf(stderr, "test_result_of_passing_null_head_returns_void_ptr: failure\n" );
    }
    dlinked_free_list( &l );
}

static void test_result_of_passing_out_of_bounds_returns_void_ptr(void * (* func)( void *, void *, void * )) {
    dlinked_list * l = dlinked_create_list();
    dlinked_push( l, NULL );
    dlinked_push( l, NULL );
    dlinked_push( l, NULL );
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
    dlinked_free_list( &l );
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
    dlinked_list * l = dlinked_create_list();
    int result = func( l, NULL, NULL );
    if ( result == BAD_ARGS) {
        fprintf(stderr, "test_result_of_passing_null_head_returns_numeric:  success\n" );
    } else {
        fprintf(stderr, "test_result_of_passing_null_head_returns_numeric:  failure\n" );
    }
    dlinked_free_list( &l );
}

static void test_result_of_passing_out_of_bounds_returns_numeric( void * (* func)( void *, void *, void * )) {
    dlinked_list * l = dlinked_create_list();
    dlinked_push( l, NULL );
    dlinked_push( l, NULL );
    dlinked_push( l, NULL );
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
    dlinked_free_list( &l );
}

static void test_dlinked_free_list() {
    dlinked_list * l = dlinked_create_list();
    dlinked_push(l, NULL);
    dlinked_free_list( &l );
    if ( l == NULL) {
        fprintf(stderr, "test_dlinked_free_list: success\n" );
    } else {
        fprintf(stderr, "test_dlinked_free_list: failure\n" );
    }
}

static void test_dlinked_push( ) {
    test_result_of_passing_null_list_returns_numeric(( void * ( * )( void *, void *, void * )) dlinked_push );
    dlinked_list * l = dlinked_create_list();
    dlinked_push(l, NULL);
    if (l->size == 1 && l->head && l->tail && l->head == l->tail) {
        fprintf(stderr, "test_dlinked_push: success\n" );
    } else {
        fprintf(stderr, "test_dlinked_push: failure\n" );
    }
    dlinked_free_list( &l );
}

// pass null, pass null head, pass not null head
static void test_dlinked_push_head( ) {
    test_result_of_passing_null_list_returns_numeric(( void * ( * )( void *, void *, void * )) dlinked_push_head );
    dlinked_list * l = dlinked_create_list();
    dlinked_push_head(l, NULL);
    if ( ! (l->size == 1 && l->head && l->tail && l->head == l->tail)) {
        fprintf(stderr, "test_dlinked_push_head 1: failure\n" );
    }
    dlinked_push_head(l, 1);
    if (l->head != l->tail && l->size == 2 && l->head->content == 1) {
        fprintf(stderr, "test_dlinked_push_head: success\n" );
    } else {
        fprintf(stderr, "test_dlinked_push_head 2: failure\n" );
    }
    dlinked_free_list( &l );
}

// pass null, pass null head, pass size 1, pass size 2
static void test_pop_head( ) {
    test_result_of_passing_null_list_returns_void_ptr(( void * ( * )( void *, void *, void * )) dlinked_pop_head );
    test_result_of_passing_null_head_returns_void_ptr(( void * ( * )( void *, void *, void * )) dlinked_pop_head );
    dlinked_list * l = dlinked_create_list();
    dlinked_push_head(l, NULL);
    dlinked_pop_head(l);
    if ( ! (l->size == 0 && !l->head && !l->tail )) {
        fprintf(stderr, "test_pop_head 1: failure\n" );
    }
    dlinked_push_head(l, 1);
    dlinked_push_head(l, 2);
    dlinked_pop_head(l);
    if (l->size == 1 && l->head && l->tail && l->head == l->tail && l->head->content == 1) {
        fprintf(stderr, "test_pop_head: success\n" );
    } else {
        fprintf(stderr, "test_pop_head 2: failure\n" );
    }
    dlinked_free_list( &l );
}

void test_dlinked_pop_tail() {
    test_result_of_passing_null_list_returns_void_ptr(( void * ( * )( void *, void *, void * )) dlinked_pop_tail );
    test_result_of_passing_null_head_returns_void_ptr(( void * ( * )( void *, void *, void * )) dlinked_pop_tail );
    dlinked_list * l = dlinked_create_list();
    dlinked_push_head(l, NULL);
    dlinked_pop_tail(l);
    if ( ! (l->size == 0 && !l->head && !l->tail )) {
        fprintf(stderr, "test_dlinked_pop_tail 1: failure\n" );
    }
    dlinked_push_head(l, 2);
    dlinked_push_head(l, 1);
    dlinked_pop_tail(l);
    if (l->size == 1 && l->head && l->tail && l->head == l->tail && l->head->content == 1) {
        fprintf(stderr, "test_dlinked_pop_tail: success\n" );
    } else {
        fprintf(stderr, "test_dlinked_pop_tail 2: failure\n" );
    }
    dlinked_free_list( &l );
}

// pass null, pass null head, pass size 1
void test_dlinked_peek_tail( ) {
    test_result_of_passing_null_list_returns_void_ptr(( void * ( * )( void *, void *, void * )) dlinked_peek_tail );
    test_result_of_passing_null_head_returns_void_ptr(( void * ( * )( void *, void *, void * )) dlinked_peek_tail );
    dlinked_list * l = dlinked_create_list();
    dlinked_push_head(l, 2);
    if (dlinked_peek_tail(l) == 2) {
        fprintf(stderr, "test_dlinked_peek_tail 1: success\n" );
    } else {
        fprintf(stderr, "test_dlinked_peek_tail 1: failure\n" );
    }
    dlinked_push(l, NULL);
    dlinked_push(l, 1);
    if (dlinked_peek_tail(l) == 1) {
        fprintf(stderr, "test_dlinked_peek_tail 2: success\n" );
    } else {
        fprintf(stderr, "test_dlinked_peek_tail 2: failure\n" );
    }
    dlinked_free_list( &l );
}

// pass null, pass null head, pass size 1, pass size 10, dlinked_get_value first, center, last, out of bounds
void test_dlinked_get_value( ) {
    test_result_of_passing_null_list_returns_void_ptr(( void * ( * )( void *, void *, void * )) dlinked_get_value );
    test_result_of_passing_null_head_returns_void_ptr(( void * ( * )( void *, void *, void * )) dlinked_get_value );
    test_result_of_passing_out_of_bounds_returns_void_ptr(( void * ( * )( void *, void *, void * )) dlinked_get_value );
    dlinked_list * l = dlinked_create_list();
    dlinked_push_head(l, 2);
    if (dlinked_get_value(l, 0) == 2) {
        fprintf(stderr, "test_dlinked_get_value 1: success\n" );
    } else {
        fprintf(stderr, "test_dlinked_get_value 1: failure\n" );
    }
    dlinked_push(l, NULL);
    dlinked_push(l, 1);
    if (dlinked_get_value(l, 2) == 1 && dlinked_get_value(l, 1) == NULL) {
        fprintf(stderr, "test_dlinked_get_value 2: success\n" );
    } else {
        fprintf(stderr, "test_dlinked_get_value 2: failure\n" );
    }
    dlinked_free_list( &l );
}

// pass null, pass null head, pass size 1, pass size 10, remove first, center, last, out of bounds
void test_dlinked_extract_value( ) {
    test_result_of_passing_null_list_returns_void_ptr(( void * ( * )( void *, void *, void * )) dlinked_extract_value );
    test_result_of_passing_null_head_returns_void_ptr(( void * ( * )( void *, void *, void * )) dlinked_extract_value );
    test_result_of_passing_out_of_bounds_returns_void_ptr(( void * ( * )( void *, void *, void * )) dlinked_extract_value );
    dlinked_list * l = dlinked_create_list();
    dlinked_push_head(l, 2);
    if (dlinked_extract_value(l, 0) == 2) {
        fprintf(stderr, "test_dlinked_extract_value 1: success\n" );
    } else {
        fprintf(stderr, "test_dlinked_extract_value 1: failure\n" );
    }
    dlinked_push(l, NULL);
    dlinked_push(l, 1);
    dlinked_push(l, 2);
    dlinked_push(l, 3);
    dlinked_push(l, 4);
    int res1 = dlinked_extract_value(l, 2);
    int res2 = dlinked_extract_value(l, 3);
    if ( res1 == 2 && res2 == 4) {
        fprintf(stderr, "test_dlinked_extract_value 2: success\n" );
    } else {
        fprintf(stderr, "test_dlinked_extract_value 2: failure\n" );
    }
    dlinked_free_list( &l );
}

// pass null, pass null head, pass size 1, pass size 10, remove first, center, last, out of bounds
void test_dlinked_insert_value( ) {
    test_result_of_passing_null_list_returns_numeric(( void * ( * )( void *, void *, void * )) dlinked_insert_value );
    test_result_of_passing_out_of_bounds_returns_numeric(( void * ( * )( void *, void *, void * )) dlinked_insert_value );
    dlinked_list * l = dlinked_create_list();
    if (dlinked_insert_value(l, 0, 1) == SUCCESS && l->head->prev == NULL) {
        fprintf(stderr, "test_dlinked_insert_value 1: success\n" );
    } else {
        fprintf(stderr, "test_dlinked_insert_value 1: failure\n" );
    }
    if (dlinked_insert_value(l, 0, NULL) == SUCCESS
    && dlinked_insert_value(l, 1, 2) == SUCCESS
    && dlinked_insert_value(l, 1, 3) == SUCCESS) {
        fprintf(stderr, "test_dlinked_insert_value 2: success\n" );
    } else {
        fprintf(stderr, "test_dlinked_insert_value 2: failure\n" );

    }
    if (dlinked_get_value(l, 0) == NULL
    && dlinked_get_value(l, 3) == 1
    && dlinked_get_value(l, 1) == 3
    && l->tail->next == NULL
    && l->size == 4) {
        fprintf(stderr, "test_dlinked_insert_value 3: success\n" );
    } else {
        fprintf(stderr, "test_dlinked_insert_value 3: failure\n" );
    }
    dlinked_free_list( &l );
}


void test_dlinked_set_value( ) {
    test_result_of_passing_null_list_returns_numeric(( void * ( * )( void *, void *, void * )) dlinked_set_value );
    test_result_of_passing_null_head_returns_numeric(( void * ( * )( void *, void *, void * )) dlinked_set_value );
    test_result_of_passing_out_of_bounds_returns_numeric(( void * ( * )( void *, void *, void * )) dlinked_set_value );
    dlinked_list * l = dlinked_create_list();
    dlinked_push_head(l, 2);
    if (dlinked_set_value(l, 0, 2) == SUCCESS && l->head->prev == NULL) {
        fprintf(stderr, "test_dlinked_set_value 1: success\n" );
    } else {
        fprintf(stderr, "test_dlinked_set_value 1: failure\n" );
    }
    dlinked_push(l, NULL);
    dlinked_push(l, 1);
    dlinked_push(l, 2);
    dlinked_push(l, 3);
    dlinked_push(l, 4);
    int res1 = dlinked_set_value(l, 2, 5);
    int res2 = dlinked_set_value(l, 5, 6);
    if ( res1 == SUCCESS
    && res2 == SUCCESS
    && dlinked_get_value(l, 2) == 5
    && dlinked_get_value(l, 5) == 6
    && l->size == 6
    && l->tail->next == NULL) {
        fprintf(stderr, "test_dlinked_set_value 2: success\n" );
    } else {
        fprintf(stderr, "test_dlinked_set_value 2: failure\n" );
    }
    dlinked_free_list( &l );
}

int comparator(void * lhs, void * rhs) {
    return lhs == rhs;
}

void test_dlinked_index_of_value( ) {
    int index1 = 0;
    if ( dlinked_index_of_value(NULL, NULL, NULL, &index1) == BAD_ARGS &&
         index1 == 0) {
        fprintf(stderr, "test_dlinked_index_of_value 1: success\n" );
    } else {
        fprintf(stderr, "test_dlinked_index_of_value 1: failure\n" );
    }


    int index2= 0;
    dlinked_list * l = dlinked_create_list();
    if ( dlinked_index_of_value(l, 1, comparator, &index2) == FAILURE &&
         index2 == 0) {
        fprintf(stderr, "test_dlinked_index_of_value 2: success\n" );
    } else {
        fprintf(stderr, "test_dlinked_index_of_value 2: failure\n" );
    }
    dlinked_push(l, 1);
    dlinked_push(l, 2);
    size_t index3 = 0;
    if (dlinked_index_of_value(l, 2, comparator, &index3) == SUCCESS
    && index3 == 1) {
        fprintf(stderr, "test_dlinked_index_of_value 3: success\n" );
    } else {
        fprintf(stderr, "test_dlinked_index_of_value 3: failure\n" );
    }
    dlinked_free_list( &l );
}

int size_comparator(void * lhs, void * rhs) {
    if (lhs < rhs) {
        return LHS_SMALLER;
    }
    if (lhs > rhs) {
        return LHS_LARGER;
    }
    return LHS_EQUAL;
}

void test_sort( ) {
    dlinked_list * list = dlinked_create_list();
    dlinked_push(list, 3);
    dlinked_push(list, 1);
    dlinked_push(list, 8);
    dlinked_push(list, 8);
    dlinked_push(list, 0);
    dlinked_push(list, 8);
    dlinked_push(list, 3);
    dlinked_push(list, 10);
    dlinked_list * sorted = dlinked_quicksort(list, size_comparator);
    size_t result_arr[] = {0, 1, 3, 3, 8, 8, 8, 10};
    int all_good = 1;
    for (int i = 0; i < 8; i++) {
        size_t el = (size_t) dlinked_pop_head(sorted);
        if (el != result_arr[i]) {
            fprintf(stderr, "sorting failure\nexpected: %zu\ngot: %zu\n", result_arr[i], el);
            all_good = 0;
        }
    }
    if (all_good) {
        fprintf(stderr, "sorting all good\n");
    }
    dlinked_free_list(&list);
    dlinked_free_list(&sorted);
}

void err_handler() {
    fprintf(stderr, "error in sort!");
    exit(EXIT_FAILURE);
}

void test_inplace_sort( ) {
    dlinked_list * list = dlinked_create_list();
    dlinked_push(list, 3);
    dlinked_push(list, 1);
    dlinked_push(list, 8);
    dlinked_push(list, 8);
    dlinked_push(list, 0);
    dlinked_push(list, 8);
    dlinked_push(list, 3);
    dlinked_push(list, 10);
    int status;
    list = dlinked_quicksort_custom_error_handler(list, size_comparator, err_handler, &status);
    size_t result_arr[] = {0, 1, 3, 3, 8, 8, 8, 10};
    int all_good = 1;
    for (int i = 0; i < 8; i++) {
        size_t el = (size_t) dlinked_pop_head(list);
        if (el != result_arr[i]) {
            fprintf(stderr, "sorting failure\nexpected: %zu\ngot: %zu\n", result_arr[i], el);
            all_good = 0;
        }
    }
    if (all_good) {
        fprintf(stderr, "sorting all good\n");
    }
    dlinked_free_list(&list);
}

void test_shallow_copy() {
    dlinked_list * list = dlinked_create_list();
    dlinked_push(list, 3);
    dlinked_push(list, 1);
    dlinked_push(list, 8);
    dlinked_push(list, 8);
    dlinked_push(list, 0);
    dlinked_push(list, 8);
    dlinked_push(list, 3);
    dlinked_push(list, 10);
    dlinked_list * shallow_copy = dlinked_shallow_copy(list);
    dlink * head = list->head;
    dlink * cp = shallow_copy->head;
    int index = 0;
    while (index < list->size && head->content == cp->content) {
        index++;
        head = head->next;
        cp = cp->next;
    }
    if (index == list->size) {
        fprintf(stderr, "shallow copy passed!\n");
    } else {
        fprintf(stderr,"shallow copy failed at index: %d\n", index);
    }
    dlinked_free_list(&list);
    dlinked_free_list(&shallow_copy);
}

void test_to_pointer() {
    u_int8_t ** pointer;
    dlink * head;

    dlinked_list * list = dlinked_create_list();
    dlinked_push(list, 3);
    dlinked_push(list, 1);
    dlinked_push(list, 8);
    dlinked_push(list, 8);
    dlinked_push(list, 0);
    dlinked_push(list, 8);
    dlinked_push(list, 3);
    dlinked_push(list, 10);
    if (dlinked_to_pointer(list, (void ***)&pointer)!= SUCCESS) {
        fprintf(stderr, "to pointer failed!\n");
        dlinked_free_list(&list);
        return;
    }

    head = list->head;
    int index = 0;
    while (index < list->size) {
        if (pointer[index] != head->content) {
            fprintf(stderr, "to pointer failed!\n");
            dlinked_free_list(&list);
            return;
        }

        index++;
        head = head->next;
    }
    fprintf(stderr, "to pointer passed!\n");
    dlinked_free_list(&list);
}


int main() {
    test_dlinked_free_list();
    test_dlinked_push();
    test_dlinked_push_head();
    test_pop_head();
    test_dlinked_pop_tail();
    test_dlinked_peek_tail();
    test_dlinked_get_value();
    test_dlinked_extract_value();
    test_dlinked_insert_value();
    test_dlinked_set_value();
    test_dlinked_index_of_value();
    test_sort();
    test_inplace_sort();
    test_shallow_copy();
    test_to_pointer();
    fprintf(stderr, "all tests are done\n");
    return 0;
}