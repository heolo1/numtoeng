#include "number_words.h"

const char *nw_digits[] = {
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

const char *nw_tens[] = {
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

const char *nw_illions[] = {
    "zero",
    "thousand",
    "million",
    "billion",
    "trillion",
    "quadrillion",
};

const long nw_n_illions = sizeof(nw_illions) / sizeof(nw_illions[0]);