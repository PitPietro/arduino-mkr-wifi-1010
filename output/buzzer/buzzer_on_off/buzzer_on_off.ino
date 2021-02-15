/*
 * Buzzer On/Off
 * 
 * This code shows how to "blink" a buzzer.
 * 
 * Reference: https://create.arduino.cc/projecthub/SURYATEJA/use-a-buzzer-module-piezo-speaker-using-arduino-uno-89df45
 */

// connect the buzzer to pin 9
unsigned const short int buzzer = 9;

void setup(){
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
}

void loop(){
  // send 1KHz sound signal
  tone(buzzer, 1000);

  // wait for 1 second
  delay(1000);

  // stop sound
  noTone(buzzer);

  // wait for 1 second
  delay(1000);
}
