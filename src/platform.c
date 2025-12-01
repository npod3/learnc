#include "platform.h"

#include <stdio.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <unistd.h>
#include <sys/time.h>
#include <termios.h>
#include <fcntl.h>
static int termios_initialized = 0;
static struct termios orig_termios;
static void termios_init(void) {
    if (termios_initialized) return;
    struct termios t;
    if (tcgetattr(STDIN_FILENO, &orig_termios) == 0) {
        t = orig_termios;
        t.c_lflag &= ~(ICANON | ECHO);
        t.c_cc[VMIN] = 0;
        t.c_cc[VTIME] = 0;
        tcsetattr(STDIN_FILENO, TCSANOW, &t);
        int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
        termios_initialized = 1;
    }
}
static void termios_restore(void) {
    if (termios_initialized) tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}
__attribute__((destructor)) static void cleanup(void) { termios_restore(); }
#endif

void platform_sleep_ms(unsigned ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    struct timespec ts; ts.tv_sec = ms / 1000; ts.tv_nsec = (long)(ms % 1000) * 1000000L;
    nanosleep(&ts, NULL);
#endif
}

void platform_clear_screen(void) {
#ifdef _WIN32
    /* Attempt ANSI first (modern Windows 10+), else fallback */
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD mode = 0;
        if (GetConsoleMode(hOut, &mode)) {
            SetConsoleMode(hOut, mode | 0x0004); // ENABLE_VIRTUAL_TERMINAL_PROCESSING
        }
    }
    printf("\x1b[2J\x1b[H");
#else
    printf("\x1b[2J\x1b[H");
#endif
    fflush(stdout);
}

uint64_t platform_millis(void) {
#ifdef _WIN32
    return (uint64_t)GetTickCount64();
#else
    struct timespec ts; clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000ULL + (uint64_t)ts.tv_nsec / 1000000ULL;
#endif
}

int platform_kbhit(void) {
#ifdef _WIN32
    return _kbhit();
#else
    termios_init();
    unsigned char c;
    int r = (int)read(STDIN_FILENO, &c, 1);
    if (r == 1) {
        // push back by storing in a static buffer? Simpler: keep char in a static.
        static unsigned char buf = 0; static int has = 0;
        buf = c; has = 1;
        // install a getter that returns this first.
        // We'll mark using a static.
        // We'll set a flag accessible via platform_getch.
        // Simpler approach: store in global.
        extern int platform_getch(void); // forward
        // We'll just reuse a static inside platform_getch.
        // Indicate presence by returning 1.
        // Implementation below will check a static.
        // Use an internal variable.
        // Done.
        // For now, we stash in a global static below.
        // Actually simpler: create static.
        // Already done above.
        // We'll set a static accessible.
        // Continue.
        // We can't push back into STDIN easily; keep char in static.
        // We'll define them here.
        extern int platform_internal_set_buffer(unsigned char);
        platform_internal_set_buffer(c);
        return 1;
    }
    return 0;
#endif
}

#ifndef _WIN32
static unsigned char keybuf = 0; static int keybuf_has = 0;
int platform_internal_set_buffer(unsigned char c) { keybuf = c; keybuf_has = 1; return 0; }
#endif

int platform_getch(void) {
#ifdef _WIN32
    if (_kbhit()) return _getch();
    return -1;
#else
    termios_init();
    if (keybuf_has) { keybuf_has = 0; return (int)keybuf; }
    unsigned char c;
    int r = (int)read(STDIN_FILENO, &c, 1);
    if (r == 1) return (int)c;
    return -1;
#endif
}
