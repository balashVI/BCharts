#include "label_configs.h"

#include <QFontMetrics>

LabelConfigs::LabelConfigs(QObject *parent)
    : QObject(parent),
      pVisible{true},
      pColor{"#222222"},
      pDrawBackground{true}
{
    pFont.setPointSize(9);

    QFontMetrics metrics(pFont);
    mHeight = metrics.height();
}

bool LabelConfigs::visible() const
{
    return pVisible;
}

void LabelConfigs::setVisible(bool visible)
{
    if (visible != pVisible)
    {
        pVisible = visible;
        emit visibleChanged(pVisible);
    }
}

QFont LabelConfigs::font() const
{
    return pFont;
}

void LabelConfigs::setFont(QFont f)
{
    if (f != pFont)
    {
        pFont = f;

        QFontMetrics metrics(pFont);
        mHeight = metrics.height();

        emit fontChanged(pFont);
    }
}

QColor LabelConfigs::color() const
{
    return pColor;
}

void LabelConfigs::setColor(QColor c)
{
    if (c != pColor)
    {
        pColor = c;
        emit colorChanged((pColor));
    }
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

double LabelConfigs::height() const
{
    return mHeight;
}
