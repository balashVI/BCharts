#include "piechart.h"
#include <QPainter>

PieChart::PieChart(QQuickItem *parent) :
    BaseChart(parent),
    pAngleOffset{0}
{
    setFlag(ItemHasContents, true);
}

QQmlListProperty<PieSlice> PieChart::slices()
{
    return QQmlListProperty<PieSlice>(this, 0, &PieChart::appendSlice, &PieChart::slicesListLength,
                                      &PieChart::sliceAt, 0);
}


double PieChart::angleOffset() const
{
    return pAngleOffset;
}

void PieChart::setAngleOffset(double value)
{
    pAngleOffset = value;
    emit angleOffsetChanged();
}

void PieChart::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    if (newGeometry == oldGeometry) {
        return;
    }

    for (auto s:slicesList) {
        s->setX(newGeometry.x());
        s->setY(newGeometry.y());
        s->setWidth(newGeometry.width());
        s->setHeight(newGeometry.height());
    }

    QQuickItem::geometryChanged(newGeometry, oldGeometry);
}

//QVariantList PieChart::generateLegend()
//{
//    QVariantList list;
//    QVariantMap map;
//    for(PieSlice *slice: slicesList){
//        map.clear();
//        map.insert("name", slice->name());
//        map.insert("color", slice->color());
//        list.append(map);
//    }
//    return list;
//}

void PieChart::appendSlice(QQmlListProperty<PieSlice> *slicesList, PieSlice *slice)
{
    PieChart *chart = qobject_cast<PieChart *>(slicesList->object);
    if (chart) {
        slice->setParentItem(chart);
        chart->slicesList.append(slice);
        connect(slice, SIGNAL(valueChanged()), chart, SLOT(calculateDataRange()));
        chart->calculateDataRange();

        emit chart->slicesChanged();
    }
}

int PieChart::slicesListLength(QQmlListProperty<PieSlice> *slicesList)
{
    PieChart *chart = qobject_cast<PieChart *>(slicesList->object);
    if(chart)
        return chart->slicesList.length();
    else return 0;
}

PieSlice *PieChart::sliceAt(QQmlListProperty<PieSlice> *slicesList, int index)
{
    PieChart *chart = qobject_cast<PieChart *>(slicesList->object);
    if(chart)
        return chart->slicesList.at(index);
    return nullptr;
}

/*void PieChart::paint(QPainter *painter)
{
    painter->setRenderHints(QPainter::Antialiasing, true);
    //Обчислення області для малювання
    QRectF fillRect = boundingRect();
    if(fillRect.height() > fillRect.width()){
        fillRect.setY(fillRect.y() + (fillRect.height()-fillRect.width())/2);
        fillRect.setHeight(fillRect.width());
    } else {
        fillRect.setX(fillRect.x() + (fillRect.width()-fillRect.height())/2);
        fillRect.setWidth(fillRect.height());
    }
    fillRect.adjust(pStrokePen->width(), pStrokePen->width(), -pStrokePen->width(),
                    -pStrokePen->width());

    //Малювання сегментів
    painter->setPen(pStrokePen->getPen());
    double beginAngle = pAngleOffset;
    double segmentAngle;
    for(PieSlice* i:slicesList){
        painter->setBrush(QBrush(i->color()));
        segmentAngle = 5760.0 * fabs(i->value())/sumSliceValue;
        painter->drawPie(fillRect, beginAngle, segmentAngle);
        beginAngle += segmentAngle;
    }
}*/

void PieChart::calculateDataRange()
{
    double sumValue = 0;
    for(PieSlice* i:slicesList)
    {
        sumValue += i->value();
    }

    double startAngle = 0;
    double endAngle;
    for(PieSlice* i:slicesList)
    {
        endAngle = startAngle + i->value()/sumValue*6.28;
        i->setStartAngle(startAngle);
        i->setEndAngle(endAngle);
        startAngle = endAngle;
    }
}
