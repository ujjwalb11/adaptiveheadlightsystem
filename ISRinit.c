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

void isr_init()
{
    CLR_BIT(EICRA,ISC01); //any logic interrupt0
    SET_BIT(EICRA,ISC00);
    CLR_BIT(EICRA,ISC11); //any logic interrupt1
    SET_BIT(EICRA,ISC10);
    SET_BIT(SREG,7); //setting global interrupt
    SET_BIT(EIMSK,INT0); //INT0 set
    SET_BIT(EIMSK,INT1); //INT1 set
    FLAG_BIT.FLAG_ISR=0; //ISR BIT TO 0
    FLAG_BIT.FLAG_ISR1=0; //ISR1 BIT TO 0
}

