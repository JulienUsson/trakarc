#pragma once

#include "mode.h"

class SettingsMode;

class ScoreMode : public Mode
{
public:
    void setSettingsMode(SettingsMode *settings);
    void load() override;
    void save() override;
    void draw() override;
    bool onPrimaryPress() override;
    bool onPrimaryHoldRepeat() override;
    bool onSecondaryPress() override;
    bool onSecondaryLongPress() override;
    void onEnter() override;
    void reset() override;
    const char *key() override { return "B"; }
    const char *name() const override;
    unsigned long getHoldThreshold() override { return 300; }

private:
    unsigned int totalScore = 0;
    unsigned int arrowCount = 0;
    unsigned int currentArrow = 0;
    bool arrowInProgress = false;
    SettingsMode *settingsMode = nullptr;
};
