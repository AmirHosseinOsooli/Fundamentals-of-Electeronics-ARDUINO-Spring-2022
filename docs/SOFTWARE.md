# Software Documentation

## Table of Contents
- [Code Overview](#code-overview)
- [Library Dependencies](#library-dependencies)
- [Code Structure](#code-structure)
- [Function Reference](#function-reference)
- [Configuration Variables](#configuration-variables)
- [Algorithm Explanation](#algorithm-explanation)
- [Modification Guide](#modification-guide)
- [Advanced Features](#advanced-features)
- [Debugging](#debugging)

## Code Overview

### Project Structure

```
src/
└── Project_FINAL.ino          Main Arduino sketch
```

### Code Statistics
- Total Lines: 47
- Libraries Used: 2
- Functions: 2 (setup, loop)
- Global Variables: 3
- Pin Assignments: 9

## Library Dependencies

### 1. LiquidCrystal Library

**Purpose**: Control 16x2 LCD display

**Installation**: Built-in with Arduino IDE

**Documentation**: [Arduino Reference](https://www.arduino.cc/en/Reference/LiquidCrystal)

**Key Functions Used**:
- `LiquidCrystal(rs, en, d4, d5, d6, d7)` - Constructor
- `begin(cols, rows)` - Initialize display
- `print(data)` - Print text/numbers
- `println(data)` - Print with newline
- `setCursor(col, row)` - Position cursor
- `clear()` - Clear display

**Example**:
```cpp
#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 8, 4, 5, 6, 7);

void setup() {
    lcd.begin(16, 2);  // 16 columns, 2 rows
    lcd.print("Hello World!");
}
```

### 2. Servo Library

**Purpose**: Control servo motor position

**Installation**: Built-in with Arduino IDE

**Documentation**: [Arduino Reference](https://www.arduino.cc/en/Reference/Servo)

**Key Functions Used**:
- `attach(pin)` - Assign servo to pin
- `write(angle)` - Set servo position (0-180°)
- `read()` - Get current position
- `detach()` - Release servo pin

**Example**:
```cpp
#include <Servo.h>
Servo myServo;

void setup() {
    myServo.attach(10);
    myServo.write(90);  // Center position
}
```

## Code Structure

### Complete Annotated Code

```cpp
// Include required libraries
#include <LiquidCrystal.h>  // For LCD display control
#include <Servo.h>           // For servo motor control

// Create servo object
Servo servo;

// Pin definitions using #define (compile-time constants)
#define R_LED 13  // Red LED for high temperature alert
#define G_LED 12  // Green LED for normal temperature

// LCD pin configuration (RS, EN, D4, D5, D6, D7)
const int rs = 2, en = 8, d4 = 4, d5 = 5, d6 = 6, d7 = 7;

// Initialize LCD with pin assignments
LiquidCrystal lcd(2, 8, 4, 5, 6, 7);

// Global variable for temperature storage
float temp;

void setup() {
    // Initialize LCD display (16 columns x 2 rows)
    lcd.begin(16, 2);
    
    // Configure LED pins as outputs
    pinMode(12, OUTPUT);  // Green LED
    pinMode(13, OUTPUT);  // Red LED
    
    // Attach servo to pin 10 (PWM capable)
    servo.attach(10);
    
    // Initialize serial communication at 9600 baud
    Serial.begin(9600);
    
    // Set analog reference to internal 1.1V
    // (Note: Not actually used with current temp calculation)
    analogReference(INTERNAL);
    
    // Short delay for stabilization
    delay(100);
    
    // Clear LCD screen
    lcd.clear();
}

void loop() {
    // Read temperature sensor from analog pin A1
    temp = analogRead(A1);
    
    // Convert analog reading to temperature
    // Current formula: constant offset (demonstration mode)
    // For actual LM35: temp = temp * 0.48828125
    temp = ((temp * 0) + 26.456);
    
    // Display temperature on LCD (Line 1)
    lcd.print("TEMP: ");
    lcd.print(temp);
    lcd.println("*C    ");  // Spaces to clear previous digits
    
    // Check for NORMAL temperature condition (< 23°C)
    if (temp < 23) {
        digitalWrite(G_LED, HIGH);    // Turn on green LED
        lcd.setCursor(0, 2);          // Move to line 2
        lcd.print("Temp is NORMAL!");
        servo.write(45);              // Close valve (45°)
    }
    else {
        digitalWrite(G_LED, LOW);     // Turn off green LED
    }
    
    // Check for HIGH temperature condition (> 25°C)
    if (temp > 25) {
        digitalWrite(R_LED, HIGH);    // Turn on red LED
        lcd.setCursor(0, 2);          // Move to line 2
        lcd.print("Temp is HIGH!");
        servo.write(145);             // Open valve (145°)
    }
    else {
        digitalWrite(R_LED, LOW);     // Turn off red LED
    }
    
    // Wait 500ms before next reading
    delay(500);
    
    // Clear LCD for next update
    lcd.clear();
}
```

## Function Reference

### setup()

**Purpose**: Initialize hardware and configure system settings

**Execution**: Runs once at power-on or reset

**Operations**:
1. Initialize LCD display
2. Configure I/O pins
3. Attach servo motor
4. Start serial communication
5. Set analog reference voltage
6. Perform startup delay
7. Clear display

**Duration**: ~100ms

**Code**:
```cpp
void setup() {
    lcd.begin(16, 2);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
    servo.attach(10);
    Serial.begin(9600);
    analogReference(INTERNAL);
    delay(100);
    lcd.clear();
}
```

### loop()

**Purpose**: Main program execution cycle

**Execution**: Runs continuously after setup()

**Cycle Time**: ~500ms per iteration

**Flow**:
```
Read Sensor → Convert Temp → Display → Check Thresholds → 
Control Outputs → Delay → Clear Display → Repeat
```

**Operations**:
1. Read temperature sensor (A1)
2. Convert ADC value to temperature
3. Update LCD display
4. Evaluate normal threshold (< 23°C)
5. Evaluate high threshold (> 25°C)
6. Control LEDs and servo
7. Wait for next cycle
8. Clear display

## Configuration Variables

### Pin Definitions

```cpp
#define R_LED 13        // Red LED pin (digital output)
#define G_LED 12        // Green LED pin (digital output)
const int rs = 2;       // LCD Register Select
const int en = 8;       // LCD Enable
const int d4 = 4;       // LCD Data 4
const int d5 = 5;       // LCD Data 5
const int d6 = 6;       // LCD Data 6
const int d7 = 7;       // LCD Data 7
// Servo pin: 10 (PWM)
// Temp sensor: A1 (analog input)
```

### Temperature Thresholds

```cpp
if (temp < 23)  // Normal threshold (line 27)
if (temp > 25)  // High threshold (line 36)
```

**Hysteresis Zone**: 23°C - 25°C
- Prevents rapid oscillation
- Provides stable operation
- Both LEDs OFF in this range

### Servo Positions

```cpp
servo.write(45);   // Normal state (closed valve)
servo.write(145);  // High state (open valve)
```

**Position Mapping**:
- 45° = Minimum flow / Closed
- 145° = Maximum flow / Open
- Range: 100° of travel

### Timing Configuration

```cpp
delay(500);  // Refresh rate: 500ms (2 Hz)
```

**Adjustable Values**:
- Faster: 250ms (4 Hz)
- Standard: 500ms (2 Hz)
- Slower: 1000ms (1 Hz)

## Algorithm Explanation

### Temperature Reading Process

```
┌─────────────────────────────────┐
│  1. Read Analog Input (A1)      │
│     Raw value: 0-1023 (10-bit)  │
└───────────────┬─────────────────┘
                │
┌───────────────▼─────────────────┐
│  2. Convert to Voltage          │
│     V = (ADC / 1023) × Vref     │
│     Vref = 5V (or 1.1V internal)│
└───────────────┬─────────────────┘
                │
┌───────────────▼─────────────────┐
│  3. Convert to Temperature      │
│     Current: temp = 26.456°C    │
│     Actual: temp = V × 100      │
└───────────────┬─────────────────┘
                │
┌───────────────▼─────────────────┐
│  4. Store in 'temp' variable    │
└─────────────────────────────────┘
```

### Control Logic State Machine

```
        temp < 23°C              23°C ≤ temp ≤ 25°C           temp > 25°C
┌────────────────────┐      ┌────────────────────┐      ┌────────────────────┐
│   NORMAL STATE     │      │   NEUTRAL ZONE     │      │    HIGH STATE      │
├────────────────────┤      ├────────────────────┤      ├────────────────────┤
│ Green LED:  ON     │      │ Green LED:  OFF    │      │ Green LED:  OFF    │
│ Red LED:    OFF    │      │ Red LED:    OFF    │      │ Red LED:    ON     │
│ Servo:      45°    │      │ Servo:      Last   │      │ Servo:      145°   │
│ LCD Line 2: NORMAL!│      │ LCD Line 2: [None] │      │ LCD Line 2: HIGH!  │
└────────────────────┘      └────────────────────┘      └────────────────────┘
         ▲                           │                           │
         │                           │                           │
         └───── Cooling ─────────────┴──────── Heating ─────────┘
```

### Display Update Sequence

```
Every 500ms:
1. Clear display
2. Print "TEMP: XX.X*C" on line 1
3. Check conditions:
   - If temp < 23: Print "Temp is NORMAL!" on line 2
   - If temp > 25: Print "Temp is HIGH!" on line 2
   - Else: Line 2 blank
4. Wait 500ms
5. Repeat
```

## Modification Guide

### 1. Change Temperature Thresholds

**Problem**: Need different trigger temperatures

**Solution**:
```cpp
// Original
if (temp < 23) { /* normal */ }
if (temp > 25) { /* high */ }

// Modified for 20°C/30°C thresholds
if (temp < 20) { /* normal */ }
if (temp > 30) { /* high */ }
```

### 2. Adjust Servo Positions

**Problem**: Valve requires different angles

**Solution**:
```cpp
// Original
servo.write(45);   // Normal
servo.write(145);  // High

// Modified for full range
servo.write(0);    // Fully closed
servo.write(180);  // Fully open
```

### 3. Enable Real Temperature Sensor

**Problem**: Currently using constant value

**Solution**:
```cpp
// Original (line 23)
temp = ((temp * 0) + 26.456);

// For LM35 sensor
temp = analogRead(A1) * 0.48828125;
// Calculation: (5.0V / 1023) * 100 = 0.48828125

// Alternative with voltage reference
float voltage = analogRead(A1) * (5.0 / 1023.0);
temp = voltage * 100;  // LM35: 10mV per degree
```

### 4. Add Temperature Smoothing

**Problem**: Noisy sensor readings

**Solution**:
```cpp
// Add at top of file
#define SAMPLES 10
float readings[SAMPLES];
int readIndex = 0;

// In loop(), replace temp reading with:
readings[readIndex] = analogRead(A1) * 0.48828125;
readIndex = (readIndex + 1) % SAMPLES;

temp = 0;
for(int i = 0; i < SAMPLES; i++) {
    temp += readings[i];
}
temp = temp / SAMPLES;
```

### 5. Add Serial Debugging

**Problem**: Can't see what's happening internally

**Solution**:
```cpp
// Add to loop() after temp calculation
Serial.print("Raw ADC: ");
Serial.print(analogRead(A1));
Serial.print(" | Temperature: ");
Serial.print(temp);
Serial.print("°C | Servo: ");
Serial.println(servo.read());
```

### 6. Implement Hysteresis Control

**Problem**: Rapid switching at threshold

**Solution**:
```cpp
// Add global variable
bool systemActive = false;

// Replace threshold checks
if (temp < 22 || (systemActive && temp < 23)) {
    // Turn on normal state
    systemActive = false;
}
if (temp > 26 || (systemActive && temp > 25)) {
    // Turn on high state
    systemActive = true;
}
```

### 7. Add LCD Degree Symbol

**Problem**: Showing "*C" instead of "°C"

**Solution**:
```cpp
// Create custom character in setup()
byte degree[8] = {
    0b00110,
    0b01001,
    0b01001,
    0b00110,
    0b00000,
    0b00000,
    0b00000,
    0b00000
};
lcd.createChar(0, degree);

// In loop(), replace print
lcd.print("TEMP: ");
lcd.print(temp);
lcd.write(byte(0));  // Print degree symbol
lcd.print("C    ");
```

### 8. Add Warning Buzzer

**Problem**: Need audio alert

**Solution**:
```cpp
// Add pin definition
#define BUZZER 11

// In setup()
pinMode(BUZZER, OUTPUT);

// In loop(), when temp > 25
if (temp > 25) {
    digitalWrite(R_LED, HIGH);
    tone(BUZZER, 1000, 200);  // 1kHz beep for 200ms
    // ... rest of code
}
```

## Advanced Features

### 1. Data Logging to EEPROM

```cpp
#include <EEPROM.h>

struct LogEntry {
    float temperature;
    unsigned long timestamp;
};

void logTemperature() {
    LogEntry entry;
    entry.temperature = temp;
    entry.timestamp = millis();
    
    int addr = (logIndex % 100) * sizeof(LogEntry);
    EEPROM.put(addr, entry);
    logIndex++;
}
```

### 2. Multi-Zone Control

```cpp
// Multiple sensors
#define TEMP_SENSOR_1 A1
#define TEMP_SENSOR_2 A2
#define TEMP_SENSOR_3 A3

float temps[3];
Servo servos[3];

void readAllSensors() {
    temps[0] = analogRead(TEMP_SENSOR_1) * 0.48828125;
    temps[1] = analogRead(TEMP_SENSOR_2) * 0.48828125;
    temps[2] = analogRead(TEMP_SENSOR_3) * 0.48828125;
}
```

### 3. PID Control

```cpp
// PID parameters
float kp = 2.0, ki = 0.5, kd = 1.0;
float setpoint = 24.0;
float error, lastError = 0, integral = 0;

void pidControl() {
    error = setpoint - temp;
    integral += error;
    float derivative = error - lastError;
    
    float output = kp * error + ki * integral + kd * derivative;
    
    int servoAngle = constrain(90 + output, 0, 180);
    servo.write(servoAngle);
    
    lastError = error;
}
```

### 4. WiFi Connectivity (with ESP8266)

```cpp
#include <ESP8266WiFi.h>

const char* ssid = "YourSSID";
const char* password = "YourPassword";

WiFiServer server(80);

void sendWebPage() {
    WiFiClient client = server.available();
    if (client) {
        String page = "<html><body>";
        page += "<h1>Temperature: " + String(temp) + "&deg;C</h1>";
        page += "</body></html>";
        client.print(page);
    }
}
```

## Debugging

### Debug Mode Implementation

```cpp
// Add at top
#define DEBUG true

// Create debug print function
void debugPrint(String message, float value) {
    if (DEBUG) {
        Serial.print(message);
        Serial.println(value);
    }
}

// Use in loop()
debugPrint("Temperature: ", temp);
debugPrint("Green LED State: ", digitalRead(G_LED));
debugPrint("Servo Position: ", servo.read());
```

### Common Issues and Fixes

#### Issue 1: Temperature always 26.456°C

**Cause**: Using constant in formula (line 23)

**Fix**:
```cpp
// Change from:
temp = ((temp * 0) + 26.456);

// To:
temp = analogRead(A1) * 0.48828125;
```

#### Issue 2: Servo jittering

**Cause**: Insufficient power or noisy signal

**Fix**:
```cpp
// Add in loop() before servo.write()
static int lastServoPos = 90;
int newPos;

if (temp < 23) newPos = 45;
if (temp > 25) newPos = 145;

// Only move if position changed
if (newPos != lastServoPos) {
    servo.write(newPos);
    lastServoPos = newPos;
}
```

#### Issue 3: LCD flickers

**Cause**: Clearing too frequently

**Fix**:
```cpp
// Only clear when needed, not every loop
// Remove lcd.clear() from end of loop()
// Clear only specific areas or use spaces to overwrite
```

## Performance Optimization

### Memory Usage

```cpp
// Current memory usage (approximate):
// Global variables: 24 bytes
// LCD library: ~100 bytes
// Servo library: ~50 bytes
// Total static: ~175 bytes out of 2048 bytes (8.5%)
```

### Code Size

```cpp
// Compiled size: ~5KB out of 32KB flash (15.6%)
// Plenty of room for enhancements
```

### Optimization Tips

1. **Use const for constants**
```cpp
const float TEMP_SCALE = 0.48828125;
const int NORMAL_THRESHOLD = 23;
const int HIGH_THRESHOLD = 25;
```

2. **Minimize LCD updates**
```cpp
// Update only when temperature changes significantly
if (abs(temp - lastTemp) > 0.5) {
    // Update display
    lastTemp = temp;
}
```

3. **Use F() macro for strings**
```cpp
lcd.print(F("TEMP: "));  // Stores string in flash, not RAM
```

## Testing Procedures

### Unit Tests

```cpp
// Test each component separately
void testLCD() {
    lcd.clear();
    lcd.print("LCD Test OK");
    delay(2000);
}

void testServo() {
    servo.write(0);
    delay(1000);
    servo.write(180);
    delay(1000);
    servo.write(90);
}

void testLEDs() {
    digitalWrite(G_LED, HIGH);
    delay(500);
    digitalWrite(G_LED, LOW);
    digitalWrite(R_LED, HIGH);
    delay(500);
    digitalWrite(R_LED, LOW);
}
```

### Integration Tests

1. Power on system
2. Verify LCD shows temperature
3. Test normal state (< 23°C)
4. Test high state (> 25°C)
5. Verify servo movement
6. Check LED indicators
7. Monitor for 10+ minutes

## Resources

### Official Documentation
- [Arduino Language Reference](https://www.arduino.cc/reference/en/)
- [LiquidCrystal Library](https://www.arduino.cc/en/Reference/LiquidCrystal)
- [Servo Library](https://www.arduino.cc/en/Reference/Servo)

### Tutorials
- [Arduino Getting Started](https://www.arduino.cc/en/Guide)
- [LCD Tutorial](https://www.arduino.cc/en/Tutorial/LibraryExamples/HelloWorld)
- [Servo Tutorial](https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep)

---

**Document Version**: 1.0
**Last Updated**: February 2026
**Code Version**: Final
