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

void pin_config()
{
    SET_BIT(DDRD,PD6); //servo motor o/p
    CLR_BIT(DDRD,PD2); //to show left turn i/p
    CLR_BIT(DDRD,PD3); //to show right turn i/p
    SET_BIT(DDRB,PB2); //LED o/p
    SET_BIT(DDRC,PC5); //power o/p port for servomotor
    CLR_BIT(PORTC,PC5); // default position
    SET_BIT(PORTD,PD2); //pull up configuration
    SET_BIT(PORTD,PD3); //pull up configuration
    SET_BIT(DDRB,PB5); //high beam LED o/p
    SET_BIT(DDRB,PB4); //Low beam LED o/p
}
