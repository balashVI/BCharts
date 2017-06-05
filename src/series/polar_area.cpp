#include "../tools/stroke.h"

#include <cmath>

#include "../nodes/qsg_circular_segment_node.h"
#include "../axes/base_axis.h"
#include "polar_area.h"

PolarArea::PolarArea(QObject *parent)
    : BaseSeries(parent),
      pValue{0},
      pStroke{new Stroke(this)},
      mStartAngle{0},
      mEndAngle{3.14 / 2}
{
}

QSGNode *PolarArea::updatePaintNode(QSGNode *oldNode, QRectF boundingRect)
{
    QSGCircularSegmentNode* node = 0;
    if (oldNode)
    {
        node = static_cast<QSGCircularSegmentNode*>(oldNode);
    }
    else
    {
        node = new QSGCircularSegmentNode;
    }

    double radius = std::max(0.0, mAxis->map(value()));
    node->update(boundingRect.center(), radius, mStartAngle, mEndAngle, 0, color(), true);

    return node;
}

double PolarArea::value() const
{
    return pValue;
}

void PolarArea::setValue(double value)
{
    if (value != pValue)
    {
        pValue = value;
        emit valueChanged();
    }
}

void PolarArea::setStartAngle(double angle)
{
    if (angle != mStartAngle)
    {
        mStartAngle = angle;
        emit needsUpdate();
    }
}

void PolarArea::setEndAngle(double angle)
{
    if (angle != mEndAngle)
    {
        mEndAngle = angle;
        emit needsUpdate();
    }
}

Stroke *PolarArea::stroke() const
{
    return pStroke;
}

void PolarArea::setAxis(BaseAxis *axis)
{
    if (axis != mAxis)
    {
        mAxis = axis;
    }
}

int PolarArea::vertexCount(QRectF r)
{
    double radius = qMin(r.width(), r.height()) / 2;

    double l = 2 * M_PI * radius / ((mEndAngle - mStartAngle) / 2 * M_PI);
    int segmentsCount = ceil(l / 5.0); // 1 segment each 5 pixels

    return segmentsCount + 2;
}
