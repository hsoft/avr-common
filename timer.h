#pragma once

#include <stdbool.h>

typedef enum {
    TIMER_MODE_NOMATCH = 0, // Just run without matching on anything.
    TIMER_MODE_INTERRUPT = 1, // CTC with interrupt
} TIMER_MODE;

bool set_timer0_target(unsigned long usecs);
void set_timer0_mode(TIMER_MODE mode);
bool set_timer1_target(unsigned long usecs);
void set_timer1_mode(TIMER_MODE mode);
unsigned long get_timer1_rescaled_tcnt();
unsigned long ticks_to_msecs(unsigned long ticks);
