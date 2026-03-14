#include <M5StickCPlus2.h>
#include "counter_mode.h"
#include "score_mode.h"

const unsigned long LONG_PRESS_MS = 2000;
const unsigned long SLEEP_TIMEOUT_MS = 8000;

RTC_DATA_ATTR int currentModeIndex = 0;

CounterMode counterMode;
ScoreMode scoreMode;
Mode *modes[] = {&counterMode, &scoreMode};
const int MODE_COUNT = sizeof(modes) / sizeof(modes[0]);

unsigned long lastActivity = 0;
unsigned long btnAPressStart = 0;
bool btnALongPressHandled = false;

void drawScreen()
{
    M5.Lcd.fillScreen(BLACK);

    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(220, 10);
    M5.Lcd.print(modes[currentModeIndex]->label());

    modes[currentModeIndex]->draw();
}

void setup()
{
    auto cfg = M5.config();
    M5.begin(cfg);

    M5.Lcd.setRotation(1);
    drawScreen();
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
        modes[currentModeIndex]->onPrimaryLongPress();
        drawScreen();
        btnALongPressHandled = true;
    }

    if (M5.BtnA.wasReleased() && !btnALongPressHandled)
    {
        modes[currentModeIndex]->onPrimaryPress();
        drawScreen();
    }

    if (M5.BtnB.wasPressed())
    {
        modes[currentModeIndex]->onSecondaryPress();
        drawScreen();
        lastActivity = millis();
    }

    if (M5.BtnPWR.wasPressed())
    {
        currentModeIndex = (currentModeIndex + 1) % MODE_COUNT;
        modes[currentModeIndex]->reset();
        drawScreen();
        lastActivity = millis();
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