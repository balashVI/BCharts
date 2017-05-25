#ifndef QSG_CIRCLE_NODE_H
#define QSG_CIRCLE_NODE_H

#include <QSGGeometryNode>
#include <QSGGeometry>
#include <QColor>

#include "smoothcolormaterial.h"

struct Color4ub
{
    unsigned char r, g, b, a;
};

inline Color4ub colorToColor4ub(const QColor &c)
{
    Color4ub color = { uchar(c.redF() * c.alphaF() * 255),
                       uchar(c.greenF() * c.alphaF() * 255),
                       uchar(c.blueF() * c.alphaF() * 255),
                       uchar(c.alphaF() * 255)
                     };
    return color;
}

struct SmoothVertex
{
    float x, y;
    Color4ub color;
    float dx, dy;
    void set(float nx, float ny, Color4ub ncolor, float ndx, float ndy)
    {
        x = nx; y = ny; color = ncolor;
        dx = ndx; dy = ndy;
    }
};



class QSGCircleNode : public QSGGeometryNode
{
public:
    QSGCircleNode(double radius, int segmentsCount, QColor color);

    void setRadius(double r);
    void setSegmentsCount(int count);
    void setColor(QColor color);

private:
    void updateGeometry();

private:
    QSGGeometry mGeometry;
    QSGSmoothColorMaterial mMaterial;
    QColor mColor;
    int mSegmentsCount;
    double mRadius;
};

#endif // QSG_CIRCLE_NODE_H
