//codigo motor con 3 botones 6 movimientos base

#define F_CPU 16000000UL  
#include <avr/io.h>  
#include <util/delay.h> 

int main(void) {
    DDRD |= 0xC0; // PD6 y PD7 salida (motor 1)
    PORTD &= ~0xC0;

    DDRD |= 0x0C; // PD2 y PD3 salida (motor 2)
    PORTD &= ~0x0C;

    DDRB &= ~0x02; // PB1 como entrada (botón 1)
    PORTB |= 0x02; // pull-up para botón 1

    DDRB &= ~0x01; // PB0 como entrada (botón 2)
    PORTB |= 0x01; // pull-up para botón 2

    DDRB &= ~0x04; // PD5 como entrada (botón 3)
    PORTB |= 0x04; // pull-up para botón 3

    char A = 0;
    char B = 0;
    char C = 0;
    char D = 0;
    char E = 0;
    char F = 0;

    while (1) {
        // Primera condición gira motor 1 apaga motor 2 botnon2+boton3
        if (!(PINB & 0x02) && !(PINB & 0x01)) {
            _delay_ms(100);
            if (A == 0) {
                PORTD &= ~0x0C;     // Apaga motor 2
                PORTD &= ~0xC0;     // Apaga motor 1
                _delay_ms(100);
                PORTD |= 0x80;      // Enciende PD6 (motor 1)
                PORTD &= ~0x40;     // Apaga PD7
                A = 1;
                B = 0;              // corta la otra condición
                C = 0;
                D = 0;
                E = 0;
                F = 0;

            }
        }
        else{ //si solo presiono el b2  se ejecuta lo anterior que va actvar ambos motoresm1 isquierda m2 derecha
            if (!(PINB & 0x02)) {
                _delay_ms(100);
                if (E == 0) {
    
                PORTD&=~(0X0C); 
                PORTD&=~(0XC0);
                _delay_ms(100); //abra un delay
                PORTD|=(0X40); //
                PORTD|=(0X08);//el pin4 en 1
                PORTD &= ~0x80;
                PORTD &= ~0x04;
    
                    B = 0;
                    C = 0;
                    D = 0;
                    A = 0;
                    E = 1;
                    F = 0;

    
                }
        }

        // Segunda condición  gira motor 2 apaga motor 1 boton1+boton2
        if (!(PINB & 0x01) && !(PINB & 0x04)) {
            _delay_ms(100);
            if (B == 0) {
                PORTD &= ~0x0C;     // Apaga motor 2
                PORTD &= ~0xC0;     // Apaga motor 1
                _delay_ms(100);
                PORTD |= 0x04;      // Enciende PD2 (motor 2)
                PORTD &= ~0x08;     // apaga PD3
                B = 1;
                C = 0;
                D = 0;
                E = 0;
                F = 0;
                A = 0;              // corta la otra condición
            }
        }
        
        else{ //si solo presiono el b1  van los dos hacia adedlante
            if (!(PINB & 0x01)) {
                _delay_ms(100);

                if (F == 0) {
    
                PORTD&=~(0X0C); 
                PORTD&=~(0XC0);
                _delay_ms(100); //abra un delay
                PORTD|=(0X08); // ambos
                PORTD|=(0X80);//

    
                    B = 0;
                    C = 0;
                    D = 0;
                    A = 0;
                    E = 0;
                    F = 1;
                }
            }
        }
    
        //giro corto 1 m1 derecha m2 izquierda
        if (!(PINB & 0x02) && !(PINB & 0x04)) {
            _delay_ms(100);
            if (D == 0) {
                PORTD&=~(0X0C); 
                PORTD&=~(0XC0);
                _delay_ms(100); //abra un delay
                PORTD|=(0X80); //
                PORTD|=(0X04);//el pin4 en 1
                
                B = 0;
                C = 0;
                D = 1;
                A = 0; 
                E = 0;
                F = 0;

            }
        } 
        else{ //APAGADO AMBOS MOTORES
            if (!(PINB & 0x04)) {
                _delay_ms(100);

                if (C == 0) {
    
                PORTD&=~(0X0C); 
                PORTD&=~(0XC0);
                _delay_ms(100); //abra un delay
                PORTD&=~(0X0C); 
                PORTD&=~(0XC0);

    
                    B = 0;
                    C = 1;
                    D = 0;
                    A = 0;
                    E = 0;
                    F = 0;
                }
            }
        }
          

    }
}
}