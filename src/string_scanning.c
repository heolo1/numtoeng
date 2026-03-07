#include "string_scanning.h"

#include <stdbool.h>

bool ss_empty(const char *str) {
    return str[0] == '\0';
}

bool ss_zeroesn(const char *str, int length) {
    for (int i = 0; i < length; i++) {
        if (str[i] != '0') {
            return false;
        }
    }
    return true;
}

bool ss_zeroes(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != '0') {
            return false;
        }
    }
    return true;
}

bool ss_number(char c) {
    return c >= '0' && c <= '9';
}

bool ss_numbersn(const char *str, int length) {
    for (int i = 0; i < length; i++) {
        if (!ss_number(str[i])) {
            return false;
        }
    }
    return true;
}

bool ss_numbers(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!ss_number(str[i])) {
            return false;
        }
    }
    return true;
}

ss_num_kind ss_get_num_kind(const char *str) {
    if (ss_empty(str)) {
        return SS_NUM_INVALID;
    }

    bool str1_numbers = ss_numbers(str + 1);

    if (ss_number(str[0]) && str1_numbers) {
        return SS_NUM_PLAIN_INTEGER;
    }

    if ((str[0] == '+' || str[0] == '-') &&
        !ss_empty(str + 1) &&
        str1_numbers) {
        return SS_NUM_SIGNED_INTEGER;
    }

    // will add more later
    return SS_NUM_INVALID;
}