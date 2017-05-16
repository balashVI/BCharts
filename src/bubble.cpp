#include "bubble.h"

Bubble::Bubble(QQuickItem *parent): ChartPoint(parent), pValue{0}
{

}

Bubble::Bubble(const QVariantMap &data, QQuickItem *parent): ChartPoint(data, parent)
{
    if(data.value("value").canConvert(QMetaType::Double))
        pValue = data.value("value").toDouble();
    else
        pValue = 0;
}

Bubble::~Bubble()
{

}

double Bubble::value() const
{
    return pValue;
}

void Bubble::setValue(double value)
{
    pValue = value;
    emit valueChanged();
}

