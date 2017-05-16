#include "chartpoint.h"

ChartPoint::ChartPoint(QQuickItem *parent): QQuickItem(parent), pX{0}, pY{0}
{

}

ChartPoint::ChartPoint(const QVariantMap &data, QQuickItem *parent): QQuickItem(parent)
{
    if(data.value("x").canConvert(QMetaType::Double))
        pX = data.value("x").toDouble();
    if(data.value("y").canConvert(QMetaType::Double))
        pY = data.value("y").toDouble();
}

ChartPoint::~ChartPoint()
{

}

double ChartPoint::x() const
{
    return pX;
}

void ChartPoint::setX(double value)
{
    pX = value;
    emit xChanged();
}

double ChartPoint::y() const
{
    return pY;
}

void ChartPoint::setY(double value)
{
    pY = value;
    emit yChanged();
}
