/*
 * Portable Weather Station with MKR IoT Carrier
 *
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
  CARRIER_CASE = false;
  
  // initialize the MKR IoT Carrier and output any errors in the serial monitor
  carrier.begin();
  carrier.display.setRotation(0);
}

void loop() {
  // read values from sensors
  temperature = carrier.Env.readTemperature();
  humidity = carrier.Env.readHumidity();

  printInfo();

  delay(1000);
}

void printInfo() {
  // background
  carrier.display.fillScreen(ST77XX_BLUE);
  // white text
  carrier.display.setTextColor(ST77XX_WHITE);
  // medium sized text
  carrier.display.setTextSize(2);

  //sets position for printing (x and y)
  carrier.display.setCursor(30, 110); 
  
  carrier.display.print("TEMP ");
  carrier.display.print(temperature);
  carrier.display.print(" ");
  // since ° cannot be printed with a simple 'print()', let's create it
  carrier.display.drawCircle(156, 112, 2, ST77XX_WHITE);
  carrier.display.println("C");

  //sets new position for printing (x and y)
  carrier.display.setCursor(30, 130);

  carrier.display.print("HUM  ");
  carrier.display.print(humidity);
  carrier.display.println(" %");
}