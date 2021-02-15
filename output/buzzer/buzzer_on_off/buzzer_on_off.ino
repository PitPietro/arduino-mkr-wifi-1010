/*
 * Buzzer On/Off
 * 
 * This code shows how to "blink" a buzzer.
 * 
 * > Circuit
 * The Buzzer has two legs:
 * - black leg to ground (GND)
 * - red leg through a 100 Ohm resistor (brown - black - brown - gold/silver) and then to a given pin of the Arduino board.
 * 
 * > The Code
 * 'tone()'
 * - tone(pin, frequency)
 * - tone(pin, frequency, duration)
 * 
 * Generates a square wave of the specified frequency (and 50% duty cycle) on a pin. If you do not specify
 * the 'duration' parameter, the wave continues until a call to 'noTone()'. If you want to play different
 * pitches on multiple pins, you need to call 'noTone()' on one pin before calling tone() on the next pin.
 * 
 * Note: 'tone()' will interfere with PWM output on pins 3 and 11 (on boards other than the Mega).
 * Moreover, it is not possible to generate tones lower than 31Hz.
 * 
 * > 'noTone()'
 * - noTone(pin)
 * 
 * Stops the generation of a square wave triggered by 'tone()'. Has no effect if no tone is being generated.
 * 
 * Reference: https://create.arduino.cc/projecthub/SURYATEJA/use-a-buzzer-module-piezo-speaker-using-arduino-uno-89df45
 * Docs: tone() https://www.arduino.cc/reference/en/language/functions/advanced-io/tone/
 * B. Hagman's note: https://github.com/bhagman/Tone#ugly-details
 */

// connect the buzzer to pin 3
unsigned const char buzzer = 3;

void setup(){
  // set buzzer (pin 3) as an output
  pinMode(buzzer, OUTPUT);
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
