typedef enum {
    ADC_PIN0,
    ADC_PIN1,
} ADC_PIN;

void adc_select(ADC_PIN pin);
void adc_enable();
unsigned int adc_val();
