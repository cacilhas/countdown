#include <string.h>
#include "k-utils.h"
#include "progbar.h"

void plot_progbar(WINDOW *scr, time_t cur, time_t duration) {
    int large = cur * 50 / duration;
    large = min(large, 50) - 1;
    large = max(large, 0);
    char buf[51];
    memset(buf, ' ', 50);
    fromto(0, large, i)  buf[i] = '.';
    buf[50] = 0;
    mvwaddstr(scr, 1, 1, buf);
    mvwaddwstr(scr, 1, 1, L"💣");
    mvwaddwstr(scr, 1, max(large, 1), L"🔥");
}
