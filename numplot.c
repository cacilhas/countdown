#include <iso646.h>
#include <sys/time.h>
#include "numplot.h"

void plot_number(WINDOW *scr, int value) {
    switch (value) {
        case 0:
            mvwaddwstr(scr, 0, 0, L"┌─┐");
            mvwaddwstr(scr, 1, 0, L"│ │");
            mvwaddwstr(scr, 2, 0, L"└─┘");
            break;
        case 1:
            mvwaddwstr(scr, 0, 0, L"  ╷");
            mvwaddwstr(scr, 1, 0, L"  │");
            mvwaddwstr(scr, 2, 0, L"  ╵");
            break;
        case 2:
            mvwaddwstr(scr, 0, 0, L"╶─┐");
            mvwaddwstr(scr, 1, 0, L"┌─┘");
            mvwaddwstr(scr, 2, 0, L"└─╴");
            break;
        case 3:
            mvwaddwstr(scr, 0, 0, L"╶─┐");
            mvwaddwstr(scr, 1, 0, L" ─┤");
            mvwaddwstr(scr, 2, 0, L"╶─┘");
            break;
        case 4:
            mvwaddwstr(scr, 0, 0, L"╷ ╷");
            mvwaddwstr(scr, 1, 0, L"└─┤");
            mvwaddwstr(scr, 2, 0, L"  ╵");
            break;
        case 5:
            mvwaddwstr(scr, 0, 0, L"┌─╴");
            mvwaddwstr(scr, 1, 0, L"└─┐");
            mvwaddwstr(scr, 2, 0, L"╶─┘");
            break;
        case 6:
            mvwaddwstr(scr, 0, 0, L"┌─╴");
            mvwaddwstr(scr, 1, 0, L"├─┐");
            mvwaddwstr(scr, 2, 0, L"└─┘");
            break;
        case 7:
            mvwaddwstr(scr, 0, 0, L"╶─┐");
            mvwaddwstr(scr, 1, 0, L"  │");
            mvwaddwstr(scr, 2, 0, L"  ╵");
            break;
        case 8:
            mvwaddwstr(scr, 0, 0, L"┌─┐");
            mvwaddwstr(scr, 1, 0, L"├─┤");
            mvwaddwstr(scr, 2, 0, L"└─┘");
            break;
        case 9:
            mvwaddwstr(scr, 0, 0, L"┌─┐");
            mvwaddwstr(scr, 1, 0, L"└─┤");
            mvwaddwstr(scr, 2, 0, L"  ╵");
            break;
    }
}

void plot_colon(WINDOW *scr) {
    struct timeval now;
    gettimeofday(&now, NULL);
    mvwaddwstr(scr, 0, 0, now.tv_usec % 1000000 < 500000 ? L"╎" : L" ");
}

/*
void plot_dot(WINDOW *scr) {
    mvaddwstr(scr, 2, 0, L"╷");
}
*/
