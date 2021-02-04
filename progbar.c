#include <string.h>
#include "progbar.h"

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

void plot_progbar(WINDOW *scr, time_t cur, time_t duration) {
    int large = cur * 50 / duration;
    large = min(large, 50) - 1;
    large = max(large, 0);
    char buf[51];
    memset(buf, 0, 51);
    for (int i = 0; i < large; ++i)
        buf[i] = '.';
    for (int i = large; i < 49; ++i)
        buf[i] = ' ';
    mvwaddstr(scr, 1, 1, buf);
    mvwaddwstr(scr, 1, 1, L"💣");
    mvwaddwstr(scr, 1, max(large, 1), L"🔥");
}
