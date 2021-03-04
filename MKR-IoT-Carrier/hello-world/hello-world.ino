/*
 * Hello World with MKR IoT Carrier
 * The boolean 'CARRIER_CASE' can be set to either 'true' or 'false' (by default has been set to 'false').
 * This refers to the plastic casing in the kit and the capacitive buttons on the carrier.
 * If you use the plastic casing, set it to 'true' and if not, set it to 'false'. 
 * 
 * Docs: https://opla.arduino.cc/opla/module/carrier/lesson/get-to-know-the-carrier
*/

#include <Arduino_MKRIoTCarrier.h>

MKRIoTCarrier carrier;

float temperature = 0;
float humidity = 0;

void setup() {
  Serial.begin(9600);
  // ensures that unless the Serial Monitor is opened, it won't be able to initialize the carrier
  while (!Serial);
  CARRIER_CASE = false;
  
  // initialize the MKR IoT Carrier and output any errors in the serial monitor
  carrier.begin();
  carrier.display.setRotation(0);

  printTemperature();
}

void loop() {
  // read values from sensors
  temperature = carrier.Env.readTemperature();
  humidity = carrier.Env.readHumidity();

  // update touch buttons
  carrier.Buttons.update();

  // print the sensor values
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");  
  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println(" %");
  
  // print out values if the buttons are pressed
  if (carrier.Button0.onTouchDown()) {
    printTemperature();
  }

  if (carrier.Button1.onTouchDown()) {
    printHumidity();
  }
}

void printTemperature() {
  //configuring display, setting background color, text size and text color
  // red background
  carrier.display.fillScreen(ST77XX_RED);
  // white text
  carrier.display.setTextColor(ST77XX_WHITE);
  // medium sized text
  carrier.display.setTextSize(2);

  //sets position for printing (x and y)
  carrier.display.setCursor(30, 110); 
  
  carrier.display.print("Temp: ");
  carrier.display.print(temperature);
  carrier.display.println(" C");
}

void printHumidity() {
  // configuring display, setting background color, text size and text color
  // blue background
  carrier.display.fillScreen(ST77XX_BLUE);
  // white text
  carrier.display.setTextColor(ST77XX_WHITE);
  // medium sized text
  carrier.display.setTextSize(2);

  //sets new position for printing (x and y)
  carrier.display.setCursor(30, 110);

  carrier.display.print("Humi: ");
  carrier.display.print(humidity);
  carrier.display.println(" %");
}
