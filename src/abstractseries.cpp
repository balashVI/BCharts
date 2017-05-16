#include "abstractseries.h"

AbstractSeries::AbstractSeries(QQuickItem *parent) :
    QQuickItem(parent), pName{"Series"}, pColor{"gray"}
{
}

void AbstractSeries::setColor(const QColor &value)
{
    pColor = value;
    emit colorChanged();
}

QColor AbstractSeries::color() const
{
    return pColor;
}

QString AbstractSeries::name() const
{
    return pName;
}

void AbstractSeries::setName(const QString &value)
{
    pName=value;
    emit nameChanged();
}
