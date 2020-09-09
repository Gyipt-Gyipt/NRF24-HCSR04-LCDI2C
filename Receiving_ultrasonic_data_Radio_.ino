#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LiquidCrystal_I2C.h>

#define CE_PIN 7
#define CSN_PIN 8

LiquidCrystal_I2C lcd(0x27,16,2);
RF24 radio(CE_PIN,CSN_PIN);
const uint64_t pipe = 0xE8E8F0F0E1LL;


struct Type_of_distance {
  long inches;
  long cm;
};
Type_of_distance TD;



void setup() {
  Serial.begin(9600);
    radio.begin();
    lcd.init();
    lcd.backlight();
    radio.openReadingPipe (1,pipe);
    radio.setPALevel(RF24_PA_MIN);
    radio.startListening();
    lcd.setCursor(0,0);
    lcd.print("Hello! There;");
    
    delay(1000);
    lcd.clear();
  
    
   
    
}

void loop() {
  if (radio.available()) {
     lcd.setCursor(0,0);
     lcd.print(TD.inches);
     lcd.print("inches");
     lcd.print("  ");
     lcd.print(TD.cm);
     lcd.print("cm");
     lcd.print("    ");
      
     
    radio.read(&TD,sizeof(TD));
    Serial.print(TD.inches);
    Serial.print("inches");
    Serial.print(TD.cm);
    Serial.print("cm");
    Serial.println();
  }
}  
void Runtxt() {
  int i;
  
     for (i=16; i>=0; i--)
     {lcd.setCursor(0,1);
      lcd.print("I'm here to measure something");
       lcd.scrollDisplayLeft(); 
        delay(250);
     }
     }
     
