#include <util/delay.h>

#include "seg7serial.h"
#include "intmath.h"

static PinID CLK;
static PinID SER;

static void clock(bool high)
{
    pinlow(CLK);
    pinset(SER, high);
    _delay_us(50);
    pinhigh(CLK);
}

static void digit(uint8_t digit)
{
    if (digit >= 10) {
        return;
    }
    clock(false); // no dot
    clock(digit & (1 << 3));
    clock(digit & (1 << 2));
    clock(digit & (1 << 1));
    clock(digit & 1);
}

void seg7serial_setpins(PinID clk, PinID ser)
{
    CLK = clk;
    SER = ser;
    pinoutputmode(CLK);
    pinoutputmode(SER);
}

void seg7serial_send(uint16_t val)
{
    uint8_t digits[SEG7SERIAL_DIGITS];
    uint8_t verif = 0;

    /* The computation below doesn't look like much, but it's actually intensive
     * for the MCU. If it has to perform it while clocking has begun, we bust
     * timeout, even if, in general, sending is much easier on the MCU than
     * receiving (see _delay_us() comment in clock()). So, pre-compute before
     * clocking.
     */
    for (int i=0; i < SEG7SERIAL_DIGITS; i++) {
        digits[i] = (val / int_pow10(i)) % 10;
        verif += digits[i];
    }

    // Empty CLK to begin
    clock(false);
    _delay_us(200);
    for (int i=0; i < SEG7SERIAL_DIGITS; i++) {
        digit(digits[i]);
    }
    clock(verif & (1 << 4));
    clock(verif & (1 << 3));
    clock(verif & (1 << 2));
    clock(verif & (1 << 1));
    clock(verif & 1);
}
