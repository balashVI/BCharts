#ifndef BUBBLECHART_H
#define BUBBLECHART_H

#include "xychart.h"
#include "bubbleseries.h"

class BubbleChart: public XYChart
{
    Q_OBJECT
public:
    explicit BubbleChart(QQuickPaintedItem *parent =0);
    ~BubbleChart();
    Q_PROPERTY(QQmlListProperty<BubbleSeries> series READ series NOTIFY seriesChanged)
    QQmlListProperty<BubbleSeries> series();

    Q_PROPERTY(int maxBubbleRadius READ maxBubbleRadius WRITE setMaxBubbleRadius NOTIFY maxBubbleRadiusChanged)
    int maxBubbleRadius() const;
    void setMaxBubbleRadius(int value);

    Q_PROPERTY(int minBubbleRadius READ minBubbleRadius WRITE setMinBubbleRadius NOTIFY minBubbleRadiusChanged)
    int minBubbleRadius() const;
    void setMinBubbleRadius(int value);

    Q_INVOKABLE virtual QVariantList generateLegend() override;

protected:
    static void appendSeries(QQmlListProperty<BubbleSeries> *seriesList, BubbleSeries *series);
    static int seriesListLength(QQmlListProperty<BubbleSeries> *seriesList);
    static BubbleSeries *seriesAt(QQmlListProperty<BubbleSeries> *seriesList, int index);
    QList<BubbleSeries *> seriesList;

    double upperValue, loverValue;
    int pMaxBubbleRadius, pMinBubbleRadius;

    void virtual paint(QPainter *painter) override;

signals:
    void seriesChanged();
    void maxBubbleRadiusChanged();
    void minBubbleRadiusChanged();

protected slots:
    void calculateDataRange();
};

#endif // BUBBLECHART_H
