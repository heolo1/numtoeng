#pragma once

#include "string_scanning.h"

// prints the nth -ion word, corresponding to 10^3n
// this should theoretically be able to cover all inputs n
// uses conway-guy system, extended by milli- & -nilli-
// refer to https://en.wikipedia.org/wiki/Names_of_large_numbers#Extensions_of_the_standard_dictionary_numbers
void print_illion(int n);

// assumes that 1 <= length <= 3, ss_numbers(str, length), !ss_zeroesn(str, length)
void print_short_int(const char *str, int length);

// prints numbers as specified by SS_NUM_PLAIN_INTEGER
void print_plain_int(const char *str, int length);

// prints numbers as specified by SS_NUM_SIGNED_INTEGER
void print_signed_int(const char *str, int length);

// prints numbers as specified by the kind provided
void print_by_kindn(const char *str, int length, ss_num_kind kind);

// equivalent to print_by_kindn(str, strlen(str), kind)
void print_by_kind(const char *str, ss_num_kind kind);