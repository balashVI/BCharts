#include "barseries.h"

BarSeries::BarSeries(QQuickItem *parent) :
    AbstractSeries(parent), pStrokePen{new ChartPen(this)}
{
}

ChartPen *BarSeries::strokePen() const
{
    return pStrokePen;
}

void BarSeries::setStrokePen(ChartPen *value)
{
    if(value){
        pStrokePen->deleteLater();
        pStrokePen=value;
        emit strokePenChanged();
    }
}

const QList<double> &BarSeries::data() const
{
    return pData;
}

void BarSeries::setData(QList<double> value)
{
    pData = std::move(value);
    emit dataChanged();
}
