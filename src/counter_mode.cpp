#include "counter_mode.h"

RTC_DATA_ATTR unsigned int counterValue = 0;

unsigned int &CounterMode::getCounter()
{
    return counterValue;
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
    M5.Lcd.println(getCounter());
}

void CounterMode::onPrimaryPress()
{
    getCounter()++;
}

void CounterMode::onPrimaryLongPress()
{
    getCounter() = 0;
}

void CounterMode::onSecondaryPress()
{
}
