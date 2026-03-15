#include "counter_mode.h"

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
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.println("Compteur");
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(5);
    M5.Lcd.setCursor(60, 50);
    M5.Lcd.println(counter);
}

bool CounterMode::onPrimaryPress()
{
    counter++;
    save();
    return true;
}

bool CounterMode::onPrimaryLongPress()
{
    if (counter == 0)
    {
        return false;
    }
    counter = 0;
    save();
    return true;
}

bool CounterMode::onPrimaryHoldRepeat()
{
    return false;
}

bool CounterMode::onSecondaryPress()
{
    return false;
}

void CounterMode::onWakeUp()
{
}

void CounterMode::reset()
{
    counter = 0;
    save();
}
