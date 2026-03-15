#pragma once

#include <M5StickCPlus2.h>
#include <Preferences.h>

class Mode
{
public:
    virtual ~Mode() = default;
    virtual const char *key() = 0;
    virtual const char *name() const = 0;
    virtual void draw() = 0;
    virtual void load() {}
    virtual void save() {}
    virtual bool onPrimaryPress() { return false; }
    virtual bool onPrimaryLongPress() { return false; }
    virtual bool onPrimaryHoldRepeat() { return false; }
    virtual bool onSecondaryPress() { return false; }
    virtual void onWakeUp() { onEnter(); }
    virtual void onEnter() {}
    virtual void onExit() {}
    virtual void reset() {}
    virtual unsigned long getHoldRepeatIntervalMs() { return 200; }
    virtual unsigned long getHoldThreshold() { return 400; }
};
