#include "baseseries.h"

BaseSeries::BaseSeries(QQuickItem *parent) :
    QQuickItem(parent),
    pName{"Series"},
    pColor{"gray"}
{
}

void BaseSeries::setColor(const QColor &value)
{
    pColor = value;
    emit colorChanged();
}

QColor BaseSeries::color() const
{
    return pColor;
}

QString BaseSeries::name() const
{
    return pName;
}

void BaseSeries::setName(const QString &value)
{
    pName=value;
    emit nameChanged();
}
