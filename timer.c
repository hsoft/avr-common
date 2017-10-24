#include <avr/io.h>
#include "timer.h"
#include "util.h"

#define USECS_PER_SECOND 1000000UL

static unsigned long usecs_to_ticks(unsigned long usecs)
{
    unsigned long r;
    if (F_CPU >= USECS_PER_SECOND) {
        r = (F_CPU / USECS_PER_SECOND) * usecs;
    } else {
        r = (F_CPU * usecs) / USECS_PER_SECOND;
        if (r == 0) {
            r = 1;
        }
    }
    return r;
}

bool set_timer0_target(unsigned long usecs)
{
    unsigned char prescaler_shifts[5] = {0, 3, 6, 8, 10};
    unsigned char prescaler_bits[5] = {0b001, 0b010, 0b011, 0b100, 0b101};
    unsigned char prescaler_index;
    unsigned long ticks;

    if (usecs == 0) {
        // Stop the timer.
        TCCR0B &= 0b11111000;
        OCR0A = 0;
        return true;
    }

    ticks = usecs_to_ticks(usecs);

    for (prescaler_index=0; prescaler_index<=5; prescaler_index++) {
        if (ticks >> prescaler_shifts[prescaler_index] <= 0xff) {
            break;
        }
    }
    if (prescaler_index > 5) {
        return false;
    }
    // Set CS10, CS11 and CS12 according to our selected prescaler bits
    TCCR0B &= 0b11111000;
    TCCR0B |= prescaler_bits[prescaler_index];
    OCR0A = ticks >> prescaler_shifts[prescaler_index];
    return true;
}

void set_timer0_mode(TIMER_MODE mode)
{
    switch (mode) {
        case TIMER_MODE_NOMATCH:
            // Disable CTC mode
            cbi(TCCR0A, WGM01);
            break;
        case TIMER_MODE_INTERRUPT:
            // Enable CTC mode
            sbi(TCCR0A, WGM01);
            // Enable interrupt on compare match on OCR0A.
            sbi(TIMSK, OCIE0A);
            break;
    }
    TCNT0 = 0;
}

bool set_timer1_target(unsigned long usecs)
{
    unsigned char prescaler_shift;
    unsigned long ticks;

    if (usecs == 0) {
        // Stop the timer.
        TCCR1 &= 0b11110000;
        OCR1C = 0;
        return true;
    }

    ticks = usecs_to_ticks(usecs);

    // Timer1 has a prescaler for every possible shift situation, from 0 to 14. No need
    // for a prescaler_shifts table! It also happens that these prescaler ids are sequential. We
    // don't need a table of prescaler_bits either. We only need to take (shiftvalue + 1) and
    // there are our prescaler bits!
    for (prescaler_shift=0; prescaler_shift<=14; prescaler_shift++) {
        if (ticks >> prescaler_shift <= 0xff) {
            break;
        }
    }
    if (prescaler_shift > 14) {
        return false;
    }
    // Set CS10, CS11 and CS12 according to our selected prescaler bits
    TCCR1 &= 0b11110000;
    TCCR1 |= (prescaler_shift+1);
    // Unlike timer0, it's the **C** register that acts as the "TOP" value with timer1
    OCR1C = ticks >> prescaler_shift;
    OCR1A = OCR1C;
    return true;
}

void set_timer1_mode(TIMER_MODE mode)
{
    switch (mode) {
        case TIMER_MODE_NOMATCH:
            // Disable CTC mode
            cbi(TCCR1, CTC1);
            break;
        case TIMER_MODE_INTERRUPT:
            // Enable CTC mode
            sbi(TCCR1, CTC1);
            // Enable interrupt on compare match on OCR1A.
            sbi(TIMSK, OCIE1A);
            break;
    }
    TCNT1 = 0;
}

unsigned long get_timer1_rescaled_tcnt()
{
    unsigned char prescaler_shift;

    prescaler_shift = (TCCR1 & 0b11110000) - 1;
    return TCNT1 << prescaler_shift;
}

unsigned long ticks_to_msecs(unsigned long ticks)
{
    // If we have F_CPU/1000 ticks per msecs, we can divide ticks by (F_CPU/1000) to get msecs
    return ticks / (F_CPU / 1000);
}
