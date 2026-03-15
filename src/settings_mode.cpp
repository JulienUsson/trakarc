#include "settings_mode.h"
#include "counter_mode.h"
#include "score_mode.h"

void SettingsMode::setModes(CounterMode *counter, ScoreMode *score)
{
    counterMode = counter;
    scoreMode = score;
}

void SettingsMode::draw()
{
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.println("Parametres");

    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(10, 50);

    switch (currentItem)
    {
    case RESET_ALL:
        M5.Lcd.setTextColor(YELLOW);
        M5.Lcd.println("> Reinitialiser");
        break;
    }
}

bool SettingsMode::onPrimaryPress()
{
    switch (currentItem)
    {
    case RESET_ALL:
        if (counterMode != nullptr)
        {
            counterMode->reset();
        }
        if (scoreMode != nullptr)
        {
            scoreMode->reset();
        }
        break;
    default:
        break;
    }
    return true;
}

bool SettingsMode::onSecondaryPress()
{
    currentItem = (MenuItem)((currentItem + 1) % MENU_ITEM_COUNT);
    return true;
}