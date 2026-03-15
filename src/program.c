#include "program.h"

#include <stdbool.h>
#include <stdio.h>

void init_default_program(program_t *program) {
    program->read_stdin = false;
    program->f_valid = stdout;
    program->f_invalid = stdout;
    program->label_opt = FV_no_label;
}

void ff_stdin(program_t *program) {
    program->read_stdin = true;
}

void ff_invalid(program_t *program) {
    program->f_invalid = stderr;
}

void ff_labels(program_t *program) {
    program->label_opt = FV_label_1;
}

void ff_labels_0(program_t *program) {
    program->label_opt = FV_label_0;
}