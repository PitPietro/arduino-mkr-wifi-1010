/*
 * Attack a potentiometer to Analog Pin A0.
 * This code evaluates the voltage (from 0V to 5V) that the board recive and interprets as a value from 0 to 1023.
 * 
 * The 'map()' function can only be used to rescale analog value to the int or long data types but, since
 * the volga value is a floating point number, you need to use the 'floatMap' function.
 * 
 * Reference: https://arduinogetstarted.com/tutorials/arduino-potentiometer
*/

const int potPin = A0;

float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup() {
  // initialize serial communication and wait for port to open
  Serial.begin(9600);
  // wait for serial port to connect. Needed for native USB port only
  while (!Serial);
}

void loop() {
  // read the input on analog pin A0
  int analogValue = analogRead(potPin);
  
  // Rescale to potentiometer's voltage (from 0V to 5V):
  float voltage = floatMap(analogValue, 0, 1023, 0, 5);

  // print out the value you read:
  Serial.print("analog: ");
  Serial.print(analogValue);
  Serial.print("\tvoltage: ");
  Serial.println(voltage);
  delay(50);
}
