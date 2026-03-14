#pragma once

#include "mode.h"

class ScoreMode : public Mode
{
public:
    void draw() override;
    void onPrimaryPress() override;
    void onPrimaryLongPress() override;
    void onSecondaryPress() override;
    const char *label() override { return "B"; }

private:
    static unsigned int &getScore();
};
