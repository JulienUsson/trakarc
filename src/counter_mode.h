#pragma once

#include "mode.h"

class CounterMode : public Mode
{
public:
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
};
