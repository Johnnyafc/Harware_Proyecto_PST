#include <SoftwareSerial.h>


SoftwareSerial miBT (10,11);

char NOMBRE[21]= "BLUETOOTH HC-06";
char BPS = '4';
char PASS[5]="1234";


void setup() {
  // put your setup code here, to run once:
  miBT.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  delay(4000);
 
  digitalWrite(13,HIGH);

  miBT.print("AT");
  delay(1000);  
  
  miBT.print("AT+NAME");
  miBT.print(NOMBRE);
  delay(1000);

  miBT.print("AT+BAUD");
  miBT.print(BPS);
  delay(1000);

  miBT.print("AT+PIN");
  miBT.print(PASS);
  delay(1000);  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13,!digitalRead(13));
  delay(300);
}
