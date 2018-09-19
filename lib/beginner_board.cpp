#include "Arduino.h"
#include "beginner_board.h"
#include <Stepper.h>

BeginnerBoard::BeginnerBoard()
{
}


/*
 * Function:		void BeginnerBoard::setup(void)	
 * Description:		Sets all static pins as input/output
 */
void BeginnerBoard::setup()
{
	pinMode(PIN_LED1, OUTPUT);								//Setting pin of the first LED as output
	Serial.println("First LED has been set.");
	
	delay(10);												//Delaying print message 
	
	pinMode(PIN_LED2, OUTPUT);								//Setting pin of the second LED as output
	Serial.println("Second LED has been set.");
	
	delay(10);												//Delaying print message 
	
	pinMode(PIN_LED3, OUTPUT);								//Setting pin of the third LED as output
	Serial.println("Third LED has been set.");
	
	delay(10);												//Delaying print message 
	
	pinMode(PIN_RELAY, OUTPUT);								//Setting pin of the relay as output
	Serial.println("Relay has been set.");
	
	delay(10);												//Delaying print message 
	
	pinMode(PIN_POT, INPUT);								//Setting pin of the potentiometer as output
	Serial.println("Potentiometer has been set.");
	
	delay(10);
	
	Serial.println("System Ready.");
	
} // End of BeginnerBoard::setup()


/*
 * Function:		void BeginnerBoard::turnLEDSon(void)
 * Description:		Turns on every LED on the board
 */
void BeginnerBoard::turnLEDSon()
{
	digitalWrite(PIN_LED1, HIGH);							//Turning on first LED
	digitalWrite(PIN_LED2, HIGH);							//Turning on second LED
	digitalWrite(PIN_LED3, HIGH);							//Turning on third LED
	
	Serial.println("turnLEDSon() - LEDs have turned on");
	
} // End of BeginnerBoard::turnLEDSon()


/*
 * Function:		void BeginnerBoard::turnLEDSoff(void)
 *
 * Description:		Turns off every LED on the board
 */
void BeginnerBoard::turnLEDSoff()
{	
	digitalWrite(PIN_LED1, LOW);							//Turning off first LED
	digitalWrite(PIN_LED2, LOW);							//Turning off second LED
	digitalWrite(PIN_LED3, LOW);							//Turning off third LED
	Serial.println("turnLEDSoff() - LEDs have turned off");
} // End of BeginnerBoard::turnLEDSoff()


/*
 * Function:		void BeginnerBoard::potScrollLEDs(void)
 * Description:		Makes LEDs interact with potentiometer, making it able to scroll them left and right
 */
void BeginnerBoard::potScrollLEDs()
{
	/* How it works:
	 *	0-256    -> ooo
	 *  256-512  -> oox (xoo)
	 *  512-768  -> oxo
	 *  768-1024 -> xoo (oox)
	 */

	int pot = analogRead(PIN_POT);							//Reading potentiometer value
					
	if (pot < 256) {										//Splitting potemtiometer values in 4 parts for every possible scenario of LEDs 
															//(all off, third turned on, second turned on, first turned on)
		digitalWrite(PIN_LED3, LOW);
		digitalWrite(PIN_LED2,LOW);							//First case, potentiometer value is 0-256, which means that every LED is turned off
		digitalWrite(PIN_LED1,LOW);
	
	} else if (pot >= 256 && pot < 512) {
	
		digitalWrite(PIN_LED3,HIGH);
		digitalWrite(PIN_LED2,LOW);							//Second case, potentiometer value is 256-512, which means that only the first (third) LED is turned on
		digitalWrite(PIN_LED1,LOW);
		
	} else if (pot >= 512 && pot < 768){
	
		digitalWrite(PIN_LED3,LOW);
		digitalWrite(PIN_LED2,HIGH);						//Third case, potentiometer value is 512-768, which means that only the second LED is turned on
		digitalWrite(PIN_LED1,LOW);
		
	} else if (pot >= 768 && pot <= 1024){
	
		digitalWrite(PIN_LED3,LOW);
		digitalWrite(PIN_LED2,LOW);							//Fourth and final case, potentiometer value is 768-1024, which means that only the third (first) LED is turned on
		digitalWrite(PIN_LED1,HIGH);
		
	}
	
	Serial.println("potScrollLEDs() - LEDs are being controlled by the potentiometer");
	
} // End of BeginnerBoard::potScrollLEDs()


/*
 * Function:		void BeginnerBoard::potScrollMotor(int motor_number, int revolution_steps)
 * Parameters:		motor_number (selected motor), revolution_steps (steps needed to do a revolution)
 * Description:		Makes motors interact with potentiometer, making it able to speed the motor up or slow it down
 */
void BeginnerBoard::potScrollMotor(int motor_number, int revolution_steps)
{
	//Since we have 2 motor segments, we need to specify which one we're using
	if (motor_number == 1){
	
		Stepper myStepper(revolution_steps, 2, 3, 5, 6);					//Initializing first motor
		int sensorReading 	= analogRead(PIN_POT);							//Reading potentiometer value
		int motorSpeed 		= map(sensorReading, 0, 1023, 0, 100);			//Mapping potentiometer value (0-1023) into values (0-100)
		
		//Speeding up, slowing down the motor
		if (motorSpeed > 0) {
		
			myStepper.setSpeed(motorSpeed);
			myStepper.step(revolution_steps / 00);
			
		}	
	} else if (motor_number == 2) {
	
		Stepper myStepper_2(revolution_steps, 9, 10, 12, 13);				//Initializing first motor
		int sensorReading_2 	= analogRead(PIN_POT);						//Reading potentiometer value
		int motorSpeed_2 		= map(sensorReading_2, 0, 1023, 0, 100);	//Mapping potentiometer value (0-1023) into values (0-100)
			
		if (motorSpeed_2 > 0) {												//Speeding up, slowing down the motor
		
			myStepper_2.setSpeed(motorSpeed_2);
			myStepper_2.step(revolution_steps / 100);
			
		}
	}
	
	Serial.println("potScrollMotor - Motor is being controlled by the potentiometer");
	
} // End of BeginnerBoard::potScrollMotor()


/*
 * Function:		void BeginnerBoard::btnsTurnRelay(void)
 * Description:		Makes buttons interact with relay, turning it off/on
 */
void BeginnerBoard::btnsTurnRelay()
{
	
	pinMode(PIN_BTN1, INPUT);												//Setting first button pin to Input mode
	Serial.println("Button 1 has been set");
	
	pinMode(PIN_BTN2, INPUT);												//Setting second button pin to Input mode
	Serial.println("Button 2 has been set");
	
	int btn_1 = digitalRead(PIN_BTN1);										//Reading first button button value
	int btn_2 = digitalRead(PIN_BTN2);										//Reading second button button value
	
	//Simple if, else if statements which turn the relay on and off
	if (btn_1 == HIGH){
	
		digitalWrite(PIN_RELAY, HIGH);										//First button pressed -> relay switches on
		
	} else if (btn_2 == HIGH){
	
		digitalWrite(PIN_RELAY, LOW);										//Second button pressed -> relay switches off
		
	}
} // End of BeginnerBoard::btnsTurnRelay()