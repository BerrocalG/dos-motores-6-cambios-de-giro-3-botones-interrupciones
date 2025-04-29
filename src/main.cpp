/*
//todo en la interrupcion
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

*/

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
    PCICR |= 0x01; // habilita interrupciones en el puerto B
    PCMSK0 |= 0x01; // B0
    DDRB &= ~0x01;
    PORTB |= 0x01;

    PCMSK0 |= 0x02; // B1
    DDRB &= ~0x02;
    PORTB |= 0x02;

    PCMSK0 |= 0x04; // B2
    DDRB &= ~0x04;
    PORTB |= 0x04;
}

ISR(PCINT0_vect) {
    _delay_ms(100); // antirrebote

    if (!(PINB & 0x02) && !(PINB & 0x01)) { // B1 + B0
        A = 1;
        B = C = D = E = F = 0;
    }
    else if (!(PINB & 0x01) && !(PINB & 0x04)) { // B0 + B2
        B = 1;
        A = C = D = E = F = 0;
    }
    else if (!(PINB & 0x02) && !(PINB & 0x04)) { // B1 + B2
        D = 1;
        A = B = C = E = F = 0;
    }
    else if (!(PINB & 0x02)) { // solo B1
        E = 1;
        A = B = C = D = F = 0;
    }
    else if (!(PINB & 0x01)) { // solo B0
        F = 1;
        A = B = C = D = E = 0;
    }
    else if (!(PINB & 0x04)) { // solo B2
        C = 1;
        A = B = D = E = F = 0;
    }
}

int main(void) {
    DDRD |= 0xC0; // motor1: PD6 y PD7
    PORTD &= ~0xC0;

    DDRD |= 0x0C; // motor2: PD2 y PD3
    PORTD &= ~0x0C;

    config_PCI();
    sei(); // habilita interrupciones globales

    while (1) {
        if (A == 1) {
            PORTD &= ~0x0C; // apaga motor2
            PORTD &= ~0xC0; // apaga motor1
            _delay_ms(100);
            PORTD |= 0x80; // motor1 adelante
            PORTD &= ~0x40; // motor1: solo PD7 activo
            A = 0;
        }
        else if (E == 1) {
            PORTD &= ~0x0C;
            PORTD &= ~0xC0;
            _delay_ms(100);
            PORTD |= 0x40; // motor1 atrás
            PORTD |= 0x08; // motor2 adelante
            E = 0;
        }
        else if (B == 1) {
            PORTD &= ~0x0C;
            PORTD &= ~0xC0;
            _delay_ms(100);
            PORTD |= 0x04; // motor2 atrás
            PORTD &= ~0x08;
            B = 0;
        }
        else if (F == 1) {
            PORTD &= ~0x0C;
            PORTD &= ~0xC0;
            _delay_ms(100);
            PORTD |= 0x08; // motor2 adelante
            PORTD |= 0x80; // motor1 adelante
            F = 0;
        }
        else if (D == 1) {
            PORTD &= ~0x0C;
            PORTD &= ~0xC0;
            _delay_ms(100);
            PORTD |= 0x80; // motor1 adelante
            PORTD |= 0x04; // motor2 atrás
            D = 0;
        }
        else if (C == 1) {
            PORTD &= ~0x0C; // apaga motor2
            PORTD &= ~0xC0; // apaga motor1
            _delay_ms(100);
            C = 0;
        }
    }
}
