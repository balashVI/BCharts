#ifndef LINEAR_AXIS_H
#define LINEAR_AXIS_H

#include "base_axis.h"

class LinearAxis : public BaseAxis
{
    Q_OBJECT
public:
    explicit LinearAxis(QObject *parent = 0);

    double map(double value) const override;

    int gridLinesCount() const override;
    double gridLinePosition(int i) const override;

protected:
    void updateGridParams() override;
    void populateLabels() override;

private:
    int mGridLinesCount;
    double mGridLinesStep;
    double mGridLinesValueStep;
    double mMinVisible;
    double mMaxVisible;
};

#endif // LINEAR_AXIS_H
