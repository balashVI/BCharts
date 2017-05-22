#ifndef POLAR_AREA_H
#define POLAR_AREA_H

#include "base_series.h"

class BaseAxis;
class Stroke;

class PolarArea : public BaseSeries
{
    Q_OBJECT

    Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(Stroke *stroke READ stroke)

public:
    explicit PolarArea(QObject *parent = 0);

    QSGNode *updatePaintNode(QSGNode *oldNode, QRectF boundingRect, bool force = false) override;

    double value() const;
    void setValue(double value);

    void setStartAngle(double angle);
    void setEndAngle(double angle);

    Stroke *stroke() const;

    void setAxis(BaseAxis *axis);

signals:
    void valueChanged();

protected:
    double pValue;
    Stroke *pStroke;
    double mStartAngle, mEndAngle;

    bool mNeedGeometryUpdate;
    double mScaleAtLastGUpdate;

    BaseAxis *mAxis;

private:
    int vertexCount(QRectF r);
};

#endif // POLAR_AREA_H
