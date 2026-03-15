#include "counter_mode.h"
#include "settings_mode.h"

void CounterMode::setSettingsMode(SettingsMode *settings)
{
    settingsMode = settings;
}

void CounterMode::load()
{
    Preferences prefs;
    prefs.begin("counter", true);
    counter = prefs.getUInt("value", 0);
    prefs.end();
}

void CounterMode::save()
{
    Preferences prefs;
    prefs.begin("counter", false);
    prefs.putUInt("value", counter);
    prefs.end();
}

void CounterMode::draw()
{
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(5);
    M5.Lcd.setCursor(60, 50);
    M5.Lcd.println(counter);
    M5.Lcd.setTextColor(SILVER);
    M5.Lcd.setTextSize(1.5);
    M5.Lcd.setCursor(10, 120);
    M5.Lcd.print("Volee: ");
    M5.Lcd.print(settingsMode->getEndSize());
}

bool CounterMode::incrementCounter(unsigned int value)
{
    counter = (counter + value) % 10000;
    save();
    return true;
}

bool CounterMode::onPrimaryPress()
{
    return incrementCounter(1);
}

bool CounterMode::onPrimaryLongPress()
{
    return incrementCounter(settingsMode->getEndSize());
}

void CounterMode::reset()
{
    counter = 0;
    save();
}
