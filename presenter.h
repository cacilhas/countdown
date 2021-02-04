#pragma once

#include <curses.h>
#include <time.h>

typedef struct {
    WINDOW *stdscr;
    time_t  start, end, duration;
    int     width;
    WINDOW *hour10;
    WINDOW *hour1;
    WINDOW *min10;
    WINDOW *min1;
    WINDOW *sec10;
    WINDOW *sec1;
    WINDOW *sep1;
    WINDOW *sep2;
    WINDOW *msec;
    WINDOW *progbar;
} state_t;

state_t *setup_window(WINDOW*, time_t);
void mainloop(state_t*);
