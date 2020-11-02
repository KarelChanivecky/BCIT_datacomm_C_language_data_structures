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

#define BYTE    8
#define BIT     1

static void bit_array_set_one( bit_array * this, size_t index ) {
    this->array[ index / BYTE ] |= ( BIT << ( index % BYTE ));
}

static void bit_array_set_zero( bit_array * this, size_t index ) {
    this->array[ index / BYTE ] &= ~( BIT << ( index % BYTE ));
}

static bool bit_array_check( bit_array * this, size_t index ) {
    return this->array[ ( index / BYTE ) ] & ( BIT << ( index % 8 ));
}

static bool get_bit_value( uint8_t val, uint8_t mask ) {
    if ( val & mask ) {
        return true;
    } else {
        return false;
    }
}

bit_array * bit_array_create( void ) {
    bit_array * this = calloc( 1, sizeof( struct bit_array_s ));
    if ( this == NULL) return NULL;
    return this;
}

void bit_array_destroy( bit_array ** p_this ) {
    free( *p_this );
    *p_this = NULL;
}

int bit_array_init( bit_array * this, size_t initial_bit_capacity ) {
    size_t byte_capacity = ( initial_bit_capacity + 7 ) / BYTE;

    this->array = calloc( byte_capacity, sizeof( uint8_t ));
    if ( this->array == NULL) return OPERATION_FAIL;

    this->bit_capacity = byte_capacity * BYTE;
    this->bit_length = 0;
    this->enable_error_logs = false;
    return OPERATION_SUCCESS;
}

void bit_array_set_logging( bit_array * this, bool enable_logging ) {
    this->enable_error_logs = enable_logging;
}

int bit_array_check_bit( bit_array * this, size_t index ) {
    if ( index >= this->bit_length ) {
        if ( this->enable_error_logs ) fprintf( stderr, "bit_array_set_bit: index out of bounds.\n" );
        return OPERATION_FAIL;
    }
    return bit_array_check( this, index );
}

uint8_t bit_array_check_byte( bit_array * this, size_t index ) {
    if (( index + BYTE ) > this->bit_length ) {
        if ( this->enable_error_logs ) fprintf( stderr, "bit_array_set_bit: index out of bounds.\n" );
        return OPERATION_FAIL;
    }

    uint8_t byte = 0;
    byte += bit_array_check_bit( this, index++ ) * 128;
    byte += bit_array_check_bit( this, index++ ) * 64;
    byte += bit_array_check_bit( this, index++ ) * 32;
    byte += bit_array_check_bit( this, index++ ) * 16;
    byte += bit_array_check_bit( this, index++ ) * 8;
    byte += bit_array_check_bit( this, index++ ) * 4;
    byte += bit_array_check_bit( this, index++ ) * 2;
    byte += bit_array_check_bit( this, index++ ) * 1;

    return byte;
}

int bit_array_add_bit( bit_array * this, bool bit_value ) {
    if ( this->bit_length >= this->bit_capacity ) {
        this->bit_capacity = ( this->bit_capacity ) * 2;
        size_t byte_capacity = this->bit_capacity / BYTE;
        uint8_t * ptr = realloc( this->array, byte_capacity * sizeof( uint8_t ));
        if (ptr == NULL) return OPERATION_FAIL;
        else this->array = ptr;
    }

    if ( bit_value ) {
        bit_array_set_one( this, this->bit_length++ );
    } else {
        bit_array_set_zero( this, this->bit_length++ );
    }
    return OPERATION_SUCCESS;
}

int bit_array_set_bit( bit_array * this, size_t index, bool bit_value ) {
    if ( index >= this->bit_length ) {
        if ( this->enable_error_logs ) fprintf( stderr, "bit_array_set_bit: index out of bounds.\n" );
        return OPERATION_FAIL;
    }

    if ( bit_value ) {
        bit_array_set_one( this, index );
    } else {
        bit_array_set_zero( this, index );
    }

    return OPERATION_SUCCESS;
}

int bit_array_pop_bit( bit_array * this ) {
    if ( this->bit_length == 0 ) return OPERATION_FAIL;
    bit_array_set_zero( this, --this->bit_length );
    return OPERATION_SUCCESS;
}

int bit_array_add_byte( bit_array * this, uint8_t byte_value ) {
    bit_array_add_bit( this, get_bit_value( byte_value, MASK_10000000 ));
    bit_array_add_bit( this, get_bit_value( byte_value, MASK_01000000 ));
    bit_array_add_bit( this, get_bit_value( byte_value, MASK_00100000 ));
    bit_array_add_bit( this, get_bit_value( byte_value, MASK_00010000 ));
    bit_array_add_bit( this, get_bit_value( byte_value, MASK_00001000 ));
    bit_array_add_bit( this, get_bit_value( byte_value, MASK_00000100 ));
    bit_array_add_bit( this, get_bit_value( byte_value, MASK_00000010 ));
    bit_array_add_bit( this, get_bit_value( byte_value, MASK_00000001 ));

    return OPERATION_SUCCESS;
}


int bit_array_add_byte_reversed( bit_array * this, uint8_t byte_value ) {
    bit_array_add_bit( this, get_bit_value( byte_value, MASK_00000001 ));
    bit_array_add_bit( this, get_bit_value( byte_value, MASK_00000010 ));
    bit_array_add_bit( this, get_bit_value( byte_value, MASK_00000100 ));
    bit_array_add_bit( this, get_bit_value( byte_value, MASK_00001000 ));
    bit_array_add_bit( this, get_bit_value( byte_value, MASK_00010000 ));
    bit_array_add_bit( this, get_bit_value( byte_value, MASK_00100000 ));
    bit_array_add_bit( this, get_bit_value( byte_value, MASK_01000000 ));
    bit_array_add_bit( this, get_bit_value( byte_value, MASK_10000000 ));

    return OPERATION_SUCCESS;
}

bit_array * bit_array_combine(bit_array * first, bit_array * second) {
    bit_array * combined = bit_array_create();
    bit_array_init(combined, 8);

    for (size_t i = 0; i < first->bit_length; i++) {
        int bit = bit_array_check_bit(first, i);
        bit_array_add_bit(combined, bit);
    }

    for (size_t i = 0; i < second->bit_length; i++) {
        int bit = bit_array_check_bit(second, i);
        bit_array_add_bit(combined, bit);
    }

    return combined;
}

bit_array * bit_array_clone(bit_array * this) {
    bit_array * copy = bit_array_create();
    bit_array_init(copy, 8);

    for (size_t i = 0; i < this->bit_length; i++) {
        int bit = bit_array_check_bit(this, i);
        bit_array_add_bit(copy, bit);
    }

    return copy;
}
