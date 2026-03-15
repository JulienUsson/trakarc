#pragma once

#include "mode.h"

class CounterMode;
class ScoreMode;

class SettingsMode : public Mode
{
public:
    enum TargetType
    {
        TARGET_CLASSIQUE = 0,
        TARGET_TRISPOT,
        TARGET_FIELD,
        TARGET_TYPE_COUNT
    };

    void setModes(CounterMode *counter, ScoreMode *score);
    void draw() override;
    void load() override;
    void save() override;
    bool onPrimaryPress() override;
    bool onSecondaryPress() override;
    void onEnter() override;
    void onWakeUp() override;
    const char *key() override { return "C"; }
    const char *name() const override { return "Parametres"; }
    TargetType getTargetType() const { return targetType; }
    const char *getTargetTypeLabel() const;
    unsigned int getMaxScore() const;
    unsigned int getMinScore() const;
    uint16_t getArrowColor(unsigned int score) const;
    unsigned int getEndSize() const { return endSize; }

private:
    enum MenuItem
    {
        RESET_ALL = 0,
        TARGET_TYPE_ITEM,
        END_SIZE_ITEM,
        MENU_ITEM_COUNT
    };

    MenuItem currentItem = RESET_ALL;
    TargetType targetType = TARGET_CLASSIQUE;
    unsigned int endSize = 6;
    CounterMode *counterMode = nullptr;
    ScoreMode *scoreMode = nullptr;

    static const char *getTargetTypeLabel(TargetType type);
    void drawMenuItem(int y, MenuItem item, const char *label);
};
