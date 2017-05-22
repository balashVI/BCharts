#include "base_grid.h"

BaseGrid::BaseGrid(QObject *parent) : QObject(parent)
{
}

void BaseGrid::setAxis(BaseAxis *axis)
{
    if (axis != mAxis)
    {
        mAxis = axis;
    }
}
