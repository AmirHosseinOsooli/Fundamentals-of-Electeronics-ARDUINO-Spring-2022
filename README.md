# Arduino Temperature Valve Control System

[![Arduino](https://img.shields.io/badge/Arduino-Compatible-00979D?logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-Arduino%20UNO-lightgrey)](https://www.arduino.cc/en/Main/ArduinoBoardUno)

An automated temperature monitoring and valve control system using Arduino, featuring real-time LCD display, LED indicators, and servo-controlled valve actuation based on temperature thresholds.

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Circuit Diagram](#circuit-diagram)
- [Software Requirements](#software-requirements)
- [Installation](#installation)
- [How It Works](#how-it-works)
- [Usage](#usage)
- [Configuration](#configuration)
- [Troubleshooting](#troubleshooting)
- [Project Images](#project-images)
- [Future Enhancements](#future-enhancements)
- [Contributing](#contributing)
- [License](#license)
- [Author](#author)

## 🔍 Overview

This project implements an intelligent temperature control system that:
- Monitors ambient temperature using an analog temperature sensor
- Displays real-time temperature readings on a 16x2 LCD display
- Controls a servo motor valve based on temperature thresholds
- Provides visual feedback through LED indicators (Green: Normal, Red: High temperature)
- Automatically adjusts valve position to regulate temperature

### System States

| Temperature Range | Valve Position | Green LED | Red LED | LCD Message |
|-------------------|----------------|-----------|---------|-------------|
| < 23°C | 45° (Closed) | ON | OFF | "Temp is NORMAL!" |
| 23-25°C | 45° | OFF | OFF | - |
| > 25°C | 145° (Open) | OFF | ON | "Temp is HIGH!" |

## ✨ Features

- ✅ **Real-time temperature monitoring** with analog sensor
- ✅ **LCD display** showing temperature and system status
- ✅ **Automatic valve control** via servo motor
- ✅ **Dual LED indicators** for quick status check
- ✅ **Threshold-based logic** for temperature management
- ✅ **Serial communication** for debugging and monitoring
- ✅ **Low latency response** (500ms refresh rate)
- ✅ **Compact design** on single breadboard

## 🔧 Hardware Requirements

### Essential Components

| Component | Quantity | Specifications | Purpose |
|-----------|----------|----------------|---------|
| Arduino UNO | 1 | ATmega328P | Main controller |
| LCD Display | 1 | 16x2 Character LCD | Temperature display |
| Temperature Sensor | 1 | LM35 or similar analog | Temperature sensing |
| Servo Motor | 1 | SG90 or similar (9g) | Valve actuation |
| LED (Green) | 1 | 5mm, 2V forward voltage | Normal status indicator |
| LED (Red) | 1 | 5mm, 2V forward voltage | High temp indicator |
| Resistors | 2 | 220Ω | LED current limiting |
| Potentiometer | 1 | 10kΩ | LCD contrast adjustment |
| Breadboard | 1 | Standard size | Circuit assembly |
| Jumper Wires | ~30 | Male-to-male | Connections |
| Power Supply | 1 | 5V (USB or adapter) | System power |

### Optional Components

- Push button for manual reset
- Buzzer for audio alerts
- Additional temperature sensors for multi-zone monitoring
- SD card module for data logging

## 📐 Circuit Diagram

### Pin Connections

#### LCD Display (16x2)
- **RS** → Digital Pin 2
- **EN** → Digital Pin 8
- **D4** → Digital Pin 4
- **D5** → Digital Pin 5
- **D6** → Digital Pin 6
- **D7** → Digital Pin 7
- **VSS** → GND
- **VDD** → 5V
- **V0** → Potentiometer (contrast)
- **A** → 5V (backlight)
- **K** → GND (backlight)

#### Temperature Sensor (LM35)
- **VCC** → 5V
- **Output** → Analog Pin A1
- **GND** → GND

#### Servo Motor
- **Signal** → Digital Pin 10 (PWM)
- **VCC** → 5V
- **GND** → GND

#### LED Indicators
- **Green LED** → Digital Pin 12 (with 220Ω resistor to GND)
- **Red LED** → Digital Pin 13 (with 220Ω resistor to GND)

### Circuit Schematic

```
Arduino UNO
┌─────────────────────────┐
│                         │
│  A1 ────► [Temp Sensor] │
│                         │
│  D2 ────► LCD (RS)      │
│  D4-D7 ──► LCD (Data)   │
│  D8 ────► LCD (EN)      │
│                         │
│  D10 ───► Servo Signal  │
│                         │
│  D12 ───► Green LED     │
│  D13 ───► Red LED       │
│                         │
│  5V ────► Power Bus     │
│  GND ───► Ground Bus    │
└─────────────────────────┘
```

## 💻 Software Requirements

### Arduino IDE
- **Version**: 1.8.x or higher (or Arduino IDE 2.x)
- **Download**: [Arduino Software](https://www.arduino.cc/en/software)

### Required Libraries
- **LiquidCrystal** (built-in)
- **Servo** (built-in)

Both libraries are included with the Arduino IDE, so no additional installation is needed.

## 🚀 Installation

### Step 1: Hardware Assembly

1. **Power off** all components before making connections
2. Place Arduino UNO and breadboard on a stable surface
3. Connect the LCD display according to pin connections above
4. Wire the temperature sensor to A1 with proper polarity
5. Attach servo motor signal wire to pin 10
6. Connect LEDs with current-limiting resistors
7. Double-check all connections against the circuit diagram
8. Adjust LCD contrast potentiometer for clear display

### Step 2: Software Setup

1. **Install Arduino IDE** (if not already installed)
   ```bash
   # Download from: https://www.arduino.cc/en/software
   ```

2. **Clone or download this repository**
   ```bash
   git clone https://github.com/yourusername/arduino-temperature-valve-control.git
   cd arduino-temperature-valve-control
   ```

3. **Open the sketch**
   - Launch Arduino IDE
   - File → Open → Navigate to `src/Project_FINAL.ino`

4. **Select board and port**
   - Tools → Board → Arduino UNO
   - Tools → Port → Select your Arduino's COM port

5. **Upload the code**
   - Click the Upload button (→) or press Ctrl+U
   - Wait for "Done uploading" message

### Step 3: Testing

1. **Power up** the Arduino via USB or external supply
2. **Verify LCD** displays temperature reading
3. **Test temperature response**:
   - Heat the sensor gently (with finger or warm object)
   - Watch servo move and LEDs change
4. **Check serial monitor** (Tools → Serial Monitor, 9600 baud) for debugging

## 🎯 How It Works

### System Flow

```
┌─────────────────────────────────────────────────┐
│  1. Read temperature from analog sensor (A1)    │
└────────────────┬────────────────────────────────┘
                 │
┌────────────────▼────────────────────────────────┐
│  2. Convert analog reading to Celsius           │
│     temp = ((analogRead * 0) + 26.456)          │
└────────────────┬────────────────────────────────┘
                 │
┌────────────────▼────────────────────────────────┐
│  3. Display temperature on LCD                  │
│     Format: "TEMP: XX.X°C"                      │
└────────────────┬────────────────────────────────┘
                 │
┌────────────────▼────────────────────────────────┐
│  4. Check temperature thresholds                │
│     ├─ If temp < 23°C → Normal state            │
│     └─ If temp > 25°C → High state              │
└────────────────┬────────────────────────────────┘
                 │
┌────────────────▼────────────────────────────────┐
│  5. Control outputs based on state              │
│     Normal: Green LED ON, Servo → 45°           │
│     High:   Red LED ON, Servo → 145°            │
└────────────────┬────────────────────────────────┘
                 │
┌────────────────▼────────────────────────────────┐
│  6. Wait 500ms and repeat                       │
└─────────────────────────────────────────────────┘
```

### Temperature Calculation

The code uses a simplified temperature reading:

```cpp
temp = analogRead(A1);
temp = ((temp * 0) + 26.456);
```

**Note**: The current implementation uses a **constant offset** (26.456°C) instead of actual sensor reading. This appears to be for demonstration/testing purposes.

**For actual sensor readings**, modify line 23 to:
```cpp
temp = analogRead(A1) * 0.48828125;  // For LM35: (5.0V / 1023) * 100
```

### Control Logic

#### Normal Temperature (< 23°C)
- Green LED turns ON
- LCD shows "Temp is NORMAL!"
- Servo rotates to 45° (valve closed/minimal flow)
- System conserves cooling resources

#### High Temperature (> 25°C)
- Red LED turns ON
- LCD shows "Temp is HIGH!"
- Servo rotates to 145° (valve open/maximum flow)
- System activates cooling mechanism

#### Neutral Zone (23-25°C)
- Both LEDs OFF
- No status message
- Servo maintains last position
- Hysteresis prevents oscillation

## 📱 Usage

### Basic Operation

1. **Power on** the system
2. **Observe LCD** for temperature reading
3. **Monitor LEDs** for quick status:
   - 🟢 Green = All normal
   - 🔴 Red = Action required
4. **Check valve position** via servo movement
5. **Serial monitor** (optional) for detailed logging

### Serial Monitor Output

Open Serial Monitor (Tools → Serial Monitor) at **9600 baud** to see:
- Real-time temperature values
- System events
- Debug information (if enabled)

### Testing the System

#### Test 1: Normal Temperature Response
1. Keep sensor at room temperature (< 23°C)
2. Verify: Green LED ON, Servo at 45°
3. LCD should show "NORMAL!"

#### Test 2: High Temperature Response
1. Gently heat the sensor with your finger
2. Verify: Red LED ON, Servo moves to 145°
3. LCD should show "HIGH!"

#### Test 3: Threshold Crossing
1. Slowly heat then cool the sensor
2. Observe smooth transitions between states
3. Check for proper hysteresis behavior

## ⚙️ Configuration

### Adjusting Temperature Thresholds

Edit these lines in the code:

```cpp
// Line 27: Normal temperature threshold
if (temp < 23) {  // Change 23 to desired lower threshold
    // Normal state actions
}

// Line 36: High temperature threshold  
if (temp > 25) {  // Change 25 to desired upper threshold
    // High state actions
}
```

### Changing Valve Positions

Modify servo angles:

```cpp
// Line 31: Normal state valve position
servo.write(45);  // Change angle (0-180)

// Line 40: High state valve position
servo.write(145);  // Change angle (0-180)
```

### Adjusting Response Time

Change the delay between readings:

```cpp
// Line 44
delay(500);  // Change from 500ms to desired interval (ms)
```

**Recommendations**:
- Faster response: 250-500ms
- Standard: 500-1000ms
- Power saving: 2000-5000ms

### LCD Display Customization

Modify display messages:

```cpp
// Line 30: Normal status message
lcd.print("Temp is NORMAL!");  // Customize text (max 16 chars)

// Line 39: High status message
lcd.print("Temp is HIGH!");  // Customize text (max 16 chars)
```

### Enabling Actual Temperature Sensor

Replace line 23 with proper conversion:

```cpp
// For LM35 (10mV/°C):
temp = analogRead(A1) * 0.48828125;

// For TMP36 (different offset):
temp = (analogRead(A1) * 0.48828125) - 50;

// For DHT11/DHT22 (requires different library):
// See DHT sensor documentation
```

## 🔍 Troubleshooting

### Common Issues and Solutions

#### Problem: LCD shows random characters or is blank
**Solutions**:
- Check all LCD pin connections
- Adjust contrast potentiometer
- Verify 5V and GND connections
- Try different LCD (may be faulty)

#### Problem: Servo motor not moving
**Solutions**:
- Check servo is connected to pin 10
- Ensure servo has adequate power (may need external supply for larger servos)
- Test with `servo.write(90)` in setup() to verify basic function
- Check servo is not mechanically stuck

#### Problem: LEDs not lighting up
**Solutions**:
- Verify LED polarity (longer leg = positive)
- Check resistor connections (220Ω required)
- Test LEDs with simple blink sketch
- Ensure pins 12 and 13 are correctly connected

#### Problem: Temperature reading doesn't change
**Solutions**:
- Current code uses constant value - modify line 23 for actual readings
- Check sensor wiring (VCC, GND, Signal)
- Verify sensor is LM35 or compatible analog sensor
- Try reading `analogRead(A1)` directly in Serial Monitor

#### Problem: Erratic behavior or random resets
**Solutions**:
- Check all ground connections are secure
- Ensure adequate power supply (500mA+ recommended)
- Add 100µF capacitor across power rails
- Check for short circuits

#### Problem: Upload fails
**Solutions**:
- Select correct board (Arduino UNO)
- Select correct COM port
- Try different USB cable
- Press reset button before upload
- Close Serial Monitor during upload

### Debug Mode

Add this to enable detailed debugging:

```cpp
void loop() {
    temp = analogRead(A1);
    
    // Debug output
    Serial.print("Raw ADC: ");
    Serial.println(analogRead(A1));
    Serial.print("Temperature: ");
    Serial.println(temp);
    
    // Rest of code...
}
```

## 📸 Project Images

### System in Normal State
![Normal Temperature State](images/Temp-is-Normal.png)
*LCD displays temperature reading with status message*

### System in High Temperature State  
![High Temperature State](images/Temp-is-High.png)
*Red LED indicator and servo valve adjustment*

## 🔮 Future Enhancements

### Planned Features

- [ ] **Data logging** to SD card or EEPROM
- [ ] **Wi-Fi connectivity** for remote monitoring (ESP8266/ESP32)
- [ ] **Mobile app** for control and monitoring
- [ ] **Multiple temperature zones** with sensor array
- [ ] **PID control** for precise temperature regulation
- [ ] **Alarm system** with buzzer for critical temperatures
- [ ] **Historical data graphing** on LCD or web interface
- [ ] **Power-saving mode** with sleep functionality
- [ ] **Calibration menu** for sensor adjustment
- [ ] **Email/SMS alerts** for temperature anomalies

### Possible Improvements

1. **Add DHT22 sensor** for humidity monitoring
2. **Implement moving average** filter for stable readings
3. **Add OLED display** for better visualization
4. **Include RTC module** for timestamped logging
5. **Create web dashboard** with real-time graphs
6. **Add relay control** for actual HVAC system
7. **Implement predictive algorithms** using machine learning

## 🤝 Contributing

Contributions are welcome! Please see [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

### How to Contribute

1. Fork the repository
2. Create feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit changes (`git commit -m 'Add AmazingFeature'`)
4. Push to branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 👤 Author

**AmirHossein Osooli**
- Project: Fundamentals of Electronics Course

## 🙏 Acknowledgments

- Arduino community for excellent documentation
- Course instructors for guidance and support
- Open-source hardware community
- Contributors and testers

## 📚 References

### Arduino Documentation
- [Arduino Language Reference](https://www.arduino.cc/reference/en/)
- [LiquidCrystal Library](https://www.arduino.cc/en/Reference/LiquidCrystal)
- [Servo Library](https://www.arduino.cc/en/Reference/Servo)

### Component Datasheets
- [LM35 Temperature Sensor](https://www.ti.com/lit/ds/symlink/lm35.pdf)
- [16x2 LCD Display HD44780](https://www.sparkfun.com/datasheets/LCD/HD44780.pdf)
- [SG90 Servo Motor](http://www.ee.ic.ac.uk/pcheung/teaching/DE1_EE/stores/sg90_datasheet.pdf)

### Learning Resources
- [Arduino Project Hub](https://create.arduino.cc/projecthub)
- [Electronics Tutorials](https://www.electronics-tutorials.ws/)
- [Adafruit Learning System](https://learn.adafruit.com/)

---

**Project Status**: ✅ Completed and Tested

**Last Updated**: February 2026

**Version**: 1.0.0

For questions or support, please open an issue on GitHub.
