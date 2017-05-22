#ifndef LINEAR_AXIS_H
#define LINEAR_AXIS_H

#include "base_axis.h"

class LinearAxis : public BaseAxis
{
    Q_OBJECT
public:
    explicit LinearAxis(QObject *parent = 0);

    double map(double value) override;
};

#endif // LINEAR_AXIS_H