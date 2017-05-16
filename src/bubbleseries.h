    #ifndef BUBBLESERIES_H
#define BUBBLESERIES_H

#include "xyseries.h"
#include "bubble.h"

class BubbleSeries: public XYSeries
{
    Q_OBJECT
public:
    explicit BubbleSeries(QQuickItem *parent=0);
    ~BubbleSeries();

    Q_PROPERTY(QQmlListProperty<Bubble> data READ data NOTIFY dataChanged)
    QQmlListProperty<Bubble> data();

    void getDataRange(double &xLoverValue, double &xUpperValue, double &yLoverValue, double &yUpperValue,
                      double &loverValue, double &upperValue);

    const QList<Bubble*>* getDataList();

protected:
    static void appendBubble(QQmlListProperty<Bubble> *dataList, Bubble *bubble);
    static int dataListLength(QQmlListProperty<Bubble> *dataList);
    static Bubble *bubbleAt(QQmlListProperty<Bubble> *dataList, int index);
    QList<Bubble *> dataList;
    double upperValue, loverValue;

signals:
    void dataChanged();

private slots:
    void calculateDataRange() override;
};

#endif // BUBBLESERIES_H
