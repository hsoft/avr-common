#include <avr/io.h>
#include "timer.h"
#include "util.h"

// "ticks" is the number of clock cycles we want our timer to last
// Returns whether we could find a suitable Target (whether "ticks" fits in the timer)
bool set_timer0_target(unsigned long ticks)
{
    unsigned char prescaler_shifts[5] = {0, 3, 6, 8, 10};
    unsigned char prescaler_bits[5] = {0b001, 0b010, 0b011, 0b100, 0b101};
    unsigned char prescaler_index;

    if (ticks == 0) {
        // Stop the timer.
        TCCR0B &= 0b11111000;
        OCR0A = 0;
        return true;
    }

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

bool set_timer1_target(unsigned long ticks)
{
    unsigned char prescaler_shift;

    if (ticks == 0) {
        // Stop the timer.
        TCCR1 &= 0b11110000;
        OCR1C = 0;
        return true;
    }

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
