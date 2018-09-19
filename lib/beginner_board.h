#ifndef beginner_board_h
#define beginner_board_h

//Defining pins of each element
#define PIN_LED1 4
#define PIN_LED2 8
#define PIN_LED3 11

#define PIN_RELAY 7

#define PIN_BTN1 2
#define PIN_BTN2 3

#define PIN_POT A1

#include "Arduino.h"

//Initializing BeginnerBoard class with it's functions
class BeginnerBoard {

	public:
		BeginnerBoard();
		void setup();
		void turnLEDSon();
		void turnLEDSoff();
		void potScrollLEDs();
		void potScrollMotor(int motor_number, int revolution_steps);
		void btnsTurnRelay();
		
};


#endif