#include <stdlib.h>
#include <string.h>
#include "argparse.h"
#include "k-utils.h"

static double parse_arg(const char*);

time_t parse_args(int argc, const char *argv[]) {
    if (argc < 2) return 60;
    double res = 0;
    fromto(1, argc, i) res += parse_arg(argv[i]);
    return (time_t) (res + 0.5);
}

double parse_arg(const char *arg) {
    size_t len = strlen(arg);
    size_t last = len - 1;
    char aux[len];
    strcpy(aux, arg);
    switch (arg[last]) {
        case 'd':
            aux[last] = 0;
            return atof(aux) * 86400.0;

        case 'h':
            aux[last] = 0;
            return atof(aux) * 3600.0;

        case 'm':
            aux[last] = 0;
            return atof(aux) * 60.0;

        case 's':
            aux[last] = 0;
            if (aux[last - 1] == 'm') {
                aux[last - 1] = 0;
                return atof(aux) * 0.001;
            }

        default:
            return atof(aux);
    }
}
