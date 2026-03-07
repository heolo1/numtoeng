#include <stdio.h>

#include "printing.h"

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        print_by_kind(argv[i], ss_get_num_kind(argv[i]));
        printf("\n");
    }

    return 0;
}