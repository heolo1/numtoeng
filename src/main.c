#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "printing.h"
#include "program.h"

bool arg_is_flag(const char *arg) {
    // safe even for empty strings, since first condition will immediately fail
    return arg[0] == '-' && arg[1] == '-';
}

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

int main(int argc, char *argv[]) {
    char **flagv = argv + 1;
    int flagc = 0;
    for (; flagc + 1 < argc && arg_is_flag(flagv[flagc]); flagc++);

    program_t program;
    init_default_program(&program);

    for (int i = 0; i < flagc; i++) {
        // i should replace this with something better sooner or later, probably
        if (strcmp("--", flagv[i]) == 0 ||
            strcmp("--stdin", flagv[i]) == 0) {
            if (program.read_stdin) {
                printf("duplicate flag: %s\n", flagv[i]);
                return 1;
            } else {
                program.read_stdin = true;
            }
        } else if (strcmp("--!", flagv[i]) == 0 ||
                   strcmp("--invalid", flagv[i]) == 0) {
            if (program.f_invalid != stdout) {
                printf("duplicate flag: %s\n", flagv[i]);
                return 1;
            } else {
                program.f_invalid = stderr;
            }
        } else if (strcmp("--#", flagv[i]) == 0 ||
                   strcmp("--labels", flagv[i]) == 0) {
            if (program.label_opt != FV_no_label) {
                printf("duplicate flag: %s\n", flagv[i]);
                return 1;
            } else {
                program.label_opt = FV_label_1;
            }
        } else if (strcmp("--#0", flagv[i]) == 0 ||
                   strcmp("--labels-0", flagv[i]) == 0) {
            if (program.label_opt != FV_no_label) {
                printf("duplicate flag: %s\n", flagv[i]);
                return 1;
            } else {
                program.label_opt = FV_label_0;
            }
        } else {
            printf("unrecognized flag: %s\n", flagv[i]);
            return 1;
        }
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
        char **numv = flagv + flagc;
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

    return 0;
}