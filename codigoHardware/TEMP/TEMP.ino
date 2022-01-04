#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f,16,2);

int SENSOR;
float TEMPERATURA;
float SUMA;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
lcd.init();
lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
SUMA=0;
SENSOR=analogRead(A2);
//for (int i=0; i<5;i++){
//  
TEMPERATURA= ((SENSOR*5000.0)/1023) /10;
// SUMA= TEMPERATURA+SUMA;
delay(5000);
//}
Serial.println(TEMPERATURA,1);
delay(1000);
lcd.setCursor(9,1);
lcd.print("T:");
lcd.print(TEMPERATURA,1);
lcd.print("C");
}
