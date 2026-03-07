#include "printing.h"

#include <stdio.h>
#include <string.h>

#include "printing_words.h"
#include "string_scanning.h"

void print_short_int(const char *str, int length) {
    str += length - 3;

    int ones = str[2] - '0';
    int tens = length >= 2 ? str[1] - '0' : 0;
    int hundreds = length >= 3 ? str[0] - '0' : 0;
    
    if (hundreds) {
        printf(nw_digits[hundreds]);
        printf(" hundred");
        if (ones || tens) {
            printf(" ");
        }
    }
    if (tens >= 2) {
        printf(nw_tens[tens]);
        if (ones) {
            printf("-");
            printf(nw_digits[ones]);
        }
    } else {
        printf(nw_digits[tens * 10 + ones]);
    }
}

void print_plain_int(const char *str, int length) {
    if (ss_zeroesn(str, length)) {
        printf(nw_digits[0]);
        return;
    }

    for (; str[0] == '0'; length--, str++);

    int max_illion = (length - 1) / 3;
    if (max_illion >= nw_n_illions) {
        printf("big num"); // not supported!
        return;
    }

    // length mod 3 != 0, handle that here
    int beginning_digits = length % 3;
    bool needs_space = false;
    if (beginning_digits) {
        if (!ss_zeroesn(str, beginning_digits)) {
            print_short_int(str, beginning_digits);
            printf(" ");
            if (max_illion) {
                printf(nw_illions[max_illion]);
            }
            needs_space = true;
        }
        max_illion--;
    }

    for (int i = beginning_digits; i < length; i += 3, max_illion--) {
        if (ss_zeroesn(str + i, 3)) {
            continue;
        }

        if (needs_space) {
            printf(" ");
        }
        
        print_short_int(str + i, 3);
        printf(" ");

        if (max_illion != 0) {
            printf(nw_illions[max_illion]);
        }

        needs_space = true;
    }
}

void print_signed_int(const char *str, int length) {
    if (str[0] == '+') {
        printf("positive ");
    } else {
        printf("negative ");
    }

    print_plain_int(str + 1, length - 1);
}

void print_by_kindn(const char *str, int length, ss_num_kind kind) {
    switch (kind) {
        case SS_NUM_INVALID:
            printf("invalid");
            break;
        case SS_NUM_PLAIN_INTEGER:
            print_plain_int(str, length);
            break;
        case SS_NUM_SIGNED_INTEGER:
            print_signed_int(str, length);
            break;
        default:
            printf("unimplemented");
            break;
    }
}

void print_by_kind(const char *str, ss_num_kind kind) {
    print_by_kindn(str, strlen(str), kind);
}