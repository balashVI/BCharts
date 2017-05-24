#include "qsg_circle_node.h"

QSGCircleNode::QSGCircleNode(double radius, int segmentsCount, QColor color)
    : mGeometry(QSGGeometry::defaultAttributes_Point2D(), 0),
      mMaterial(),
      mSegmentsCount(segmentsCount),
      mRadius(radius)
{
    setGeometry(&mGeometry);
    mGeometry.setDrawingMode(GL_LINE_LOOP);

    mMaterial.setColor(color);
    setMaterial(&mMaterial);

    updateGeometry();
}

void QSGCircleNode::setRadius(double r)
{
    if (r != mRadius)
    {
        mRadius = r;
        updateGeometry();
    }
}

void QSGCircleNode::setSegmentsCount(int count)
{
    if (count != mSegmentsCount)
    {
        mSegmentsCount = count;
        updateGeometry();
    }
}

void QSGCircleNode::setColor(QColor color)
{
    if (color != mMaterial.color())
    {
        mMaterial.setColor(color);
        markDirty(QSGNode::DirtyMaterial);
    }
}

void QSGCircleNode::updateGeometry()
{
    mGeometry.allocate(mSegmentsCount);
    QSGGeometry::Point2D *vertices = mGeometry.vertexDataAsPoint2D();

    double step = 2 * M_PI / mSegmentsCount;
    for (int i = 0; i < mSegmentsCount; ++i)
    {
        double angle = step * i;
        double x = mRadius * cos(angle);
        double y = mRadius * sin(angle);
        vertices[i].set(x, y);
    }

    markDirty(QSGNode::DirtyGeometry);
}
