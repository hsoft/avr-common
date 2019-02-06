#include <stdint.h>

#include "pin.h"

#define SEG7SERIAL_DIGITS 4

void seg7serial_setpins(PinID clk, PinID ser);
void seg7serial_send(uint16_t val);
