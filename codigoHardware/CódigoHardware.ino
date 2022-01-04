// Medidor de pulso cardiaco 
// Modificado por: www.elprofegarcia.com
// Visualiza en LCD 16x2 el valor de BPM, grafica el ritmo cardiaco por el Serial Plotter y pulso por el pin 13
// Conexion Sensor Pulsos -> Arduino UNO:   S -> A0 , Vcc -> 5V , (-) -> GND
// Conexion i2C -> Arduino UNO:  SCL-> A5   SDA->A4  VCC->5V  GND->GND
#include <DS1302.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f,16,2);   // inicializa la interfaz I2C del LCD 16x2
DS1302 rtc(2,4,5);

int SENSOR;
float TEMPERATURA;
int pulsePin = 0;                   // Sensor de Pulso conectado al puerto A0
// Estas variables son volatiles porque son usadas durante la rutina de interrupcion en la segunda Pestaña
volatile int BPM;                   // Pulsaciones por minuto
volatile int Signal;                // Entrada de datos del sensor de pulsos
volatile int IBI = 600;             // tiempo entre pulsaciones
volatile boolean Pulse = false;     // Verdadero cuando la onda de pulsos es alta, falso cuando es Baja
volatile boolean QS = false;        // Verdadero cuando el Arduino Busca un pulso del Corazon

void setup(){ 
 rtc.halt(false);
 rtc.writeProtect(false);
 pinMode(13, OUTPUT); 
 lcd.init();                         // Se inicializa el LCD 16x2
 lcd.backlight();                           
 lcd.clear();    
 lcd.setCursor(3,0); 
 lcd.print("BIENVENIDO");
 delay(3000);
 lcd.clear();
// rtc.setDOW(FRIDAY);
// rtc.setTime(02,37,00);
// rtc.setDate(31,12,2021);    
 Serial.begin(9600);                // Puerto serial configurado a 57600 Baudios
 delay(4000);
 interruptSetup();                  // Configura la interrucion para leer el sensor de pulsos cada 2mS  
}

void loop(){
 verPulsos();
 verHora();
 verTemp();
}


void verHora(){
  lcd.setCursor(0,1);
  lcd.print(rtc.getTimeStr());
  lcd.setCursor(0,0);
  lcd.print(rtc.getDateStr(FORMAT_SHORT, FORMAT_LITTLEENDIAN, '/'));
  //lcd.setCursor(13,1);
  //lcd.print(rtc.getDOWStr());
  delay(1000);
  
}

void verPulsos(){
 int pulso = analogRead(A0);           //Lee el valor del pulsometro conectado al puerto Analogo A0
 if (BPM >=530){
  digitalWrite(13,HIGH);      
 }else{
  digitalWrite(13,LOW);
 }
   lcd.setCursor(9,0); 

   //Muestra en el LCD el valor de BPM 
   lcd.print("BPM=");
   lcd.print(BPM);
   lcd.print("   "); 
   //Serial.print("BPM = ");  
   //Serial.println(BPM); //Habilitar estas linea para ver BPM en el monitor serial pero deshabilitar la siguiente
   Serial.println(pulso);                          // envia el valor del pulso por el puerto serie  (desabilitarla si habilita la anterior linea)
  if (QS == true){                       // Bandera del Quantified Self es verdadera cuando el Arduino busca un pulso del corazon
    QS = false;                          // Reset a la bandera del Quantified Self 
  }
  
}

void verTemp(){
SENSOR=analogRead(A2);
TEMPERATURA= ((SENSOR*5000.0)/1023) /10;
//Serial.println(TEMPERATURA,1);
lcd.setCursor(9,1);
lcd.print("T:");
lcd.print(TEMPERATURA,1);
lcd.print("C");
//delay(1000);
}

