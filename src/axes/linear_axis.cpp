#include "linear_axis.h"

#include <cmath>

#include "../tools/calc.h"

LinearAxis::LinearAxis(QObject *parent)
    : BaseAxis(parent)
{
}

double LinearAxis::map(double value) const
{
    double maxMin = mMaxVisible - mMinVisible;
    return maxMin ? mSize * (value - mMinVisible) / maxMin : 0;
}

int LinearAxis::gridLinesCount() const
{
    return mGridLinesCount;
}

double LinearAxis::gridLinePosition(int i) const
{
    return mGridLinesStep * (i + 1);
}

void LinearAxis::updateGridParams()
{
    double labelHeight = 20; // TODO: get from font conf
    double maxSteps = floor(mSize / (labelHeight * 0.66));
    double minSteps = floor(mSize / labelHeight * 0.5);

    double valueRange = mMax - mMin;
    double valueStep = pow(10, Calc::calculateOrderOfMagnitude(valueRange));
    double graphMin = floor(mMin / valueStep) * valueStep;
    double graphMax = ceil(mMax / valueStep) * valueStep;
    double graphRange = graphMax - graphMin;
    int numberOfSteps = round(graphRange / valueStep);
    if (!numberOfSteps)
        numberOfSteps = 1;
    while (numberOfSteps < minSteps || numberOfSteps > maxSteps)
    {
        if (numberOfSteps < minSteps)
        {
            valueStep /= 2.0;
            numberOfSteps = round(graphRange / valueStep);
        }
        else
        {
            valueStep *= 2.0;
            numberOfSteps = round(graphRange / valueStep);
        }
    }

    mMinVisible = floor(mMin / valueStep) * valueStep;
    mMaxVisible = mMinVisible + valueStep * numberOfSteps;

    mGridLinesCount = numberOfSteps;
    mGridLinesStep = map(valueStep);
}
