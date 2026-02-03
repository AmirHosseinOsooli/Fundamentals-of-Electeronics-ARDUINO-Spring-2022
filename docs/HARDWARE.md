# Hardware Documentation

## Bill of Materials (BOM)

### Complete Parts List with Pricing Estimate

| # | Component | Specification | Quantity | Est. Price (USD) | Notes |
|---|-----------|---------------|----------|------------------|-------|
| 1 | Arduino UNO R3 | ATmega328P, 16MHz | 1 | $25.00 | Original or compatible |
| 2 | LCD Display | 16x2 Character, HD44780 | 1 | $5.00 | Blue or green backlight |
| 3 | Temperature Sensor | LM35DZ or TMP36 | 1 | $2.00 | Analog output |
| 4 | Servo Motor | SG90, 9g micro servo | 1 | $3.00 | 180° rotation |
| 5 | LED - Green | 5mm, 2-2.2V, 20mA | 1 | $0.10 | Standard diffused |
| 6 | LED - Red | 5mm, 1.8-2V, 20mA | 1 | $0.10 | Standard diffused |
| 7 | Resistor 220Ω | 1/4W, ±5% | 2 | $0.10 | For LED current limiting |
| 8 | Potentiometer | 10kΩ, linear taper | 1 | $0.50 | LCD contrast adjust |
| 9 | Breadboard | 830 points, standard | 1 | $3.00 | Solderless |
| 10 | Jumper Wires | Male-to-male, 20cm | 30 | $3.00 | Various colors |
| 11 | USB Cable | Type A to Type B | 1 | $2.00 | For programming/power |
| 12 | Power Supply | 5V 2A adapter (optional) | 1 | $5.00 | If not using USB |
| | | | **Total** | **~$48.80** | Prices vary by supplier |

### Where to Buy

- **Arduino & Components**: Arduino.cc, Adafruit, SparkFun, DigiKey, Mouser
- **Budget Options**: AliExpress, eBay, Amazon (compatible boards)
- **Local**: Electronics hobby stores, maker spaces

## Detailed Component Specifications

### 1. Arduino UNO R3

**Technical Specifications:**
- Microcontroller: ATmega328P
- Operating Voltage: 5V
- Input Voltage: 7-12V (recommended)
- Digital I/O Pins: 14 (6 PWM)
- Analog Input Pins: 6
- DC Current per I/O: 20mA
- Flash Memory: 32KB
- SRAM: 2KB
- EEPROM: 1KB
- Clock Speed: 16MHz

**Used Pins in This Project:**
- D2, D4-D8: LCD control
- D10: Servo PWM
- D12, D13: LED outputs
- A1: Temperature sensor input

### 2. 16x2 LCD Display

**Specifications:**
- Display Type: Character LCD
- Controller: HD44780 or compatible
- Characters: 16 columns × 2 rows
- Character Size: 5×8 dots
- Supply Voltage: 5V
- Operating Current: 1-3mA (without backlight)
- Backlight: 20-60mA depending on color
- Interface: 4-bit or 8-bit parallel
- Viewing Angle: 120°
- Contrast: Adjustable via potentiometer

**Pinout:**
```
Pin  Function    Connection
VSS  Ground      GND
VDD  Power       5V
V0   Contrast    Potentiometer wiper
RS   Register    D2
RW   Read/Write  GND (write only)
E    Enable      D8
D0-3 Data        Not used (4-bit mode)
D4   Data        D4
D5   Data        D5
D6   Data        D6
D7   Data        D7
A    Backlight+  5V (via resistor)
K    Backlight-  GND
```

### 3. Temperature Sensor (LM35)

**Specifications:**
- Operating Range: -55°C to +150°C
- Accuracy: ±0.5°C (at 25°C)
- Output: 10mV per °C
- Operating Voltage: 4V to 30V
- Current Draw: < 60µA
- Self-heating: < 0.1°C
- Output Impedance: 0.2Ω
- Nonlinearity: ±0.25°C (typical)

**Calibration:**
- 0°C = 0mV
- 25°C = 250mV
- 100°C = 1000mV

**Pinout (TO-92 Package):**
```
   ___
  /   \
 |  1  |  1: +Vs (4-30V)
 |  2  |  2: Vout (analog)
 |  3  |  3: GND
  \___/
```

**Conversion Formula:**
```
Temperature (°C) = Vout / 0.01V
For Arduino: temp = analogRead(pin) * (5.0/1023.0) * 100
```

### 4. Servo Motor (SG90)

**Specifications:**
- Type: Micro servo
- Weight: 9g
- Dimensions: 22.2 × 11.8 × 31mm
- Operating Voltage: 4.8-6V
- Operating Current: 100-250mA
- Stall Current: 650mA (at 6V)
- Torque: 1.8kg·cm (at 4.8V)
- Speed: 0.1s/60° (at 4.8V)
- Rotation: ~180° (0-180 command range)
- Control Signal: PWM, 50Hz
- Pulse Width: 1-2ms (1ms=0°, 1.5ms=90°, 2ms=180°)
- Dead Band: 10µs
- Temperature Range: 0°C to 55°C

**Wire Colors:**
- Brown/Black: Ground (GND)
- Red: Power (4.8-6V)
- Orange/Yellow: Control Signal (PWM)

**Position Control:**
```
Pulse Width  Position
1.0ms        0° (minimum)
1.5ms        90° (center)
2.0ms        180° (maximum)
```

### 5. LEDs (Light Emitting Diodes)

**Green LED:**
- Color: Green (525nm wavelength)
- Forward Voltage: 2.0-2.2V
- Forward Current: 20mA (max 30mA)
- Brightness: 1000-3000mcd
- Viewing Angle: 30-60°

**Red LED:**
- Color: Red (625nm wavelength)
- Forward Voltage: 1.8-2.0V
- Forward Current: 20mA (max 30mA)
- Brightness: 1000-3000mcd
- Viewing Angle: 30-60°

**Current Limiting Resistor Calculation:**
```
R = (Vs - Vf) / If
Where:
  Vs = Supply voltage (5V)
  Vf = Forward voltage (2V avg)
  If = Forward current (0.02A)

R = (5 - 2) / 0.02 = 150Ω
Using 220Ω provides safety margin
```

## Circuit Assembly Instructions

### Step-by-Step Assembly

#### Step 1: Prepare the Breadboard
1. Place breadboard on stable, non-conductive surface
2. Identify power rails (+ and - marked sides)
3. Connect Arduino 5V to breadboard + rail
4. Connect Arduino GND to breadboard - rail

#### Step 2: Install LCD Display
1. Insert LCD carefully into breadboard
2. Wire VSS to GND
3. Wire VDD to 5V
4. Connect potentiometer for V0 (contrast)
5. Wire RS to Arduino D2
6. Connect RW to GND
7. Wire E to Arduino D8
8. Connect D4-D7 to Arduino D4-D7
9. Wire backlight (A to 5V, K to GND)

#### Step 3: Connect Temperature Sensor
1. Insert LM35 with correct orientation
2. Pin 1 (+Vs) to 5V rail
3. Pin 2 (Vout) to Arduino A1
4. Pin 3 (GND) to GND rail

#### Step 4: Attach Servo Motor
1. Place servo near breadboard
2. Brown/Black wire to GND
3. Red wire to 5V
4. Orange/Yellow wire to Arduino D10

#### Step 5: Install LED Indicators
1. Insert Green LED (long leg to resistor)
2. Connect 220Ω resistor from LED to D12
3. Connect LED short leg to GND
4. Insert Red LED (long leg to resistor)
5. Connect 220Ω resistor from LED to D13
6. Connect LED short leg to GND

#### Step 6: Final Checks
- Verify all power connections
- Check all GND connections
- Confirm no short circuits
- Double-check pin numbers
- Ensure polarity of components

### Wiring Diagram Reference

```
                    Arduino UNO
        ┌──────────────────────────┐
        │                          │
    5V ─┤ 5V                   A1 ├─ Temperature Sensor
   GND ─┤ GND                     │
        │                      D2 ├─ LCD RS
        │                      D4 ├─ LCD D4
        │                      D5 ├─ LCD D5
        │                      D6 ├─ LCD D6
        │                      D7 ├─ LCD D7
        │                      D8 ├─ LCD EN
        │                     D10 ├─ Servo Signal
        │                     D12 ├─ Green LED (+ resistor)
        │                     D13 ├─ Red LED (+ resistor)
        │                          │
        └──────────────────────────┘
```

## Power Considerations

### Power Budget Analysis

| Component | Voltage | Current | Power |
|-----------|---------|---------|-------|
| Arduino UNO | 5V | 50mA | 250mW |
| LCD Display | 5V | 3mA + 30mA (backlight) | 165mW |
| LM35 Sensor | 5V | 0.06mA | 0.3mW |
| Servo Motor (idle) | 5V | 100mA | 500mW |
| Servo Motor (moving) | 5V | 250mA | 1250mW |
| Green LED | 2V | 20mA | 40mW |
| Red LED | 2V | 20mA | 40mW |
| **Total (idle)** | **5V** | **~200mA** | **~1W** |
| **Total (active)** | **5V** | **~350mA** | **~1.75W** |

### Power Supply Options

**Option 1: USB Power (Recommended for Development)**
- Standard USB 2.0: 500mA @ 5V
- USB 3.0: 900mA @ 5V
- ✅ Sufficient for this project
- ✅ Easy programming interface
- ⚠️ May struggle with large/multiple servos

**Option 2: External Power Adapter**
- 7-12V DC input (9V recommended)
- Minimum 1A current rating
- ✅ More stable for servos
- ✅ Better for continuous operation
- ⚠️ Requires separate USB for programming

**Option 3: Battery Power (Portable)**
- 9V battery via barrel jack
- 6× AA batteries (9V) via barrel jack
- ⚠️ Limited runtime
- ⚠️ Voltage drops as battery drains

### Power Protection

**Recommended Additions:**
1. **Decoupling capacitors**: 100nF ceramic near each IC
2. **Bulk capacitor**: 470µF-1000µF electrolytic across power rails
3. **Diode protection**: 1N4007 reverse voltage protection
4. **Fuse**: 500mA resettable polyfuse on power input

## Mechanical Considerations

### Mounting and Enclosure

**Recommended Enclosure Features:**
- Ventilation holes for sensor accuracy
- LCD viewing window
- LED indicator holes
- Servo mounting bracket
- Cable management channels
- Access to USB port
- Reset button access

**Materials:**
- Acrylic sheet (laser cut)
- 3D printed housing
- Plastic project box
- Custom PCB with mounting holes

### Servo Valve Attachment

**Mounting Options:**
1. **Direct shaft attachment**: Valve on servo horn
2. **Linkage mechanism**: Rod connecting servo to valve
3. **Gear reduction**: For heavier valves
4. **Bracket mount**: Secure servo to fixed structure

**Design Considerations:**
- Servo torque vs valve resistance
- Travel distance and angle needed
- Alignment and stability
- Mechanical stops to prevent damage

## Testing and Calibration

### Initial Testing Procedure

1. **Visual inspection**: Check all connections
2. **Continuity test**: Use multimeter
3. **Power test**: Measure voltages at key points
4. **Component test**: Test each part individually
5. **Integration test**: Run complete system
6. **Load test**: Operate for extended period

### Calibration Steps

**Temperature Sensor Calibration:**
1. Measure ice water (0°C reference)
2. Measure boiling water (100°C reference)
3. Calculate offset and scaling factors
4. Update code with calibration values

**LCD Contrast Adjustment:**
1. Turn potentiometer fully counterclockwise
2. Slowly turn clockwise until characters visible
3. Adjust for best contrast and readability

**Servo Range Calibration:**
1. Test minimum position (0°)
2. Test maximum position (180°)
3. Verify no binding or stress
4. Adjust code values if needed

## Troubleshooting Hardware Issues

### Systematic Diagnosis

1. **Check power**: Measure voltages with multimeter
2. **Verify connections**: Use continuity tester
3. **Isolate components**: Test each separately
4. **Check for shorts**: Look for unintended connections
5. **Inspect solder joints**: If using permanent assembly
6. **Test with known-good parts**: Swap components

### Common Hardware Problems

**LCD Not Working:**
- Check contrast adjustment
- Verify wiring (especially RS and EN)
- Test with simple "Hello World" sketch
- Try different power source

**Sensor Reading Error:**
- Check sensor orientation
- Verify analog reference voltage
- Test with multimeter on sensor output
- Try different analog pin

**Servo Jittering:**
- Insufficient power supply
- Add capacitor across servo power
- Use external power for servo
- Check PWM signal with oscilloscope

**LED Not Lighting:**
- Check polarity
- Verify resistor value
- Test LED with battery
- Check pin assignments in code

## Safety Guidelines

### Electrical Safety
- Never touch circuitry while powered
- Use insulated tools
- Work on non-conductive surface
- Disconnect power before modifications
- Check polarity before connecting power

### Component Safety
- Don't exceed voltage/current ratings
- Allow components to cool if hot
- Use proper heat sinking if needed
- Protect against ESD (electrostatic discharge)
- Store components in anti-static bags

### Environmental Considerations
- Keep away from moisture
- Avoid extreme temperatures
- Provide adequate ventilation
- Protect from dust and debris
- Shield from direct sunlight

## Maintenance

### Regular Checks
- Inspect connections monthly
- Clean dust from components
- Check servo for smooth operation
- Verify LCD readability
- Test sensor accuracy

### Replacement Schedule
- Servo: 1-2 years (heavy use)
- LEDs: 5+ years (20,000+ hours)
- Sensor: 5+ years
- Breadboard connections: Clean/replace as needed
- Wires: Check for fraying/damage

## Upgrades and Modifications

### Easy Upgrades
- Add OLED display for better graphics
- Include buzzer for audio alerts
- Add button for user interaction
- Install relay for actual valve control
- Include SD card for data logging

### Advanced Modifications
- Multiple temperature sensors
- Wireless communication (ESP8266/ESP32)
- Battery backup with RTC
- Touchscreen interface
- PID control algorithm

## Resources

### Datasheets
- [Arduino UNO Schematic](https://www.arduino.cc/en/uploads/Main/Arduino_Uno_Rev3-schematic.pdf)
- [HD44780 LCD Controller](https://www.sparkfun.com/datasheets/LCD/HD44780.pdf)
- [LM35 Temperature Sensor](https://www.ti.com/lit/ds/symlink/lm35.pdf)
- [SG90 Servo Motor Datasheet](http://www.ee.ic.ac.uk/pcheung/teaching/DE1_EE/stores/sg90_datasheet.pdf)

### Tools Needed
- Wire strippers
- Needle-nose pliers
- Multimeter
- Soldering iron (for permanent assembly)
- Screwdriver set
- Wire cutters

---

**Document Version**: 1.0
**Last Updated**: February 2026
