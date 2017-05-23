#include "base_axis.h"

#include "../tools/label_configs.h"

BaseAxis::BaseAxis(QObject *parent)
    : QObject(parent),
      mMin{0},
      mMax{1},
      mGridColor{"#000000"},
      mLabelConfigs(new LabelConfigs(this))
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

QColor BaseAxis::gridColor() const
{
    return mGridColor;
}

void BaseAxis::setGridColor(QColor color)
{
    if (color != mGridColor)
    {
        mGridColor = color;
        emit gridColorChanged(mGridColor);
    }
}

LabelConfigs *BaseAxis::labelConfigs() const
{
    return mLabelConfigs;
}
