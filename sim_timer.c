#include "timer.h"
#include "sim.h"
#include "icemu/capi/icemu.h"
#include "icemu/capi/avr/attiny.h"

bool set_timer0_target(unsigned long usecs)
{
    return icemu_start_timer(ICEMU_TIMER0, usecs);
}

void set_timer0_mode(TIMER_MODE mode)
{
}

bool set_timer1_target(unsigned long usecs)
{
    return icemu_start_timer(ICEMU_TIMER1, usecs);
}

void set_timer1_mode(TIMER_MODE mode)
{
}

unsigned long get_timer1_rescaled_tcnt()
{
    return 0;
}

unsigned long ticks_to_msecs(unsigned long ticks)
{
    // If we have F_CPU/1000 ticks per msecs, we can divide ticks by (F_CPU/1000) to get msecs
    return ticks / (F_CPU / 1000);
}
