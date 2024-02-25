#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
constexpr uint8_t pinRX = 8, pinTX = 7;


SoftwareSerial pc(pinRX, pinTX);

struct SendInfo {
    uint8_t cpuUsage;
    uint8_t memUsage;
    uint8_t cpuTemp;
};


SendInfo sInfo = {};

void setup() {
  Serial.begin(9600);
  pc.begin(9600);
  lcd.init();  
  lcd.backlight();
  lcd.print("No Data...");
}

void loop() {

  if(pc.available()){
    //Serial.println("Reading data...");
    pc.readBytes((uint8_t*)&sInfo, sizeof(SendInfo));
    //Serial.println("DataRead: " + String(read));
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("CPU: " + String(sInfo.cpuUsage) + "%  ");
    lcd.print(String(sInfo.cpuTemp) + (char)223 + 'C');
    lcd.setCursor(0,1);
    lcd.print("MEM: " + String(sInfo.memUsage) + "%");
  
  }
  else{
   // Serial.println("Waiting for data...");

   // Serial.println("Read: " + String(pc.read()));
  }
  delay(1000);
}

