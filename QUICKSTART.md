# Quick Start Guide

Get your Arduino Temperature Valve Control System running in **10 minutes**!

## 📦 What You Need

### Hardware
- ✅ Arduino UNO
- ✅ 16x2 LCD Display
- ✅ LM35 Temperature Sensor
- ✅ SG90 Servo Motor
- ✅ 2× LEDs (1 Green, 1 Red)
- ✅ 2× 220Ω Resistors
- ✅ 1× 10kΩ Potentiometer
- ✅ Breadboard & Jumper Wires
- ✅ USB Cable

### Software
- ✅ Arduino IDE ([Download](https://www.arduino.cc/en/software))

## 🚀 Quick Setup (3 Steps)

### Step 1: Wire It Up (5 minutes)

Follow this simple connection guide:

#### LCD Display
```
LCD Pin → Arduino Pin
VDD → 5V
VSS → GND
V0  → Potentiometer (middle pin)
RS  → D2
RW  → GND
E   → D8
D4  → D4
D5  → D5
D6  → D6
D7  → D7
A   → 5V
K   → GND
```

#### Temperature Sensor (LM35)
```
Pin 1 (+) → 5V
Pin 2 (Out) → A1
Pin 3 (-) → GND
```

#### Servo Motor
```
Red → 5V
Brown/Black → GND
Orange/Yellow → D10
```

#### LEDs
```
Green LED:
  Long leg → 220Ω resistor → D12
  Short leg → GND

Red LED:
  Long leg → 220Ω resistor → D13
  Short leg → GND
```

**Tip**: Use the provided circuit images as reference!

### Step 2: Upload Code (3 minutes)

1. **Open Arduino IDE**

2. **Copy the code** from `src/Project_FINAL.ino` or type:

```cpp
#include <LiquidCrystal.h>
#include <Servo.h>

Servo servo;
#define R_LED 13
#define G_LED 12
LiquidCrystal lcd(2, 8, 4, 5, 6, 7);
float temp;

void setup() {
  lcd.begin(16, 2);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  servo.attach(10);
  Serial.begin(9600);
  delay(100);
  lcd.clear();
}

void loop() {
  temp = analogRead(A1);
  temp = ((temp*0)+26.456);  // Demo mode - see docs to enable real sensor
  
  lcd.print("TEMP: ");
  lcd.print(temp);
  lcd.println("*C    ");
  
  if (temp<23){
    digitalWrite(G_LED, HIGH);
    lcd.setCursor(0, 2);
    lcd.print("Temp is NORMAL!");
    servo.write(45);
  }
  else digitalWrite(G_LED, LOW);
  
  if (temp>25){
    digitalWrite(R_LED, HIGH);
    lcd.setCursor(0, 2);
    lcd.print("Temp is HIGH!");
    servo.write(145);
  }
  else digitalWrite(R_LED, LOW);
  
  delay(500);
  lcd.clear();
}
```

3. **Select board**: Tools → Board → Arduino UNO

4. **Select port**: Tools → Port → (your COM port)

5. **Click Upload** (→ button)

### Step 3: Test It (2 minutes)

1. **Power on** - LCD should light up
2. **Check display** - Should show temperature
3. **Adjust LCD contrast** - Turn potentiometer until text is clear
4. **Watch the demo**:
   - Green LED should be ON (temp < 23°C in demo)
   - Servo at 45°
   - LCD shows "NORMAL!"

## ✅ Success! What's Next?

### Enable Real Temperature Sensor

The code currently shows a constant temperature (26.456°C) for demonstration. To use the actual sensor:

**Change line 23 from:**
```cpp
temp = ((temp*0)+26.456);
```

**To:**
```cpp
temp = analogRead(A1) * 0.48828125;
```

Now touch the sensor with your finger to see it heat up!

### Test the System

1. **Heat the sensor** (with finger or warm object)
2. **Watch** temperature rise on LCD
3. **Observe** when it crosses 25°C:
   - Red LED turns ON
   - Green LED turns OFF
   - Servo moves to 145°
   - LCD shows "HIGH!"

## 🔧 Common First-Time Issues

### LCD shows nothing
→ Adjust contrast potentiometer (turn it slowly)

### LCD shows boxes/random characters
→ Check all 6 data wires (RS, E, D4-D7) are connected correctly

### Servo doesn't move
→ Check it's connected to pin 10 (PWM pin)

### LEDs don't light up
→ Check polarity - long leg goes to resistor, short leg to GND

### Temperature always 26.456°C
→ This is normal in demo mode! See "Enable Real Temperature Sensor" above

## 📊 Understanding Your Display

```
┌────────────────┐
│TEMP: 26.5*C    │  ← Line 1: Current temperature
│Temp is NORMAL! │  ← Line 2: System status
└────────────────┘
```

**Status Messages**:
- "Temp is NORMAL!" = Everything OK (< 23°C)
- "Temp is HIGH!" = Alert condition (> 25°C)
- No message = In between (23-25°C)

**LED Indicators**:
- 🟢 Green ON = Normal temperature
- 🔴 Red ON = High temperature
- Both OFF = Neutral zone

## 🎯 Quick Customization

### Change Temperature Thresholds

Find these lines and change the numbers:

```cpp
if (temp < 23)  // Line 27 - Normal threshold
if (temp > 25)  // Line 36 - High threshold
```

### Change Valve Positions

```cpp
servo.write(45);   // Line 31 - Normal position
servo.write(145);  // Line 40 - High position
```

### Adjust Response Speed

```cpp
delay(500);  // Line 44 - Wait time in milliseconds
```

## 📸 Quick Reference Images

See the `images/` folder for:
- ✅ Working system photos
- ✅ Correct wiring examples
- ✅ LCD display states

## 🆘 Need Help?

### Quick Checks
1. Is USB cable plugged in?
2. Is Arduino IDE showing your COM port?
3. Did upload complete successfully?
4. Are all wires firmly connected?
5. Is LCD contrast adjusted?

### Serial Monitor Debugging

Open Serial Monitor (Tools → Serial Monitor, 9600 baud):
- Should show temperature values
- Use to verify sensor readings

### Documentation

For detailed help:
- 📖 **README.md** - Full project documentation
- 🔧 **docs/HARDWARE.md** - Complete wiring guide
- 💻 **docs/SOFTWARE.md** - Code explanation
- 🔌 **hardware/CIRCUIT_DIAGRAMS.md** - Detailed schematics

## 🎓 Learn More

### Next Steps
1. ✅ Get basic system working (you're here!)
2. 📚 Read the full README for deeper understanding
3. 🔧 Try customizing thresholds
4. 🌡️ Enable the real temperature sensor
5. 💡 Add your own features!

### Experiment Ideas
- Add a buzzer for audio alerts
- Log data to SD card
- Add more sensors
- Create a web interface
- Build a custom enclosure

## 🏁 Congratulations!

You've successfully built an Arduino temperature control system! 

**Project Status**: ✅ Running

**What's Happening**:
- System monitors temperature every 500ms
- Controls valve position based on thresholds
- Provides visual feedback via LCD and LEDs
- Can be customized to your needs

---

**Quick Start Version**: 1.0
**Estimated Setup Time**: 10 minutes
**Difficulty**: Beginner-Friendly

For detailed documentation, see [README.md](README.md)

Happy Making! 🎉
