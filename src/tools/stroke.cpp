#include "stroke.h"


Stroke::Stroke(QObject *parent)
    : QObject(parent),
      pEnable{false},
      pWidth{8},
      pColor{"white"}
{

}

bool Stroke::enable() const
{
    return pEnable;
}

void Stroke::setEnable(bool e)
{
    if (e != pEnable)
    {
        pEnable = e;
        emit enableChanged();
    }
}

uint Stroke::width() const
{
    return pWidth;
}

void Stroke::setWidth(uint w)
{
    if (w != pWidth)
    {
        pWidth = w;
        emit widthChanged();
    }
}

QColor Stroke::color() const
{
    return pColor;
}

void Stroke::setColor(QColor c)
{
    if (c != pColor)
    {
        pColor = c;
        emit colorChanged();
    }
}
