#include "score_mode.h"
#include "settings_mode.h"

void ScoreMode::setSettingsMode(SettingsMode *settings)
{
    settingsMode = settings;
}

const char *ScoreMode::name() const
{
    static String name;
    name = "Score ";
    if (settingsMode)
    {
        name += settingsMode->getTargetTypeLabel();
    }
    return name.c_str();
}

void ScoreMode::load()
{
    Preferences prefs;
    prefs.begin("score", true);
    totalScore = prefs.getUInt("total", 0);
    arrowCount = prefs.getUInt("arrows", 0);
    prefs.end();
}

void ScoreMode::save()
{
    Preferences prefs;
    prefs.begin("score", false);
    prefs.putUInt("total", totalScore);
    prefs.putUInt("arrows", arrowCount);
    prefs.end();
}

void ScoreMode::draw()
{
    M5.Lcd.println();

    if (arrowInProgress)
    {
        M5.Lcd.setTextColor(settingsMode->getArrowColor(currentArrow));
        M5.Lcd.setTextSize(3);
        M5.Lcd.setCursor(10, 40);
        M5.Lcd.print("Fleche: ");
        if (currentArrow == 0)
        {
            M5.Lcd.println("X");
        }
        else
        {
            M5.Lcd.println(currentArrow);
        }
    }

    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(10, 80);
    M5.Lcd.print("Total: ");
    M5.Lcd.println(totalScore);

    M5.Lcd.setCursor(10, 110);
    M5.Lcd.print("Fleches: ");
    M5.Lcd.println(arrowCount);
}

bool ScoreMode::onPrimaryPress()
{
    unsigned int maxScore = settingsMode->getMaxScore();
    unsigned int minScore = settingsMode->getMinScore();

    if (!arrowInProgress)
    {
        currentArrow = maxScore;
        arrowInProgress = true;
    }
    else if (currentArrow > minScore)
    {
        currentArrow--;
    }
    else if (currentArrow == minScore)
    {
        currentArrow = 0;
    }
    else
    {
        currentArrow = maxScore;
    }

    return true;
}

bool ScoreMode::onPrimaryHoldRepeat()
{
    return onPrimaryPress();
}

bool ScoreMode::onSecondaryPress()
{
    if (arrowInProgress)
    {
        totalScore += currentArrow;
        arrowCount++;
        currentArrow = 0;
        arrowInProgress = false;
        save();
        return true;
    }
    return false;
}

void ScoreMode::onEnter()
{
    currentArrow = 0;
    arrowInProgress = false;
}

void ScoreMode::reset()
{
    totalScore = 0;
    arrowCount = 0;
    currentArrow = 0;
    arrowInProgress = false;
    save();
}
