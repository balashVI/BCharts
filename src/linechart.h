#ifndef LINECHART_H
#define LINECHART_H

#include "barchart.h"
#include "lineseries.h"

class LineChart : public BarChart
{
    Q_OBJECT
public:
    explicit LineChart(QQuickPaintedItem *parent = 0);
    ~LineChart();

    Q_PROPERTY(QQmlListProperty<LineSeries> series READ series NOTIFY seriesChanged())
    QQmlListProperty<LineSeries> series();

    Q_INVOKABLE virtual QVariantList generateLegend() override;

protected:
    static void appendSeries(QQmlListProperty<LineSeries> *seriesList, LineSeries *series);
    static int seriesListLength(QQmlListProperty<LineSeries> *seriesList);
    static LineSeries *seriesAt(QQmlListProperty<LineSeries> *seriesList, int index);
    QList<LineSeries *> seriesList;

    void virtual paint(QPainter *painter) override;

signals:
    void seriesChanged();

protected slots:
    void calculateDataRange();
};

#endif // LINECHART_H
