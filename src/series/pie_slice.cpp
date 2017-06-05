#include <cmath>

#include "../nodes/qsg_circular_segment_node.h"
#include "../tools/stroke.h"
#include "pie_slice.h"

PieSlice::PieSlice(QObject *parent)
    : BaseSeries(parent),
      pValue{0},
      pStroke{new Stroke(this)},
      mStartAngle{0},
      mEndAngle{3.14 / 2},
      mNeedGeometryUpdate{true},
      mScaleAtLastGUpdate{0}
{
    pName = "Slice";
}

double PieSlice::value() const
{
    return pValue;
}

void PieSlice::setValue(double value)
{
    if (value != pValue)
    {
        pValue = value;
        emit valueChanged();
    }
}

void PieSlice::setStartAngle(double angle)
{
    if (angle != mStartAngle)
    {
        mStartAngle = angle;
        mNeedGeometryUpdate = true;
        emit needsUpdate();
    }
}

void PieSlice::setEndAngle(double angle)
{
    if (angle != mEndAngle)
    {
        mEndAngle = angle;
        mNeedGeometryUpdate = true;
        emit needsUpdate();
    }
}

Stroke *PieSlice::stroke() const
{
    return pStroke;
}

int PieSlice::vertexCount(QRectF r)
{
    double radius = qMin(r.width(), r.height()) / 2;

    double l = 2 * M_PI * radius / ((mEndAngle - mStartAngle) / 2 * M_PI);
    int segmentsCount = ceil(l / 5.0); // 1 segment each 5 pixels

    return segmentsCount + 2;
}

QSGNode *PieSlice::updatePaintNode(QSGNode *oldNode, QRectF boundingRect)
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

    double radius = std::min(boundingRect.width(), boundingRect.height())*0.5;
    node->update(boundingRect.center(), radius, mStartAngle, mEndAngle, 0, color(), true);

    return node;
}
