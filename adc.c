#include <avr/io.h>
#include "util.h"
#include "adc.h"

void adc_select(ADC_PIN pin)
{
    switch (pin) {
        case ADC_PIN0:
            ADMUX = 0;
            break;
        case ADC_PIN1:
            ADMUX = (1 << MUX0);
            break;
    }
}

void adc_enable()
{
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    sbi(ADCSRA, ADEN);
}

unsigned int adc_val()
{
    unsigned char high, low;

    sbi(ADCSRA, ADSC);
    while (bit_is_set(ADCSRA, ADSC));
    low = ADCL;
    high = ADCH;
    return (high << 8) | low;
}

