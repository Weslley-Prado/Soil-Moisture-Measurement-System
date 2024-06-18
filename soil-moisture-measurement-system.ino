// Pin assignment for display segments
const int segmentPins[7] = {2, 3, 4, 5, 6, 7, 8};

// Arrays to represent numbers from 0 to 9
const int digitPatterns[10][7] = {
  {1, 1, 1, 1, 1, 1, 0},  // 0
  {0, 1, 1, 0, 0, 0, 0},  // 1
  {1, 1, 0, 1, 1, 0, 1},  // 2
  {1, 1, 1, 1, 0, 0, 1},  // 3
  {0, 1, 1, 0, 0, 1, 1},  // 4
  {1, 0, 1, 1, 0, 1, 1},  // 5
  {1, 0, 1, 1, 1, 1, 1},  // 6
  {1, 1, 1, 0, 0, 0, 0},  // 7
  {1, 1, 1, 1, 1, 1, 1},  // 8
  {1, 1, 1, 0, 0, 1, 1}   // 9
};

int moisture = 0;

void setup() {
  // Set segment pins as output
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  // Configure moisture sensor pins
  pinMode(A0, OUTPUT);
  pinMode(A1, INPUT);
  // Initialize serial monitor for debugging
  Serial.begin(9600);
}

void loop() {
  // Turn on the moisture sensor
  digitalWrite(A0, HIGH);
  delay(10); // Wait 10 ms for the reading to stabilize
  // Read the analog value from the moisture sensor
  moisture = analogRead(A1);
  // Turn off the moisture sensor to avoid corrosion
  digitalWrite(A0, LOW);

  // Ensure the sensor value stays within the expected range
  if (moisture < 0) {
    moisture = 0;
  } else if (moisture > 876) {
    moisture = 876;
  }

  // Map the sensor value to a value between 0 and 9
  int moistureLevel = map(moisture, 0, 876, 0, 9);

  // Debug: print the sensor value and the mapped value
  Serial.print("Sensor Value: ");
  Serial.print(moisture);
  Serial.print(" -> Moisture Level: ");
  Serial.println(moistureLevel);

  // Update the display with the mapped value
  displayDigit(moistureLevel);

  // Wait 1 second before the next reading
  delay(1000);
}

void displayDigit(int digit) {
  // Iterate through each segment and set its state (on or off)
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], digitPatterns[digit][i] == 1 ? HIGH : LOW);
  }
}
