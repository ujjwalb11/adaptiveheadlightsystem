#include"header.h"


struct
{
    volatile unsigned int FLAG_ISR;
    volatile unsigned int FLAG_ISR1;
    volatile uint8_t duty;
    uint8_t low;
    uint16_t speed;
    uint16_t light;
} FLAG_BIT;

void adc_init()
{
    ADMUX&=0x00;
    SET_BIT(ADCSRA, ADEN); //ADC ENABLE
    SET_BIT(ADMUX,REFS0); //ADC0 CHANNEL ENABLE
    SET_BIT(ADCSRA,ADSC);
    FLAG_BIT.low = ADCL; //storing the value in the ADC
    FLAG_BIT.speed = (ADCH<<8) | FLAG_BIT.low; //Start conversion
    while(ADCSRA & (1<<ADSC));
    CLR_BIT(ADCSRA,ADSC);
    SET_BIT(ADMUX,MUX0);
    SET_BIT(ADCSRA,ADSC);
    FLAG_BIT.low = ADCL; //storing the value in the ADC
    FLAG_BIT.light = (ADCH<<8) | FLAG_BIT.low; //Start conversion
    while(ADCSRA & (1<<ADSC));
}

