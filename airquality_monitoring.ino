#include <SPI.h> 
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// OLED display dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// OLED reset pin
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// DHT sensor setup
#define DHT11PIN 2
DHT dht(DHT11PIN, DHT11); // Initialize DHT sensor

// Gas sensor setup
#define GAS_SENSOR A0

// Variables
int gasLevel = 0;
String airQuality = "";

void displaySensorReadings(float temperature, float humidity) {
  display.setTextColor(WHITE);
  display.setTextSize(1);

  display.setCursor(0, 43);
  display.println("Temp :");
  display.setCursor(80, 43);
  display.print(temperature);
  display.print(" C");

  display.setCursor(0, 56);
  display.println("RH   :");
  display.setCursor(80, 56);
  display.print(humidity);
  display.println(" %");
}

void readAirSensor() {
  gasLevel = analogRead(GAS_SENSOR);

  if (gasLevel < 151) {
    airQuality = "GOOD!";
  } else if (gasLevel < 200) {
    airQuality = "Poor!";
  } else if (gasLevel < 300) {
    airQuality = "Very bad!";
  } else if (gasLevel < 500) {
    airQuality = "Toxic!";
  } else {
    airQuality = "TOXIC!";
  }

  display.setTextColor(WHITE);
  display.setTextSize(1);

  display.setCursor(1, 5);
  display.println("Air Quality:");
  display.setCursor(4, 23);
  display.print("Level: ");
  display.println(gasLevel);
  display.setCursor(4, 33);
  display.println(airQuality);
}

void drawZoomInOutCircle(int centerX, int centerY) {
  // Zoom in
  for (int r = 0; r < 30; r++) { // Increase the radius from 0 to 30
    display.clearDisplay();
    display.drawCircle(centerX, centerY, r, WHITE);
    display.display();
    delay(50); // Increased delay to slow down the animation
  }
  
  // Zoom out
  for (int r = 30; r >= 0; r--) { // Decrease the radius from 30 to 0
    display.clearDisplay();
    display.drawCircle(centerX, centerY, r, WHITE);
    display.display();
    delay(50); // Increased delay to slow down the animation
  }
}

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(GAS_SENSOR, INPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(WHITE);

  // Splash screen
  display.setTextSize(2);
  display.setCursor(46, 15);
  display.println("Air");
  display.setTextSize(1);
  display.setCursor(20, 35);
  display.println("Quality monitor");
  display.display();
  delay(1500);

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(20, 20);
  display.println("Designed By");
  display.setCursor(20, 40);
  display.println("Savion Thomas");
  display.display();
  delay(1500);

  // Call the zoom-in and zoom-out circle animation
  drawZoomInOutCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

  display.clearDisplay();
}

void loop() {
  display.clearDisplay();

  // Read DHT11 sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    display.setCursor(0, 43);
    display.println("DHT Error!");
  } else {
    displaySensorReadings(temperature, humidity);
  }

  // Read and display air quality
  readAirSensor();

  // Update display
  display.display();

  delay(2000); // Delay to allow readings to stabilize
}
