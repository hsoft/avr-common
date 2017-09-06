#include "pin.h"

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
}

void pintoggle(Pin pin)
{
    pinset(pin, !pinishigh(pin));
}

bool pinishigh(Pin pin)
{
    return false;
}

void pininputmode(Pin pin)
{
}

void pinoutputmode(Pin pin)
{
}

