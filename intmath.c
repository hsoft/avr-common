#include "intmath.h"

static int32_t int32_pow10_table[10] = {
        1, 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000, 1000000000
};

int32_t int_pow10(int8_t pow)
{
    return int32_pow10_table[pow];
}
