#ifndef BASECHART_H
#define BASECHART_H

#include <QQuickItem>
#include <QtMath>
#include <math.h>

class BaseChart : public QQuickItem
{
    Q_OBJECT
public:
    explicit BaseChart(QQuickItem *parent = 0);

    virtual QVariantList generateLegend() = 0;

protected:
    double calculateOrderOfMagnitude(double x);
    void calculateScale(double drawingHeight, double maxSteps, double minSteps,
                        double maxValue, double minValue, int &numberOfSteps,
                        double &stepValue, double &graphMin);
    QList<QString> populateLabels(int numberOfSteps, double graphMin, double stepValue);
    double calculateOffset(double value, int steps, double stepValue, double graphMin, double scaleHop);

signals:
    void spacingChanged();
    void legendChanged();

protected slots:
    void emitLegendChanged();

protected:
    bool mForceUpdate;
};

#endif // BASECHART_H
