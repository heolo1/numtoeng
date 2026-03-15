#include "flags.h"

#include <stdlib.h>
#include <string.h>

#define LABEL_FAMILY 1

flag_collection_t *make_def_flag_col() {
    // yeah three mallocs who cares i'll maybe change it in the future
    int n_flags = 4;
    flag_info_t *flags = malloc(sizeof(flag_info_t) * n_flags);
    memcpy(flags, (flag_info_t []) {
        { "stdin"   , 0           , ff_stdin    },
        { "invalid" , 0           , ff_invalid  },
        { "labels"  , LABEL_FAMILY, ff_labels   },
        { "labels-0", LABEL_FAMILY, ff_labels_0 },
    }, sizeof(flag_info_t) * n_flags);
    
    int n_aliases = 4;
    const char **alias_map = malloc(sizeof(const char *) * n_aliases * 2);
    memcpy(alias_map, (const char *[]) {
        ""  , "stdin"   ,
        "!" , "invalid" ,
        "#" , "labels"  ,
        "#0", "labels-0",
    }, sizeof(const char *) * n_aliases * 2);

    flag_collection_t *fcol = malloc(sizeof(flag_collection_t));
    memcpy(fcol, &(flag_collection_t) {
        flags,
        n_flags,
        alias_map,
        n_aliases,
    }, sizeof(flag_collection_t));
    
    return fcol;
}

void free_flag_col(flag_collection_t *col) {
    free(col->flags);
    free(col->alias_map);
    free(col);
}

// intended to be changed in the future, because we'll want to stop at equals signs as well
static int flag_strcmp(const char *a, const char *b) {
    return strcmp(a, b);
}

int process_flags(int argc, char **argv, int *processedc,
    flag_collection_t *fcol, program_t *program, bool print_errors) {
    int prc = 0;
    int ret = 0;

    bool funiqueness_table[256] = { 0 };
    bool *uniqueness_table = malloc( fcol->n_flags * sizeof(bool) );
    memset(uniqueness_table, 0, fcol->n_flags * sizeof(bool));

    for (; prc < argc; prc++) {
        if (argv[prc][0] != '-' || argv[prc][0] != '-') {
            break;
        }

        // we want to skip initial --
        const char *ocurr_flag = argv[prc];
        const char *curr_flag = ocurr_flag + 2;

        // look for aliasing
        for (int i = 0; i < fcol->n_aliases; i++) {
            if (flag_strcmp(curr_flag, fcol->alias_map[2 * i]) == 0) {
                curr_flag = fcol->alias_map[2 * i + 1];
                break;
            }
        }

        // start actually looking for flags
        for (int i = 0; i < fcol->n_flags; i++) {
            flag_info_t *flag = &fcol->flags[i];
            if (flag_strcmp(curr_flag, flag->name) != 0) {
                continue;
            }

            // check for duplicates
            bool *ut = flag->family == 0 ? uniqueness_table : funiqueness_table;
            int lookup_idx = flag->family == 0 ? i : flag->family;
            if (ut[lookup_idx]) {
                if (print_errors) {
                    fprintf(stderr, "error: duplicate flag '%s' found\n", ocurr_flag);
                }
                ret = 1;
                goto end;
            } else {
                ut[lookup_idx] = true;
            }

            // this is the part where we do something with the flag
            // we just pass it the program struct for now
            // i'll figure something else out later
            flag->func(program);
            
            goto loop_end;
        }

        // we get here if we didnt match a flag name:
        if (print_errors) {
            fprintf(stderr, "error: unknown flag '%s'\n", ocurr_flag);
        }
        ret = 1;
        break;

        loop_end:; // we want a blank statement here
    }

    end:
    free(uniqueness_table);
    *processedc = prc;
    return ret;
}