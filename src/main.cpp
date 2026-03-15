#include <M5StickCPlus2.h>
#include <Preferences.h>
#include "counter_mode.h"
#include "score_mode.h"
#include "Arduino.h"

const unsigned long DIM_TIMEOUT_MS = 5000;
const unsigned long SLEEP_TIMEOUT_MS = 10000;

CounterMode counterMode;
ScoreMode scoreMode;
Mode *modes[] = {&counterMode, &scoreMode};
const int MODE_COUNT = sizeof(modes) / sizeof(modes[0]);
int currentModeIndex = 0;

unsigned long lastActivity = 0;
bool isDimmed = false;

int loadMode();
void saveMode(int mode);
void sleep();
void resetActivity();
void drawModeLabel();
void drawBatteryLevel();

void drawModeLabel()
{
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(220, 10);
    M5.Lcd.print(modes[currentModeIndex]->label());
}

void drawBatteryLevel()
{
    int batteryLevel = M5.Power.getBatteryLevel();
    bool isCharging = M5.Power.isCharging() == M5.Power.is_charging;

    if (isCharging)
    {
        M5.Lcd.setTextColor(GREEN);
    }
    else if (batteryLevel < 10)
    {
        M5.Lcd.setTextColor(RED);
    }
    else if (batteryLevel < 20)
    {
        M5.Lcd.setTextColor(ORANGE);
    }
    else
    {
        M5.Lcd.setTextColor(DARKGREY);
    }

    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(215, 128);
    M5.Lcd.print(batteryLevel);
    M5.Lcd.print("%");
}

void drawScreen()
{
    M5.Lcd.fillScreen(BLACK);

    drawModeLabel();
    modes[currentModeIndex]->draw();
    drawBatteryLevel();
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

    if (M5.BtnA.wasHold())
    {
        if (modes[currentModeIndex]->onPrimaryLongPress())
        {
            resetActivity();
            drawScreen();
        }
    }

    if (M5.BtnA.wasClicked())
    {
        if (modes[currentModeIndex]->onPrimaryPress())
        {
            resetActivity();
            drawScreen();
        }
    }

    if (M5.BtnB.wasPressed())
    {
        if (modes[currentModeIndex]->onSecondaryPress())
        {
            resetActivity();
            drawScreen();
        }
    }

    if (M5.BtnPWR.wasClicked())
    {
        currentModeIndex = (currentModeIndex + 1) % MODE_COUNT;
        saveMode(currentModeIndex);
        resetActivity();
        drawScreen();
    }

    unsigned long inactiveTime = millis() - lastActivity;

    if (inactiveTime >= SLEEP_TIMEOUT_MS)
    {
        sleep();
    }
    else if (inactiveTime >= DIM_TIMEOUT_MS && !isDimmed)
    {
        M5.Display.setBrightness(20);
        isDimmed = true;
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

void resetActivity()
{
    lastActivity = millis();
    if (isDimmed)
    {
        M5.Display.setBrightness(255);
        isDimmed = false;
    }
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
    M5.Display.setBrightness(255);
    isDimmed = false;
    M5.update();
    modes[currentModeIndex]->onWakeUp();
    drawScreen();
    lastActivity = millis();
}