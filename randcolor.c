#include <ncurses.h>
#include <stdlib.h>
#include "k-utils.h"
#include "randcolor.h"

static int *randints(int, int);

void init_rand_pairs(int npairs) {
    int *colors = randints(npairs, 8);
    fromto(0, npairs, i) init_pair(i+1, colors[i], COLOR_BLACK);
    free(colors);
}

int *randints(int nitems, int m) {
    if (nitems > m) return NULL;
    int values[m];
    int *res = malloc(sizeof(int) * nitems);
    fromto(0, m, num) values[num] = num;

    fromto(0, nitems, i) {
        int j = rand() % m;
        while (values[j] == 0) j = (j + 1) % m;
        res[i] = values[j];
        values[j] = 0;
    }

    return res;
}
