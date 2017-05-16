#include "bubbleseries.h"

BubbleSeries::BubbleSeries(QQuickItem *parent):XYSeries(parent)
{

}

BubbleSeries::~BubbleSeries()
{

}

QQmlListProperty<Bubble> BubbleSeries::data()
{
    return QQmlListProperty<Bubble>(this, 0, &BubbleSeries::appendBubble, &BubbleSeries::dataListLength,
                                    &BubbleSeries::bubbleAt, 0);
}

void BubbleSeries::getDataRange(double &xLoverValue, double &xUpperValue, double &yLoverValue, double &yUpperValue, double &loverValue, double &upperValue)
{
    xLoverValue = this->xLoverValue;
    xUpperValue = this->xUpperValue;
    yUpperValue = this->yUpperValue;
    yLoverValue = this->yLoverValue;
    upperValue = this->upperValue;
    loverValue = this->loverValue;
}

void BubbleSeries::appendBubble(QQmlListProperty<Bubble> *dataList, Bubble *bubble)
{
    BubbleSeries *series = qobject_cast<BubbleSeries *>(dataList->object);
    if (series) {
        bubble->setParent(series);
        series->dataList.append(bubble);
        connect(bubble, &Bubble::xChanged, series, &BubbleSeries::calculateDataRange);
        connect(bubble, &Bubble::yChanged, series, &BubbleSeries::calculateDataRange);
        connect(bubble, &Bubble::valueChanged, series, &BubbleSeries::calculateDataRange);
        series->calculateDataRange();
        emit series->dataChanged();
    }
}

int BubbleSeries::dataListLength(QQmlListProperty<Bubble> *dataList)
{
    BubbleSeries *series = qobject_cast<BubbleSeries *>(dataList->object);
    if (series) {
        return series->dataList.length();
    } else
        return 0;
}

Bubble *BubbleSeries::bubbleAt(QQmlListProperty<Bubble> *dataList, int index)
{
    BubbleSeries *series = qobject_cast<BubbleSeries *>(dataList->object);
    if (series) {
        return series->dataList.at(index);
    } else return nullptr;
}

const QList<Bubble *> *BubbleSeries::getDataList()
{
    return &dataList;
}

void BubbleSeries::calculateDataRange()
{
    xUpperValue = std::numeric_limits<int>::min();
    xLoverValue = std::numeric_limits<int>::max();
    yUpperValue = std::numeric_limits<int>::min();
    yLoverValue = std::numeric_limits<int>::max();
    upperValue = std::numeric_limits<int>::min();
    loverValue = std::numeric_limits<int>::max();

    for(Bubble *i: dataList){
        if(i->x()>xUpperValue)
            xUpperValue = i->x();
        if(i->x()<xLoverValue)
            xLoverValue = i->x();
        if(i->y()>yUpperValue)
            yUpperValue = i->y();
        if(i->x()<yLoverValue)
            yLoverValue = i->y();
        if(i->value()>upperValue)
            upperValue = i->value();
        if(i->value()<loverValue)
            loverValue = i->value();
    }
}

