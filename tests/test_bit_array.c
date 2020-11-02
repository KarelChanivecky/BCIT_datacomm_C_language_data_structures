// Copyright 2020 Andrey Goryelov :-)

#include <stdio.h>
#include "../lib/bit_array.h"

static void test_bit_array_create() {
    bit_array * my_bits = bit_array_create();
    if (my_bits == NULL) {
        fprintf(stderr, "test_bit_array_create: failure\n" );
    } else {
        fprintf(stderr, "test_bit_array_create: success\n" );
    }
    bit_array_destroy( &my_bits );
}

static void test_bit_array_init() {
    bit_array * my_bits = bit_array_create();
    bit_array_init(my_bits, 1);
    if (my_bits->bit_capacity != 8 || my_bits->bit_length != 0) {
        fprintf(stderr, "test_bit_array_create: failure\n" );
    } else {
        fprintf(stderr, "test_bit_array_create: success\n" );
    }
    bit_array_destroy( &my_bits );
}

static void test_bit_array_dynamic_resize() {
    bit_array * my_bits = bit_array_create();
    bit_array_init(my_bits, 1);

    bit_array_add_bit(my_bits, 1);
    bit_array_add_bit(my_bits, 1);
    bit_array_add_bit(my_bits, 1);
    bit_array_add_byte(my_bits, 'a');
    bit_array_add_byte(my_bits, 'g');

    if (my_bits->bit_capacity != 32 || my_bits->bit_length != 19) {
        fprintf(stderr, "test_bit_array_create: failure\n" );
    } else {
        fprintf(stderr, "test_bit_array_create: success\n" );
    }

    bit_array_destroy( &my_bits );
}

static void test_bit_array_add_byte() {
    bit_array * my_bits = bit_array_create();
    bit_array_init(my_bits, 1);

    bit_array_add_bit(my_bits, 1);
    bit_array_add_bit(my_bits, 1);
    bit_array_add_bit(my_bits, 1);
    bit_array_add_byte(my_bits, 'a');
    bit_array_add_byte(my_bits, 'g');

    if (bit_array_check_byte(my_bits, 3) != 'a' || bit_array_check_byte(my_bits, 11) != 'g') {
        fprintf(stderr, "test_bit_array_create: failure\n" );
    } else {
        fprintf(stderr, "test_bit_array_create: success\n" );
    }

    bit_array_destroy( &my_bits );
}

static void test_bit_array_combine() {
    bit_array * first_array = bit_array_create();
    bit_array_init(first_array, 8);
    bit_array_add_byte(first_array, 'a');
    bit_array_add_byte(first_array, 'b');

    bit_array * second_array = bit_array_create();
    bit_array_init(second_array, 8);
    bit_array_add_byte(first_array, 'c');
    bit_array_add_byte(first_array, 'd');

    bit_array * combined = bit_array_combine(first_array, second_array);


    if (bit_array_check_byte(combined, 0) != 'a') {
        fprintf(stderr, "test_bit_array_combine: failure\n" );
    } else if (bit_array_check_byte(combined, 8) != 'b') {
        fprintf(stderr, "test_bit_array_combine: failure\n" );
    } else if (bit_array_check_byte(combined, 16) != 'c') {
        fprintf(stderr, "test_bit_array_combine: failure\n" );
    } else if (bit_array_check_byte(combined, 24) != 'd') {
        fprintf(stderr, "test_bit_array_combine: failure\n" );
    } else {
        fprintf(stderr, "test_bit_array_combine: success\n" );
    }

    bit_array_destroy( &first_array );
    bit_array_destroy( &second_array );
    bit_array_destroy( &combined );
}


int main() {
    test_bit_array_create();
    test_bit_array_init();
    test_bit_array_dynamic_resize();
    test_bit_array_add_byte();
    test_bit_array_combine();
    fprintf(stderr, "all tests are done\n");
    return 0;
}