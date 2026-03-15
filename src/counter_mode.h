#pragma once

#include "mode.h"

class CounterMode : public Mode
{
public:
    void load() override;
    void save() override;
    void draw() override;
    bool onPrimaryPress() override;
    bool onPrimaryLongPress() override;
    bool onPrimaryHoldRepeat() override;
    bool onSecondaryPress() override;
    void onWakeUp() override;
    void onEnter() override;
    void onExit() override;
    void reset() override;
    const char *label() override { return "A"; }

private:
    unsigned int counter = 0;
};
