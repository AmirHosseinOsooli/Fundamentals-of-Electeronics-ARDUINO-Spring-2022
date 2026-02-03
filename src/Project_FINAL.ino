#include <LiquidCrystal.h>
#include <Servo.h>
Servo servo;
#define R_LED 13
#define G_LED 12
const int rs = 2,en = 8 , d4 = 4 , d5 = 5 , d6 = 6, d7 = 7;
LiquidCrystal lcd(2, 8, 4, 5, 6, 7);
float temp;

void setup() {
lcd.begin(16, 2);
pinMode (12, OUTPUT);
pinMode (13, OUTPUT);
servo.attach(10);
Serial.begin(9600);
analogReference(INTERNAL);                 
delay(100);
lcd.clear();
}

void loop() {
 temp = analogRead(A1);
 temp = ((temp*0)+26.456);            //temp = temp * 0.48828125 which is (5.0/1023.0)*100
 lcd.print("TEMP: ");
 lcd.print(temp);
 lcd.println("*C    ");
 if (temp<23){
    digitalWrite(G_LED, HIGH);
    lcd.setCursor(0, 2);
    lcd.print("Temp is NORMAL!");
    servo.write(45);
 }
    else
    digitalWrite(G_LED, LOW);
  
 if (temp>25){
    digitalWrite(R_LED, HIGH);
    lcd.setCursor(0, 2);
    lcd.print("Temp is HIGH!");
    servo.write(145);
 }
    else
    digitalWrite(R_LED, LOW);
 delay(500);
 lcd.clear();
}
