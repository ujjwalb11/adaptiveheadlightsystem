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

int main()
{
    pin_config(); //I/P and O/P pin configuration function call

    isr_init(); //ISR initialization function call

    TCCR0A =0x83; //Fast PWM mode
    TCNT0=0x00;// Timer counter register
    TCCR0B=0x05; //clock pre-scalar set to 1024


    while(1) //super loop
    {
        adc_init();

        if(FLAG_BIT.speed>=512) //speed threshold
        {
            CLR_BIT(PORTB,PB4);
            SET_BIT(PORTB,PB5); //high beam
        }

        else if(FLAG_BIT.speed<500)
        {
            CLR_BIT(PORTB,PB5);
            SET_BIT(PORTB,PB4); //low beam
        }
        if(FLAG_BIT.light>=512) //light threshold as day time
        {
            CLR_BIT(PORTB,PB3); //headlight OFF
        }
        else if(FLAG_BIT.light<512) //light threshold as night time
        {
            SET_BIT(PORTB,PB3); //headlight ON
        }

        if(FLAG_BIT.FLAG_ISR1%2==1 && FLAG_BIT.FLAG_ISR%2==1) //if both are on due to defect then
            //default position of headlights
        {
            CLR_BIT(PORTC,PC5); //default position
        }


        if(FLAG_BIT.FLAG_ISR%2==1) //for left turning path
        {
            FLAG_BIT.duty=0;
            OCR0A=FLAG_BIT.duty;
            SET_BIT(PORTC,PC5); //headlights turn left
        }
        else if(FLAG_BIT.FLAG_ISR%2==0 && FLAG_BIT.FLAG_ISR1%2!=1)
        {
            CLR_BIT(PORTC,PC5); //default position
        }

        if(FLAG_BIT.FLAG_ISR1%2==1) //for right turning path
        {
            FLAG_BIT.duty=128;
            OCR0A=FLAG_BIT.duty;
            SET_BIT(PORTC,PC5); //headlights turn right
        }
        else if(FLAG_BIT.FLAG_ISR1%2==0 && FLAG_BIT.FLAG_ISR%2!=1)
        {
            CLR_BIT(PORTC,PC5); //default position
        }
    }
}

ISR(INT0_vect) //INT0 vector
{
    tog(PORTB,PB2); //indicator in information cluster
    cli();
    FLAG_BIT.FLAG_ISR+=1;
    sei();
}

ISR(INT1_vect) //INT1 vector
{
    tog(PORTB,PB2); //indicator in information cluster
    cli();
    FLAG_BIT.FLAG_ISR1+=1;
    sei();
}
