#ifndef PIESLICE_H
#define PIESLICE_H

#include "../base/baseseries.h"
#include "stroke.h"


class PieSlice : public BaseSeries
{
    Q_OBJECT

    Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(Stroke *stroke READ stroke)

public:
    explicit PieSlice(QObject *parent = 0);

    QSGNode *updatePaintNode(QSGNode *oldNode, QRectF boundingRect, bool force = false) override;

    double value() const;
    void setValue(double value);

    void setStartAngle(double angle);
    void setEndAngle(double angle);

    Stroke *stroke() const;

signals:
    void valueChanged();

protected:
    int vertexCount(QRectF r);

protected:
    double pValue;
    Stroke *pStroke;
    double mStartAngle, mEndAngle;

    bool mNeedGeometryUpdate;
    double mScaleAtLastGUpdate;

};

#endif // PIESLICE_H
