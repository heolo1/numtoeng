#pragma once

// array containing list of single digit words up to (and including) 19
// pw_digits[n] corresponds to n
extern const char *pw_digits[];

// array containing list of -ty words, with pw_tens[n] corresponding to 10n
extern const char *pw_tens[];

// array containing list of small -illion words, with pw_illions[n] corresponding to 1000^n
extern const char *pw_illions[];

// number of illions
extern const long pw_n_illions;