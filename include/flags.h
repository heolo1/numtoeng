#pragma once

#include <stdbool.h>

#include "program.h"

/**
 * @brief a struct describing a program flag
 * 
 * name is the name of the flag
 * 
 * family = incompatibility family
 * family groups flags together, which will be incompatible with each other
 * - family = 0 indicates no family
 * - so, there are 255 possible families
 * 
 * in the future, i'll add:
 * - possible arguments
 * - function that consumes program_t
 * - flags can have multiple of the same type in a family
 */
typedef struct flag_info_t {
    const char *name;
    char family;
    void (*func)(program_t *);
} flag_info_t;

typedef struct flag_collection_t {
    flag_info_t *flags;
    int n_flags; // size of flags
    
    // alias map, this should be a map between aliases and actual command names
    // the size of this should be even = n_aliases * 2
    // format: { alias, real command of previous alias, ... };
    // this map is assumed to be malloc'd, but the string inside are not
    const char **alias_map;
    int n_aliases;
} flag_collection_t;

// returns a new default flag collection
// expects to be freed by malloc
flag_collection_t *make_def_flag_col();

// frees every pointer structure inside
void free_flag_col(flag_collection_t *);

/**
 * @brief processes argv by info in flags, outputting program format data
 * all flags are assumed to start with --
 * 
 * @param argc number of arguments in argv
 * @param argv pointer of all arguments to process, this is expected to start with the first flag
 * @param processedc pointer to output integer of the number of arguments parsed as being flags
 * @param fcollection the flag collection to process flags based on
 * @param program where to output the program info to
 * @param print_errors whether or not this function should print errors to stderr
 * @return 0 if everything is ok, 1 if error occurred while processing
 */
int process_flags(int argc, char **argv, int *processedc,
    flag_collection_t *fcollection, program_t *program, bool print_errors);