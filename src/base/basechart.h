#ifndef BASECHART_H
#define BASECHART_H

#include <QQuickItem>
#include <QtMath>
#include <math.h>

/**
 * @brief Базовий клас усіх графіків
 *
 * Містить властивості та фінкції властиві усім графікам
 */
class BaseChart : public QQuickItem
{
    Q_OBJECT
public:
    ///Конструктор класу
    explicit BaseChart(QQuickItem *parent = 0);

//    virtual QVariantList generateLegend();

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
};

#endif // BASECHART_H
