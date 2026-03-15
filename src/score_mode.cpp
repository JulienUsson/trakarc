#include "score_mode.h"

uint16_t ScoreMode::getArrowColor(unsigned int score)
{
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
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.println("Score");

    if (arrowInProgress)
    {
        M5.Lcd.setTextColor(getArrowColor(currentArrow));
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
    if (!arrowInProgress)
    {
        currentArrow = 10;
        arrowInProgress = true;
    }
    else if (currentArrow > 0)
    {
        currentArrow--;
    }
    else
    {
        currentArrow = 10;
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
