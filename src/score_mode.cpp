#include "score_mode.h"

RTC_DATA_ATTR unsigned int scoreValue = 0;

unsigned int &ScoreMode::getScore()
{
    return scoreValue;
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
    M5.Lcd.println(getScore());
}

void ScoreMode::onPrimaryPress()
{
    getScore()++;
}

void ScoreMode::onPrimaryLongPress()
{
    getScore() = 0;
}

void ScoreMode::onSecondaryPress()
{
}

void ScoreMode::reset()
{
    getScore() = 0;
}
