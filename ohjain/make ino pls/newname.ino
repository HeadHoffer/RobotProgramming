#include <SPI.h>
#include <RF24.h>

#define LED 13
#define analogPin A0


RF24 radio(7, 8); //RF_CS, RF_CSN
//const uint64_t pipes[2] = { 0xe7e7e7e7e7LL, 0xc2c2c2c2c2LL };
byte pipes[][6] = { "1Node", "5Node" }; //use nodes 1Node -> 6Node

int serial_putc(char c, FILE *)
{
	Serial.write(c);

	return c;
}

void printf_begin(void)
{
	fdevopen(&serial_putc, 0);
}

void setup() {
	Serial.begin(9600);
	printf_begin();
	pinMode(LED, OUTPUT);
	radio.begin();
	radio.openWritingPipe(pipes[0]);
	radio.openReadingPipe(1, pipes[1]);
	radio.startListening();
	radio.printDetails();
}

void loop() {
	unsigned long time = millis();

	uint8_t data[32];  // we'll transmit a 32 byte packet
	data[0] = analogRead(analogPin);// our first byte in the pcaket will just be the Ldr value.

	// transmit the data
	radio.stopListening();
	radio.write(&data, sizeof(data));
	Serial.print("Ldr value...");
	Serial.println(data[0]);
	radio.startListening();

	// listen for acknowledgement from the receiver
	unsigned long started_waiting_at = millis();
	bool timeout = false;
	while (!radio.available() && !timeout)
		if (millis() - started_waiting_at > 250)
			timeout = true;

	if (timeout){
		Serial.println("Failed, response timed out.");
	}
	else {
		// the receiver is just going to spit the data back
		radio.read(&data, sizeof(data));
		digitalWrite(LED, HIGH);
		delay(100);  // light up the LED for 100ms if it worked.
		digitalWrite(LED, LOW);
		Serial.print("Got response, round trip delay: ");
		Serial.print(millis() - started_waiting_at);
	}

	delay(1000); // wait a second and do it again. 
}