/* 
 * qut-brushless-controller, an open-source Brushless DC motor controller
 * Copyright (C) 2011 Toby Lockley <tobylockley@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

//===================================//
//       RC Signal Handling          //
//===================================//
//Converts pulse time measurement to PWM value

#include "rc_signal.h"

ISR(INT0_vect) //Signal capture
{
	STOP_TIMER0(); //Stop timer at an edge detection to ensure accurate pulse timing

	if (RC_PIN & (1<<RC)) {
		//Pin is high which means the signal is on the rising edge (start of pulse)
		//Reset timer count and overflows, and start timer
		
		if (MCUCR & (1 << ISC01)) { MCUCR &= ~(1 << ISC01); } //If rising edge detection was selected, switch to toggle detection
		TCNT0 = 0;
		t0_ovfs = 0;
		START_TIMER0(); //Start timer
	}
	else {
		//Pin is low which means the signal is on the falling edge (end of pulse)
		//Record time since start of pulse, and store value in signalBuffer
		
		if (TIFR & (1<<TOV0)) t0_ovfs++; //Catches when the timer has overflowed since start of this interrupt vector
		signalBuffer = ((t0_ovfs << 8) | TCNT0); //Combine overflows and counts into one 16 bit var
		
		//No need to time the off-pulse, and the timer is already stopped, so timer is not reset until rising edge
	}

}

ISR(TIMER0_OVF_vect)
{
	//Timer for the RC servo signal capture, just increments an overflow variable
	// which creates a virtual 16-bit timer
	t0_ovfs++;
}

void init_rc(void)
{
	//INT0 pin initialisation
	GICR |= (1<<INT0); //Enable external interrupt INT0
	MCUCR |= (1 << ISC01) | (1<<ISC00); //Set INT0 to detect rising edge only
										//This makes sure a false signal is not captured on power up
	
	//Timer0 initialisation
	TIMSK |= TIMER0_TIMSK; //Enable Timer0 interrupts
	START_TIMER0();
}

uint8_t processRCSignal(uint32_t RCsignal)
{
	//Called from main, converts input RC signal to 8-bit PWM value

	//Clip signal between low and high values
	if (RCsignal > RCSIGNAL_TICKS_HIGH) RCsignal = RCSIGNAL_TICKS_HIGH;
	if (RCsignal < RCSIGNAL_TICKS_LOW) RCsignal = RCSIGNAL_TICKS_LOW;
	
	//Scale values between Low->High to 0->PWM_TOP
	RCsignal -= RCSIGNAL_TICKS_LOW;
	return (uint8_t)((RCsignal * PWM_TOP)/(RCSIGNAL_TICKS_HIGH - RCSIGNAL_TICKS_LOW));
}