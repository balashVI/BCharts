#include "polar_area_chart.h"

#include <QSGNode>

#include "../tools/label_configs.h"
#include "../tools/text_layout.h"
#include "../series/polar_area.h"
#include "../axes/linear_axis.h"
#include "../grids/polar_grid.h"

PolarAreaChart::PolarAreaChart(QQuickItem *parent)
    : BaseChart(parent),
      mAxis{new LinearAxis(this)},
      mTextLayout{new TextLayout(this)},
      mGrid{new PolarGrid(mAxis, mTextLayout, this)},
      mAngleOffset{0}
{
    mGrid->setAxis(mAxis);
    setFlag(ItemHasContents, true);

    mTextLayout->setFont(mAxis->labelConfigs()->font());
    mTextLayout->setColor(mAxis->labelConfigs()->color());
    connect(mAxis->labelConfigs(), &LabelConfigs::colorChanged, mTextLayout, &TextLayout::setColor);
    connect(mAxis->labelConfigs(), &LabelConfigs::fontChanged, mTextLayout, &TextLayout::setFont);
}

QQmlListProperty<PolarArea> PolarAreaChart::areas()
{
    return QQmlListProperty<PolarArea>(this, 0,
                                       &PolarAreaChart::appendArea,
                                       &PolarAreaChart::areasListLength,
                                       &PolarAreaChart::areaAt, 0);
}

double PolarAreaChart::angleOffset() const
{
    return mAngleOffset;
}

void PolarAreaChart::setAngleOffset(double value)
{
    mAngleOffset = value;
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
        area->setAxis(chart->mAxis);
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

void PolarAreaChart::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    if (newGeometry != oldGeometry)
    {
        mTextLayout->setHeight(newGeometry.height());
        mTextLayout->setWidth(newGeometry.width());
    }
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
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

    mAxis->setMax(max);
}

QSGNode *PolarAreaChart::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    auto b = boundingRect();
    mAxis->setSize(std::min(b.width(), b.height()) * 0.5);

    QSGNode *node = 0;
    if (!oldNode)
    {
        node = new QSGTransformNode;
    }
    else
    {
        node = static_cast<QSGTransformNode *>(oldNode);
    }

    // update grid
    int oldChildsCount = node->childCount();
    if (oldChildsCount == 0)
    {
        node->appendChildNode(mGrid->updatePaintNode(nullptr, b, mForceUpdate));
    }
    else
    {
        mGrid->updatePaintNode(node->childAtIndex(0), b, mForceUpdate);
    }

    // delete redundand child nodes
    while (oldChildsCount >= mAreasList.count())
    {
        auto n = node->childAtIndex(1);
        node->removeChildNode(n);
        delete n;

        --oldChildsCount;
    }

    // update polar areas
    // TODO: improve iterating
    for (int i = 0; i != mAreasList.length(); ++i)
    {
        if (i + 1 < oldChildsCount)
        {
            mAreasList.at(i)->updatePaintNode(node->childAtIndex(i + 1), b);
        }
        else
        {
            node->appendChildNode(mAreasList.at(i)->updatePaintNode(nullptr, b));
        }
    }

    mForceUpdate = false;

    return node;
}

BaseAxis *PolarAreaChart::axis() const
{
    return mAxis;
}
