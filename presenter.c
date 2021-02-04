#include <stdlib.h>
#include "k-utils.h"
#include "numplot.h"
#include "presenter.h"
#include "progbar.h"

state_t *setup_window(WINDOW *scr, time_t duration) {
    state_t *state = malloc(sizeof(state_t));
    state->stdscr = scr;
    int wi, hei;
    getmaxyx(scr, hei, wi);
    state->width = wi;
    int lx = (wi - 13) / 2;
    int ly = (hei - 7) / 2;

    keypad(scr, TRUE);
    nodelay(scr, TRUE);
    fromto(1, 4, id) init_rand_pair(id);
    wbkgdset(scr, COLOR_PAIR(1));

    state->min10   = subwin(scr, 3, 3,  ly,   lx);
    state->min1    = subwin(scr, 3, 3,  ly,   lx+3);
    state->sep     = subwin(scr, 1, 1,  ly+1, lx+6);
    state->sec10   = subwin(scr, 3, 3,  ly,   lx+7);
    state->sec1    = subwin(scr, 3, 3,  ly,   lx+10);
    state->progbar = subwin(scr, 3, 52, ly+4, (wi - 52) / 2);
    wbkgdset(state->progbar, COLOR_PAIR(2));
    wbkgdset(state->sep,     COLOR_PAIR(3));

    time(&state->start);
    state->duration = duration;
    state->end = state->start + duration;

    return state;
}

void mainloop(state_t *state) {
    wclear(state->stdscr);
    box(state->stdscr,  0, 0);
    box(state->progbar, 0, 0);
    mvwaddwstr(state->stdscr, 0, (state->width - 13) / 2, L"⏳ COUNTDOWN ⌛");

    time_t cur;
    while(time(&cur) < state->end) {
        time_t miss = state->end - cur;
        int min = miss / 60;
        int sec = miss % 60;

        plot_time(state, min);
        plot_time(state, sec);
        plot_colon(state->sep);
        plot_progbar(state->progbar, miss, state->duration);

        wrefresh(state->min10);
        wrefresh(state->min1);
        wrefresh(state->sep);
        wrefresh(state->sec10);
        wrefresh(state->sec1);
        wrefresh(state->progbar);
        wrefresh(state->stdscr);
    }

    free(state);
}
