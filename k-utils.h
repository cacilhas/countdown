#pragma once

#include <stdlib.h>
#include "numplot.h"

#define fromto(S, E, V)    for (int V = (S); V < (E); ++V)
#define init_rand_pair(ID) init_pair((ID), (rand() % 7) + 1, COLOR_BLACK)
#define max(a, b)          ((a) > (b) ? (a) : (b))
#define min(a, b)          ((a) < (b) ? (a) : (b))
#define plot_time(S, V)    (plot_number((S)->V##10, V / 10), plot_number((S)->V##1, V))
