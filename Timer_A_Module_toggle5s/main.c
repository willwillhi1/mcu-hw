#include <msp430.h> 

static unsigned int counter = 0;

void main(void) {
  WDTCTL = WDTPW + WDTHOLD;   // Stop watchdog timer
  P1DIR |= BIT6|BIT0;         // Set P1.0 and P1.6 to output direction
  TA0CCTL0 = 0x10;            // Enable counter interrupts, bit 4=1
  TA0CTL = TASSEL_2 + MC_2;   // Timer A 0 with SMCLK @ 1 MHz, continuous mode
  _BIS_SR(LPM0_bits + GIE);   // LPM0 (low power mode) with interrupts enabled
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0 (void) {              // Timer0 A0 interrupt service routine
  ++counter;
  if (counter >= 80) {
    P1OUT ^= BIT6|BIT0;              // Toggle red and green LED
    counter = 0;
  }
}