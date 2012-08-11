//******************************************************************************
//  MSP430G2xx3 Demo - P1 Interrupt from LPM4 with Internal Pull-up
//
//  Description: A hi/low transition on P1.4 will trigger P1_ISR which,
//  toggles P1.0. Normal mode is LPM4 ~ 0.1uA.
//  Internal pullup enabled on P1.4.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//               MSP430G2xx3
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//     /|\   |      R          |
//      --o--| P1.4-o      P1.0|-->LED
//     \|/
//
//  D. Dang
//  Texas Instruments Inc.
//  December 2010
//   Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************
//PIN VCC = POWERTOSENSOR, PIN1.1=SENSORDATA
#include  <msp430g2553.h>
#include "HALL.h"
void Init_HALL(void)
{
  P1OUT |= BIT1;
  P1REN |= BIT1;                            // P1.1 pullup
  P1IE |= BIT1;                             // P1.1 interrupt enabled
  P1IES |= BIT1;                            // P1.1 Hi/lo edge
  P1IFG &= ~BIT1;                           // P1.1 IFG cleared

}


