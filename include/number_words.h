#pragma once

// array containing list of single digit words up to (and including) 19
// nw_digits[n] corresponds to n
extern const char *nw_digits[];

// array containing list of -ty words, with nw_tens[n] corresponding to 10n
extern const char *nw_tens[];

// array containing list of -illion words, with nw_illions[n] corresponding to 1000^n
extern const char *nw_illions[];

// number of illions
extern const long nw_n_illions;