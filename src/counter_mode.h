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
    bool onPrimaryLongPress() override;
    bool incrementCounter(unsigned int value);
    void reset() override;
    const char *key() override { return "A"; }
    const char *name() const override { return "Compteur"; }

private:
    unsigned int counter = 0;
    SettingsMode *settingsMode = nullptr;
};
