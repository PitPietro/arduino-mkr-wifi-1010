#define TRIG_PIN 3
#define ECHO_PIN 2

long duration, distance;

void setup() {
  // define I/O pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // initialize serial communication and wait for port to open
  // open the Serial Monitor with the shortcut Ctrl + Shift + M
  Serial.begin(9600);
  while (!Serial);

  Serial.println("~~~ SR04 ~~~");
}

void loop() {
  // clear TRIG_PIN by setting it LOW
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(5);

  // trigger the sensor by setting TRIG_PIN ti HIGH for 10 microseconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // read the ECHO_PIN. 'pulseIn()' returns the duration (length of the pulse) in microseconds
  duration = pulseIn(ECHO_PIN, HIGH);
  // Calculate the distance:
  distance = duration * 0.0343 / 2;

  // print the distance on the Serial Monitor
  Serial.print("distance = ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(50);
}
