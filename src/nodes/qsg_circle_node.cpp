#include "qsg_circle_node.h"

const QSGGeometry::AttributeSet &smoothAttributeSet()
{
    static QSGGeometry::Attribute data[] = {
        QSGGeometry::Attribute::create(0, 2, GL_FLOAT, true),
        QSGGeometry::Attribute::create(1, 4, GL_UNSIGNED_BYTE, false),
        QSGGeometry::Attribute::create(2, 2, GL_FLOAT, false)
    };
    static QSGGeometry::AttributeSet attrs = { 3, sizeof(SmoothVertex), data };
    return attrs;
}

QSGCircleNode::QSGCircleNode(double radius, int segmentsCount, QColor color)
    : mGeometry(smoothAttributeSet(), 0, 0, QSGGeometry::UnsignedIntType),
      mMaterial(),
      mColor(color),
      mSegmentsCount(segmentsCount),
      mRadius(radius)
{
    setGeometry(&mGeometry);
    mGeometry.setDrawingMode(GL_TRIANGLE_STRIP);

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
    if (color != mColor)
    {
        mColor = color;
        updateGeometry();
    }
}

void QSGCircleNode::updateGeometry()
{
    mGeometry.allocate(mSegmentsCount*4, mSegmentsCount*6+6);

    SmoothVertex *smoothVertices = reinterpret_cast<SmoothVertex *>(mGeometry.vertexData());

//    float delta = lineWidth * 0.5f;

    Color4ub fillColor = colorToColor4ub(mColor);
    Color4ub transparent = {0,0,0,0};

    double step = 2 * M_PI / mSegmentsCount;
    for (int i = 0; i < mSegmentsCount; ++i)
    {
        double lineWidth = 0.02;

        double angle = step * i;
        double c = cos(angle);
        double s = sin(angle);

        double x = mRadius * c;
        double y = mRadius * s;
        double x2 = (mRadius-lineWidth) * c;
        double y2 = (mRadius-lineWidth) * s;

        double dx = x*(0.6*lineWidth/mRadius);
        double dy = y*(0.6*lineWidth/mRadius);

        smoothVertices[4*i].set(x, y, transparent, dx, dy);
        smoothVertices[4*i+1].set(x, y, fillColor, -dx,-dy);

        smoothVertices[4*i+2].set(x2, y2, fillColor, dx,dy);
        smoothVertices[4*i+3].set(x2, y2, transparent, -dx,-dy);
    }

    uint *indexes = mGeometry.indexDataAsUInt();

    for (int i = 0; i < mSegmentsCount; ++i)
    {
        indexes[2*i]=4*i;
        indexes[2*i+1]=4*i+1;

        indexes[2*mSegmentsCount+2+2*i]=4*i+1;
        indexes[2*mSegmentsCount+2+2*i+1]=4*i+2;

        indexes[4*mSegmentsCount+4+2*i]=4*i+2;
        indexes[4*mSegmentsCount+4+2*i+1]=4*i+3;
    }

    indexes[2*mSegmentsCount]=0;
    indexes[2*mSegmentsCount+1]=1;
    indexes[4*mSegmentsCount+2]=1;
    indexes[4*mSegmentsCount+3]=2;
    indexes[6*mSegmentsCount+4]=2;
    indexes[6*mSegmentsCount+5]=3;

    markDirty(QSGNode::DirtyGeometry);
}
