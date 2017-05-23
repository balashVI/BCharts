#include "label_configs.h"

LabelConfigs::LabelConfigs(QObject *parent)
    : QObject(parent),
      pDrawBackground{true}
{
}

bool LabelConfigs::drawBackground() const
{
    return pDrawBackground;
}

void LabelConfigs::setDrawBackground(bool draw)
{
    if (draw != pDrawBackground)
    {
        pDrawBackground = draw;
        emit drawBackgroundChanged(pDrawBackground);
    }
}
