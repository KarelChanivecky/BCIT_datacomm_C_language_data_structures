// Copyright 2020 Andrey Goryelov :-)

#include "bit_array.h"

#include <stdlib.h>
#include <stdio.h>

#define MASK_00000001 0x01
#define MASK_00000010 0x02
#define MASK_00000100 0x04
#define MASK_00001000 0x08
#define MASK_00010000 0x10
#define MASK_00100000 0x20
#define MASK_01000000 0x40
#define MASK_10000000 0x80

#define BYTE 8
#define BIT 1

bit_array bit_array_create(void) {
    bit_array this = calloc(1, sizeof(struct bit_array_s));
    return this;
}

void bit_array_destroy(bit_array * p_this) {
    free((*p_this)->array);
    free(*p_this);
    *p_this = NULL;
}

void bit_array_init(bit_array this, size_t initial_bit_capacity) {
    size_t byte_capacity = (initial_bit_capacity + 7) / BYTE;
    this->array = calloc(byte_capacity, sizeof(uint8_t));
    this->bit_capacity = byte_capacity * BYTE;
    this->bit_length = 0;
}

static void bit_array_set_one(bit_array this, size_t index) {
    this->array[index / BYTE] |= (BIT << (index % BYTE));
}

static void bit_array_set_zero(bit_array this, size_t index) {
    this->array[index / BYTE] &= ~(BIT << (index % BYTE));
}

static bool bit_array_check(bit_array this, size_t index) {
    return this->array[(index / BYTE)] & (BIT << (index % 8));
}

bool bit_array_check_bit(bit_array this, size_t index) {
    if (index >= this->bit_length) {
        fprintf(stderr, "bit_array_set_bit: index out of bounds.\n");
        return -1;
    }
    return bit_array_check(this, index);
}

uint8_t bit_array_check_byte(bit_array this, size_t index) {
    if ((index + BYTE) > this->bit_length) {
        fprintf(stderr, "bit_array_set_bit: index out of bounds.\n");
        return -1;
    }
    uint8_t byte = 0;
    byte += bit_array_check_bit(this, index++) * 128;
    byte += bit_array_check_bit(this, index++) * 64;
    byte += bit_array_check_bit(this, index++) * 32;
    byte += bit_array_check_bit(this, index++) * 16;
    byte += bit_array_check_bit(this, index++) * 8;
    byte += bit_array_check_bit(this, index++) * 4;
    byte += bit_array_check_bit(this, index++) * 2;
    byte += bit_array_check_bit(this, index++) * 1;

    return byte;
}

void bit_array_add_bit(bit_array this, bool bit_value) {
    if (this->bit_length >= this->bit_capacity) {
        fprintf(stderr, "bit_array_add_bit: byte_array capacity reached.\n");
        return;
    }

    if (bit_value) {
        bit_array_set_one(this, this->bit_length++);
    } else {
        bit_array_set_zero(this, this->bit_length++);
    }
}

void bit_array_set_bit(bit_array this, size_t index, bool bit_value) {
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

void bit_array_pop_bit(bit_array this) {
    if (this->bit_length == 0) return;
    bit_array_set_zero(this, --this->bit_length);
}

static bool get_bit_value(uint8_t val, uint8_t mask) {
    uint8_t masked = val & mask;

    if(masked > 0) {
        return true;
    } else {
        return false;
    }
}

void bit_array_add_byte(bit_array this, uint8_t byte_value) {
    if ((this->bit_length + BYTE) > this->bit_capacity) {
        fprintf(stderr, "bit_array_add_byte: byte_array capacity reached.\n");
        return;
    }

    bit_array_add_bit(this, get_bit_value(byte_value, MASK_10000000));
    bit_array_add_bit(this, get_bit_value(byte_value, MASK_01000000));
    bit_array_add_bit(this, get_bit_value(byte_value, MASK_00100000));
    bit_array_add_bit(this, get_bit_value(byte_value, MASK_00010000));
    bit_array_add_bit(this, get_bit_value(byte_value, MASK_00001000));
    bit_array_add_bit(this, get_bit_value(byte_value, MASK_00000100));
    bit_array_add_bit(this, get_bit_value(byte_value, MASK_00000010));
    bit_array_add_bit(this, get_bit_value(byte_value, MASK_00000001));
}
