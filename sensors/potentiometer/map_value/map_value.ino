/*
 * Attack a potentiometer to Analog Pin A0.
 * Use the 'map()' function to map the values from 10 bits (0-1023) to 8 bits (0-255) so that the
 * potentiometer can light up a PWM LED, or an RGB LED (this will require tree potentiometers).
 * 
 * Reference: https://www.arduino.cc/en/pmwiki.php?n=Reference/Map
*/

int potPin = A0;

void setup() {
  // initialize serial communication and wait for port to open
  Serial.begin(9600);
  // wait for serial port to connect. Needed for native USB port only
  while (!Serial);
}

void loop() {
  // read the input on analog pin A0
  int analogValue = analogRead(potPin);
  int mappedValue = map(analogValue, 0, 1023, 0, 255);
  // analogWrite(4, mappedValue); // for a PWM LED
  
  Serial.print(analogValue);
  Serial.print("\t-->\t");
  Serial.println(mappedValue);
  delay(50);
}
