#ifndef PIESLICE_H
#define PIESLICE_H

#include <QQuickItem>
#include <QColor>

#include "../base/baseseries.h"

/**
 * @brief Сегмент PieChart
 *
 * Інкапсулює властивості сегмента графіка PieChart
 */
class PieSlice : public BaseSeries
{
    Q_OBJECT
public:
    ///Конструктор класу
    explicit PieSlice(QQuickItem *parent = 0);

    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);

    ///Задає числове значення сегмента
    Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged)
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

signals:
    void valueChanged();

public slots:

};

#endif // PIESLICE_H
