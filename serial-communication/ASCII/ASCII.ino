/*
  ASCII table

  Inspired by http://www.arduino.cc/en/Tutorial/ASCIITable
*/

void setup() {
  //Initialize serial
  Serial.begin(9600);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("ASCII Table");
}

// the first visible ASCII element is '!' which is associated with the number 33

char character = 33; // this declaration is equivalent to the one below
// char character = '!'; // this declaration is equivalent to the one above

void loop() {
  // Serial Monitor interprets all bytes as ASCII, so 33 will show up as '!'
  // Note: use the 'write()' function 
  Serial.write(character);

  // prints value as string as an ASCII-encoded decimal (base 10).
  // Note: Decimal is the default format for 'print()' and 'println()' functions: no modifier is needed
  Serial.print("\tdec: ");

  // you can declare the modifier for decimal if you want to
  Serial.print(character);
  // Serial.print(character, DEC); // this line is equivalent to the one above


  Serial.print("\t\t hex: ");
  
  // prints value as string in hexadecimal (base 16)
  Serial.print(character, HEX);

  Serial.print("\t oct: ");
  
  // prints value as string in octal (base 8)
  Serial.print(character, OCT);

  Serial.print("\tbin: ");
  
  // prints value as string in binary (base 2)
  // Note: 'println()' function is used in place if 'print()' to apply a line break
  Serial.println(character, BIN);

  // if the last visible character '~' (or 126) is printed, when stop:
  // Note: the condition below is equivalent to: if (character == '~')
  if (character == 126) {     {
    // this loop, loops forever and does nothing
    while (true) {
      continue;
    }
  }
  
  // increment the variable and go on to the next character
  character++;
}
