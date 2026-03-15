#include <M5StickCPlus2.h>
#include <Preferences.h>
#include "counter_mode.h"
#include "score_mode.h"
#include "Arduino.h"

const unsigned long SLEEP_TIMEOUT_MS = 5000;

CounterMode counterMode;
ScoreMode scoreMode;
Mode *modes[] = {&counterMode, &scoreMode};
const int MODE_COUNT = sizeof(modes) / sizeof(modes[0]);
int currentModeIndex = 0;

unsigned long lastActivity = 0;

int loadMode();
void saveMode(int mode);
void sleep();

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

    currentModeIndex = loadMode();

    for (int i = 0; i < MODE_COUNT; i++)
        modes[i]->load();

    M5.Lcd.setRotation(1);
    drawScreen();
    lastActivity = millis();
}
void loop()
{
    M5.update();

    if (M5.BtnA.isHolding())
    {
        modes[currentModeIndex]->onPrimaryLongPress();
        drawScreen();
    }

    if (M5.BtnA.wasClicked())
    {
        modes[currentModeIndex]->onPrimaryPress();
        lastActivity = millis();
        drawScreen();
    }

    if (M5.BtnB.wasPressed())
    {
        modes[currentModeIndex]->onSecondaryPress();
        lastActivity = millis();
        drawScreen();
    }

    if (M5.BtnPWR.wasClicked())
    {
        currentModeIndex = (currentModeIndex + 1) % MODE_COUNT;
        saveMode(currentModeIndex);
        lastActivity = millis();
        drawScreen();
    }

    if (millis() - lastActivity >= SLEEP_TIMEOUT_MS)
    {
        sleep();
    }

    delay(10);
}

int loadMode()
{
    Preferences prefs;
    prefs.begin("app", true);
    int mode = prefs.getInt("mode", 0);
    prefs.end();
    return mode;
}

void saveMode(int mode)
{
    Preferences prefs;
    prefs.begin("app", false);
    prefs.putInt("mode", mode);
    prefs.end();
}

void sleep()
{
    M5.Display.sleep();
    M5.Display.waitDisplay();
    gpio_wakeup_enable(GPIO_NUM_37, GPIO_INTR_LOW_LEVEL);
    esp_sleep_enable_gpio_wakeup();
    esp_light_sleep_start();
    while (digitalRead(GPIO_NUM_37) == LOW)
    {
        delay(10);
    }
    M5.Lcd.wakeup();
    M5.update();
    modes[currentModeIndex]->onWakeUp();
    drawScreen();
    lastActivity = millis();
}