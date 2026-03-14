#include "score_mode.h"

void ScoreMode::load()
{
    Preferences prefs;
    prefs.begin("score", true);
    score = prefs.getUInt("value", 0);
    prefs.end();
}

void ScoreMode::save()
{
    Preferences prefs;
    prefs.begin("score", false);
    prefs.putUInt("value", score);
    prefs.end();
}

void ScoreMode::draw()
{
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.println("Score");
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(5);
    M5.Lcd.setCursor(60, 50);
    M5.Lcd.println(score);
}

void ScoreMode::onPrimaryPress()
{
    score++;
    save();
}

void ScoreMode::onPrimaryLongPress()
{
    score = 0;
    save();
}

void ScoreMode::onSecondaryPress()
{
}

void ScoreMode::reset()
{
    score = 0;
    save();
}
