#include "settings_mode.h"
#include "counter_mode.h"
#include "score_mode.h"

const char *SettingsMode::getTargetTypeLabel(TargetType type)
{
    switch (type)
    {
    case TARGET_CLASSIQUE:
        return "Classique";
    case TARGET_TRISPOT:
        return "Trispot";
    case TARGET_FIELD:
        return "Campagne";
    default:
        return "Inconnu";
    }
}

const char *SettingsMode::getTargetTypeLabel() const
{
    return SettingsMode::getTargetTypeLabel(targetType);
}

unsigned int SettingsMode::getMaxScore() const
{
    switch (targetType)
    {
    case TARGET_CLASSIQUE:
    case TARGET_TRISPOT:
        return 10;
    case TARGET_FIELD:
        return 6;
    default:
        return 10;
    }
}

unsigned int SettingsMode::getMinScore() const
{
    switch (targetType)
    {
    case TARGET_CLASSIQUE:
    case TARGET_FIELD:
        return 1;
    case TARGET_TRISPOT:
        return 5;
    default:
        return 1;
    }
}

uint16_t SettingsMode::getArrowColor(unsigned int score) const
{
    switch (targetType)
    {
    case TARGET_FIELD:
        if (score >= 5)
            return YELLOW;
        else if (score >= 1)
            return DARKGREY;
        else
            return LIGHTGREY;
    default:
        if (score >= 9)
            return YELLOW;
        else if (score >= 7)
            return RED;
        else if (score >= 5)
            return BLUE;
        else if (score >= 3)
            return DARKGREY;
        else if (score >= 1)
            return WHITE;
        else
            return LIGHTGREY;
    }
}

void SettingsMode::setModes(CounterMode *counter, ScoreMode *score)
{
    counterMode = counter;
    scoreMode = score;
}

void SettingsMode::load()
{
    Preferences prefs;
    prefs.begin("settings", true);
    targetType = (TargetType)prefs.getUInt("target", TARGET_CLASSIQUE);
    endSize = prefs.getUInt("endSize", 6);
    prefs.end();
}

void SettingsMode::save()
{
    Preferences prefs;
    prefs.begin("settings", false);
    prefs.putUInt("target", targetType);
    prefs.putUInt("endSize", endSize);
    prefs.end();
}

void SettingsMode::drawMenuItem(int y, MenuItem item, const char *label)
{
    M5.Lcd.setCursor(10, y);
    if (currentItem == item)
    {
        M5.Lcd.setTextColor(YELLOW);
        M5.Lcd.print("> ");
    }
    else
    {
        M5.Lcd.setTextColor(WHITE);
        M5.Lcd.print("  ");
    }
    M5.Lcd.print(label);
}

void SettingsMode::draw()
{
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.println("Parametres");

    M5.Lcd.setTextSize(2);

    drawMenuItem(50, RESET_ALL, "Reinitialiser");

    drawMenuItem(80, TARGET_TYPE_ITEM, "Blason: ");
    M5.Lcd.println(getTargetTypeLabel(targetType));

    drawMenuItem(110, END_SIZE_ITEM, "Volee: ");
    M5.Lcd.println(endSize);
}

bool SettingsMode::onPrimaryPress()
{
    switch (currentItem)
    {
    case TARGET_TYPE_ITEM:
        targetType = (TargetType)((targetType + 1) % TARGET_TYPE_COUNT);
        scoreMode->reset();
        save();
        break;
    case END_SIZE_ITEM:
        endSize++;
        if (endSize > 12)
            endSize = 2;
        save();
        break;
    case RESET_ALL:
        counterMode->reset();
        scoreMode->reset();
        break;
    default:
        break;
    }
    return true;
}

void SettingsMode::onEnter()
{
    currentItem = RESET_ALL;
}

void SettingsMode::onWakeUp()
{
}

bool SettingsMode::onSecondaryPress()
{
    currentItem = (MenuItem)((currentItem + 1) % MENU_ITEM_COUNT);
    return true;
}