#include "string_scanning.h"

#include <ctype.h>
#include <stdbool.h>

bool ss_empty(const char *str) {
    return str[0] == '\0';
}

int ss_zero_cntn(const char *str, int length) {
    for (int i = 0; i < length; i++) {
        if (str[i] != '0') {
            return i;
        }
    }
    return length;
}

int ss_zero_cnt(const char *str) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != '0') {
            break;
        }
    }
    return i;
}

bool ss_zeroesn(const char *str, int length) {
    return ss_zero_cntn(str, length) == length;
}

bool ss_zeroes(const char *str) {
    return str[ss_zero_cnt(str)] == '\0';
}

bool ss_number(char c) {
    return c >= '0' && c <= '9';
}

int ss_number_cntn(const char *str, int length) {
    for (int i = 0; i < length; i++) {
        if (!ss_number(str[i])) {
            return i;
        }
    }
    return length;
}

int ss_number_cnt(const char *str) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        if (!ss_number(str[i])) {
            break;
        }
    }
    return i;
}

bool ss_numbersn(const char *str, int length) {
    return ss_number_cntn(str, length) == length;
}

bool ss_numbers(const char *str) {
    return str[ss_number_cnt(str)] == '\0';
}

static bool ss_is_end_(int ch) {
    return ch == 0 || isspace(ch);
}

ss_num_kind ss_get_num_kind(const char *str) {
    if (ss_empty(str)) {
        return SS_NUM_INVALID;
    }
    
    if (str[0] == '+' || str[0] == '-') {
        str++;
    }

    int numbers = ss_number_cnt(str);

    if (numbers && ss_is_end_(str[numbers])) {
        return SS_NUM_INTEGER;
    }

    if (str[numbers] == '.') {
        int post_decimal = ss_number_cnt(str + numbers + 1);
        if ((numbers || post_decimal) &&
            ss_is_end_(str[numbers + post_decimal + 1])) {
            return SS_NUM_FLOAT;
        }
    }

    // will add more later
    return SS_NUM_INVALID;
}