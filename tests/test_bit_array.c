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


int main() {
    test_bit_array_create();
    test_bit_array_init();
    test_bit_array_dynamic_resize();
    test_bit_array_add_byte();
    fprintf(stderr, "all tests are done\n");
    return 0;
}