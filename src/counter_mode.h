#pragma once

#include "mode.h"

class CounterMode : public Mode
{
public:
    void draw() override;
    void onPrimaryPress() override;
    void onPrimaryLongPress() override;
    void onSecondaryPress() override;
    const char *label() override { return "A"; }

private:
    static unsigned int &getCounter();
};
