#pragma once

// list of -illi- combining flags
// COMB_A is for if the tens prefix should end with an -a,
// given no following hundreds prefix
#define PW_ILLI_COMB_S 0x01
#define PW_ILLI_COMB_X 0x02
#define PW_ILLI_COMB_N 0x04
#define PW_ILLI_COMB_M 0x08
#define PW_ILLI_COMB_A 0x10

// array containing list of single digit words up to (and including) 19
// pw_digits[n] corresponds to n
extern const char *pw_digits[];

// array containing list of -ty words, with pw_tens[n] corresponding to 10n
extern const char *pw_tens[];

// array containing list of small -illi- prefixes, with pw_illi_small[n] corresponding to the nth -illi- prefix
// pw_illi_small[0] -> nilli, pw_illi_small[1] -> milli, pw_illi_small -> billi, etc.
extern const char *pw_illi_small[];

// length of the pw_illi_small array
extern const long pw_n_illi_small;

// array containing -illi- prefixes for the unit position of n in 10^(3n+3)
extern const char *pw_illi_unit[];

// array containing -illi- prefixes for the tens position of n in 10^(3n+3)
extern const char *pw_illi_tens[];

// array containing -illi- prefixes for the hundreds position of n in 10^(3n+3)
extern const char *pw_illi_hundreds[];

// array containing combining flags for the unit position -illi- prefixes
extern char pw_illi_unit_comb[];

// array containing combining flags for the tens position -illi- prefixes
extern char pw_illi_tens_comb[];

// array containing combining flags for the hundreds position -illi- prefixes
extern char pw_illi_hundreds_comb[];