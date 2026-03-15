#include "program.h"

#include <stdio.h>

void init_default_program(program_t *program) {
    program->read_stdin = false;
    program->f_valid = stdout;
    program->f_invalid = stdout;
    program->label_opt = FV_no_label;
}