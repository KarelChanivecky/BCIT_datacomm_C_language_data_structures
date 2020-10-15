// Copyright 2020 Andrey Goryelov :-)

#include "bit_array.h"

#include <stdlib.h>
#include <stdio.h>
#include "bitarray.h"

static uint8_t ONE_BIT = 1;

struct bit_array * bit_array_create(void) {
    struct bit_array * this = malloc(sizeof(struct bit_array));
    return this;
}

void bit_array_destroy(struct bit_array ** p_this) {
    free(*p_this);
    *p_this = NULL;
}

void bit_array_init(struct bit_array * this, size_t initial_bit_capacity) {
    size_t byte_capacity = (initial_bit_capacity + 7) / 8;
    this->array = calloc(byte_capacity, sizeof(uint8_t));
    this->bit_capacity = byte_capacity * 8;
    this->bit_length = 0;
}

static void bit_array_set_one(struct bit_array * this, size_t index) {
    this->array[index / 8] |= (ONE_BIT << (index % 8));
}

static void bit_array_set_zero(struct bit_array * this, size_t index) {
    this->array[index / 8] &= ~(ONE_BIT << (index % 8));
}

static bool bit_array_check(struct bit_array * this, size_t index) {
    return this->array[(index / 8)] & (ONE_BIT << (index % 8));
}

bool bit_array_check_bit(struct bit_array * this, size_t index) {
    if (index >= this->bit_length) {
        fprintf(stderr, "bit_array_set_bit: index out of bounds.\n");
        return -1;
    }
    return bit_array_check(this, index);
}

void bit_array_add_bit(struct bit_array * this, bool bit_value) {
    if (this->bit_length >= this->bit_capacity) {
        fprintf(stderr, "bit_array_add_bit: BitArray capacity reached.\n");
        return;
    }

    if (bit_value) {
        bit_array_set_one(this, this->bit_length++);
    } else {
        bit_array_set_zero(this, this->bit_length++);
    }
}

void bit_array_set_bit(struct bit_array * this, size_t index, bool bit_value) {
    if (index >= this->bit_length) {
        fprintf(stderr, "bit_array_set_bit: index out of bounds.\n");
        return;
    }

    if (bit_value) {
        bit_array_set_one(this, index);
    } else {
        bit_array_set_zero(this, index);
    }
}

void bit_array_pop_bit(struct bit_array * this) {
    if (this->bit_length == 0) return;
    bit_array_set_zero(this, --this->bit_length);
}