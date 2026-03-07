#include "printing.h"

#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "printing_words.h"
#include "string_scanning.h"

#define putspace() putchar(' ');

// prints nth illi prefix, 0 <= n < 1000
static void print_illi_(int n) {
    if (n < pw_n_illi_small) {
        printf(pw_illi_small[n]);
        return;
    }

    int unit = n % 10;
    int tens = (n / 10) % 10;
    int hund = n / 100;

    int right_comb = tens ? pw_illi_tens_comb[tens]
                          : pw_illi_hundreds_comb[tens];

    printf(pw_illi_unit[unit]);
    switch (pw_illi_unit_comb[unit] & right_comb) {
        // can never be more than one at once
    case PW_ILLI_COMB_S:
        putchar('s');
        break;
    case PW_ILLI_COMB_X:
        putchar('x');
        break;
    case PW_ILLI_COMB_N:
        putchar('n');
        break;
    case PW_ILLI_COMB_M:
        putchar('m');
        break;
    }
    printf(pw_illi_tens[tens]);
    if (tens) {
        if (hund && pw_illi_tens_comb[tens] & PW_ILLI_COMB_A) {
            putchar('a');
        } else {
            putchar('i');
        }
    }
    printf(pw_illi_hundreds[hund]);
    printf("lli");
}

void print_illion(int n) {
    if (n < 2) {
        switch (n) {
        case 0:
            printf("zero");
            break;
        case 1:
            printf("thousand");
            break;
        }
        return;
    }

    n--; // previously n = 2 -> million, now n = 1 -> milli-
    // this will be 1000^floor(log base 1000(n))
    // so n = 5 -> n_size = 1, n = 1000 -> n_size = 1000,
    /// n = 10'000'000 -> n_size = 1'000'000, etc.
    int n_size = 1; 
    for (; INT_MAX / 1000 >= n_size && n / 1000 >= n_size; n_size *= 1000);

    for (; n_size != 0; n %= n_size, n_size /= 1000) {
        print_illi_(n / n_size);
    }
    printf("on");
}

void print_short_int(const char *str, int length) {
    str += length - 3;

    int ones = str[2] - '0';
    int tens = length >= 2 ? str[1] - '0' : 0;
    int hundreds = length >= 3 ? str[0] - '0' : 0;
    
    if (hundreds) {
        printf(pw_digits[hundreds]);
        putspace();
        printf("hundred");
        if (ones || tens) {
            putspace();
        }
    }
    if (tens >= 2) {
        printf(pw_tens[tens]);
        if (ones) {
            putchar('-');
            printf(pw_digits[ones]);
        }
    } else {
        printf(pw_digits[tens * 10 + ones]);
    }
}

void print_plain_int(const char *str, int length) {
    if (ss_zeroesn(str, length)) {
        printf(pw_digits[0]);
        return;
    }

    for (; str[0] == '0'; length--, str++);

    int max_illion = (length - 1) / 3;

    // length mod 3 != 0, handle that here
    int beginning_digits = length % 3;
    bool needs_space = false;
    if (beginning_digits) {
        if (!ss_zeroesn(str, beginning_digits)) {
            print_short_int(str, beginning_digits);
            putspace();
            if (max_illion) {
                print_illion(max_illion);
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
            putspace();
        }
        
        print_short_int(str + i, 3);
        putspace();

        if (max_illion != 0) {
            print_illion(max_illion);
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
    size_t size = strlen(str);
    if (size > INT_MAX) {
        printf("long num");
    } else {
        print_by_kindn(str, size, kind);
    }
}