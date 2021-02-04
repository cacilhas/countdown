#include <stdlib.h>
#include "numplot.h"
#include "presenter.h"

state_t *setup_window(WINDOW *scr, time_t duration) {
    state_t *state = malloc(sizeof(state_t));
    state->stdscr = scr;
    int wi, hei;
    getmaxyx(scr, hei, wi);
    state->width = wi;
    int lx = (wi - 13) / 2;
    int ly = (hei - 3) / 2;
    int color = (rand() % 7) + 1;

    keypad(scr, TRUE);
    nodelay(scr, TRUE);
    init_pair(1, color, COLOR_BLACK);
    wbkgdset(scr, COLOR_PAIR(1));

    state->min10 = subwin(scr, 3, 3, ly,   lx);
    state->min1  = subwin(scr, 3, 3, ly,   lx+3);
    state->sep   = subwin(scr, 1, 1, ly+1, lx+6);
    state->sec10 = subwin(scr, 3, 3, ly,   lx+7);
    state->sec1  = subwin(scr, 3, 3, ly,   lx+10);

    time(&(state->start));
    state->end = state->start + duration;

    return state;
}

void mainloop(state_t *state) {
    wclear(state->stdscr);
    box(state->stdscr, 0, 0);
    mvwaddwstr(state->stdscr, 0, (state->width - 11)/ 2, L" COUNTDOWN ");
    time_t cur;
    time(&cur);

    while(cur < state->end) {
        time_t miss = state->end - cur;
        int min = miss / 60;
        int sec = miss % 60;

        plot_number(state->min10, min / 10);
        plot_number(state->min1,  min % 10);
        plot_number(state->sec10, sec / 10);
        plot_number(state->sec1,  sec % 10);
        plot_colon(state->sep);

        wrefresh(state->min10);
        wrefresh(state->min1);
        wrefresh(state->sep);
        wrefresh(state->sec10);
        wrefresh(state->sec1);
        wrefresh(state->stdscr);
        time(&cur);
    }

    free(state);
}
