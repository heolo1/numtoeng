#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "flags.h"
#include "printing.h"
#include "program.h"

// searches in [str + str_start, str + str_size) for \r, \n, or \0
// returns str_size if not found
int find_next_num_break(const char *str, int str_start, int str_size) {
    int i;
    for (i = str_start; i < str_size; i++) {
        if (str[i] == '\0' || str[i] == '\n' || str[i] == '\r') {
            break;
        }
    }
    return i;
}

int count_flags(int flagc, char **flagv) {
    int i;
    for (i = 0; i < flagc; i++) {
        if (flagv[i][0] != '-' || flagv[i][1] != '-') {
            break;
        }
    }
    return i;
}

int main(int argc, char *argv[]) {
    program_t program;
    init_default_program(&program);

    flag_collection_t *flags = make_def_flag_col();
    int flagc;
    if (process_flags(argc - 1, argv + 1, &flagc, flags, &program, true)) {
        free_flag_col(flags);
        return 1;
    }

    int num_idx = program.label_opt == FV_label_1;

    if (program.read_stdin) {
        // arbitrary constants
        int read_size = 256;
        int buf_size = read_size * 8;

        int buf_pos = 0;
        char *buf = malloc(sizeof(char) * buf_size);

        int read_bytes;
        // at the end of each loop, buf_pos is after the last read char
        while ((read_bytes = read(STDIN_FILENO, buf + buf_pos, read_size)) > 0) {
            // this is the end of our searching bytes, where buf_pos will go
            int new_buf_pos = buf_pos + read_bytes;

            // start looking for breaks
            int break_pos = buf_pos;
            buf_pos = 0;
            // buf_pos from here acts as the beginning of a string, and break_pos as the exclusive end
            while ((break_pos = find_next_num_break(buf, break_pos, new_buf_pos)) != new_buf_pos) {
                // first need to make sure whether or not we should ignore this
                int length = break_pos - buf_pos;
                if (length) {
                    ss_num_kind num_kind = ss_get_num_kindn(buf + buf_pos,
                        length);
                    FILE *f_out = get_desired_f(program.f_valid, program.f_invalid, num_kind);
                    if (program.label_opt != FV_no_label) {
                        fprintf(f_out, "%d: ", num_idx++);
                    }
                    print_by_kindn(program.f_valid, program.f_invalid, buf + buf_pos, length,
                        num_kind);
                    putc('\n', f_out);
                }

                // look past the delimiter at break_pos
                buf_pos = ++break_pos;
            }

            // want to move data if any numbers were found and parsed
            if (buf_pos) {
                memmove(buf, buf + buf_pos, new_buf_pos -= buf_pos);
            }

            buf_pos = new_buf_pos;
            // expand buf if necessary
            if (buf_pos + read_size >= buf_size) {
                buf_size *= 2;
                char *new_buf = malloc(sizeof(char) * buf_size);
                memcpy(new_buf, buf, buf_pos);
                free(buf);
                buf = new_buf;
            }
        }

        // eof reached, check if there are any numbers remaining at the end
        if (buf_pos) {
            ss_num_kind num_kind = ss_get_num_kindn(buf, buf_pos);
            FILE *f_out = get_desired_f(program.f_valid, program.f_invalid, num_kind);
            if (program.label_opt != FV_no_label) {
                fprintf(f_out, "%d: ", num_idx++);
            }
            print_by_kindn(program.f_valid, program.f_invalid, buf, buf_pos, num_kind);
            putc('\n', f_out);
        }

        free(buf);
    } else {
        // char **numv = flagv + flagc;
        char **numv = argv + flagc + 1;
        int numc = argc - flagc - 1;

        for (int i = 0; i < numc; i++) {
            ss_num_kind num_kind = ss_get_num_kind(numv[i]);
            FILE *f_out = get_desired_f(program.f_valid, program.f_invalid, num_kind);
            if (program.label_opt != FV_no_label) {
                fprintf(f_out, "%d: ", num_idx++);
            }
            print_by_kind(program.f_valid, program.f_invalid, numv[i], num_kind);
            putc('\n', f_out);
        }
    }

    free_flag_col(flags);

    return 0;
}