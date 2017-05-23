#include "polar_area_chart.h"

#include <QSGNode>

#include "../series/polar_area.h"
#include "../axes/linear_axis.h"
#include "../grids/polar_grid.h"

PolarAreaChart::PolarAreaChart(QQuickItem *parent)
    : BaseChart(parent),
      pAxis{new LinearAxis(this)},
      mGrid{new PolarGrid(this)},
      pAngleOffset{0}
{
    mGrid->setAxis(pAxis);
    setFlag(ItemHasContents, true);
}

QQmlListProperty<PolarArea> PolarAreaChart::areas()
{
    return QQmlListProperty<PolarArea>(this, 0, &PolarAreaChart::appendArea, &PolarAreaChart::areasListLength,
                                       &PolarAreaChart::areaAt, 0);
}

double PolarAreaChart::angleOffset() const
{
    return pAngleOffset;
}

void PolarAreaChart::setAngleOffset(double value)
{
    pAngleOffset = value;
    emit angleOffsetChanged();
    update();
}

QVariantList PolarAreaChart::generateLegend()
{
    QVariantList list;
    QVariantMap map;
    for (PolarArea *area : mAreasList)
    {
        map.clear();
        map.insert("name", area->name());
        map.insert("color", area->color());
        list.append(map);
    }
    return list;
}

void PolarAreaChart::appendArea(QQmlListProperty<PolarArea> *areasList, PolarArea *area)
{
    PolarAreaChart *chart = qobject_cast<PolarAreaChart *>(areasList->object);
    if (chart)
    {
        area->setParent(chart);
        area->setAxis(chart->pAxis);
        chart->mAreasList.append(area);

        connect(area, &PolarArea::needsUpdate, chart, &PolarAreaChart::update);
        connect(area, &PolarArea::valueChanged, chart, &PolarAreaChart::updateDataRange);

        chart->updateAngles();
        chart->updateDataRange();

        chart->mForceUpdate = true;

        emit chart->areasChanged();
    }
}

int PolarAreaChart::areasListLength(QQmlListProperty<PolarArea> *areasList)
{
    PolarAreaChart *chart = qobject_cast<PolarAreaChart *>(areasList->object);
    return chart ? chart->mAreasList.length() : 0;
}

PolarArea *PolarAreaChart::areaAt(QQmlListProperty<PolarArea> *areasList, int index)
{
    PolarAreaChart *chart = qobject_cast<PolarAreaChart *>(areasList->object);
    return chart ? chart->mAreasList.at(index) : nullptr;
}

void PolarAreaChart::updateAngles()
{
    auto step = M_PI * 2 / mAreasList.count();

    for (int i = 0; i != mAreasList.count(); ++i)
    {
        mAreasList[i]->setStartAngle(i * step);
        mAreasList[i]->setEndAngle((i + 1) * step);
    }
}

void PolarAreaChart::updateDataRange()
{
    double max = std::numeric_limits<double>::min();

    for (auto i : mAreasList)
    {
        if (i->value() > max)
        {
            max = i->value();
        }
    }

    pAxis->setMax(max);
}

QSGNode *PolarAreaChart::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
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

    // update grid
    int oldChildsCount = tNode->childCount();
    if (oldChildsCount == 0)
    {
        tNode->appendChildNode(mGrid->updatePaintNode(nullptr, b, mForceUpdate));
    }
    else
    {
        mGrid->updatePaintNode(tNode->childAtIndex(0), b, mForceUpdate);
    }

    //    // delete redundand child nodes

    //    while (oldChildsCount > mAreasList.count())
    //    {
    //        auto n = tNode->childAtIndex(0);
    //        tNode->removeChildNode(n);
    //        delete n;

    //        --oldChildsCount;
    //    }

    //    // update child nodes
    //    // TODO: improve iterating
    //    for (int i = 0; i != mAreasList.length(); ++i)
    //    {
    //        if (i < oldChildsCount)
    //        {
    //            mAreasList.at(i)->updatePaintNode(tNode->childAtIndex(i), b, mForceUpdate);
    //        }
    //        else
    //        {
    //            tNode->appendChildNode(mAreasList.at(i)->updatePaintNode(nullptr, b, true));
    //        }
    //    }

    mForceUpdate = false;

    return tNode;
}
