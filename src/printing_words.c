#include "printing_words.h"

const char *pw_digits[] = {
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
    "ten",
    "eleven",
    "twelve",
    "thirteen",
    "fourteen",
    "fifteen",
    "sixteen",
    "seventeen",
    "eighteen",
    "nineteen",
};

const char *pw_tens[] = {
    "zero",
    "ten",
    "twenty",
    "thirty",
    "forty",
    "fifty",
    "sixty",
    "seventy",
    "eighty",
    "ninety",
};

const char *pw_illi_small[] = {
    "nilli",
    "milli",
    "billi",
    "trilli",
    "quadrilli",
    "quintilli",
    "sextilli",
    "septilli",
    "octilli",
    "nonilli",
    "decilli",
    "undecilli",
    "duodecilli",
    "tredecilli",
    "quattuordecilli",
    "quindecilli",
    "sexdecilli", // we use the dictionary word here
    "septendecilli",
    "octodecilli",
    "novemdecilli", // we use the dictionary word here
};

const long pw_n_illi_small = sizeof(pw_illi_small) / sizeof(pw_illi_small[0]);

const char *pw_illi_unit[] = {
    "",
    "un",
    "duo",
    "tre",
    "quattuor",
    "quin",
    "se",
    "septe",
    "octo",
    "nove"
};

const char *pw_illi_tens[] = {
    "",
    "dec",
    "vigint",
    "trigint",
    "quadragint",
    "quinquagint",
    "sexagint",
    "septuagint",
    "octogint",
    "nonagint"
};

const char *pw_illi_hundreds[] = {
    "",
    "centi",
    "ducenti",
    "trecenti",
    "quadringenti",
    "quingenti",
    "sescenti",
    "septingenti",
    "octingenti",
    "nongenti"
};

char pw_illi_unit_comb[] = {
    0, 0, 0,
    PW_ILLI_COMB_S,                  // 3: tre -> tres
    0, 0,
    PW_ILLI_COMB_S | PW_ILLI_COMB_X, // 6: se -> ses, sex
    PW_ILLI_COMB_M | PW_ILLI_COMB_N, // 7: septe -> septem, septen
    0,
    PW_ILLI_COMB_M | PW_ILLI_COMB_N, // 9: nove -> novem, noven
};

char pw_illi_tens_comb[] = {
    0,
    PW_ILLI_COMB_N,                                   // 1: deci
    PW_ILLI_COMB_M | PW_ILLI_COMB_S,                  // 2: viginti
    PW_ILLI_COMB_N | PW_ILLI_COMB_S | PW_ILLI_COMB_A, // 3: triginta
    PW_ILLI_COMB_N | PW_ILLI_COMB_S | PW_ILLI_COMB_A, // 4: quadraginta
    PW_ILLI_COMB_N | PW_ILLI_COMB_S | PW_ILLI_COMB_A, // 5: quinquaginta
    PW_ILLI_COMB_N | PW_ILLI_COMB_A,                  // 6: sexaginta
    PW_ILLI_COMB_N | PW_ILLI_COMB_A,                  // 7: septuaginta
    PW_ILLI_COMB_M | PW_ILLI_COMB_X | PW_ILLI_COMB_A, // 8: octoginta
    PW_ILLI_COMB_A,                                   // 9: nonaginta
};

char pw_illi_hundreds_comb[] = {
    0,
    PW_ILLI_COMB_N | PW_ILLI_COMB_X, // 1: centi
    PW_ILLI_COMB_N,                  // 2: ducenti
    PW_ILLI_COMB_N | PW_ILLI_COMB_S, // 3: trecenti
    PW_ILLI_COMB_N | PW_ILLI_COMB_S, // 4: quadringenti
    PW_ILLI_COMB_N | PW_ILLI_COMB_S, // 5: quingenti
    PW_ILLI_COMB_N,                  // 6: sescenti
    PW_ILLI_COMB_N,                  // 7: septingenti
    PW_ILLI_COMB_M | PW_ILLI_COMB_X, // 8: octingenti
    0,
};