#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define sensor A0
#define DHT11PIN 2
#define DHTTYPE DHT11
#define BUZZER_PIN 7

int gasLevel = 0;
String quality = "";
DHT dht(DHT11PIN, DHTTYPE);

void sendSensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 43);
  display.print("Temp  :");
  display.setCursor(80, 43);
  display.print(t, 1);
  display.print("C");
  display.setCursor(0, 56);
  display.print("RH    :");
  display.setCursor(80, 56);
  display.print(h, 1);
  display.print("%");
}

void air_sensor() {
  gasLevel = analogRead(sensor);

  if (gasLevel < 151) {
    quality = "  GOOD!";
    digitalWrite(BUZZER_PIN, LOW);
  } else if (gasLevel > 151 && gasLevel < 200) {
    quality = "  Poor!";
    digitalWrite(BUZZER_PIN, LOW);
  } else if (gasLevel > 200 && gasLevel < 300) {
    quality = "Very bad!";
    digitalWrite(BUZZER_PIN, LOW);
  } else if (gasLevel > 300 && gasLevel < 500) {
    quality = "Toxic!";
    digitalWrite(BUZZER_PIN, HIGH);
    delay(500);
    digitalWrite(BUZZER_PIN, LOW);
    delay(500);
  } else {
    quality = " Toxic";
    digitalWrite(BUZZER_PIN, HIGH);
    delay(500);
    digitalWrite(BUZZER_PIN, LOW);
    delay(500);
  }

  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(1, 5);
  display.print("Air Quality:");
  display.setTextSize(1);
  display.setCursor(5, 23);
  display.print(gasLevel);
  display.setCursor(20, 23);
  display.print(quality);
}

void startupAnimation() {
  for (int r = 0; r < 30; r++) {
    display.clearDisplay();
    display.drawCircle(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, r, WHITE);
    display.drawCircle(3 * SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, r, WHITE);
    display.display();
    delay(50);
  }
  
  for (int r = 30; r > 0; r--) {
    display.clearDisplay();
    display.drawCircle(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, r, WHITE);
    display.drawCircle(3 * SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, r, WHITE);
    display.display();
    delay(50);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  dht.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
  }
  
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);

  int textWidth1 = (SCREEN_WIDTH - (11 * 6)) / 2;
  display.setCursor(textWidth1, 15);
  display.print("Air Quality");

  int textWidth2 = (SCREEN_WIDTH - (11 * 6)) / 2;
  display.setCursor(textWidth2, 35);
  display.print("Monitoring");
  
  display.display();
  delay(2000);
  
  display.clearDisplay();
  int textWidth3 = (SCREEN_WIDTH - (13 * 6)) / 2;
  display.setCursor(textWidth3, 15);
  display.print("Designed By:");

  int textWidth4 = (SCREEN_WIDTH - (18 * 6)) / 2;
  display.setCursor(textWidth4, 35);
  display.print("Savion Thomas Babu");
  display.display();
  delay(3000);

  startupAnimation();
}

void loop() {
  display.clearDisplay();
  air_sensor();
  sendSensor();
  display.display();
  delay(500);
}
