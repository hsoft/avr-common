#include "icemu/capi/icemu.h"

// In simulation, we define a F_CPU where one cycle == 1us
#define F_CPU 1000000

#define _delay_us icemu_delay_us
#define _delay_ms icemu_delay_ms
