#include "qsg_circular_segment_node.h"

#include <QSGFlatColorMaterial>
#include <QSGGeometry>

#include "qsg_smooth_color_material.h"
#include "../tools/calc.h"

QSGCircularSegmentNode::QSGCircularSegmentNode()
    : mGeometry(new QSGGeometry(QSGSmoothColorMaterial::attributeSet(), 0, 0, QSGGeometry::UnsignedIntType)),
      mMaterial(new QSGSmoothColorMaterial)
{
    mGeometry->setDrawingMode(QSGGeometry::DrawTriangleStrip);
    setGeometry(mGeometry);
    setFlag(QSGNode::OwnsGeometry);

    setMaterial(mMaterial);
    setFlag(QSGNode::OwnsMaterial);
}

void QSGCircularSegmentNode::update(QPointF center, float radius, float startAndgle, float endAngle, int lineWidth, QColor color, bool antialiasing)
{
    Color4ub fillColor = colorToColor4ub(color);

    int sCount = Calc::segmentContInCircleSegment(radius, startAndgle, endAngle);
    int vCount = 2 + sCount;
    int iCount = vCount + std::floor(sCount / 2.0);

    mGeometry->allocate(vCount, iCount);
    SmoothVertex *vertices = reinterpret_cast<SmoothVertex *>(mGeometry->vertexData());

    // VERTICES
    vertices[0].set(center.x(), center.y(), fillColor, 0, 0);
    double step = (endAngle - startAndgle) / sCount;
    for (int i = 0; i < vCount; ++i)
    {
        double angle = startAndgle + step * i;
        double x = center.x() + radius * cos(angle);
        double y = center.y() + radius * sin(angle);
        vertices[i + 1].set(x, y, fillColor, 0, 0);
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
