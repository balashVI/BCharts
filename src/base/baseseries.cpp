#include "baseseries.h"

BaseSeries::BaseSeries(QObject *parent) :
    QObject(parent),
    pName{"Series"},
    pColor{"gray"},
    mNeedMaterialUpdate{true}
{
}

void BaseSeries::setColor(const QColor &value)
{
    if (value != pColor) {
        pColor = value;
        mNeedMaterialUpdate = true;
        emit colorChanged();
    }
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
