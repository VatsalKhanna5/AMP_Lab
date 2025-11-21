/*
 * Project: DHT11 Monitor with 1.8" TFT Display (ST7735)
 * Status: Updated with Debugging & Green Tab Default
 */

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>
#include <DHT.h>

// --- PIN DEFINITIONS ---
#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11

// --- DISPLAY PINS ---
#define TFT_CS     10
#define TFT_RST    9
#define TFT_DC     8

// --- OBJECT INITIALIZATION ---
// Uses Hardware SPI (Pins 11 & 13)
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("System Starting...");
  
  // 1. Initialize Sensor
  dht.begin();

  // 2. Initialize Display - FIX ATTEMPT
  // Most "White Screen" issues are solved by switching from BLACKTAB to GREENTAB.
  // If this doesn't work, comment this out and uncomment the next option.
  
  Serial.println("Initializing Display...");
  
  // OPTION 1: Green Tab (Try this first for white screens)
  tft.initR(INITR_GREENTAB);
  
  // OPTION 2: Black Tab (Standard)
  // tft.initR(INITR_BLACKTAB); 
  
  // OPTION 3: Red Tab
  // tft.initR(INITR_REDTAB);

  // OPTION 4: 1.44" Screen (Sometimes sold as 1.8")
  // tft.initR(INITR_144GREENTAB); 

  tft.fillScreen(ST7735_BLACK); 
  Serial.println("Display Initialized. Drawing Smiley...");

  // 3. Startup Sequence
  drawSmiley();
  delay(2000); 

  drawWelcome();
  delay(2000); 
}

void loop() {
  Serial.println("Reading Sensor...");
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Check if any reads failed
  if (isnan(h) || isnan(t)) {
    Serial.println("Sensor Error - Check DHT Wiring!");
    displayError();
    return;
  }
  
  Serial.print("Temp: "); Serial.print(t);
  Serial.print(" | Hum: "); Serial.println(h);

  // --- CYCLE 1: TEMPERATURE ---
  displayTemperature(t);
  delay(2000); 

  // --- CYCLE 2: HUMIDITY ---
  displayHumidity(h);
  delay(2000); 
}

// --- HELPER FUNCTIONS ---

void drawSmiley() {
  tft.fillScreen(ST7735_BLACK);
  int centerX = tft.width() / 2;
  int centerY = tft.height() / 2;
  
  // Face
  tft.fillCircle(centerX, centerY, 40, ST7735_YELLOW);
  // Eyes
  tft.fillCircle(centerX - 15, centerY - 10, 5, ST7735_BLACK);
  tft.fillCircle(centerX + 15, centerY - 10, 5, ST7735_BLACK);
  // Smile
  tft.fillRect(centerX - 20, centerY + 15, 40, 4, ST7735_BLACK);
  tft.fillRect(centerX - 20, centerY + 11, 5, 4, ST7735_BLACK);
  tft.fillRect(centerX + 15, centerY + 11, 5, 4, ST7735_BLACK);
}

void drawWelcome() {
  tft.fillScreen(ST7735_BLUE);
  tft.setCursor(15, 50);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(2);
  tft.println("Welcome");
  
  tft.setCursor(25, 80);
  tft.setTextSize(1);
  tft.println("Initializing...");
}

void displayTemperature(float temp) {
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(10, 20);
  tft.setTextColor(ST7735_RED);
  tft.setTextSize(2);
  tft.println("TEMP");
  
  tft.setCursor(10, 60);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(3);
  tft.print(temp, 1); 
  tft.setTextSize(2);
  tft.print(" C");
  tft.drawCircle(tft.getCursorX() - 25, 60, 3, ST7735_WHITE); 
}

void displayHumidity(float hum) {
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(10, 20);
  tft.setTextColor(ST7735_CYAN);
  tft.setTextSize(2);
  tft.println("HUMIDITY");
  
  tft.setCursor(10, 60);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(3);
  tft.print(hum, 0); 
  tft.setTextSize(2);
  tft.print(" %");
}

void displayError() {
  tft.fillScreen(ST7735_RED);
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(2);
  tft.println("Sensor Error!");
  delay(2000);
}