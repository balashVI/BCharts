#include "grid_configs.h"

GridConfigs::GridConfigs(QObject *parent)
    : QObject(parent),
      pVisible{true},
      pLineWidth{2},
      pColor{"gray"}
{
}

bool GridConfigs::visible() const
{
    return pVisible;
}

void GridConfigs::setVisible(bool visible)
{
    if (visible != pVisible)
    {
        pVisible = visible;
        emit visibleChanged(pVisible);
    }
}

uint GridConfigs::lineWidth() const
{
    return pLineWidth;
}

void GridConfigs::setLineWidth(uint width)
{
    if (width != pLineWidth)
    {
        pLineWidth = width;
        emit lineWidthChanged(pLineWidth);
    }
}

QColor GridConfigs::color() const
{
    return pColor;
}

void GridConfigs::setColor(QColor color)
{
    if (color != pColor)
    {
        pColor = color;
        emit colorChanged(pColor);
    }
}
