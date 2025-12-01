#ifndef LEARNC_PLATFORM_H
#define LEARNC_PLATFORM_H

#include <stddef.h>
#include <stdint.h>

// Cross-platform utilities: sleep, time, clear screen, input, timestamp.

#ifdef _WIN32
#define LEARNC_PLATFORM_WINDOWS 1
#else
#define LEARNC_PLATFORM_WINDOWS 0
#endif

void platform_sleep_ms(unsigned ms);
void platform_clear_screen(void);
uint64_t platform_millis(void); // monotonic milliseconds
int platform_kbhit(void);       // non-blocking keyboard check (1 if key available)
int platform_getch(void);       // get single char (no echo), returns -1 if none

#endif // LEARNC_PLATFORM_H
