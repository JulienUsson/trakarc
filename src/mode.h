#pragma once

#include <M5StickCPlus2.h>
#include <Preferences.h>

class Mode
{
public:
    virtual ~Mode() = default;
    virtual void load() = 0;
    virtual void save() = 0;
    virtual void draw() = 0;
    virtual void onPrimaryPress() = 0;
    virtual void onPrimaryLongPress() = 0;
    virtual void onSecondaryPress() = 0;
    virtual void reset() = 0;
    virtual const char *label() = 0;
};
