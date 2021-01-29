/*
 * the analog pin the TMP36's Vout (sense) pin is connected to
 * the resolution is 10 mV / degree centigrade with a 500 mV offset
 * to allow for negative temperatures
 */

#define TMP_PIN A1

// 5 for Arduino Uno / 3.3 for Arduino MKR 
const float RANGE_MAX = 3.3;
/*
 * setup() - this function runs once when you turn your Arduino on
 * We initialize the serial connection with the computer
 */
void setup() {
  Serial.begin(9600);
  while(!Serial);
}
 
void loop() {
  //getting the voltage reading from the temperature sensor
  int reading = analogRead(TMP_PIN);  
 
  // converting that reading to voltage
  float voltage = reading * RANGE_MAX;
  voltage /= 1024.0; 
 
  // print out the voltage
  Serial.print(voltage); Serial.println(" volts");
 
  // now print out the temperature
  float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
  Serial.print(temperatureC);
  Serial.println(" degrees C");
 
  // now convert to Fahrenheit
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
  Serial.print(temperatureF);
  Serial.println(" degrees F");
 
  delay(1000); // waiting a second
}

// Reference: https://learn.adafruit.com/tmp36-temperature-sensor/using-a-temp-sensor
