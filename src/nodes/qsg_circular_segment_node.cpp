#include "qsg_circular_segment_node.h"

#include <QSGFlatColorMaterial>
#include <QSGGeometry>
#include <cmath>

#include "qsg_smooth_color_material.h"
#include "../tools/calc.h"

QSGCircularSegmentNode::QSGCircularSegmentNode()
    : mGeometry(new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 0, 0, QSGGeometry::UnsignedIntType)),
      mMaterial(new QSGFlatColorMaterial)
{
    mGeometry->setDrawingMode(QSGGeometry::DrawTriangleFan);
    setGeometry(mGeometry);
    setFlag(QSGNode::OwnsGeometry);

    setMaterial(mMaterial);
    setFlag(QSGNode::OwnsMaterial);
}

void QSGCircularSegmentNode::update(QPointF center, float radius, float startAndgle, float endAngle, int lineWidth, QColor color, bool antialiasing)
{
    // update material
    mMaterial->setColor(color);
    markDirty(QSGNode::DirtyMaterial);

    // update points
    int vCount = Calc::vertexContInCircleSegment(radius, startAndgle, endAngle);
    mGeometry->allocate(vCount);
    QSGGeometry::Point2D *vertices = mGeometry->vertexDataAsPoint2D();

    vertices[0].set(center.x(), center.y());

    double step = (endAngle - startAndgle) / (vCount - 2);
    for (int i = 0; i < vCount - 1; ++i)
    {
        double angle = startAndgle + step * i;
        double x = center.x() + radius * cos(angle);
        double y = center.y() + radius * sin(angle);
        vertices[i + 1].set(x, y);
    }

    markDirty(QSGNode::DirtyGeometry);
}
