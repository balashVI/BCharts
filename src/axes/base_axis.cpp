#include "base_axis.h"

BaseAxis::BaseAxis(QObject *parent) : QObject(parent), mMin{0}, mMax{1}
{
}

double BaseAxis::min() const
{
    return mMin;
}

void BaseAxis::setMin(double m)
{
    if (m != mMin)
    {
        mMin = m;
        emit minChanged(mMin);
    }
}

double BaseAxis::max() const
{
    return mMax;
}

void BaseAxis::setMax(double m)
{
    if (m != mMax)
    {
        mMax = m;
        emit minChanged(mMax);
    }
}
