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
    Color4ub transparent = {0, 0, 0, 0};

    int sumVerticesCount = 0;
    int sumIndexesCount = 0;

    int segmentsCount = Calc::segmentContInCircleSegment(radius, startAndgle, endAngle);
    int verticesCount = 2 + segmentsCount;
    sumVerticesCount += verticesCount;

    int outerIndexesCount = verticesCount + std::floor(segmentsCount / 2.0);
    sumIndexesCount += outerIndexesCount;

    int outerAntialiasedIndexesCount = 0;
    if (antialiasing)
    {
        sumVerticesCount += verticesCount;
        outerAntialiasedIndexesCount = 2 * (segmentsCount + 1) + 5;
        sumIndexesCount += outerAntialiasedIndexesCount;
    }

    // allocate memory
    mGeometry->allocate(sumVerticesCount, sumIndexesCount);

    // draw outer triangles
    SmoothVertex *vertices = reinterpret_cast<SmoothVertex *>(mGeometry->vertexData());
    vertices[0].set(center.x(), center.y(), fillColor, 0, 0);
    double step = (endAngle - startAndgle) / segmentsCount;
    for (int i = 0; i < verticesCount - 1; ++i)
    {
        double angle = startAndgle + step * i;
        double x = center.x() + radius * cos(angle);
        double y = center.y() + radius * sin(angle);

        vertices[i + 1].set(x, y, fillColor, 0, 0);
    }

    uint *indexes = mGeometry->indexDataAsUInt();
    for (int i = 0; i < outerIndexesCount; ++i)
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

    // draw outer fade triangles
    if (antialiasing)
    {
        // vertices
        double dAngle = 0.5 * (startAndgle + endAngle);
        double dx = 2 * std::cos(dAngle);
        double dy = 2 * std::sin(dAngle);

        vertices[0].dx = dx;
        vertices[0].dy = dy;
        vertices[verticesCount].set(vertices[0].x, vertices[0].y, transparent, -dx, -dy);

        for (int i = 1; i < verticesCount; ++i)
        {
            double angle = startAndgle + step * i;
            double dAngle = angle + M_PI_2 * step * i / (endAngle - startAndgle) - M_PI_4;
            double dx = std::cos(dAngle);
            double dy = std::sin(dAngle);

            vertices[i].dx = -dx;
            vertices[i].dy = -dy;
            vertices[verticesCount + i].set(vertices[i].x, vertices[i].y, transparent, dx, dy);
        }

        // indexes
        indexes[outerIndexesCount] = 0;
        indexes[outerIndexesCount + 1] = 0;
        indexes[outerIndexesCount + 2] = verticesCount;
        for (int i = 1; i < verticesCount; ++i)
        {
            indexes[outerIndexesCount + 2 * i + 1] = i;
            indexes[outerIndexesCount + 2 * i + 2] = verticesCount + i;
        }
        indexes[outerIndexesCount + 2 * verticesCount + 1] = 0;
        indexes[outerIndexesCount + 2 * verticesCount + 2] = verticesCount;
    }

    markDirty(QSGNode::DirtyGeometry);
}
