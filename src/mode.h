#pragma once

#include <M5StickCPlus2.h>

class Mode
{
public:
    virtual ~Mode() = default;
    virtual void draw() = 0;
    virtual void onPrimaryPress() = 0;
    virtual void onPrimaryLongPress() = 0;
    virtual void onSecondaryPress() = 0;
    virtual const char *label() = 0;
};
