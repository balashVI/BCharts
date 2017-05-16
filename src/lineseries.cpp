#include "lineseries.h"

LineSeries::LineSeries(QQuickItem *parent) : BarSeries(parent), pDrawPoints{true}
{
    pStrokePen->setWidth(3);
}

bool LineSeries::drawPoints() const
{
    return pDrawPoints;
}

void LineSeries::setDrawPoints(bool value)
{
    pDrawPoints = value;
    emit drawPointsChanged();
}
