#pragma once

#include <stdbool.h>

typedef enum {
    TIMER_MODE_NOMATCH = 0, // Just run without matching on anything.
    TIMER_MODE_INTERRUPT = 1, // CTC with interrupt
} TIMER_MODE;

bool set_timer0_target(unsigned long ticks);
bool set_timer1_target(unsigned long ticks);
void set_timer1_mode(TIMER_MODE mode);

