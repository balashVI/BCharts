#ifndef PIESLICE_H
#define PIESLICE_H

#include "../base/baseseries.h"

/**
 * @brief Сегмент PieChart
 *
 * Інкапсулює властивості сегмента графіка PieChart
 */
class PieSlice : public BaseSeries
{
    Q_OBJECT

    Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged)

public:
    ///Конструктор класу
    explicit PieSlice(QObject *parent = 0);

    QSGNode *updatePaintNode(QSGNode *oldNode, QRectF boundingRect, bool force = false) override;

    double value() const;
    void setValue(double value);

    void setStartAngle(double angle);
    void setEndAngle(double angle);

private:
    int vertexCount(QRectF r);

private:
    double pValue;
    double mStartAngle, mEndAngle;

    bool mNeedGeometryUpdate;
    double mScaleAtLastGUpdate;

signals:
    void valueChanged();

public slots:

};

#endif // PIESLICE_H
