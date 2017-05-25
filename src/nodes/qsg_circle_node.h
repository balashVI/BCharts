#ifndef QSG_CIRCLE_NODE_H
#define QSG_CIRCLE_NODE_H

#include <QSGGeometryNode>
#include <QColor>

class QSGSmoothColorMaterial;
class QSGGeometry;

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
    QSGCircleNode(double radius, int lineWidth, int segmentsCount, QColor color, double scaleFactor);

    void setRadius(double r);
    void setLineWidth(int w);
    void setSegmentsCount(int count);
    void setColor(QColor color);
    void setScaleFactor(double scale);

private:
    void updateGeometry();

private:
    QSGGeometry *mGeometry;
    QSGSmoothColorMaterial *mMaterial;
    QColor mColor;
    int mSegmentsCount;
    double mRadius;
    int mLineWidth;
    double mScaleFactor;
};

#endif // QSG_CIRCLE_NODE_H
