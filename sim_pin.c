#include "pin.h"
#include "sim.h"
#include "icemu/capi/icemu.h"

void pinhigh(Pin pin)
{
    pinset(pin, true);
}

void pinlow(Pin pin)
{
    pinset(pin, false);
}

void pinset(Pin pin, bool high)
{
    icemu_pinset(pin & 0x7, high);
}

void pintoggle(Pin pin)
{
    pinset(pin, !pinishigh(pin));
}

bool pinishigh(Pin pin)
{
    return icemu_pinread(pin & 0x7);
}

void pininputmode(Pin pin)
{
    icemu_pinsetmode(pin & 0x7, false);
}

void pinoutputmode(Pin pin)
{
    icemu_pinsetmode(pin & 0x7, true);
}

