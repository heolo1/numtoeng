#pragma once

#include <stdbool.h>

typedef enum {
    SS_NUM_INVALID,

    // we will merge PLAIN_INTEGER and SIGNED_INTEGER eventually, maybe
    SS_NUM_PLAIN_INTEGER, // anything of the form [0-9]+
    SS_NUM_SIGNED_INTEGER, // anything of the form (-|\+)[0-9]+
} ss_num_kind;

// returns true if the null-terminated string is an empty string
bool ss_empty(const char *str);

// returns true if [str, str + length) entirely consists of 0s
bool ss_zeroesn(const char *str, int length);
// returns true if the null-terminated string entirely consists of 0s
bool ss_zeroes(const char *str);

// returns true if c is in the range ['0', '9']
bool ss_number(char c);
// returns true if [str, str + length] entirely consists of numbers
bool ss_numbersn(const char *str, int length);
// returns true if the null-terminated string entirely consists of numbers
bool ss_numbers(const char *str);

// returns the type of the number in the string, determining how it will be parsed
ss_num_kind ss_get_num_kind(const char *str);