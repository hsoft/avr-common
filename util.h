#pragma once

#ifndef SIMULATION
#include <avr/io.h>

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#define tbi(sfr, bit) (_SFR_BYTE(sfr) ^= _BV(bit))
#define isset(sfr, bit) (_SFR_BYTE(sfr) & _BV(bit))

#else

#include "icemu.h"

#define _delay_us(us) icemu_sim_delay(us)
#define _delay_ms(ms) icemu_sim_delay(ms * 1000)
#endif
