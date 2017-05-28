#include "base_grid.h"

BaseGrid::BaseGrid(BaseAxis *axis, TextLayout *textLayer, QObject *parent)
    : QObject(parent),
      mAxis{axis},
      mTextLayer{textLayer}
{
}

void BaseGrid::setAxis(BaseAxis *axis)
{
    mAxis = axis;
}
