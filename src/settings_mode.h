#pragma once

#include "mode.h"

class CounterMode;
class ScoreMode;

class SettingsMode : public Mode
{
public:
    void setModes(CounterMode *counter, ScoreMode *score);
    void draw() override;
    bool onPrimaryPress() override;
    bool onSecondaryPress() override;
    const char *label() override { return "C"; }

private:
    enum MenuItem
    {
        RESET_ALL = 0,
        MENU_ITEM_COUNT
    };

    MenuItem currentItem = RESET_ALL;
    CounterMode *counterMode = nullptr;
    ScoreMode *scoreMode = nullptr;
};
