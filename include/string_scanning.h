#pragma once

#include <stdbool.h>

typedef enum {
    SS_NUM_INVALID,

    SS_NUM_INTEGER, // anything of the form (-|\+)?[0-9]+
    SS_NUM_FLOAT, // anything of the form (-|\+)?([0-9]*\.[0-9]+)|([0-9]+\.[0-9]*)
} ss_num_kind;

// returns true if the null-terminated string is an empty string
bool ss_empty(const char *str);

// returns the index of the first character that is not '0'
// returns length if the entirety of [str, str + length) is '0' 
int ss_zero_cntn(const char *str, int length);
// like ss_zero_cntn, but stops at \0.
int ss_zero_cnt(const char *str);
// returns true if [str, str + length) entirely consists of 0s
bool ss_zeroesn(const char *str, int length);
// returns true if the null-terminated string entirely consists of 0s
bool ss_zeroes(const char *str);

// returns true if c is in the range ['0', '9']
bool ss_number(char c);
// returns the index of the first non-number (as specified by ss_number) char
// returns length if the entirety of [str, str + length) is a number 
int ss_number_cntn(const char *str, int length);
// like ss_number_cntn, but stops at \0.
int ss_number_cnt(const char *str);
// returns true if [str, str + length] entirely consists of numbers
bool ss_numbersn(const char *str, int length);
// returns true if the null-terminated string entirely consists of numbers
bool ss_numbers(const char *str);

// returns the type of the number in the string, determining how it will be parsed
ss_num_kind ss_get_num_kind(const char *str);