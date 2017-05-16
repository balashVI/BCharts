#ifndef ABSTRACTCHART_H
#define ABSTRACTCHART_H

#include <QQuickPaintedItem>
#include <QtMath>
#include <math.h>

/**
 * @brief Базовий клас усіх графіків
 *
 * Містить властивості та фінкції властиві усім графікам
 */
class AbstractChart : public QQuickPaintedItem
{
    Q_OBJECT
public:
    ///Конструктор класу
    explicit AbstractChart(QQuickPaintedItem *parent = 0);

    virtual QVariantList generateLegend();

    void paint(QPainter *painter) override;

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

#endif // ABSTRACTCHART_H
