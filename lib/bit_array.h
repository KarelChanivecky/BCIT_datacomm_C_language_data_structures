// Copyright 2020 Andrey Goryelov :-)

#ifndef DC_LIBS_BIT_ARRAY_H
#define DC_LIBS_BIT_ARRAY_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define OPERATION_SUCCESS   0
#define OPERATION_FAIL      -1

/**
 * Array of bits of static size. Size is dlinked_set_value when bit_array is initialized.
 * The bits are added left to right.
 *
 * Example: you create bit_array with minimum capacity of 16 bits
 * and then add 4 individual bits: 1 -> 1 -> 0 -> 1 to the array.
 * Your data will be stored like so: [1 1 0 1 0 0 0 0] [0 0 0 0 0 0 0 0]
 *
 * Note: bit_length is separate from bit_capacity meaning that after
 * you initialize the array, you still need to add the bits before
 * setting or checking them. An advantage of this is that the
 * array is able to track it's own length exactly to the bit, rather
 * than in chunks of 8.
 */
struct bit_array_s {
    uint8_t * array;
    size_t bit_length;
    size_t bit_capacity;
    bool enable_error_logs;
};

typedef struct bit_array_s * bit_array;

/**
 * Allocates memory for a new bit_array.
 * @return pointer to a newly created bit_array
 */
bit_array bit_array_create( void );

/**
 * Frees the memory taken up by bit_array and sets its pointer to NULL.
 * @param p_this pointer to pointer to bit_array
 */
void bit_array_destroy( bit_array * p_this );

/**
 * Initializes bit_array that can hold at least min_bit_capacity bits. Actual capacity
 * is rounded up to the closes multiple of 8 bits (closest byte).
 * @param this pointer to bit_array
 * @param min_bit_capacity minimum number of bits the array should be able to hold
 */
int bit_array_init( bit_array this, size_t min_bit_capacity );

/**
 * Use this to enable and disable errors printed to stderr.
 * Logging is disabled by default.
 */
void bit_array_set_logging( bit_array this, bool enable_logging );

/**
 * Checks the bit at the specified index and returns its value (1 or 0).
 * Returns -1 and prints an error if the index is larger than length of bit_array.
 */
bool bit_array_check_bit( bit_array this, size_t index );

/**
 * Checks the byte starting at the specified index and returns its value.
 * Returns -1 and prints an error if the (index + 7) is larger than length of bit_array.
 */
uint8_t bit_array_check_byte( bit_array this, size_t index );

/**
 * Adds a new bit to the array specified by bit_value param. This will increase
 * the bit_length of the array by 1. If bit_length of the array exceeds bit_capacity,
 * new bit will not be added an an error will be printed to stderr.
 */
int bit_array_add_bit( bit_array this, bool bit_value );

/**
 * Adds 8 bits to the array specified by bit_value param. This will increase
 * the bit_length of the array by 8. If new bit_length of the array exceeds bit_capacity,
 * new bits will not be added an an error will be printed to stderr.
 */
int bit_array_add_byte( bit_array this, uint8_t byte_value );

/**
 * Sets the value of a bit at index to bit_value. This will fail if the bit has not yet been
 * added to the array (AKA index >= bit_length), even if bit_capacity allows it.
 */
int bit_array_set_bit( bit_array this, size_t index, bool bit_value );

/**
 * If array is not empty, removes the last added bit from the array.
 */
int bit_array_pop_bit( bit_array this );

#endif //DC_LIBS_BIT_ARRAY_H
