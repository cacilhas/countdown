#pragma once

#include "numplot.h"

#define fromto(S, E, V)    for (int V = (S); V < (E); ++V)
#define max(a, b)          ((a) > (b) ? (a) : (b))
#define min(a, b)          ((a) < (b) ? (a) : (b))
#define plot_time(S, V)    (plot_number((S)->V##10, V / 10), plot_number((S)->V##1, V))
