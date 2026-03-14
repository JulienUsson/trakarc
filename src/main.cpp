#include <M5StickCPlus2.h>

const unsigned long LONG_PRESS_MS = 2000;
const unsigned long SLEEP_TIMEOUT_MS = 8000;

RTC_DATA_ATTR unsigned int counter = 0;
unsigned long lastActivity = 0;

unsigned long btnAPressStart = 0;
bool btnALongPressHandled = false;

void drawCounter()
{
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(YELLOW);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.println("Compteur");
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.setTextSize(5);
    M5.Lcd.setCursor(60, 50);
    M5.Lcd.println(counter);
}

void setup()
{
    auto cfg = M5.config();
    M5.begin(cfg);

    M5.Lcd.setRotation(1);
    drawCounter();
    lastActivity = millis();
}

void loop()
{
    M5.update();

    if (M5.BtnA.wasPressed())
    {
        btnAPressStart = millis();
        btnALongPressHandled = false;
        lastActivity = millis();
    }

    if (M5.BtnA.isPressed() && !btnALongPressHandled && (millis() - btnAPressStart >= LONG_PRESS_MS))
    {
        counter = 0;
        drawCounter();
        btnALongPressHandled = true;
    }

    if (M5.BtnA.wasReleased() && !btnALongPressHandled)
    {
        counter++;
        drawCounter();
    }

    if (millis() - lastActivity >= SLEEP_TIMEOUT_MS)
    {
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.sleep();
        esp_sleep_enable_ext0_wakeup(GPIO_NUM_37, LOW);
        esp_deep_sleep_start();
    }

    delay(10);
}