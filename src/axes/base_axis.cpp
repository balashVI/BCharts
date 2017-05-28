#include "base_axis.h"

#include "../tools/label_configs.h"
#include "../tools/grid_configs.h"

BaseAxis::BaseAxis(QObject *parent)
    : QObject(parent),
      mMin{0},
      mMax{1},
      mLabelConfigs(new LabelConfigs(this)),
      mGridConfigs(new GridConfigs(this)),
      mSize{0}
{
}

QString BaseAxis::gridLabel(int i) const
{
    i = std::min(mLabels.length() - 1, i);
    return mLabels.at(i);
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

LabelConfigs *BaseAxis::labelConfigs() const
{
    return mLabelConfigs;
}

GridConfigs *BaseAxis::gridConfigs() const
{
    return mGridConfigs;
}

void BaseAxis::setSize(double size)
{
    size -= 1;

    double gridLineWidth = 0;
    if (gridConfigs()->visible())
    {
        gridLineWidth = gridConfigs()->lineWidth();
    }

    double labelHeight = 0;
    if (labelConfigs()->visible()){
        labelHeight = labelConfigs()->height();
    }

    size -= std::max(gridLineWidth, labelHeight)*0.5;

    if (size != mSize)
    {
        mSize = size;
        updateGridParams();
    }
}
