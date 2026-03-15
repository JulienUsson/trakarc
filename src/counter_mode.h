#pragma once

#include "mode.h"

class SettingsMode;

class CounterMode : public Mode
{
public:
    void setSettingsMode(SettingsMode *settings);
    void load() override;
    void save() override;
    void draw() override;
    bool onPrimaryPress() override;
    bool onPrimaryHoldRepeat() override;
    void reset() override;
    const char *label() override { return "A"; }
    unsigned long getHoldRepeatIntervalMs() override { return 400; }

private:
    unsigned int counter = 0;
    SettingsMode *settingsMode = nullptr;
};
