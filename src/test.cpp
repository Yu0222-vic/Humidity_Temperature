#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long lastReadTime = 0;
const unsigned long interval = 5000;

void displayData(float temperature, float humidity){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp");
    lcd.print(temperature,1);
    lcd.print((char)223); //This prints out the degree simple on the monitor
    lcd.print("C");

    lcd.setCursor(0,1);
    lcd.print("Humidity");
    lcd.print(humidity,1);
    lcd.print("%")
}

void setUp(){
    Serial.begin(115200);
    dht.begin();
    lcd.init();
    lcd.backlight();
    delay(3000);
}

void loop(){
    if(millis()-lastReadTime >= interval){
        float humidity = dht.readHumidity();
        float temperature = dht.readTemperature();

        if (isnan(humidity) || isnan(temperature)){
            Serial.print("Null data for humidity or temperature");
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Null DHT Data");
            return
        }
        displayData(humidity,temperature);
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" C, Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");
        delay(3000);


    }
}