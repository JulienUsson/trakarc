#pragma once

#include "mode.h"

class CounterMode : public Mode
{
public:
    void load() override;
    void save() override;
    void draw() override;
    bool onPrimaryPress() override;
    void reset() override;
    const char *label() override { return "A"; }

private:
    unsigned int counter = 0;
};
