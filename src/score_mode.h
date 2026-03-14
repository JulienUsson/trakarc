#pragma once

#include "mode.h"

class ScoreMode : public Mode
{
public:
    void load() override;
    void save() override;
    void draw() override;
    void onPrimaryPress() override;
    void onPrimaryLongPress() override;
    void onSecondaryPress() override;
    void reset() override;
    const char *label() override { return "B"; }

private:
    unsigned int score = 0;
};
