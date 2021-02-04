#pragma once

#include <stddef.h>
#include "numplot.h"

#define fromto(S, E, V)    for (size_t V = (S); V < (E); ++V)
#define max(a, b)          ((a) > (b) ? (a) : (b))
#define min(a, b)          ((a) < (b) ? (a) : (b))
#define plot_time(S, V)    (plot_number((S)->V##10, V / 10), plot_number((S)->V##1, V))
