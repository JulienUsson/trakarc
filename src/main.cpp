#include <M5StickCPlus2.h>

void setup()
{
    auto cfg = M5.config();
    M5.begin(cfg);

    M5.Lcd.setRotation(1);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(YELLOW);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(10, 30);
    M5.Lcd.println("DEVENVI + M5");
    M5.Lcd.setCursor(10, 60);
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.println("FLASH OK !");
}

void loop()
{
    digitalWrite(19, HIGH);
    delay(500);
    digitalWrite(19, LOW);
    delay(500);
}