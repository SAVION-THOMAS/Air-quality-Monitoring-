# Air Quality Monitoring System

This project monitors air quality using a gas sensor and a DHT11 temperature and humidity sensor. The system displays real-time temperature, humidity, and air quality levels on an OLED display. If the air quality index (AQI) exceeds a dangerous threshold, a buzzer will activate to alert the user.

## Components Required

1. **Arduino Uno**
2. **Adafruit SSD1306 OLED Display (128x64)**
3. **DHT11 Temperature and Humidity Sensor**
4. **Gas Sensor (Analog output)**
5. **Buzzer**
6. **Connecting Wires**
7. **Breadboard**

## Pin Connections

### OLED Display
| OLED Pin | Arduino Pin |
|----------|-------------|
| VCC      | 5V          |
| GND      | GND         |
| SCL      | A5          |
| SDA      | A4          |
| RESET    | Pin 4       |

### DHT11 Sensor
| DHT11 Pin | Arduino Pin |
|-----------|-------------|
| VCC       | 5V          |
| GND       | GND         |
| DATA      | Pin 2       |

### Gas Sensor
| Gas Sensor Pin | Arduino Pin |
|----------------|-------------|
| VCC            | 5V          |
| GND            | GND         |
| A0             | A0          |

### Buzzer
| Buzzer Pin | Arduino Pin |
|------------|-------------|
| +          | Pin 7       |
| -          | GND         |

## Features

1. **Startup Animation**:
   - Two circles animate on the OLED display during startup.

2. **Real-time Monitoring**:
   - Displays air quality levels, temperature, and humidity on the OLED screen.
   - Updates every 500 milliseconds.

3. **Alert System**:
   - Activates a buzzer when the gas level exceeds a dangerous threshold (AQI > 300).

## How to Use

1. Connect all components according to the pin connections provided.
2. Upload the code to the Arduino Uno using the Arduino IDE.
3. Power the Arduino Uno.
4. Observe the OLED display for real-time updates on air quality, temperature, and humidity.
5. Listen for the buzzer if the air quality exceeds the dangerous threshold.

## Notes

- Ensure that the OLED display address is correctly set to `0x3C` in the code.
- The DHT11 sensor requires initialization in the `setup()` function.
- The gas sensor should be calibrated for accurate readings.
- Use a 5V power supply for the Arduino Uno to ensure proper operation.

## Troubleshooting

- **OLED Display Not Working**:
  - Verify the I2C connections (SCL and SDA).
  - Check the OLED address in the code.

- **DHT11 Sensor Issues**:
  - Ensure the DATA pin is connected to the correct Arduino pin.
  - Check for a "Failed to read from DHT sensor" message on the Serial Monitor.

- **No Sound from Buzzer**:
  - Verify the buzzer connections.
  - Check if the AQI threshold is being reached.

If you think the code can be improved or that if something is wrong in the code, Feel free to contact me:D.
My email is provided in my github profile.

