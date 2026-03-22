#include "settings_mode.h"
#include "counter_mode.h"
#include "score_mode.h"

const char *SettingsMode::getTargetTypeLabel(TargetType type)
{
    switch (type)
    {
    case TARGET_CLASSIQUE:
        return "classique";
    case TARGET_TRISPOT:
        return "trispot";
    case TARGET_FIELD:
        return "campagne";
    default:
        return "inconnu";
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
        return 6;
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
    brightnessLevel = prefs.getUInt("bright", 2);
    prefs.end();
}

void SettingsMode::save()
{
    Preferences prefs;
    prefs.begin("settings", false);
    prefs.putUInt("target", targetType);
    prefs.putUInt("endSize", endSize);
    prefs.putUInt("bright", brightnessLevel);
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
    M5.Lcd.setTextSize(2);

    const int MAX_VISIBLE = 3;
    int scrollOffset = max(0, (int)currentItem - (MAX_VISIBLE - 1));

    for (int i = 0; i < MAX_VISIBLE && (scrollOffset + i) < MENU_ITEM_COUNT; i++)
    {
        MenuItem item = (MenuItem)(scrollOffset + i);
        int y = 40 + i * 30;

        switch (item)
        {
        case RESET_ALL:
            drawMenuItem(y, RESET_ALL, "Reinitialiser");
            break;
        case TARGET_TYPE_ITEM:
            drawMenuItem(y, TARGET_TYPE_ITEM, "Blason: ");
            M5.Lcd.print(getTargetTypeLabel(targetType));
            break;
        case END_SIZE_ITEM:
            drawMenuItem(y, END_SIZE_ITEM, "Volee: ");
            M5.Lcd.print(endSize);
            break;
        case BRIGHTNESS_ITEM:
        {
            drawMenuItem(y, BRIGHTNESS_ITEM, "Luminosite: ");
            M5.Lcd.print(brightnessLevel + 1);
            break;
        }
        default:
            break;
        }
    }

    if (scrollOffset > 0)
    {
        M5.Lcd.setTextColor(SILVER);
        M5.Lcd.setTextSize(1);
        M5.Lcd.setCursor(220, 35);
        M5.Lcd.print("^");
    }
    if (scrollOffset + MAX_VISIBLE < MENU_ITEM_COUNT)
    {
        M5.Lcd.setTextColor(SILVER);
        M5.Lcd.setTextSize(1);
        M5.Lcd.setCursor(220, 105);
        M5.Lcd.print("v");
    }
}

bool SettingsMode::onPrimaryPress()
{
    switch (currentItem)
    {
    case TARGET_TYPE_ITEM:
        targetType = (TargetType)((targetType + 1) % TARGET_TYPE_COUNT);
        scoreMode->reset();
        save();
        return true;
    case END_SIZE_ITEM:
        endSize++;
        if (endSize > 12)
            endSize = 2;
        save();
        return true;
    case BRIGHTNESS_ITEM:
        brightnessLevel = (brightnessLevel + 1) % 3;
        M5.Display.setBrightness(getBrightness());
        save();
        return true;
    case RESET_ALL:
        counterMode->reset();
        scoreMode->reset();
        return false;
    default:
        return false;
    }
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

uint8_t SettingsMode::getBrightness() const
{
    const uint8_t levels[] = {80, 160, 255};
    return levels[brightnessLevel];
}

uint8_t SettingsMode::getDimBrightness() const
{
    const uint8_t levels[] = {1, 30, 60};
    return levels[brightnessLevel];
}