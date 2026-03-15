#pragma once

#include <stdbool.h>
#include <stdio.h>

typedef enum FVS_label {
    FV_no_label,
    FV_label_0,
    FV_label_1,
} FVS_label;

typedef struct program_t {
    bool read_stdin;
    FILE *f_valid;
    FILE *f_invalid;
    FVS_label label_opt;
} program_t;

void init_default_program(program_t *);

void ff_stdin(program_t *);
void ff_invalid(program_t *);
void ff_labels(program_t *);
void ff_labels_0(program_t *);