#include "linear_axis.h"

LinearAxis::LinearAxis(QObject *parent)
    : BaseAxis(parent)
{
}

double LinearAxis::map(double value)
{
    double maxMin = mMax - mMin;
    return maxMin ? (value - mMin) / maxMin : 0;
}
