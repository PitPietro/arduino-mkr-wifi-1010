/*
 * sizeof() tests
 * 
 * Docs: https://www.arduino.cc/reference/en/language/variables/utilities/sizeof/
 */

void setup() {
  // initialize serial communication and wait for port to open
  Serial.begin(9600);
  // wait for serial port to connect. Needed for native USB port only
  while (!Serial);
  
  int arrayInt[] = {123, 456, 789};

  byte i;

  // this for loop works correctly with an array of any type or size
  for (i = 0; i < (sizeof(arrayInt) / sizeof(arrayInt[0])); i++) {
    // print arrayInt[i]
    Serial.print(arrayInt[i]);
    Serial.print("\t");
  }

  Serial.println();

  Serial.print("The dimension is ");
  Serial.print(i);
}

void loop() {
  // no need for the loop
}
