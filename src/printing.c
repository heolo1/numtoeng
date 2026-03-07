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
        } else {
            return;
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

void print_int(const char *str, int length) {
    switch (str[0]) {
    case '+': case '-':
        printf(str[0] == '+' ? "positive " : "negative ");
        str++;
        length--;
    }

    int start_zeroes = ss_zero_cntn(str, length);

    if (start_zeroes == length) {
        printf(pw_digits[0]);
        return;
    }

    str += start_zeroes;
    length -= start_zeroes;

    int max_illion = (length - 1) / 3;

    // length mod 3 != 0, handle that here
    int beginning_digits = length % 3;
    bool needs_space = false;
    if (beginning_digits) {
        if (!ss_zeroesn(str, beginning_digits)) {
            print_short_int(str, beginning_digits);
            if (max_illion != 0) {
                putspace();
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

        if (max_illion != 0) {
            putspace();
            print_illion(max_illion);
        }

        needs_space = true;
    }
}

void print_float(const char *str, int length) {
    switch (str[0]) {
    case '+': case '-':
        printf(str[0] == '+' ? "positive " : "negative ");
        str++;
        length--;
    }

    int start_numbers = ss_number_cntn(str, length);
    bool start_is_zero = start_numbers == ss_zero_cntn(str, length);

    if (!start_is_zero) {
        print_int(str, start_numbers);
    }

    // we add + 1 to account for the decimal place
    int dec_pos = start_numbers + 1;
    str += dec_pos;
    length -= dec_pos; // [str, str + length) should now be the decimals
    bool end_is_zero = length == ss_zero_cntn(str, length);

    if (!end_is_zero) {
        if (!start_is_zero) {
            printf(" and ");
        }

        // chop off last few zeroes so it doesnt look goofy
        // e.g. 0.0010 -> "ten ten thousandths"
        for (; str[length - 1] == '0'; length--);

        print_int(str, length);
        putspace();

        // length = 1 -> tenths, length = 2 -> hundredths
        int non_illion = length % 3; // everything but the illions
        int illion = length / 3;
        switch (non_illion) {
        case 1: case 2: 
            printf(non_illion == 1 ? pw_tens[1] : "hundred");
            if (illion) {
                putchar('-');
            }
        }

        if (illion) {
            print_illion(illion);
        }
        
        printf("th");
        // plural check, in the case that we just printed one
        if (!(ss_zeroesn(str, length - 1) && str[length - 1] == '1')) {
            putchar('s');
        }
    }

    if (start_is_zero && end_is_zero) {
        printf(pw_digits[0]);
    }
}

void print_by_kindn(const char *str, int length, ss_num_kind kind) {
    switch (kind) {
        case SS_NUM_INVALID:
            printf("invalid");
            break;
        case SS_NUM_INTEGER:
            print_int(str, length);
            break;
        case SS_NUM_FLOAT:
            print_float(str, length);
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