#include <QPainter>

#include <QSGNode>

#include "../series/pie_slice.h"
#include "pie_chart.h"

PieChart::PieChart(QQuickItem *parent)
    : BaseChart(parent),
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
    update();
}

QVariantList PieChart::generateLegend()
{
    QVariantList list;
    QVariantMap map;
    for (PieSlice *slice : slicesList)
    {
        map.clear();
        map.insert("name", slice->name());
        map.insert("color", slice->color());
        list.append(map);
    }
    return list;
}

void PieChart::appendSlice(QQmlListProperty<PieSlice> *slicesList, PieSlice *slice)
{
    PieChart *chart = qobject_cast<PieChart *>(slicesList->object);
    if (chart)
    {
        slice->setParent(chart);
        chart->slicesList.append(slice);

        connect(slice, &PieSlice::needsUpdate, chart, &PieChart::update);
        connect(slice, &PieSlice::valueChanged, chart, &PieChart::calculateDataRange);
        chart->calculateDataRange();

        chart->mForceUpdate = true;

        emit chart->slicesChanged();
    }
}

int PieChart::slicesListLength(QQmlListProperty<PieSlice> *slicesList)
{
    PieChart *chart = qobject_cast<PieChart *>(slicesList->object);
    if (chart)
        return chart->slicesList.length();
    else
        return 0;
}

PieSlice *PieChart::sliceAt(QQmlListProperty<PieSlice> *slicesList, int index)
{
    PieChart *chart = qobject_cast<PieChart *>(slicesList->object);
    if (chart)
        return chart->slicesList.at(index);
    return nullptr;
}

void PieChart::calculateDataRange()
{
    double sumValue = 0;
    for (PieSlice *i : slicesList)
    {
        sumValue += i->value();
    }

    double startAngle = 0;
    double endAngle;
    for (PieSlice *i : slicesList)
    {
        endAngle = startAngle + i->value() / sumValue * M_PI * 2;
        i->setStartAngle(startAngle);
        i->setEndAngle(endAngle);
        startAngle = endAngle;
    }
}

QSGNode *PieChart::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    auto b = boundingRect();

    QSGTransformNode *tNode = 0;

    if (!oldNode)
    {
        tNode = new QSGTransformNode;
        tNode->setFlag(QSGNode::OwnsGeometry);
    }
    else
    {
        tNode = static_cast<QSGTransformNode *>(oldNode);
    }

    // transform
    QMatrix4x4 m;
    m.translate(b.width() / 2, b.height() / 2, 1);
    double scale = qMin(b.width(), b.height()) / 2;
    m.scale(scale, scale, 1);
    tNode->setMatrix(m);
    tNode->markDirty(QSGNode::DirtyMatrix);

    // delete redundand child nodes
    int oldChildsCount = tNode->childCount();
    while (oldChildsCount > slicesList.count())
    {
        auto n = tNode->childAtIndex(0);
        tNode->removeChildNode(n);
        delete n;

        --oldChildsCount;
    }

    // update child nodes
    // TODO: improve iterating
    for (int i = 0; i != slicesList.length(); ++i)
    {
        if (i < oldChildsCount)
        {
            slicesList.at(i)->updatePaintNode(tNode->childAtIndex(i), b);
        }
        else
        {
            tNode->appendChildNode(slicesList.at(i)->updatePaintNode(nullptr, b));
        }
    }

    mForceUpdate = false;

    return tNode;
}
