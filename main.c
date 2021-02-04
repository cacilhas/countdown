#include <curses.h>
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "k-utils.h"
#include "presenter.h"

static void setup(void);
static void teardown(void);

int main(int argc, const char *argv[]) {
    setlocale(LC_ALL, "");
    time_t duration = 60;

    if (argc > 1)
        duration = min(atoi(argv[1]), 360000);

    WINDOW *stdscr;
    if ((stdscr = initscr()) == NULL) {
        fprintf(stderr, "couldn’t initialise standard screen\n");
        return EXIT_FAILURE;
    }
    atexit(teardown);
    setup();
    mainloop(setup_window(stdscr, duration));

    return EXIT_SUCCESS;
}

void setup() {
    srand(time(NULL));
    if (has_colors()) start_color();
    cbreak();
    noecho();
    nonl();
    curs_set(FALSE);
}

void teardown() {
    endwin();
    system("fireworks");
}
