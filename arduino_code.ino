#include "DHT.h" // Use the Adafruit library

// --- Sensor Configuration ---
#define DHTPIN 8       // DHT11 is on Digital Pin 8
#define DHTTYPE DHT11    
DHT dht(DHTPIN, DHTTYPE);

// --- LED Configuration ---
#define LOW_HUM_LED 11   // Blue LED
#define MED_HUM_LED 12   // Green LED
#define HIGH_HUM_LED 13  // Red LED

// --- Timer for Non-Blocking Sensor Read ---
unsigned long previousMillis = 0;
const long interval = 2000; // Read sensor every 2 seconds

void setup() {
  Serial.begin(9600);
  Serial.println("--- Sensor Dashboard Active ---");

  // Set all LED pins to OUTPUT
  pinMode(LOW_HUM_LED, OUTPUT);
  pinMode(MED_HUM_LED, OUTPUT);
  pinMode(HIGH_HUM_LED, OUTPUT);

  // Turn all LEDs off at startup
  digitalWrite(LOW_HUM_LED, LOW);
  digitalWrite(MED_HUM_LED, LOW);
  digitalWrite(HIGH_HUM_LED, LOW);
  
  dht.begin();
  delay(2000); // Wait for sensor to stabilize
}

void loop() {
  // Use millis() for non-blocking loop
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    // Read sensor data
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    // Check for a failed read
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      // Don't update LEDs if read failed
    } else {
      // 1. Send data to Python
      // Format: T:24.50,H:65.20
      Serial.print("T:");
      Serial.print(t);
      Serial.print(",H:");
      Serial.println(h);

      // 2. Control the humidity indicator LEDs
      updateHumidityLEDs(h);
    }
  }
}

void updateHumidityLEDs(float humidity) {
  // First, turn all LEDs off
  digitalWrite(LOW_HUM_LED, LOW);
  digitalWrite(MED_HUM_LED, LOW);
  digitalWrite(HIGH_HUM_LED, LOW);

  // Now, turn the correct one on
  if (humidity < 60.0) {
    digitalWrite(LOW_HUM_LED, HIGH); // Low humidity
  } else if (humidity >= 60.0 && humidity <= 90.0) {
    digitalWrite(MED_HUM_LED, HIGH); // Medium (ideal) humidity
  } else if (humidity > 90.0) {
    digitalWrite(HIGH_HUM_LED, HIGH); // High humidity
  }
}