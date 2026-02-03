# Circuit Diagrams and Schematics

## Complete System Wiring Diagram

### ASCII Circuit Diagram

```
                                 Arduino UNO
                    ┌────────────────────────────────┐
                    │                                │
                    │  ┌──────────────────────────┐  │
     USB Power ─────┤  │      ATmega328P          │  │
                    │  └──────────────────────────┘  │
                    │                                │
     ┌──────────────┤ 5V                          │  │
     │              │                                │
     │  ┌───────────┤ GND                         │  │
     │  │           │                                │
     │  │           │  ANALOG IN                    │
     │  │           │  A0  A1  A2  A3  A4  A5      │
     │  │           │       │                        │
     │  │           └───────┼────────────────────────┘
     │  │                   │
     │  │                   │  Temperature Sensor (LM35)
     │  │                   │  ┌──────────────┐
     │  │                   └──┤ Vout    Pin2 │
     │  │                      │              │
     │  ├──────────────────────┤ +Vs     Pin1 │
     │  │                      │              │
     │  └──────────────────────┤ GND     Pin3 │
     │                         └──────────────┘
     │
     │                         16x2 LCD Display
     │                         ┌────────────────┐
     │                         │ ┌────────────┐ │
     │                         │ │            │ │
     │                         │ │  HD44780   │ │
     │                         │ │            │ │
     │                         │ └────────────┘ │
     │                         │                │
     ├─────────────────────────┤ VDD           │
     ├─────────────────────────┤ VSS           │
     │          ┌──────────────┤ V0  (contrast)│
     │          │              │                │
     │     10kΩ Pot            │  ┌─────────────┤ D4  ──► D4 (Arduino)
     │     ┌────┴────┐         │  ├─────────────┤ D5  ──► D5 (Arduino)
     ├─────┤ 1     3 ├─────────┤  ├─────────────┤ D6  ──► D6 (Arduino)
     │     │    2    │         │  ├─────────────┤ D7  ──► D7 (Arduino)
     │     └─────────┘         │  │             │        
     │                         │  ├─────────────┤ RS  ──► D2 (Arduino)
     │                         │  ├─────────────┤ EN  ──► D8 (Arduino)
     │                         │  │             │
     ├─────────────────────────┤  │ RW         │
     │                         │  │             │
     ├─────────────────────────┤ A (backlight+)│
     └─────────────────────────┤ K (backlight-)│
                               └───┼─────────────┘
                                   │
                                   │
                    ┌──────────────▼────────────────┐
                    │        BREADBOARD             │
                    │  ┌────────────────────────┐   │
                    │  │ Power Rails            │   │
                    │  │  + + + + + + + + + +   │   │
                    │  │  - - - - - - - - - -   │   │
                    │  └────────────────────────┘   │
                    │                                │
                    │  Servo Motor                   │
                    │  ┌──────────┐                  │
                    │  │  SG90    │                  │
    5V  ────────────┼──┤ VCC (red)│                  │
    GND ────────────┼──┤ GND (brn)│                  │
    D10 ────────────┼──┤ SIG (org)│                  │
                    │  └──────────┘                  │
                    │                                │
                    │  Green LED Circuit             │
                    │     ┌─────┐                    │
    D12 ────────────┼─────┤220Ω ├───►|───┐           │
                    │     └─────┘   LED  │           │
    GND ────────────┼────────────────────┘           │
                    │                                │
                    │  Red LED Circuit               │
                    │     ┌─────┐                    │
    D13 ────────────┼─────┤220Ω ├───►|───┐           │
                    │     └─────┘   LED  │           │
    GND ────────────┼────────────────────┘           │
                    │                                │
                    └────────────────────────────────┘

Legend:
  ──►  Signal flow
  ─┼─  Connection point
  ►|   LED (anode to cathode)
  ┌─┐  Component
```

## Detailed Connection Tables

### Arduino to LCD Connections

| Arduino Pin | LCD Pin | Function | Notes |
|-------------|---------|----------|-------|
| 5V | VDD (Pin 2) | Power | LCD logic power |
| GND | VSS (Pin 1) | Ground | Common ground |
| GND | RW (Pin 5) | Read/Write | Tie to GND for write-only |
| D2 | RS (Pin 4) | Register Select | Data/Command select |
| D8 | E (Pin 6) | Enable | Clock pulse |
| D4 | D4 (Pin 11) | Data Bit 4 | 4-bit mode |
| D5 | D5 (Pin 12) | Data Bit 5 | 4-bit mode |
| D6 | D6 (Pin 13) | Data Bit 6 | 4-bit mode |
| D7 | D7 (Pin 14) | Data Bit 7 | 4-bit mode |
| 5V | A (Pin 15) | Backlight + | Through 220Ω resistor |
| GND | K (Pin 16) | Backlight - | Ground |
| POT Wiper | V0 (Pin 3) | Contrast | 10kΩ potentiometer |

### Temperature Sensor Connections

| Sensor Pin | Connection | Arduino Pin | Notes |
|------------|------------|-------------|-------|
| Pin 1 | +Vs | 5V | Power supply |
| Pin 2 | Vout | A1 | Analog output |
| Pin 3 | GND | GND | Ground |

### Servo Motor Connections

| Servo Wire | Color | Arduino Pin | Function |
|------------|-------|-------------|----------|
| Power | Red | 5V | Motor power |
| Ground | Brown/Black | GND | Common ground |
| Signal | Orange/Yellow | D10 | PWM control |

### LED Connections

| Component | Arduino Pin | Connection | Notes |
|-----------|-------------|------------|-------|
| Green LED + | D12 | Via 220Ω resistor | Current limiting |
| Green LED - | GND | Direct | Common ground |
| Red LED + | D13 | Via 220Ω resistor | Current limiting |
| Red LED - | GND | Direct | Common ground |

## Breadboard Layout

### Top View of Breadboard

```
     1   5   10   15   20   25   30
  ┌─────────────────────────────────┐ +5V Rail
  │ + + + + + + + + + + + + + + + + │
  ├─────────────────────────────────┤
  │ a b c d e   f g h i j           │ Row A-E
  │ a b c d e   f g h i j           │
  │ a b c d e   f g h i j           │ LCD Display
  │ a b c d e   f g h i j           │ spans multiple rows
  │ [=========LCD=========]         │
  │ a b c d e   f g h i j           │
  │ a b c d e   f g h i j           │
  │ a b c d e   f g h i j           │
  │ a b c d e   f g h i j           │
  │                                 │
  │ [TMP]     [POT]    [Servo]      │ Component placement
  │  LM35     10kΩ      SG90        │
  │                                 │
  │ [LED] [LED]                     │
  │  🟢   🔴                         │
  │   │    │                        │
  │  [R]  [R]                       │
  │  220Ω 220Ω                      │
  │                                 │
  ├─────────────────────────────────┤
  │ - - - - - - - - - - - - - - - - │ GND Rail
  └─────────────────────────────────┘

Legend:
[LCD] = LCD Display placement
[TMP] = LM35 Temperature Sensor
[POT] = Potentiometer
[Servo] = Servo Motor (off breadboard)
[LED] = LED with resistor
🟢 = Green LED
🔴 = Red LED
[R] = Resistor
```

## Power Distribution

### Power Rail Configuration

```
5V Rail:
  ├── Arduino 5V pin
  ├── LCD VDD
  ├── LCD Backlight (A)
  ├── LM35 Pin 1 (+Vs)
  ├── Servo Red wire
  └── Potentiometer Pin 1

GND Rail:
  ├── Arduino GND pin
  ├── LCD VSS
  ├── LCD RW
  ├── LCD Backlight (K)
  ├── LM35 Pin 3
  ├── Servo Brown/Black wire
  ├── Green LED cathode
  ├── Red LED cathode
  └── Potentiometer Pin 3
```

## Signal Routing

### Digital Signals (Arduino → Components)

```
D2 ──────────────────► LCD RS
D4 ──────────────────► LCD D4
D5 ──────────────────► LCD D5
D6 ──────────────────► LCD D6
D7 ──────────────────► LCD D7
D8 ──────────────────► LCD E
D10 ─────────────────► Servo Signal
D12 ──┬──[220Ω]──────► Green LED
      └──────────────┐
D13 ──┬──[220Ω]──────► Red LED
      └──────────────┘
```

### Analog Signals (Components → Arduino)

```
LM35 Pin 2 ──────────► A1 (Temperature Reading)
```

## PCB Design Suggestions

If creating a permanent PCB:

### Recommended Layout

1. **Arduino section** (left)
   - Arduino headers
   - Power input connector

2. **Display section** (center)
   - LCD connector
   - Contrast potentiometer

3. **Sensor section** (right)
   - Temperature sensor connector
   - Pull-up/down resistors

4. **Output section** (bottom)
   - LED circuits with resistors
   - Servo connector
   - Screw terminals for external connections

### Layer Stack (2-layer PCB)

```
Top Layer:
  - Signal traces
  - Component pads
  - Silk screen markings

Bottom Layer:
  - Ground plane
  - Power distribution
  - Return paths
```

### Trace Widths

| Signal Type | Min Width | Recommended |
|-------------|-----------|-------------|
| Digital signals | 0.2mm | 0.3mm |
| Power (5V) | 0.5mm | 1.0mm |
| Ground | 0.5mm | 1.0mm (or plane) |
| Analog signal | 0.2mm | 0.3mm (keep short) |

## Testing Points

Add these test points for debugging:

```
TP1: 5V Power Rail
TP2: GND
TP3: LCD RS signal
TP4: LCD E signal
TP5: Temperature sensor output (A1)
TP6: Servo PWM signal (D10)
TP7: Green LED control (D12)
TP8: Red LED control (D13)
```

## Safety Considerations

### Electrical Safety

1. **Current Limiting**
   - All LEDs must have current-limiting resistors
   - Servo should have separate power if drawing > 500mA

2. **Voltage Protection**
   - Add reverse polarity protection diode
   - Consider TVS diode for servo back-EMF

3. **Decoupling**
   - Add 100nF capacitor near each IC
   - Add 470µF bulk capacitor on power rail

### Physical Safety

1. **Insulation**
   - No exposed live connections
   - Secure all wiring

2. **Heat Management**
   - Ensure servo has ventilation
   - Keep power regulators cool

3. **Mechanical**
   - Secure breadboard/PCB to base
   - Strain relief on all cables

## Troubleshooting Guide

### Wiring Checklist

- [ ] All power connections secure (5V, GND)
- [ ] LCD pins connected correctly (especially RS, E, D4-D7)
- [ ] Temperature sensor polarity correct
- [ ] Servo wires in correct order
- [ ] LED polarity correct (long leg to resistor)
- [ ] No short circuits between adjacent pins
- [ ] All ground points connected to common ground

### Visual Inspection

1. Check for loose wires
2. Verify component orientation
3. Look for solder bridges (if PCB)
4. Confirm no damaged components

---

**Document Version**: 1.0
**Last Updated**: February 2026
