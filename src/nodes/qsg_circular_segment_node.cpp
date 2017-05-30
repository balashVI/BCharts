#include "qsg_circular_segment_node.h"

#include <QSGFlatColorMaterial>
#include <QSGGeometry>

#include "qsg_smooth_color_material.h"
#include "../tools/calc.h"

QSGCircularSegmentNode::QSGCircularSegmentNode()
    : mGeometry(new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 0, 0, QSGGeometry::UnsignedIntType)),
      mMaterial(new QSGFlatColorMaterial)
{
    mGeometry->setDrawingMode(QSGGeometry::DrawTriangleStrip);
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
    int sCount = Calc::segmentContInCircleSegment(radius, startAndgle, endAngle);
    int vCount = 2 + sCount;
    int iCount = vCount + std::floor(sCount / 2.0);

    mGeometry->allocate(vCount, iCount);
    QSGGeometry::Point2D *vertices = mGeometry->vertexDataAsPoint2D();

    // VERTICES
    vertices[0].set(center.x(), center.y());
    double step = (endAngle - startAndgle) / sCount;
    for (int i = 0; i < vCount; ++i)
    {
        double angle = startAndgle + step * i;
        double x = center.x() + radius * cos(angle);
        double y = center.y() + radius * sin(angle);
        vertices[i + 1].set(x, y);
    }

    // INDEXES
    uint *indexes = mGeometry->indexDataAsUInt();
    for (int i = 0; i < iCount; ++i)
    {
        if (i % 3 == 0)
        {
            indexes[i] = 0;
        }
        else
        {
            indexes[i] = i - std::floor((double)i / 3.0);
        }
    }

    markDirty(QSGNode::DirtyGeometry);
}
