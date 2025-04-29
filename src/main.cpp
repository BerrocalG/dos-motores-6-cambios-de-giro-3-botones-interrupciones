#define F_CPU 16000000UL  
#include <avr/io.h>  
#include <util/delay.h> 
#include <avr/interrupt.h>

char A = 0;
char B = 0;
char C = 0;
char D = 0;
char E = 0;
char F = 0;

void config_PCI(void) {
    PCICR |= 0x01; // interrupciones en el puerto b
    PCMSK0 |= 0x01; // utilizar b0
    DDRB &= ~0x01;
    PORTB |= 0x01;

    PCMSK0 |= 0x02;// utilizar b1
    DDRB &= ~0x02;
    PORTB |= 0x02;

    PCMSK0 |= 0x04; // utilizar b2
    DDRB &= ~0x04;
    PORTB |= 0x04;
}

ISR(PCINT0_vect) {
    _delay_ms(100);

    //  boton1 + boton2 
    if (!(PINB & 0x02) && !(PINB & 0x01)) {
        PORTD &= ~0x0C;
        PORTD &= ~0xC0;
        _delay_ms(100);
        PORTD |= 0x80;
        PORTD &= ~0x40;
        A = 1; 
        B = C = D = E = F = 0;
    }

    // b1
    else if (!(PINB & 0x02)) {
        PORTD &= ~0x0C;
        PORTD &= ~0xC0;
        _delay_ms(100);
        PORTD |= 0x40;
        PORTD |= 0x08;
        PORTD &= ~0x80;
        PORTD &= ~0x04;
        E = 1;
        A = B = C = D = F = 0;
    }

    // b0 b2
    else if (!(PINB & 0x01) && !(PINB & 0x04)) {
        PORTD &= ~0x0C;
        PORTD &= ~0xC0;
        _delay_ms(100);
        PORTD |= 0x04;
        PORTD &= ~0x08;
        B = 1;
        A = C = D = E = F = 0;
    }

    // b0
    else if (!(PINB & 0x01)) {
        PORTD &= ~0x0C;
        PORTD &= ~0xC0;
        _delay_ms(100);
        PORTD |= 0x08;
        PORTD |= 0x80;
        F = 1;
        A = B = C = D = E = 0;
    }

    // b1 b2
    else if (!(PINB & 0x02) && !(PINB & 0x04)) {
        PORTD &= ~0x0C;
        PORTD &= ~0xC0;
        _delay_ms(100);
        PORTD |= 0x80;
        PORTD |= 0x04;
        D = 1;
        A = B = C = E = F = 0;
    }

    // b2
    else if (!(PINB & 0x04)) {
        PORTD &= ~0x0C;
        PORTD &= ~0xC0;
        _delay_ms(100);
        C = 1;
        A = B = D = E = F = 0;
    }
}

int main(void) {
    DDRD |= 0xC0; // motor1
    PORTD &= ~0xC0;

    DDRD |= 0x0C; //motor2
    PORTD &= ~0x0C;

    config_PCI();
    sei(); 

    while (1) {
       
    }
}
