#include "polarraxis.h"

PolarRAxis::PolarRAxis(QQuickItem *parent) :
    AbstractAxis(parent), pShowLabelsBackground{true}, pLabelsBackgroundColor{QColor("#bbffffff")}
{

}

QColor PolarRAxis::labelsBackgroundColor() const
{
    return pLabelsBackgroundColor;
}

void PolarRAxis::setLabelsBackgroundColor(QColor value)
{
    pLabelsBackgroundColor = value;
    emit labelsBackgroundColorChanged();
}

bool PolarRAxis::drawLabelsBackground() const
{
    return pShowLabelsBackground;
}

void PolarRAxis::setDrawLabelsBackground(bool value)
{
    pShowLabelsBackground = value;
    emit drawLabelsBackgroundChanged();
}
