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

int LinearAxis::gridLinesCount() const
{
    return 3;
}

double LinearAxis::gridLinePosition(int i) const
{
    double lines[3]{0.3,0.6, 0.9};
    return lines[i];
}
