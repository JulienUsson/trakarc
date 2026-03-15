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
    virtual bool onPrimaryPress() = 0;
    virtual bool onPrimaryLongPress() = 0;
    virtual bool onSecondaryPress() = 0;
    virtual void onWakeUp() = 0;
    virtual void reset() = 0;
    virtual const char *label() = 0;
};
