/*
 Name:		ohjain.ino
 Created:	6/6/2017 1:14:01 PM
 Author:	KimKar
*/

//joystick 1
int ledPin = 13;
int joyPinLeftY = A0;                 // slider variable connecetd to analog pin 0
int joyPinLeftX = A1;                 // slider variable connecetd to analog pin 1
int valueLeftY = 0;                  // variable to read the value from the analog pin 0
int valueLeftX = 0;                  // variable to read the value from the analog pin 1

//joystick 2

int joyPinRightX = A2;
int joyPinRightY = A3;
int valueRightX = 0;
int valueRightY = 0;

//button
int buttonPin = 3;
int buttonState = 0;

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(ledPin, OUTPUT);              // initializes digital pins 0 to 7 as outputs
	pinMode(buttonPin, INPUT);
	Serial.begin(9600);
}

int treatValue(int data) {
	return (data * 9 / 1024) + 48;
}

// the loop function runs over and over again until power down or reset
void loop() {
	/*
	// reads the value of the variable resistor 
	valueLeftY = analogRead(joyPinLeftY);
	// this small pause is needed between reading
	// analog pins, otherwise we get the same value twice
	delay(100);
	// reads the value of the variable resistor 
	valueLeftX = analogRead(joyPinLeftX);
	delay(100);
	valueRightX = analogRead(joyPinRightX);
	delay(100);
	valueRightY = analogRead(joyPinRightY);

	digitalWrite(ledPin, HIGH);
	delay(valueLeftY);
	digitalWrite(ledPin, LOW);
	delay(valueLeftX);
	Serial.print('L');
	Serial.print(valueLeftY);
	Serial.print(" ");
	Serial.println(valueLeftX);

	digitalWrite(ledPin, HIGH);
	delay(valueRightX);
	digitalWrite(ledPin, LOW);
	delay(valueRightY);
	Serial.print('R');
	Serial.print(valueRightX);
	Serial.print(" ");
	Serial.println(valueRightY);
	*/

	buttonState = digitalRead(buttonPin);
	Serial.println(buttonState);

	if (buttonState == HIGH) {
		// turn LED on:
		digitalWrite(ledPin, HIGH);
		Serial.println("Button pressed!");
	}
	else {
		// turn LED off:
		digitalWrite(ledPin, LOW);
	}

	delay(100);
}
