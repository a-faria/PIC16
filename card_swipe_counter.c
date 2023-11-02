#include <xc.h>
#define _XTAL_FREQ 4000000 // 4Mhz
// Set config word
#pragma config FOSC=INTRCIO, WDTE=OFF, PWRTE=OFF, MCLRE=ON, \
CP=OFF, CPD=OFF, BOREN=OFF, IESO=OFF, FCMEN=OFF
void displayUnits(int units) {
switch(units) {
        case 0: PORTC=0b00111111; break;
        case 1: PORTC=0b00000110; break;
        case 2: PORTC=0b01011011; break;
        case 3: PORTC=0b01001111; break;
        case 4: PORTC=0b01100110; break;
        case 5: PORTC=0b01101101; break;
        case 6: PORTC=0b01111101; break;
        case 7: PORTC=0b00000111; break;
        case 8: PORTC=0b01111111; break;
        case 9: PORTC=0b01101111; break;
}
}
void displayTens(int tens) {
    switch(tens) {
// TASK 1: Display tens value using PORTA, PORTB and PORTC
       
          case 0: PORTA=0b00110000; PORTB=0b11110000; RC7=0; break;
          case 1: PORTA=0b00100000; PORTB=0b00010000; RC7=0; break;
          case 2: PORTA=0b00110000; PORTB=0b01100000; RC7=1; break;
          case 3: PORTA=0b00110000; PORTB=0b00110000; RC7=1; break;
          case 4: PORTA=0b00100000; PORTB=0b10010000; RC7=1; break;
          case 5: PORTA=0b00010000; PORTB=0b10110000; RC7=1; break;
          case 6: PORTA=0b00010000; PORTB=0b11110000; RC7=1; break;
          case 7: PORTA=0b00110000; PORTB=0b00010000; RC7=0; break;
          case 8: PORTA=0b00110000; PORTB=0b11110000; RC7=1; break;
          case 9: PORTA=0b00110000; PORTB=0b10110000; RC7=1; break;


}
}
void displayNumber(int number) {
    int units = number % 10;
    displayUnits(units);
    int tens = (int)(number / 10);
    displayTens(tens);
}
volatile int eventCount = 0;
void __interrupt() isr(void) {
// TASK 3: Respond to interrupt
       
        __delay_ms(250); //a) Delay for 250 milliseconds
        eventCount = eventCount + 1; //b) Increments the event count variable
        INTCONbits.INTF = 0; //c) Clears the INTF flag to disable the external interrupt flag
        displayNumber(eventCount); //d) displays the current event count
      
}
void main(void) {
    TRISA = 0x04; // All outputs except for INT bit
    TRISB = 0x00;
    TRISC = 0x00;
    ANSEL = 0x00; // Set Port C pins to digital
    ANSELH = 0x00; // (they are analog by default)
// TASK 2: Perform initialisation
    
        INTCONbits.INTF = 0; //a). clears the external interrupt flag 
        OPTION_REGbits.INTEDG = 1; // b) enables an interrupt on the rising edge
        INTCONbits.INTE = 1; // c) sets the INTE bit to 1 to enable the external interrupt
        INTCONbits.GIE = 1; //d) sets the GIE bit to 1 to enable all interrupts
        
    displayNumber(eventCount);
    while(1) {

}
}

