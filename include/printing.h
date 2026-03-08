#pragma once

#include <stddef.h>
#include <stdio.h>

#include "string_scanning.h"

// prints the nth -ion word, corresponding to 10^3n
// this should theoretically be able to cover all inputs n
// uses conway-guy system, extended by milli- & -nilli-
// refer to https://en.wikipedia.org/wiki/Names_of_large_numbers#Extensions_of_the_standard_dictionary_numbers
void print_illion(FILE *f, int n);

// assumes that 1 <= length <= 3, ss_numbers(str, length), !ss_zeroesn(str, length)
void print_short_int(FILE *f, const char *str, int length);

// prints numbers as specified by SS_NUM_INTEGER
void print_int(FILE *f, const char *str, int length);

// prints numbers as specified by SS_NUM_FLOAT
void print_float(FILE *f, const char *str, int length);

// returns the file stream to be printed on given the kind
FILE *get_desired_f(FILE *f_valid, FILE *f_invalid, ss_num_kind kind);

// prints numbers as specified by the kind provided
// returns the file stream that was printed to, between f_valid and f_invalid
FILE *print_by_kindn(FILE *f_valid, FILE *f_invalid, const char *str, size_t length, ss_num_kind kind);

// equivalent to print_by_kindn(str, strlen(str), kind)
// returns the file stream that was printed to, between f_valid and f_invalid
FILE *print_by_kind(FILE *f_valid, FILE *f_invalid, const char *str, ss_num_kind kind);