#pragma once

#include "mode.h"

class ScoreMode : public Mode
{
public:
    void load() override;
    void save() override;
    void draw() override;
    bool onPrimaryPress() override;
    bool onPrimaryHoldRepeat() override;
    bool onSecondaryPress() override;
    void onEnter() override;
    void reset() override;
    const char *label() override { return "B"; }

private:
    unsigned int totalScore = 0;
    unsigned int arrowCount = 0;
    unsigned int currentArrow = 0;
    bool arrowInProgress = false;
    uint16_t getArrowColor(unsigned int score);
};
