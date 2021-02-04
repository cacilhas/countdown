#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "k-utils.h"
#include "numplot.h"
#include "presenter.h"
#include "progbar.h"
#include "randcolor.h"

state_t *setup_window(WINDOW *scr, time_t duration) {
    state_t *state = malloc(sizeof(state_t));
    state->stdscr = scr;
    int wi, hei;
    getmaxyx(scr, hei, wi);
    state->width = wi;
    int lx = (wi - 20) / 2;
    int ly = (hei - 7) / 2;

    keypad(scr, TRUE);
    nodelay(scr, TRUE);
    init_rand_pairs(5);
    wbkgdset(scr, COLOR_PAIR(1));

    state->hour10  = subwin(scr, 3, 3,  ly,   lx);
    state->hour1   = subwin(scr, 3, 3,  ly,   lx+3);
    state->sep1    = subwin(scr, 1, 1,  ly+1, lx+6);
    state->min10   = subwin(scr, 3, 3,  ly,   lx+7);
    state->min1    = subwin(scr, 3, 3,  ly,   lx+10);
    state->sep2    = subwin(scr, 1, 1,  ly+1, lx+13);
    state->sec10   = subwin(scr, 3, 3,  ly,   lx+14);
    state->sec1    = subwin(scr, 3, 3,  ly,   lx+17);
    state->msec    = subwin(scr, 1, 4,  ly+2, lx+20);
    state->progbar = subwin(scr, 3, 52, ly+4, (wi - 52) / 2);
    wbkgdset(state->hour10,  COLOR_PAIR(2));
    wbkgdset(state->hour1,   COLOR_PAIR(2));
    wbkgdset(state->min10,   COLOR_PAIR(2));
    wbkgdset(state->min1,    COLOR_PAIR(2));
    wbkgdset(state->sec10,   COLOR_PAIR(2));
    wbkgdset(state->sec1,    COLOR_PAIR(2));
    wbkgdset(state->progbar, COLOR_PAIR(3));
    wbkgdset(state->msec,    COLOR_PAIR(4));
    wbkgdset(state->sep1,    COLOR_PAIR(5));
    wbkgdset(state->sep2,    COLOR_PAIR(5));

    time(&state->start);
    state->duration = duration;
    state->end = state->start + duration;

    return state;
}

void mainloop(state_t *state) {
    wclear(state->stdscr);
    box(state->stdscr,  0, 0);
    box(state->progbar, 0, 0);
    const wchar_t *titles[] = {
        L"⏳ COUNTDOWN ⌛",
        L"⏳ COUNTDOWN ⏳",
        L"⌛ COUNTDOWN ⌛",
        L"⌛ COUNTDOWN ⏳",
    };
    int title_x = (state->width - 13) / 2;

    time_t cur;
    while(time(&cur) < state->end) {
        time_t miss = state->end - cur;
        int hour = miss / 3600;
        int min  = (miss / 60) % 60;
        int sec  = miss % 60;
        struct timeval now;
        gettimeofday(&now, NULL);
        int msec = 1000 - (now.tv_usec / 1000);
        char msec_text[5];
        sprintf(msec_text, ".%03d", msec);
        size_t title_i = msec / 250;

        mvwaddwstr(state->stdscr, 0, title_x, titles[title_i]);

        plot_time(state, hour);
        plot_time(state, min);
        plot_time(state, sec);
        mvwaddstr(state->msec, 0, 0, msec_text);
        plot_colon(state->sep1);
        plot_colon(state->sep2);
        plot_progbar(state->progbar, miss, state->duration);

        wrefresh(state->hour10);
        wrefresh(state->hour1);
        wrefresh(state->sep1);
        wrefresh(state->min10);
        wrefresh(state->min1);
        wrefresh(state->sep2);
        wrefresh(state->sec10);
        wrefresh(state->sec1);
        wrefresh(state->msec);
        wrefresh(state->progbar);
        wrefresh(state->stdscr);
    }

    free(state);
}
