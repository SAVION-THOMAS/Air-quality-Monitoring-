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

  // Warming up the MQ135 with animation
  Serial.println("Warming up MQ135 sensor...");
  unsigned long startTime = millis();
  unsigned long warmUpDuration = 30000; // 30 seconds

  while (millis() - startTime < warmUpDuration) {
    startupAnimation(); // Run the animation during warm-up
  }

  Serial.println("MQ135 sensor is ready.");
}
